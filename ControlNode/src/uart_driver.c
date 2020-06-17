/**
 * @file uart_driver.c
 * @author Madhumitha Tolakanahalli Pradeep
 *         Deepesh Sonigra
 * @brief Driver file for UART Tx and Tx
 * @version 0.1
 * @date 2019-04-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "uart_driver.h"
#include <errno.h>
#include <string.h>
#include "macros.h"

sem_t semTx;
sem_t semRx;

int uart_driver_open(const char *device)
{
	sem_init(&semTx, 0, 1);
	sem_init(&semRx, 0, 1);
    int fd_UART = -1;
    struct termios config;

    fd_UART = open(device, O_RDWR | O_NOCTTY | O_SYNC);

    #ifdef  DEBUG
    printf("UART open fd %d \n",fd_UART);
    #endif
    
    if(fd_UART < 0)
    {
        printf("ERROR : Could not open UART Port %s", device);
        return -1;
    }
    else
    {
        // Check if open device is a tty device
        if(!isatty(fd_UART))
        {
            printf("ERROR : Port not a serial device \n");
            return -1;
        }
        
        // Get current configuration of serial interface
        if(tcgetattr(fd_UART, &config) < 0)
        {
            printf("ERROR : Could not load configurations \n");
            return -1;
        }
        else
        {
            bzero(&config, sizeof(config)); 
            
            // Set Config Parameters
            config.c_cflag     = B115200| CS8 | CLOCAL | CREAD;
            config.c_cc[VMIN]  = sizeof(UART_RXPacket_t);
            config.c_cc[VTIME] = 1;
            
            tcflush(fd_UART, TCIFLUSH);
            tcsetattr(fd_UART, TCSANOW, &config);
           
            // Apply configuration changes
            if(tcsetattr(fd_UART, TCSANOW, &config))
            {
                printf("ERROR : Could not apply new baud rate \n");
                return UART_ERROR;
            }
        }
    }

    return fd_UART;
}

int uart_driver_close(int fd_UART)
{
    #ifdef  DEBUG
    printf("UART Close FD %d \n",fd_UART);
    #endif
    
    if(fd_UART != -1)
    {
        close(fd_UART);
        return 0;
    }
    else
    {
        printf("ERROR : Attempt to close a non-existent / already closed descriptor\n");
        return -1;
    }
}

int UART_sendChar(int fd_UART, char c)
{
   
    int temp = write(fd_UART,&c,sizeof(char));
    
#ifdef DEBUG
    printf("\tChar Sent (%c) \n",c);
#endif
    
    if(temp == -1)
        return -1;
    else
        return 0;
}

int UART_WRITE(int fd_UART, UART_TXPacket_t * packet)
{
    return(UART_sendPacket(fd_UART, (char *) packet, sizeof(UART_TXPacket_t)));
}

int UART_sendPacket(int fd_UART,char * packet, size_t packetSize)
{
    int count = -1;
    sem_wait(&semTx);
    // Check if UART interface is open
    if(fd_UART == -1)
    {
        printf("ERROR : Send Packet failed, invalid file descriptor \n");
        return -1;
    }
    else
    {
    	uint8_t i = 0;
        for (i = 0; i < packetSize; i++)
        {
        count += write(fd_UART, packet+i, 1);
        if( count == -1)
        {
           printf("ERROR : Write to file descriptor did not succeed. Failed to send Packet \n");
           return -1;
        }
#ifdef DEBUG_LEVEL2
        else
        printf("\tPacket Sent [%d] = [%d]\n", i, *(packet+i));
#endif
        }
    }
    sem_post(&semTx);

    return count;
}

char UART_readChar(int fd_UART)
{
    char c;
    if (fd_UART == -1)
    {
        printf("ERROR : Read Char failed, invalid file descriptor \n");
        return -1;
    }
    if (read(fd_UART, &c, sizeof(char)) == -1)
    {   
        printf("ERROR %s : Read operation failed \n",strerror(errno));
        return -1;
    }
    else
    {
        return c;
    }
}

int UART_READ(int fd_UART, UART_RXPacket_t * packet)
{
    return(UART_readPacket(fd_UART, (char *) packet, sizeof(UART_RXPacket_t)));
}

int  UART_readPacket(int fd_UART, char * packet, size_t packetSize)
{
#ifdef DEBUG_LEVEL2
    printf("Packet size %d\n", packetSize);
#endif

    sem_wait(&semRx);
    // Check if UART interface is open
    if (fd_UART == -1)
    {
        printf("ERROR : Read Packet failed, invalid file descriptor \n");
        return -1;
    }
    else
    {
    	uint8_t i = 0;
        for (i = 0; i < packetSize; i++)
        {
            if (read(fd_UART, packet+i, 1) == -1)
            {
                printf("ERROR : Failed to send packet. [REASON : %s] \n",strerror(errno));
                return -1;
            }
#ifdef DEBUG_LEVEL2
        else
        printf("\tPacket Received [%d] = [%d]\n", i, *(packet+i));
#endif
        }
    }
    sem_post(&semRx);
    return 0;
}

