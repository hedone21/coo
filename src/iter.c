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

#include "coo/class.h"
#include "coo/iterator.h"
#include "internals/error.h"

bool set_compare(void *this, void *compare)
{
	coo_class *clazz;

	coo_return_val_if_true(this == NULL || compare == NULL, false);

	clazz = (coo_class*)this;
	clazz->compare = compare;

	return true;
}

bool set_free(void *this, void *free)
{
	coo_class *clazz;

	coo_return_val_if_true(this == NULL || free == NULL, false);

	clazz = (coo_class*)this;
	clazz->free = free;

	return true;
}

void set_data(void *this, int data_type, int data_size)
{
	coo_class *clazz;

	coo_return_if_true(this == NULL);
	coo_return_if_true(data_type >= COO_TYPE_UNKNOWN);
	coo_return_if_true(data_size < data_size);

	clazz = (coo_class*)this;
	clazz->data_type = data_type;
	clazz->data_size  = data_size;
}
