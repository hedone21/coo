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

#ifndef COO_LIST_H
#define COO_LIST_H

#include <stdbool.h>

#include "commons.h"
#include "class.h"
#include "iterator.h"

#define COO_LIST 	"coo_list"

typedef struct coo_base_ coo_base;
typedef struct coo_list_private_ coo_list_private;

#define COO_LIST_PUBLIC 	\
		COO_CLASS_PUBLIC; 					\
		coo_iter* (*front)(void *this);				\
		coo_iter* (*back)(void *this);				\
		coo_riter* (*rfront)(void *this);			\
		coo_riter* (*rback)(void *this);			\
		void (*insert)(void *this, int pos, void *val);		\
		int (*get)(void *this, int pos, void **out);		\
		int (*remove)(void *this, void *val); 			\
		int (*replace)(void *this, int pos, void *val);		\
		bool (*erase)(void *this, int pos, void **out);		\
		bool (*erase_bt)(void *this, int from, int to); 	\
		void (*push_front)(void *this, void *val);		\
		void (*pop_front)(void *this, void **out);		\
		void (*push_back)(void *this, void *val);		\
		void (*pop_back)(void *this, void **out);		\
		int (*size)(void *this);				\
		void (*reverse)(void *this);				\
		void (*merge)(void *this, void *list);			\
		void (*sort)(void *this);				\
		void (*clear)(void *this);				\
		void (*print)(void *this, char *buf, int size);		\
		void (*debug)(void *this);				\
		bool (*is_empty)(void *this);

typedef struct coo_list_ {
	coo_base *base;
	coo_class *parent;
	COO_LIST_PUBLIC;
	coo_list_private *private;
}coo_list;

coo_list* 	coo_list_new();
coo_list* 	coo_list_init(void);

#endif
