/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include <stdlib.h>
#include <stdio.h> //remove

#include "LinkedList.h"
#include "CuTest.h"

void dummyDealloc(Memory* memory)
{
}

void doubleIntFunction(Memory* data)
{
	*data= *data * 2;
}

void addIntFunction(Memory* acc, Memory* data)
{
	*acc= *acc + *data;
}

int comparePointer(void* pt1, void* pt2)
{
	int result = -1;
	if (pt1 > pt2) {
		result = 1;
	} else if (pt1 == pt2) {
		result = 0;
	}
	return result;
}

void TestLinkedListCreate(CuTest* tc)
{
	uint32_t initialAllocCount = util_total_alloc_count();

	LinkedList* list = util_linkedList();
	
	CuAssertTrue(tc, util_list_is_empty(list));
	CuAssertTrue(tc, util_list_count(list) == 0);

	util_release((Memory*)list);

	CuAssertTrue(tc, initialAllocCount == util_total_alloc_count());
}

void TestLinkedListAddFirst(CuTest* tc)
{
	uint32_t initialAllocCount = util_total_alloc_count();

	LinkedList* list = util_linkedList();

	for (int i = 1; i < 5; i++) {	

		util_list_add_first(list, util_alloc(sizeof(int), &dummyDealloc));

		CuAssertTrue(tc, !util_list_is_empty(list));
		CuAssertTrue(tc, util_list_count(list) == i);
	}

	util_release((Memory*)list);

	CuAssertTrue(tc, initialAllocCount == util_total_alloc_count());
}

void TestLinkedListAddLast(CuTest* tc)
{
	uint32_t initialAllocCount = util_total_alloc_count();

	LinkedList* list = util_linkedList();

	for (int i = 1; i < 5; i++) {	

		util_list_add_last(list, util_alloc(200, &dummyDealloc));

		CuAssertTrue(tc, !util_list_is_empty(list));
		CuAssertTrue(tc, util_list_count(list) == i);
	}

	util_release((Memory*)list);

	CuAssertTrue(tc, initialAllocCount == util_total_alloc_count());
}

void TestLinkedListAddAtIndex(CuTest* tc)
{
	uint32_t initialAllocCount = util_total_alloc_count();

	LinkedList* list = util_linkedList();
	Memory* data;

	for (int i = 1; i < 5; i++) {	

		data = util_alloc(sizeof(int), &dummyDealloc);

		*data = i;

		util_list_add_last(list, data);
	}

	data = util_alloc(sizeof(int), &dummyDealloc);

	*data = 42;

	util_list_add_at_index(list, data, 2);

	CuAssertTrue(tc, util_list_count(list) == 5);

	data = util_list_index(list, 2);

	CuAssertTrue(tc, 42 == *data);

	data = util_list_index(list, 3);

	CuAssertTrue(tc, 3 == *data);

	util_release((Memory*)list);

	CuAssertTrue(tc, initialAllocCount == util_total_alloc_count());	
}

void TestLinkedListGetFirst(CuTest* tc)
{
	uint32_t initialAllocCount = util_total_alloc_count();

	LinkedList* list = util_linkedList();
	Memory* data;

	for (int i = 1; i < 5; i++) {	

		data = util_alloc(sizeof(int), &dummyDealloc);

		*data = i;

		util_list_add_last(list, data);
	}

	data = util_list_first(list);

	CuAssertTrue(tc, 1 == *data);

	util_release((Memory*)list);

	CuAssertTrue(tc, initialAllocCount == util_total_alloc_count());
}

void TestLinkedListGetLast(CuTest* tc)
{
	uint32_t initialAllocCount = util_total_alloc_count();

	LinkedList* list = util_linkedList();
	Memory* data;

	for (int i = 1; i < 5; i++) {	

		data = util_alloc(sizeof(int), &dummyDealloc);

		*data = i;

		util_list_add_first(list, data);
	}

	data = util_list_last(list);

	CuAssertTrue(tc, 1 == *data);

	util_release((Memory*)list);

	CuAssertTrue(tc, initialAllocCount == util_total_alloc_count());
}

void TestLinkedListGetEqual(CuTest* tc)
{
	uint32_t initialAllocCount = util_total_alloc_count();

	LinkedList* list = util_linkedList();
	Memory* data;

	for (int i = 1; i < 5; i++) {	

		data = util_alloc(sizeof(int), &dummyDealloc);

		*data = i;

		util_list_add_last(list, data);
	}

	data = util_list_equal(list, data, &comparePointer);

	CuAssertTrue(tc, 4 == *data);

	util_release((Memory*)list);

	CuAssertTrue(tc, initialAllocCount == util_total_alloc_count());
}

