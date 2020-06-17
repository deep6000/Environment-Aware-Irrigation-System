/**
 * @file heartbeat.h
 * @author Madhumitha Tolakanahalli Pradeep
 *         Deepesh Sonigra
 * @brief Heartbeat function sends heartbeats to Remote Node and monitors Heartbeats from remote Node
 * @version 0.1
 * @date 2019-04-21
 *
 * @copyright Copyright (c) 2019
 */

#ifndef HEARTBEAT_H_
#define HEARTBEAT_H_

#include <pthread.h>

#include "macros.h"
#include "common.h"
#include "posixtimers.h"
#include "comm_txrx.h"
#include "logger.h"
#include "gpio_interrupt.h"
#define MQ_HB  "/msgqueue_hb"

/**
 * @brief Thread handler for heartbeat task
 * 
 * @param arg 
 * @return void* 
 */
void * heartbeat_task(void * arg);

/**
 * @brief Timer handler for sending heartbeats to Remote Node
 * 
 */
void hb_task_timer_handler();

#endif /* HEARTBEAT_H_ */
