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

#ifndef COO_ITERATOR_H
#define COO_ITERATOR_H

#include "commons.h"

typedef struct coo_iter_ coo_iter;
typedef struct coo_riter_ coo_riter;

#define COO_ITER_MEMBERS		coo_iter *prev;				\
					coo_iter *next;				\
					void* (*get_value)(coo_iter* this);

#define COO_ITER_REVERSE_MEMBERS	coo_riter *next;			\
					coo_riter *prev;			\
					void* (*get_value)(coo_iter* this);

typedef struct coo_iter_ {
	COO_ITER_MEMBERS;
}coo_iter;

typedef struct coo_riter_ {
	COO_ITER_REVERSE_MEMBERS;
}coo_riter;

#endif
