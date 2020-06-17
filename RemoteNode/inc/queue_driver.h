/*
 * queue_driver.h
 *
 *  Created on: Apr 17, 2019
 *      Author: deepe
 */

#ifndef INC_QUEUE_DRIVER_H_
#define INC_QUEUE_DRIVER_H_

#include "tasks_driver.h"

#define QUEUE_LENGTH_LOGGER                            ( 10 )   /* The number of items the queue can hold*/
#define QUEUE_LENGTH_TEMPERATURE                       ( 10 )   /* The number of items the queue can hold*/
#define QUEUE_LENGTH_LIGHT                             ( 10 )   /* The number of items the queue can hold*/
#define QUEUE_LENGTH_ALERT                             ( 10 )   /* The number of items the queue can hold*/
#define QUEUE_LENGTH_MOSITURE                          ( 10 )   /* The number of items the queue can hold*/
#define QUEUE_LENGTH_HEARTBEAT                         ( 30 )   /* The number of items the queue can hold*/

extern QueueHandle_t xQueue[NUM_OF_TASKS];



/**
 * @brief Create queues for all tasks
 */
void CreateQueue();


#endif /* INC_QUEUE_DRIVER_H_ */
