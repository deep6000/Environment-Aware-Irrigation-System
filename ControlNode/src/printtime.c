/**
 * @file printtime.c
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief Function to log current time
 * @version 0.1
 * @date 2019-03-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include"printtime.h" 

void getTime(FILE * ptr)
{	
	struct timeval t;
	gettimeofday(&t,NULL);
	fprintf(ptr, "[%lu:%lu]",t.tv_sec,t.tv_usec);
}