void TestLinkedListGetByIndex(CuTest* tc)
{
	uint32_t initialAllocCount = util_total_alloc_count();

	LinkedList* list = util_linkedList();
	Memory* data;

	for (int i = 1; i < 5; i++) {	

		data = util_alloc(sizeof(int), &dummyDealloc);

		*data = i;

		util_list_add_last(list, data);
	}

	data = util_list_index(list, 2);

	CuAssertTrue(tc, 3 == *data);

	util_release((Memory*)list);

	CuAssertTrue(tc, initialAllocCount == util_total_alloc_count());
}

void TestLinkedListRemoveFirst(CuTest* tc)
{
	uint32_t initialAllocCount = util_total_alloc_count();

	LinkedList* list = util_linkedList();
	Memory* data;

	for (int i = 0; i < 5; i++) {	

		data = util_alloc(sizeof(int), &dummyDealloc);

		*data = i;

		util_list_add_last(list, data);
	}

	CuAssertTrue(tc, util_list_count(list) == 5);

	for (int i = 0; i < 5; i++) {	

		CuAssertTrue(tc, util_list_count(list) == 5 - i);

		data = util_list_remove_first(list);

		CuAssertTrue(tc, *data == i);
	}

	util_release((Memory*)list);
	util_empty_autoreleasepool();

	CuAssertTrue(tc, initialAllocCount == util_total_alloc_count());
}

void TestLinkedListRemoveLast(CuTest* tc)
{
	uint32_t initialAllocCount = util_total_alloc_count();

	LinkedList* list = util_linkedList();
	Memory* data;

	for (int i = 0; i < 5; i++) {	

		data = util_alloc(sizeof(int), &dummyDealloc);

		*data = i;

		util_list_add_first(list, data);
	}

	CuAssertTrue(tc, util_list_count(list) == 5);

	for (int i = 0; i < 5; i++) {	

		CuAssertTrue(tc, util_list_count(list) == 5 - i);

		data = util_list_remove_last(list);

		CuAssertTrue(tc, *data == i);
	}

	util_release((Memory*)list);
	util_empty_autoreleasepool();

	printf("log: %d %d", initialAllocCount,  util_total_alloc_count());

	CuAssertTrue(tc, initialAllocCount == util_total_alloc_count());
}

void TestLinkedListMap(CuTest* tc)
{
	LinkedList* list = util_linkedList();
	Memory* data;

	for (int i = 0; i < 5; i++) {	

		data = util_alloc(sizeof(int), &dummyDealloc);

		*data = i;

		util_list_add_last(list, data);
	}

	util_list_map(list, &doubleIntFunction);

	data = util_list_first(list);
	
	CuAssertTrue(tc, 0 == *data);

	data = util_list_last(list);
	
	CuAssertTrue(tc, 8 == *data);

	util_release((Memory*)list);
}

void TestLinkedListReduce(CuTest* tc)
{
	LinkedList* list = util_linkedList();
	Memory* data;

	for (int i = 0; i < 5; i++) {	

		data = util_alloc(sizeof(int), &dummyDealloc);

		*data = i;

		util_list_add_last(list, data);
	}

	Memory* acc = util_alloc(sizeof(int), &dummyDealloc);
	*acc = 0;
	
	util_list_reduce(list, &addIntFunction, acc);

	/* 0 + 0 + 1 + 2 + 3 + 4 = 10 */
	CuAssertTrue(tc, 10 == *acc);

	util_release((Memory*)list);
	util_release(acc);
}

void LinkedListGetRest(CuTest* tc)
{
	uint32_t initialAllocCount = util_total_alloc_count();

	LinkedList* list = util_linkedList();
	Memory* data;

	for (int i = 0; i < 5; i++) {	

		data = util_alloc(sizeof(int), &dummyDealloc);

		*data = i;

		util_list_add_last(list, data);
	}

	LinkedList* rest = util_list_rest(list);

	Memory* first = util_list_first(rest);
	Memory* last = util_list_last(rest);

	CuAssertTrue(tc, 1 == *first);
	CuAssertTrue(tc, 4 == *last);

	util_release((Memory*)rest);
	util_release((Memory*)list); 

	CuAssertTrue(tc, initialAllocCount == util_total_alloc_count());
}
