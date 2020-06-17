/**
 * @file printtime.h
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief Function to log current time
 * @version 0.1
 * @date 2019-03-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef PRINTTIME_H_
#define PRINTTIME_H_

#include <stdio.h>
#include <sys/time.h>
#include <stddef.h>
#include <time.h>

#define USEC_TO_MSEC(x) 	(x /= (1000000))

/**
 * @brief Get the Time object
 * 
 * @param ptr 
 * @return unsigned long 
 */
void getTime(FILE * ptr);

#endif /* PRINTTIME_H_ */