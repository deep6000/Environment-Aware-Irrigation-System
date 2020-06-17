/**
 * @file main.c
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief Header file for thread-keeping and monitoring
 * @version 0.1
 * @date 2019-03-26
 * 
 * @ Citation http://embedded-basics.blogspot.com/2014/11/executing-program-on-bootup.html
 * 			  https://github.com/madhumithatp/Environment-Monitoring-Device
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "main.h"


int main(int argc, char **argv)
{
	printf("Main task created\n");	

	sem_init(&semLog, 0, 1);
	signalhandlerInit(0X0F);
	
	queue_init();

    if(create_threads() == -1)
	{
		perror("Error Creating Threads, Exiting Program\n");
        exit(1);
	}
    else printf("Threads created successfully \n");
	
    buzzer_gpio_init();

    led_gpio_init();

    gpio_fd_write_on(LED_OK_INDICATOR);

    heartbeat_monitoring();

    // A flag is set when all the tasks have successfully exited and then the threads are deleted

    while(1)
    {
    	if((alive_comm == 0) && (alive_hb == 0) && (alive_logger == 0))
    	{
    		delete_threads();
    		break;
    	}
    }

    if(join_threads() == -1)
	{
#ifdef DEBUG
		printf("Error joining Threads ID\n");
#endif
	}

    gpio_fd_write_off(LED_OK_INDICATOR);
	printf("EXITING PROGRAM\n");
	exit(0);

}
