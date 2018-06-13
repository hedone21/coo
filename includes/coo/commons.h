/*
* Copyright (c) 2018 Minyoung Go <hedone21@gmail.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
* OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef COO_COMMONS_H
#define COO_COMMONS_H

#include <stdlib.h>
#include <stdint.h>

#define COO_INT 	1
#define COO_LONG	1<<1
#define COO_CHAR	1<<2
#define COO_STRING	1<<3
#define COO_CUSTOM	1<<4

#define COO_COMMON_MEMBERS		coo_base base;			\
					int data_type;			\
					void (*free)(void *data);

typedef struct coo_base_ {
	int (*constructor)(void *clazz);
	int (*destructor)(void *clazz);
	const char *class_type;
}coo_base;

#endif
