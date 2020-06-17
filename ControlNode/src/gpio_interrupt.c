/**
 * @file gpio_interrupt.c
 * @author Madhumitha Tolakanahalli Pradeep
 *         Deepesh Sonigra
 * @brief Functions for handling GPIO
 * @version 0.1
 * @date 2019-04-21
 *
 * @copyright Copyright (c) 2019
 */

#include "gpio_interrupt.h"


int gpio_export(unsigned int gpio)
{
    int fd, len;
    char buf[MAX_BUF];

    fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
    if (fd < 0) {
        perror("gpio/export");
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);

    return 0;
}


int gpio_set_dir(unsigned int gpio, unsigned int direction)
{
    int fd, len;
    char buf[MAX_BUF];

    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        perror("gpio/direction");
        return fd;
    }

    if (direction)
        write(fd, "out", 4);
    else
        write(fd, "in", 3);

    close(fd);
    return 0;
}

int gpio_set_edge(unsigned int gpio, char *edge)
{
    int fd,len;
    char buf[MAX_BUF];

    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        perror("gpio/set-edge");
        return fd;
    }

    write(fd, edge, strlen(edge) + 1);
    close(fd);
    return 0;
}
int gpio_fd_open(unsigned int gpio)
{
    int fd, len;
    char buf[MAX_BUF];

    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        perror("gpio/fd_open");
    }
    return fd;
}
int gpio_fd_write_on(unsigned int gpio)
{
    int fd = gpio_fd_open(gpio);
    write(fd,"1",1);
    gpio_fd_close(fd);
    return 0;
}

int gpio_fd_write_off(unsigned int gpio)
{
    int fd = gpio_fd_open(gpio);
    write(fd,"0",1);
    gpio_fd_close(fd);
    return 0;
}

int gpio_fd_close(int fd)
{
    return close(fd);
}

int gpio_init(int gpio)
{
    int gpio_fd;
    gpio_export(gpio);
    gpio_set_dir(gpio, 1);
    gpio_fd = gpio_fd_open(gpio);
    gpio_fd_write_off(gpio);
    gpio_fd_close(gpio_fd);
    return 0;
}


//test
void buzzer_gpio_init()
{
	// Buzzer Pin
	gpio_init(BUZZER_PIN);
}

void led_gpio_init()
{
	gpio_init(LED_OK_INDICATOR);
	//gpio_init(LED_NOK_INDICATOR);
}
