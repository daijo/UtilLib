/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct __Buffer Buffer;

uint32_t util_buffer_init(Buffer* buf, size_t item_size, \
	uint32_t items_in_buffer, void* item_buffer); 

uint32_t util_buffer_write(Buffer *buf, void* indata, uint32_t number_items);

uint32_t util_buffer_read(Buffer *buf, void* outdata, uint32_t number_items);

void util_buffer_peek(Buffer *buf, void* outdata);

uint32_t util_buffer_left(Buffer *buf);

uint32_t util_buffer_used(Buffer *buf);

#endif
