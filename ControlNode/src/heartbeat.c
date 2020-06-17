/**
 * @file heartbeat.c
 * @author Madhumitha Tolakanahalli Pradeep
 *         Deepesh Sonigra
 * @brief Heartbeat function sends heartbeats to Remote Node and monitors Heartbeats from remote Node
 * @version 0.1
 * @date 2019-04-21
 *
 * @copyright Copyright (c) 2019
 */
#include <heartbeat.h>

static int remotenode_HB = 0; //Heartbeat from Remote Node 1
static pthread_mutex_t hb_status;
mqd_t mq_hb;
timer_t hb_timerID;

void hb_task_timer_handler()
{
	UART_TXPacket_t * HBPacket = (UART_TXPacket_t *)malloc(sizeof(UART_TXPacket_t));
	memset(HBPacket, 0, SIZE_OF_TX_PACKET);
	HBPacket->loglevel = HEARTBEAT;

	pthread_mutex_lock(&hb_status);
	remotenode_HB++;
	pthread_mutex_unlock(&hb_status);

	if(kill_signal_hb)
	{
		comm_trasmit(HBPacket, fd_UART);
		//printf("--------------<3 Heartbeat to Remote Node\n");
		log_message(CONTROL_NODE_ID, HEARTBEAT, TID_HEARTBEAT, "Heartbeat to RN");

		send_heartbeat(TID_HEARTBEAT);
	}
	else
	{
		printf("Exiting Heartbeat Task \n");
		stop_posixtimer(hb_timerID);
		delete_posixtimer(hb_timerID);
	}

	if(remotenode_HB > 5)
	{
		printf("ERROR : Communication lost to Remote Node\n");
		log_message(CONTROL_NODE_ID, ERROR, TID_HEARTBEAT, "Communication lost");
		gpio_fd_write_on(BUZZER_PIN);
	}
	//else printf("HB = [%d]\n",remotenode_HB);
}

void controlNode_HeartbeatHandler()
{
	pthread_mutex_lock(&hb_status);
	remotenode_HB = 0;
	pthread_mutex_unlock(&hb_status);
}

void * heartbeat_task(void * arg)
{
	alive_hb = 1;
	printf("Heartbeat Task Entered\n");

	log_message(CONTROL_NODE_ID, STATUS, TID_HEARTBEAT, "Entered Heartbeat Task");

	if(create_posixtimer(&hb_timerID,&hb_task_timer_handler) == -1)
		printf("ERROR : Heartbeat Timer Create Error \n");
	else
		printf("Heartbeat Timer created ID:%p\n",hb_timerID);


	if(start_posixtimer(hb_timerID,5) == -1)
		printf("Heartbeat Timer Start Error \n");
	else
		printf("Heartbeat Timer Started ID:%p\n",hb_timerID);

	while(kill_signal_hb);

	printf("Exiting Heartbeat Task \n");
	stop_posixtimer(hb_timerID);
	delete_posixtimer(hb_timerID);
	alive_hb = 0;
	return 0;
}
