/**
 * @file comm_txrx.c
 * @author Madhumitha Tolakanahalli Pradeep
 *         Deepesh Sonigra
 * @brief UART Transmit and Receive functions
 * @version 0.1
 * @date 2019-04-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "comm_txrx.h"
#include "macros.h"

const char * UARTdevice = "/dev/ttyO4";  //UART4
int fd_UART = -1;
timer_t comm_timerID;


UART_TXPacket_t * TxPacket;
UART_RXPacket_t * RxPacket;


void comm_task_timer_handler()
{
	/* Exit included in signal handler as comm_receive is blocking, comm task will not
	   terminate if signal is received. In that case, it will terminate when it tires to
	   send a heartbeat */

	if(kill_signal_comm == 0)
	{
		uart_driver_close(fd_UART);
		free(RxPacket);
		free(TxPacket);
		stop_posixtimer(comm_timerID);
		delete_posixtimer(comm_timerID);
		printf("Exiting Comm Task \n");
		alive_comm = 0;
	}
	else
		send_heartbeat(TID_COMM);

}
int comm_trasmit(UART_TXPacket_t * TxPacket, int fd_UART_Tx)
{
    
    if(fd_UART_Tx == -1)
        printf("ERROR : UART Tx fd failed \n");
    
#ifdef UART_CHAR
    char a = 'm';
    return(UART_sendChar(fd_UART_Tx, a));
#else
//    printf("TX Packet Board ID : %d LogLevel : %d Buzzer State : %d Motor State : %d LCDData : %s\n",
//        		TxPacket->boardID,TxPacket->loglevel,TxPacket->buzzerstate, TxPacket->motorstate,TxPacket->LCDData);
    return(UART_WRITE(fd_UART_Tx, TxPacket));
#endif
    
}

int comm_recv(UART_RXPacket_t * RxPacket, int fd_UART_Rx)
{
#ifdef DEBUG
	printf("----> Receive [FD = %d] PacketSize : %d\n",fd_UART_Rx,sizeof(UART_RXPacket_t));
#endif
    
    int ret_val = 0;
    if(fd_UART_Rx == -1)
        printf("ERROR : UART Rx File Descriptor failed \n");

#ifdef UART_CHAR
    char rx;
    rx = UART_readChar(fd_UART_Rx);
    printf("\tChar read (%c) \n",rx);
#else
    memset(RxPacket, 0, sizeof(UART_RXPacket_t));
    ret_val = UART_READ(fd_UART_Rx, RxPacket);
#endif
 
    return ret_val;    
}
//
void * comm_task(void *arg)
{
	alive_comm = 1;

	TxPacket = (UART_TXPacket_t *)malloc(sizeof(UART_TXPacket_t));
	RxPacket = (UART_RXPacket_t *)malloc(sizeof(UART_RXPacket_t));

    printf("Communication Task Entered \n");

    log_message(CONTROL_NODE_ID, STATUS, TID_COMM, "Entered Communication Task");

    if(create_posixtimer(&comm_timerID,&comm_task_timer_handler) == -1)
		printf("ERROR : Communication Heartbeat Timer Create Error \n");
	else
		printf("Communication Heartbeat Timer created ID:%p\n",comm_timerID);


	if(start_posixtimer(comm_timerID,6) == -1)
		printf("Communication Heartbeat Timer Start Error \n");
	else
		printf("Communication Heartbeat Timer Started ID:%p\n",comm_timerID);

    if(log_message(CONTROL_NODE_ID, STATUS, TID_COMM, "Comm Task Init\t") == -1)
    	printf("ERROR : Log Message Failed [%s] \n",strerror(errno));

    fd_UART = uart_driver_open(UARTdevice);

    while(kill_signal_comm)
    {
#ifdef LO
    	TxPacket->boardID = 1;
		TxPacket->loglevel = 1;
		TxPacket->buzzerstate = 1;
		TxPacket->motorstate = 0;
		strncpy(TxPacket->LCDData ,"Dummy",10);


		if(comm_trasmit(TxPacket, fd_UART) == -1)
			printf("ERROR : Could not transmit data on UART FD %d", fd_UART);
#endif

		if(comm_recv(RxPacket, fd_UART) == -1)
			printf("ERROR : Could not receive data on UART FD %d", fd_UART);

		controlNode_PacketHandler(fd_UART,RxPacket,TxPacket);
    }

	uart_driver_close(fd_UART);
	free(RxPacket);
	free(TxPacket);
	stop_posixtimer(comm_timerID);
	delete_posixtimer(comm_timerID);
	printf("Exiting Comm Task \n");
	alive_comm = 0;
	return 0;


}
