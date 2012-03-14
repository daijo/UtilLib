/* 0x50 0x57 0x53 
 * Copyright 2012 Patchwork Solutions AB. All rights reserved.
 * Author: Daniel Hjort
 */

#ifndef __PWSHASHFUNCTIONS_H__
#define __PWSHASHFUNCTIONS_H__

unsigned long djb2_hash(unsigned char *str);
unsigned long sdbm_hash(unsigned char *str);

#endif
