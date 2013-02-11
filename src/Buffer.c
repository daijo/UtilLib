/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include "Buffer.h"

struct __Buffer
{
	uint32_t number_of_items;
	uint32_t start;
	uint32_t end;
	//ItemType *itemBuffer;  
};

uint32_t util_buffer_init(Buffer* buf, size_t item_size, \
	uint32_t items_in_buffer, void* item_buffer) 
{
	return 0;
} 

uint32_t util_buffer_write(Buffer *buf, void* indata, uint32_t number_items)
{
	return 0;
}

uint32_t util_buffer_read(Buffer *buf, void* outdata, uint32_t number_items)
{
	return 0;
}

void util_buffer_peek(Buffer *buf, void* outdata)
{

}

uint32_t util_buffer_left(Buffer *buf)
{
	return 0;
}

uint32_t util_buffer_used(Buffer *buf)
{
	return 0;
}

