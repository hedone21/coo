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

#include <stdio.h>
#include <coo/coo.h>



int main(void)
{
	int val = 0;
	int out;
	coo_list *list = coo_new(coo_list);

	/* Test push_front */
	list->push_front(list, val++);
	list->debug(list);

	list->push_front(list, val++);
	list->debug(list);

	list->push_front(list, val++);
	list->debug(list);

	/* Test pop_front */
	list->pop_front(list, &out);
	list->debug(list);
	printf("Out: %d\n", out);

	list->pop_front(list, &out);
	list->debug(list);
	printf("Out: %d\n", out);

	list->pop_front(list, &out);
	list->debug(list);
	printf("Out: %d\n", out);

	list->pop_front(list, &out);
	list->debug(list);
	printf("Out: %d\n", out);

	/* Test push_back */
	list->push_back(list, val++);
	list->debug(list);

	list->push_back(list, val++);
	list->debug(list);

	list->push_back(list, val++);
	list->debug(list);

	/* Test pop_back */
	list->pop_back(list, &out);
	list->debug(list);
	printf("Out: %d\n", out);

	list->pop_back(list, &out);
	list->debug(list);
	printf("Out: %d\n", out);

	list->pop_back(list, &out);
	list->debug(list);
	printf("Out: %d\n", out);

	list->pop_back(list, &out);
	list->debug(list);
	printf("Out: %d\n", out);

	/* Test clear */
	list->push_back(list, val++);
	list->debug(list);

	list->push_back(list, val++);
	list->debug(list);

	list->push_back(list, val++);
	list->debug(list);

	list->push_back(list, val++);
	list->debug(list);

	list->push_back(list, val++);
	list->debug(list);

	list->push_front(list, val++);
	list->debug(list);

	list->push_front(list, val++);
	list->debug(list);

	list->push_front(list, val++);
	list->debug(list);

	list->push_front(list, val++);
	list->debug(list);

	list->sort(list);
	list->debug(list);

	list->clear(list);
	list->debug(list);

	coo_delete(list);

	return 0;
}
