/**
 * @file gpio_interrupt.h
 * @author Madhumitha Tolakanahalli Pradeep
 *         Deepesh Sonigra
 * @brief Functions for handling GPIO
 * @version 0.1
 * @date 2019-04-21
 *
 * @copyright Copyright (c) 2019
 */

#ifndef GPIO_INTERRUPT_H
#define GPIO_INTERRUPT_H

#include <unistd.h>
#include <stdio.h>
#include "common.h"

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define MAX_BUF 64

#define BUZZER_PIN 			49

#define LED_OK_INDICATOR    115
#define LED_NOK_INDICATOR   121

/**
 * @brief  export gpio pin
 *
 * @param gpio
 * @return int
 */
int gpio_export(unsigned int gpio);

/**
 * @brief  set direction of gpio
 *
 * @param gpio
 * @param direction
 * @return int
 */
int gpio_set_dir(unsigned int gpio, unsigned int direction);

/**
 * @brief rising falling edge
 *
 * @param gpio
 * @param edge
 * @return int
 */

int gpio_set_edge(unsigned int gpio, char *edge);
/**
 * @brief open file descriptor
 *
 * @param gpio
 * @return int
 */
int gpio_fd_open(unsigned int gpio);

/**
 * @brief write into gpio
 *
 * @param gpio
 * @param on_off
 * @return int
 */
int gpio_fd_write_on(unsigned int gpio);

/**
 * @brief close descriptor
 *
 * @param fd
 * @return int
 */

/**
 * @brief turn off led
 *
 */
int gpio_fd_write_off(unsigned int gpio);


/**
 * @brief close file descriptor
 *
 * @param fd
 * @return int
 */

int gpio_fd_close(int fd);

/**
 * @brief Construct a new Led_Init object
 *
 */
void buzzer_gpio_init();

void led_gpio_init();

#endif
