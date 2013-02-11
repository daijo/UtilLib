/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#ifndef __HASHFUNCTIONS_H__
#define __HASHFUNCTIONS_H__

unsigned long djb2_hash(unsigned char *str);

unsigned long sdbm_hash(unsigned char *str);

#endif
