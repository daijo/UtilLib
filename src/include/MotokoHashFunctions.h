/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#ifndef __MotokoHASHFUNCTIONS_H__
#define __MotokoHASHFUNCTIONS_H__

unsigned long djb2_hash(unsigned char *str);
unsigned long sdbm_hash(unsigned char *str);

#endif
