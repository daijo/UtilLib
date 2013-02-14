/*  
 * Copyright 2013 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "MsgQueue.h"

bool util_msgqueue_init(MsgQueue* queue)
{
	queue->socket_index = 0;
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, queue->sv) == -1) {
		return false;
	}
	return true;
}

void util_msgqueue_is_child(MsgQueue* queue)
{
	queue->socket_index = 1;
}

int util_msgqueue_send(MsgQueue* queue, const char *msg_ptr, size_t msg_len)
{
	return write(queue->sv[queue->socket_index], msg_ptr, msg_len);
}

int util_msgqueue_receive(MsgQueue* queue, char *msg_ptr, size_t msg_len)
{
	return read(queue->sv[queue->socket_index], msg_ptr, msg_len);
}
