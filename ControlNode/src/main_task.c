/**
 * @file main_task.c
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief Task performs thread monitoring and thread keeping
 * @version 0.1
 * @date 2019-03-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "main_task.h"

static pthread_mutex_t hb_status;

int create_threads()
{
	int status;

	status = create_thread_logger();
	if(status)
	{
		perror("Logger Task not created Error code :");
		return -1;
	}
	status = create_thread_comm();
	if(status)
	{
		perror("Comm Task not created Error code :");
		return -1;
	}
	status = create_thread_hb();
	if(status)
	{
		perror("Heartbeat Task not created Error code :");
		return -1;
	}

	kill_signal_logger = 1;
	kill_signal_main = 1;
	kill_signal_hb = 1;
	kill_signal_comm = 1;
    return 0;
}

int create_thread_logger()
{
	return( pthread_create(&threadID[0],NULL,logger_task,NULL));
}

int create_thread_comm()
{
	return(pthread_create(&threadID[1],NULL,comm_task,NULL));
}

int create_thread_hb()
{
	return(pthread_create(&threadID[2],NULL,heartbeat_task,NULL));
}

int join_threads()
{
	int i = 0;
	for(i = 0; i < NUM_OF_THREADS; i++)
	{
		int status;
		status = pthread_join(threadID[i],NULL);
		if(status!= 0)
		{
#ifdef DEBUF
			printf("ERROR : Couldn't join thread (%d): %s",i, strerror(errno));
#endif
			return -1;
		}
	}
	return 0;
}

void delete_threads()
{
	int i = 0;
	for (i = 0; i<NUM_OF_THREADS;i++)
	if (pthread_cancel(threadID[i]) == -1)
	{
		perror("ERROR: Could not Destroy threads");
	}	
}

void queue_init()
{
	mq_log = log_task_mq_init();
	mq_main = main_task_mq_init();
}


mqd_t main_task_mq_init()
{
    mqd_t ret_mq;
    struct mq_attr main_mqattr;
    main_mqattr.mq_msgsize = SIZE_OF_HB_PACKET;
    main_mqattr.mq_maxmsg = 128;
    main_mqattr.mq_flags = 0;
    mq_unlink(MQ_HB);
    ret_mq = mq_open(MQ_HB,O_CREAT | O_RDWR, 0666, &main_mqattr);

    return ret_mq;
}

void main_task_timer_handler()
{
	static int comm_respawncount = 0, logger_respawncount = 0, hb_respawncount = 0;
	pthread_mutex_lock(&hb_status);
	logger_hb++;
#ifdef DEBUG_LEVEL2
	printf("\t(Internal Heartbeat Count) Logger = %d",logger_hb);
#endif
	pthread_mutex_unlock(&hb_status);

	pthread_mutex_lock(&hb_status);
	comm_hb++;
#ifdef DEBUG_LEVEL2
	printf("\t(Internal Heartbeat Count) Comm = %d",comm_hb);
#endif
	pthread_mutex_unlock(&hb_status);

	pthread_mutex_lock(&hb_status);
	heartbeat_hb++;
#ifdef DEBUG_LEVEL2
	printf("\t(Internal Heartbeat Count) HB = %d\n",heartbeat_hb);
#endif
	pthread_mutex_unlock(&hb_status);

	if(logger_hb > 5)
	{
		gpio_fd_write_off(LED_OK_INDICATOR);
//		g/pio_fd_write_on(LED_NOK_INDICATOR);
		printf("HEARTBEAT FAILED : Logger Task Inactive \n");
		pthread_mutex_lock(&hb_status);
		logger_hb = 0;
		pthread_mutex_unlock(&hb_status);
		log_message(CONTROL_NODE_ID, ERROR, TID_MAIN, "Logger Task Inactive");
		logger_respawncount++;
		printf("Respawn Count Logger Task : %d\n",logger_respawncount);
		log_message(CONTROL_NODE_ID, ERROR, TID_MAIN, "Respawn Count : %d",logger_respawncount);
		if(create_thread_logger() == -1) printf("ERROR : Couldnt create Logger thread\n");
	}

	if(comm_hb > 5)
	{
		gpio_fd_write_off(LED_OK_INDICATOR);
		//gpio_fd_write_on(LED_NOK_INDICATOR);
		printf("HEARTBEAT FAILED : Communication Task Inactive \n");
		pthread_mutex_lock(&hb_status);
		comm_hb = 0;
		pthread_mutex_unlock(&hb_status);
		log_message(CONTROL_NODE_ID, ERROR, TID_MAIN, "Comm Task Inactive");
		log_message(CONTROL_NODE_ID, ERROR, TID_MAIN, "Respawning Comm Task");
		comm_respawncount++;
		printf("Respawn Count Comm Task : %d\n",comm_respawncount);
		log_message(CONTROL_NODE_ID, ERROR, TID_MAIN, "Respawn Count : %d",comm_respawncount);
		if(create_thread_comm() == -1) printf("ERROR : Couldnt respawn Comm thread\n");
	}
	if(heartbeat_hb > 5)
	{
		gpio_fd_write_off(LED_OK_INDICATOR);
		//gpio_fd_write_on(LED_NOK_INDICATOR);
		printf("HEARTBEAT FAILED : Heartbeat Task Inactive \n");
		pthread_mutex_lock(&hb_status);
		heartbeat_hb = 0;
		pthread_mutex_unlock(&hb_status);
		log_message(CONTROL_NODE_ID, ERROR, TID_MAIN, "HB Task Inactive");
		log_message(CONTROL_NODE_ID, ERROR, TID_MAIN, "Respawning Heartbeat Task");
		hb_respawncount++;
		log_message(CONTROL_NODE_ID, ERROR, TID_MAIN, "Respawn Count : %d",hb_respawncount);
		printf("Respawn Count Heartbeat Task : %d\n",hb_respawncount);
		if(create_thread_hb() == -1) printf("ERROR : Couldnt respawn Heartbeat thread\n");
	}
}
void heartbeat_monitoring()
{
	timer_t main_timerID;

	if(create_posixtimer(&main_timerID,&main_task_timer_handler) == -1)
		printf("ERROR : Heartbeat Timer Create Error \n");
	else
		printf("Main Task Timer created \n");


	if(start_posixtimer(main_timerID,5) == -1)
		printf("Main Task Timer Start Error \n");
	else
		printf("Main Task Timer Started \n");

	logger_hb = 0;
	comm_hb = 0;
	heartbeat_hb = 0;

	HeartbeatPacket_t HBPacket;
	while(kill_signal_main)
	{
		if(mq_receive(mq_main, (char *)&HBPacket, SIZE_OF_HB_PACKET,NULL) == -1)
		{
			printf("ERROR : Message Queue Receive at Main task failed \n");
		}

		//printf("Received Heartbeat %u\n",HBPacket.TID);
		switch(HBPacket.TID)
		{
			case TID_LOGGER:
				//gpio_fd_write_off(LED_NOK_INDICATOR);
				gpio_fd_write_on(LED_OK_INDICATOR);
				pthread_mutex_lock(&hb_status);
				logger_hb = 0;
				pthread_mutex_unlock(&hb_status);
				log_message(CONTROL_NODE_ID, HEARTBEAT, TID_LOGGER, "\nHeartbeat Sent");
			break;
			case TID_COMM:
				//gpio_fd_write_off(LED_NOK_INDICATOR);
				gpio_fd_write_on(LED_OK_INDICATOR);
				pthread_mutex_lock(&hb_status);
				comm_hb = 0;
				pthread_mutex_unlock(&hb_status);
				log_message(CONTROL_NODE_ID, HEARTBEAT, TID_LOGGER, "\nHeartbeat Sent");
			break;
			case TID_HEARTBEAT:
				//gpio_fd_write_off(LED_NOK_INDICATOR);
				gpio_fd_write_on(LED_OK_INDICATOR);
				pthread_mutex_lock(&hb_status);
				heartbeat_hb = 0;
				pthread_mutex_unlock(&hb_status);
				log_message(CONTROL_NODE_ID, HEARTBEAT, TID_HEARTBEAT, "\nHeartbeat Sent");
			break;
		}
	}
	stop_posixtimer(main_timerID);
	delete_posixtimer(main_timerID);
	printf("Exiting main Task \n");
}
