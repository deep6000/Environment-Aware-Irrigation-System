/**
 * @file common.c
 * @author Madhumitha Tolakanahalli Pradeep
 *         Deepesh Sonigra
 * @brief Common functionalities required by other modules
 * @version 0.1
 * @date 2019-04-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "common.h"

int send_heartbeat(TID_t tid)
{
	char * TIDType[3] = {"LOGGER","COMM","HEARTBEAT"};
	HeartbeatPacket_t * HBPacket = (HeartbeatPacket_t *)malloc(SIZE_OF_HB_PACKET);
	HBPacket->TID = tid;
#ifdef DEBUG
	printf("-->[%s] Sending Heartbeat \n", TIDType[tid]);
#endif
	return (mq_send(mq_main, (char *)HBPacket, SIZE_OF_HB_PACKET,0));
}
