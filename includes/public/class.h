/* * Copyright (c) 2018 Minyoung Go <hedone21@gmail.com>
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

#ifndef COO_CLASS_H
#define COO_CLASS_H

#include "commons.h"

#define COO_CLASS			"coo_class"

#define COO_CLASS_PUBLIC		COO_ITER_INTERFACE;

typedef struct coo_base_ coo_base;
typedef struct coo_class_private_ coo_class_private;

typedef struct coo_class_ {
	/* 
	 * coo_base must be the first member of class.
	 */
	coo_base *base;
	/*
	 * coo_class is root class. Therefore, it does not have parents.
	 *
	 */
	void *parent;
	COO_CLASS_PUBLIC;
	coo_class_private *private;
}coo_class;

coo_class* 	coo_class_new(void);
coo_class*	coo_class_init(void);

#endif
