/**
 * @file signalhandler.h
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief Header file for signal handling and related functions
 * @version 0.1
 * @date 2019-03-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>

#include "common.h"

typedef enum
{
    USR1 = 0x01,
    USR2 = 0x02,
    INT  = 0x04,
    KILL = 0x08,
    ALL  = 0x0F 
    
}signal_type;


/**
 * @brief Funciton to init signal handler
 * 
 * @param mask 
 */
void signalhandlerInit(signal_type mask);

/**
 * @brief Signal handler that handles signals sent to the program
 * 
 * @param signal 
 * @return void* 
 */
void * signal_handler(int signal);

#endif
