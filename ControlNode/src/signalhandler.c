/**
 * @file signalhandler.c
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief  A handler for all the signals received during the execution of the program
 * @version 0.1
 * @date 2019-03-27 
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "signalhandler.h"

 void signalhandlerInit(signal_type mask)
{
    struct sigaction sa;
    sa.sa_sigaction = signal_handler;
    sa.sa_flags = SA_SIGINFO;

    if(mask & USR1)
    {
        if (sigaction(SIGUSR1,&sa,NULL))
         perror("ERROR : SIGUSR1 init failed \n");
    }
    if(mask & USR2)
    {
        if (sigaction(SIGUSR2,&sa,NULL))
            perror("ERROR : SIGUSR2 init failed \n");
    }
    if(mask & INT)
    {
        if (sigaction(SIGINT,&sa,NULL))
            perror("ERROR : SIGINT init failed \n");
    }
    if(mask & KILL)
    {
        if (sigaction(SIGTERM,&sa,NULL))
            perror("ERROR : SIGTERM init failed \n");
    }
}

void * signal_handler(int signal)
{
	switch (signal)
	{

		case SIGUSR1:
			printf("SIGUSR1 Signal Received\n");
			break;
		case SIGUSR2:
			printf("SIGUSR2 Signal Received\n");
			break;
		case SIGINT:
			printf("SIGINT Signal Received\n");
			break;
		case SIGTERM:
			printf("SIGTERM Signal Received\n");
			break;
		case SIGKILL:
			printf("SIGTSTP Signal Received\n");
			break;
		default:
			printf("Invalid Signal Received\n");
			break;
	}
	kill_signal_comm = 0;
	kill_signal_main = 0;
	kill_signal_hb = 0;
	kill_signal_logger = 0;

	return 0;
}
