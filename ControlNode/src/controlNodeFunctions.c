/**
 * @file controlNodeFunctions.c
 * @author Madhumitha Tolakanahalli Pradeep
 *         Deepesh Sonigra
 * @brief Functions related to feedback from Control Node
 * @version 0.1
 * @date 2019-04-21
 *
 * @copyright Copyright (c) 2019
 */

#include "controlNodeFunctions.h"

static pthread_mutex_t state;
static volatile int MotorState = MOTORSTATE_OFF;
static volatile int BuzzerState = BUZZERSTATE_OFF;

void controlNode_DataHandler(UART_TXPacket_t * TxPacket, float temperature, float light, uint32_t moisture)
{
	memset(TxPacket, 0, SIZE_OF_TX_PACKET);
	/* State Machine for the irrigation system */
	static int count_moisture_low = 0;
	static int count_moisture_high = 0;
	static int count_t_h_ok = 0;
	static int count_t_h_nok = 0;
	// When moisture is critically low, ignore Temperature, Light & Humidity and turn motor on
	if(moisture <= MOISTURE_LOW)
	{
		count_moisture_low++;
	}
	else if(moisture > MOISTURE_LOW && moisture < MOISTURE_OK)
	{
		// Conditions are ideal for irrigation
		if(((temperature > TEMPERATURE_LOW) && (temperature < TEMPERATURE_HIGH))||
			((light   >   LUX_LOW)          && (light    	< LUX_HIGH    )))
		{
//			pthread_mutex_lock(&state);
//			MotorState = MOTORSTATE_ON;
//			BuzzerState = BUZZERSTATE_OFF;
//			pthread_mutex_unlock(&state);
			count_t_h_ok++;
		}
		// Low/High Temperature or High Humidity : Not idea for irrigation, turn off motor
		else
		{
			pthread_mutex_lock(&state);
			MotorState = MOTORSTATE_OFF;
			BuzzerState = BUZZERSTATE_OFF;
			pthread_mutex_unlock(&state);
		}
	}
	// When there is too much moisture in the soil, turn off motor and send alert signal
	else if(moisture > MOISTURE_HIGH)
	{
		count_moisture_high++;
		pthread_mutex_lock(&state);
		MotorState = MOTORSTATE_OFF;
		BuzzerState = BUZZERSTATE_ON;
		pthread_mutex_unlock(&state);
	}

	if(count_moisture_low > 3)
	{
		pthread_mutex_lock(&state);
		MotorState = MOTORSTATE_ON;
		BuzzerState = BUZZERSTATE_OFF;
		pthread_mutex_unlock(&state);
		count_moisture_low = 0;
	}

	if(count_t_h_ok > 3)
	{
		pthread_mutex_lock(&state);
		MotorState = MOTORSTATE_ON;
		BuzzerState = BUZZERSTATE_OFF;
		pthread_mutex_unlock(&state);
		count_t_h_ok = 0;
	}

//	printf("Count Moisture Low = %d \n", count_moisture_low);
//	printf("Count HT OK = %d\n", count_t_h_ok);
//	printf("Count HT NOK = %d\n", count_t_h_nok);

	memset(TxPacket, 0, SIZE_OF_TX_PACKET);
	TxPacket->boardID = CONTROL_NODE_ID;
	TxPacket->loglevel = DATA;
	pthread_mutex_lock(&state);
	TxPacket->motorstate = MotorState;
	pthread_mutex_unlock(&state);
	pthread_mutex_lock(&state);
	TxPacket->buzzerstate = BuzzerState;
	pthread_mutex_unlock(&state);

}

void controlNode_PacketHandler(int fd_UART,UART_RXPacket_t * RxPacket,UART_TXPacket_t * TxPacket)
{
	switch(RxPacket->loglevel)
	{
		case HEARTBEAT :
			// Call Heartbeat Handler
#ifdef DEBUG_LEVEL2
			printf("--------------<3 Heartbeat from Remote Node  \n");
#endif
			log_message(REMOTE_NODE_ID, HEARTBEAT, TID_COMM, "\t\tHeartbeat received\n");
			gpio_fd_write_off(BUZZER_PIN);
			controlNode_HeartbeatHandler();
			break;

		case DATA :
			printf("RX Packet BoardID : %d Loglevel : %d  Temperature: %f Light : %f=Moisture : %d\n",     \
			    		RxPacket->boardID,RxPacket->loglevel,RxPacket->temperature,RxPacket->light,RxPacket->moisture);
			log_message(REMOTE_NODE_ID, DATA, TID_COMM, "\t\t\tTemperature = %f", RxPacket->temperature);
			log_message(REMOTE_NODE_ID, DATA, TID_COMM, "\t\t\tLuminosity = %f", RxPacket->light);
			log_message(REMOTE_NODE_ID, DATA, TID_COMM, "\t\t\tMoisture = %d", RxPacket->moisture);

			controlNode_DataHandler(TxPacket, RxPacket->temperature, RxPacket->light,RxPacket->moisture);

//			printf("RX Packet BoardID : %d Loglevel : %d  Buzzer: %d motor : %d LCD Data : %s\n",     \
//			 		RxPacket->boardID,RxPacket->loglevel,RxPacket->buzzerstate,RxPacket->motorstate,RxPacket->LCDData);

			if(TxPacket != NULL)
			{
#ifdef DEBUG_LEVEL2
				printf("----> Transmit PacketSize : %d\n",sizeof(UART_TXPacket_t));
				printf("TX Packet Board ID : %d LogLevel : %d Buzzer State : %d Motor State : %d LCDData : %s\n",
	    		TxPacket->boardID,TxPacket->loglevel,TxPacket->buzzerstate, TxPacket->motorstate,TxPacket->LCDData);
#endif
				log_message(CONTROL_NODE_ID, DATA, TID_COMM, "Sending Control Values");
				log_message(CONTROL_NODE_ID, DATA, TID_COMM, "Buzzer State = %d", TxPacket->buzzerstate);
				log_message(CONTROL_NODE_ID, DATA, TID_COMM, "Motor State = %d", TxPacket->motorstate);
				if(comm_trasmit(TxPacket, fd_UART) == -1)
					printf("ERROR : Could not transmit data on UART FD %d", fd_UART);
			}
			break;

			//TODO: Check which sensors have failed
		case DEGRADED_MODE_1 :
			log_message(REMOTE_NODE_ID, DEGRADED_MODE_1, TID_COMM, "RN in Degraded Mode 1");
			break;

		//TODO: Check which sensors have failed
			case DEGRADED_MODE_2 :
				log_message(REMOTE_NODE_ID, DEGRADED_MODE_2, TID_COMM, "RN in Degraded Mode 2");
				break;

		case PREVIOUS_DATA :
			printf("RX Packet BoardID : %d Loglevel : %d  Temperature: %f Light : %f=Moisture : %d\n",     \
						RxPacket->boardID,RxPacket->loglevel,RxPacket->temperature,RxPacket->light,RxPacket->moisture);
			log_message(REMOTE_NODE_ID, PREVIOUS_DATA, TID_COMM, "\t\t\tTemperature = %f", RxPacket->temperature);
			log_message(REMOTE_NODE_ID, PREVIOUS_DATA, TID_COMM, "\t\t\tLuminosity = %f", RxPacket->light);
			log_message(REMOTE_NODE_ID, PREVIOUS_DATA, TID_COMM, "\t\t\tMoisture = %d", RxPacket->moisture);

		default :
			// Log Packet
			//log_message(REMOTE_NODE_ID, RxPacket->loglevel, TID_COMM, "Invalid Packet");
			break;

	}
}

