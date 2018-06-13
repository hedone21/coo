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

#include "../includes/coo/class.h"
#include "../includes/internals/debug.h"
#include "../includes/internals/coo_internal.h"
#include "../includes/internals/error.h"

static int coo_class_constructor(void *this)
{
	coo_class *clazz;

	coo_return_val_if_true(this == NULL, -1);

	clazz = (coo_class*)this;
	clazz->data_type = COO_INT;
	clazz->free = NULL;

	return COO_OKAY;
}

static int coo_class_destructor(void *this)
{
	coo_class *clazz;

	coo_return_val_if_true(this == NULL, -1);

	clazz = (coo_class*)this;

	free(clazz);

	return COO_OKAY;
}

coo_class* coo_class_init(void)
{
	coo_class *clazz = 
		(coo_class*)malloc(sizeof(coo_class));
	if (!clazz)
		goto OOM_ERROR;

	clazz->parent = NULL;
	clazz->base.class_type = COO_CLASS;
	clazz->base.constructor = coo_class_constructor;
	clazz->base.destructor = coo_class_destructor;

	return clazz;

OOM_ERROR:
	return NULL;
}

coo_class* coo_class_new(void)
{
	coo_class *clazz = coo_class_init();
	if (!clazz)
		return NULL;

	clazz->base.constructor(clazz);

	return clazz;
}
