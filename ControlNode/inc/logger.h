/**
 * @file logger.h
 * @author Madhumitha Tolakanahalli Pradeep
 *         Deepesh Sonigra
 * @brief Task to log data from other tasks using Mqueue
 * @version 0.1
 * @date 2019-04-21
 *
 * @copyright Copyright (c) 2019
 */

#ifndef LOGGER_TASK_H_
#define LOGGER_TASK_H_

#include <mqueue.h>
#include <stdarg.h>
#include <fcntl.h>           /* For O_* constants */
#include "macros.h"
#include "common.h"
#include"printtime.h"
#include "main_task.h"

#define MQ_LOG  "/msgqueue_log"

#define Filename "/home/debian/project02/logs/log.txt"

/**
 * @brief Initialize attributes for message queue
 *
 * @return mqd_t
 */

mqd_t log_task_mq_init();

/**
 * @brief Callback for logger thread
 *
 * @return void*
 */

void * logger_task();

/**
 * @brief Function to log message from all tasks into logfile
 * 
 * @param boardID 
 * @param loglevel 
 * @param tid 
 * @param format 
 * @param ... 
 * @return int 
 */
int log_message(BoardID_t boardID, LogLevel_t loglevel, TID_t tid, char * format, ...);

/**
 * @brief Timer handler for sending Logger Task Heartbeats to main task
 * 
 */
void logger_task_timer_handler();

#endif /* LOGGER_TASK_H_ */
