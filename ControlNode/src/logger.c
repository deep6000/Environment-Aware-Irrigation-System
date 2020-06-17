/**
 * @file logger.c
 * @author Madhumitha Tolakanahalli Pradeep
 *         Deepesh Sonigra
 * @brief Task to log data from other tasks using Mqueue
 * @version 0.1
 * @date 2019-04-21
 *
 * @copyright Copyright (c) 2019
 */

#include "logger.h"

void logger_task_timer_handler()
{
	if(kill_signal_logger)
		send_heartbeat(TID_LOGGER);
}

mqd_t log_task_mq_init()
{
    mqd_t ret_mq;
    struct mq_attr log_mqattr;
    log_mqattr.mq_msgsize = sizeof(LogPacket_t);
    log_mqattr.mq_maxmsg = 128;
    log_mqattr.mq_flags = 0;

    mq_unlink(MQ_LOG);

    ret_mq = mq_open(MQ_LOG, O_CREAT | O_RDWR, 0666, &log_mqattr);
#ifdef DEBUG
    printf("Logger Task Queue Init FD = %d\n",ret_mq);
#endif
#ifdef DEBUG
	if(ret_mq == -1)
	{
		printf("Logger Queue Init failed [%s]\n",strerror(errno));
	}
#endif
    return ret_mq;
}

int log_message(BoardID_t boardID, LogLevel_t loglevel, TID_t tid, char * format, ...)
{
	int retval = 0;
	LogPacket_t packet;
	va_list args;
	va_start(args, format);
	vsprintf(packet.data, format, args);
	va_end(args);
	packet.TID = tid;
	packet.boardID = boardID;
	packet.loglevel = loglevel;

	retval = mq_send(mq_log, (char *)&packet, sizeof(packet),0);

#ifdef DEBUG
	if(retval == -1)
	{
		printf("LOGGER MQUEUE SEND ERROR : %s \n", strerror(errno));
	}
#endif
	return retval;

}
void * logger_task(void *arg)
{
	alive_logger = 1;

	char * TIDType[4] = {" LOGGER ","   COMM   ","HEARTBEAT","   MAIN   "};

	// Start a timer for sending Heartbeats to main task
	timer_t log_timerID;

	printf("Logger Task Entered \n");

	log_message(CONTROL_NODE_ID, STATUS, TID_LOGGER, "Entered Logger Task");

	mq_log = log_task_mq_init();

	if(create_posixtimer(&log_timerID,&logger_task_timer_handler) == -1)
		printf("ERROR : Logger Timer Create Error \n");
	else
		printf("Logger Timer created ID:%p\n",log_timerID);


	if(start_posixtimer(log_timerID,4) == -1)
		printf("Logger Timer Start Error \n");
	else
		printf("Logger Timer Started ID:%p\n",log_timerID);

	char * MsgType[15] = {"ERROR   ", "DATA      ","STATUS","INFO      ","ALERT      ","HEARTBEAT", \
							"HEARTBEAT_FAIL","HEARTBEAT_BACKUP","DEGRADED_MODE_1","DEGRADED_MODE_2", "DEGRADED_MODE_3", "PREVIOUS_DATA"};
	FILE * logfptr = fopen(Filename, "w");

	getTime(logfptr);fprintf(logfptr, "[STATUS] \t Entering Logger Task \n");
	fclose(logfptr);

	LogPacket_t LogData;
	memset(&LogData, 0, SIZE_OF_LOG_PACKET);

	while(kill_signal_logger)
	{
		if(mq_receive(mq_log, (char *)&LogData, SIZE_OF_LOG_PACKET,NULL) == -1)
		{
			printf("ERROR : Message Queue Receive failed \n");
		}
		switch(LogData.boardID)
		{
			case CONTROL_NODE_ID:
				logfptr = fopen(Filename, "a");
				getTime(logfptr);
				fprintf(logfptr,"  |Control Node|\t[%s]\t[Task:%s]\t\t%s\n", \
						MsgType[LogData.loglevel],TIDType[LogData.TID], LogData.data);
				fclose(logfptr);
#ifdef DEBUG
				printf("|Control Node|\t[%s]\t[Task:%s]\t %s\n", \
						MsgType[LogData.loglevel], TIDType[LogData.TID], LogData.data);
#endif
				break;

			case REMOTE_NODE_ID :
				logfptr = fopen(Filename, "a");
				getTime(logfptr);
				fprintf(logfptr,"  <Remote Node>\t[%s]\t\t\t%s\n", \
						MsgType[LogData.loglevel], LogData.data);
				fclose(logfptr);
#ifdef DEBUG
				printf("<Remote Node>\t[%s]\t%s\n", \
						MsgType[LogData.loglevel], LogData.data);
#endif
				break;

			default :
				printf("ERROR : Packet received from Invalid ID \n");
				break;
		}
	}

	if(kill_signal_logger == 0)
	{
		logfptr = fopen(Filename, "a");
		getTime(logfptr);
		fprintf(logfptr,"  |Control Node|\t[STATUS]\t[Task:LOGGER]\tExiting...\n");
		fclose(logfptr);
	}
	if(kill_signal_hb == 0)
	{
		logfptr = fopen(Filename, "a");
		getTime(logfptr);
		fprintf(logfptr,"  |Control Node|\t[STATUS]\t[Task:HB]\tExiting...\n");
		fclose(logfptr);
	}
	if(kill_signal_comm == 0)
	{
		logfptr = fopen(Filename, "a");
		getTime(logfptr);
		fprintf(logfptr,"  |Control Node|\t[STATUS]\t[Task:COMM]\tExiting...\n");
		fclose(logfptr);
	}

	if(kill_signal_main == 0)
	{
		logfptr = fopen(Filename, "a");
		getTime(logfptr);
		fprintf(logfptr,"  |Control Node|\t[STATUS]\t EXITING PROGRAM\n");
		fclose(logfptr);
	}
	stop_posixtimer(log_timerID);
	delete_posixtimer(log_timerID);
	printf("Exiting Logger Task \n");
	alive_logger = 0;
	return 0;

}
