/*  
 * Copyright 2013 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#ifndef __MSGQUEUE_H__
#define __MSGQUEUE_H__

#include <stdbool.h>
#include <stddef.h>

typedef struct {
	int socket_index;
	int sv[2]; // the pair of socket descriptors 
} MsgQueue;

/* Initiate on application start before fork. */
bool util_msgqueue_init(MsgQueue* queue);

/* Called by the child process. */
void util_msgqueue_is_child(MsgQueue* queue);

int util_msgqueue_send(MsgQueue* queue, const char *msg_ptr, size_t msg_len);

int util_msgqueue_receive(MsgQueue* queue, char *msg_ptr, size_t msg_len);

#endif
