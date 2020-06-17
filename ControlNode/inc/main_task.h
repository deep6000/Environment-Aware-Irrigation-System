/**
 * @file main_task.h
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief Header file for thread-keeping and monitoring
 * @version 0.1
 * @date 2019-03-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef MAIN_TASK_H
#define MAIN_TASK_H


#include <pthread.h>
#include <time.h>
#include "common.h"
#include "comm_txrx.h"
#include "uart_driver.h"
#include "logger.h"
#include "heartbeat.h"
#include "posixtimers.h"
#include "gpio_interrupt.h"

#define NUM_OF_THREADS 3

pthread_t threadID[NUM_OF_THREADS];

volatile int logger_hb;
volatile int comm_hb;
volatile int heartbeat_hb;

/**
 * @brief Task for monitoring internal heartbeats from Comm, Logger & Heartbeat task
 * 
 */
void heartbeat_monitoring();

/**
 * @brief Create a threads object
 * 
 * @return int 
 */
int create_threads();

/**
 * @brief Joins threads
 * 
 * @return int 
 */
int join_threads();

/**
 * @brief Delete threads for graceful exit
 * 
 */
void delete_threads();

/**
 * @brief Master queue init function to init all the message queues in the program
 * 
 */
void queue_init();

/**
 * @brief Funtion to init main task message queue
 * 
 * @return mqd_t 
 */
mqd_t main_task_mq_init();

/**
 * @brief Create a thread logger object
 * 
 * @return int 
 */
int create_thread_logger();

/**
 * @brief Create a thread hb object
 * 
 * @return int 
 */
int create_thread_hb();

/**
 * @brief Create a thread comm object
 * 
 * @return int 
 */
int create_thread_comm();
#endif /* MAIN_TASK_H */

