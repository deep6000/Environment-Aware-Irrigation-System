/**
 * @file uart_driver.h
 * @author Madhumitha Tolakanahalli Pradeep
 *         Deepesh Sonigra
 * @brief UART Driver related structures and enums
 * @version 0.1
 * @date 2019-04-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <semaphore.h>

#include "common.h"

typedef enum 
{
    UART_ERROR = -1,
    UART_SUCCESSFUL = 0,
    
} UART_ERROR_T;


typedef enum
{
    USR1 = 0x01,
    USR2 = 0x02,
    INT  = 0x04,
    KILL = 0x08,
    ALL  = 0x0F 

} signal_type;

typedef struct 
{
    int8_t i;
    char data[10];
    
} Packet;


/**
 * @brief Function to open UART dev
 * 
 * @param device 
 * @return int 
 */
int uart_driver_open(const char * device);

/**
 * @brief Function to close UART dev
 * 
 * @param fd_UART 
 * @return int 
 */
int uart_driver_close(int fd_UART);

/**
 * @brief Function to send char over UART
 * 
 * @param fd_UART 
 * @param c 
 * @return int 
 */
int UART_sendChar(int fd_UART, char c);

/**
 * @brief Function to send Packet over UART
 * 
 * @param fd_UART 
 * @param packet 
 * @param packetSize 
 * @return int 
 */
int UART_sendPacket(int fd_UART, char * packet, size_t packetSize);

/**
 * @brief Function to read char over UART
 * 
 * @param fd_UART 
 * @return char 
 */
char UART_readChar(int fd_UART);

/**
 * @brief Function to receive Packet over UART
 * 
 * @param fd_UART 
 * @param packet 
 * @param packetSize 
 * @return int 
 */
int UART_readPacket(int fd_UART, char * packet, size_t packetSize);

/**
 * @brief Function that converts packets into a byte stream and writes data to UART
 * 
 * @param fd_UART 
 * @param packet 
 * @return int 
 */
int UART_WRITE(int fd_UART, UART_TXPacket_t * packet);

/**
 * @brief Function that converts packets into a byte stream and read data to UART
 * 
 * @param fd_UART 
 * @param packet 
 * @return int 
 */
int UART_READ(int fd_UART, UART_RXPacket_t * packet);

/**
 * @brief Thread handler for UART Task
 * 
 * @param arg 
 * @return void* 
 */
void * uart_task(void * arg);
#endif /* UART_DRIVER_H_ */
