/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

unsigned long util_djb2_hash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;

	while ((c = *str++)) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return hash;
}

unsigned long util_sdbm_hash(unsigned char *str)
{
	unsigned long hash = 0;
	int c;

	while ((c = *str++)) {
		hash = c + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

