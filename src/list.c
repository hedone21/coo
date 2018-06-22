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

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include "public/class.h"
#include "public/list.h"
#include "public/iterator.h"
#include "private/coo.h"
#include "private/class.h"
#include "private/debug.h"
#include "private/error.h"
#include "private/list.h"

static int coo_list_constructor(void *this);
static int coo_list_destructor(void *this);

static void* coo_list_node_value(coo_iter *iter)
{
	coo_list_node *node;

	coo_return_val_if_true(iter == NULL, NULL);

	node = (coo_list_node*)iter;

	return node->data;
}

static coo_list_node* __coo_list_node_init(void *this, void *val)
{
	coo_list *clazz;
	coo_list_node *node;

	coo_return_val_if_true(this == NULL, NULL);

	clazz = (coo_list*)this;

	node = (coo_list_node*)malloc(sizeof(coo_list_node));
	if (!node) {
		goto OOM_ERROR;
	}
	coo_return_val_if_true(node == NULL, NULL);

	node->next = NULL;
	node->prev = NULL;
	node->value = coo_list_node_value;

	node->data = val;

	return node;

OOM_ERROR:
	if (node && node->data)
		free(node->data);
	if (node)
		free(node);

	return NULL;
}

static int __coo_get_abs(void *this, int pos)
{
	coo_list *clazz;
	int abs_pos;

	coo_return_val_if_true(this == NULL, -1);

	clazz = (coo_list*)this;

	if (pos < 0) {
		abs_pos = clazz->size(clazz) + pos + 1;
	}else {
		abs_pos = pos;
	}

	if (abs_pos > clazz->size(clazz)) {
		abs_pos = clazz->size(clazz);
	}
	
	if (abs_pos < 0) {
		abs_pos = 0;
	}

	return abs_pos;
}

static int __coo_list_node_del(void *this, coo_iter *node, void **out)
{
	coo_list *clazz;

	coo_return_val_if_true(this == NULL, -1);
	coo_return_val_if_true(node == NULL, -1);

	clazz = (coo_list*)this;

	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;

	if (clazz->private->head == node) {
		clazz->private->head = node->next;
	}

	if (out) {
		*out = node->value(node);
	}

	free(node);
	node = NULL;

	clazz->private->length -= 1;
	if (clazz->private->length < 0) {
		clazz->private->length = 0;
	}

	return 0;
}

static int __coo_list_compare(void *this, int pos, void *val)
{
	coo_list *clazz;
	void *ref_val;
	int result;
	int abs_pos;

	coo_return_val_if_true(this == NULL, -1);

	clazz = (coo_list*)this;

	abs_pos = __coo_get_abs(this, pos);

	coo_return_val_if_true(abs_pos < 0, -1);

	clazz->get(clazz, abs_pos, &ref_val);

	// FIXME this is for int val
	if (ref_val < val) {
		result = -1;
	}else if (ref_val == val) {
		result = 0;
	}else {
		result = 1;
	}

	return result;
}

static void __coo_list_swap(void *this, int l_pos, int r_pos)
{
	coo_list *clazz;
	coo_iter *iter;
	coo_list_node *l_node;
	coo_list_node *r_node;
	void *prev_l_data;

	coo_return_if_true(this == NULL || l_pos == r_pos);

	clazz = (coo_list*)this;

	clazz->get(clazz, l_pos, &prev_l_data);

	iter = clazz->front(this);

	for (int i = 0; i < clazz->size(clazz); i++) {
		if (i == l_pos) {
			l_node = (coo_list_node*)iter;
		}

		if (i == r_pos) {
			r_node = (coo_list_node*)iter;
		}

		if (i >= l_pos && i >= r_pos) {
			break;
		}

		iter = iter->next;
	}

	l_node->data = r_node->data;
	r_node->data = prev_l_data;
}

coo_iter* coo_list_front(void *this)
{
	coo_list *clazz;

	coo_return_val_if_true(this == NULL, NULL);

	clazz = (coo_list*)this;

	return clazz->private->head;
}

coo_iter* coo_list_back(void *this)
{
	coo_list *clazz;
	coo_iter *iter;

	coo_return_val_if_true(this == NULL, NULL);

	clazz = (coo_list*)this;
	iter = clazz->private->head;

	coo_return_val_if_true(iter == NULL, NULL);

	while (iter->next != NULL) {
		iter = iter->next;
	}

	return iter;
}

coo_riter* coo_list_rfront(void *this)
{
	coo_list *clazz;
	coo_iter *iter;

	coo_return_val_if_true(this == NULL, NULL);

	clazz = (coo_list*)this;
	iter = clazz->private->head;

	coo_return_val_if_true(iter == NULL, NULL);

	while (iter->next != NULL) {
		iter = iter->next;
	}

	return (coo_riter*)iter;
}

coo_riter* coo_list_rback(void *this)
{
	coo_list *clazz;

	coo_return_val_if_true(this == NULL, NULL);

	clazz = (coo_list*)this;

	return (coo_riter*)clazz->private->head;
}

static void coo_list_insert(void *this, int pos, void *val)
{
	coo_list *clazz;
	coo_list_node *node;
	coo_iter *iter;
	coo_iter *iter_next;
	int abs_pos;

	coo_return_if_true(this == NULL);

	clazz = (coo_list*)this;

	abs_pos = __coo_get_abs(this, pos);

	coo_return_if_true(abs_pos < 0);

	node = __coo_list_node_init(this, val);

	if (clazz->private->head == NULL || abs_pos == 0) {
		node->prev = NULL;
		node->next = clazz->private->head;
		if (clazz->private->head) {
			clazz->private->head->prev = (coo_iter*)node;
		}
		clazz->private->head = (coo_iter*)node;

		goto OUT;
	}

	iter = clazz->private->head;
	for (int i = 1; i < abs_pos; i++) {
		if (iter->next == NULL) {
			node->prev = iter;
			node->next = NULL;
			iter->next = (coo_iter*)node;

			goto OUT;
		}

		iter = iter->next;
	}

	iter_next = iter->next;
	if (iter->next) {
		iter_next->prev = (coo_iter*)node;
	}

	node->prev = iter;
	node->next = iter_next;
	iter->next = (coo_iter*)node;

OUT:
	clazz->private->length += 1;
	return;
}

static int coo_list_get(void *this, int pos, void **out)
{
	coo_list *clazz;
	coo_iter *iter;
	coo_list_node *node;
	int abs_pos;

	coo_return_val_if_true(this == NULL, -1);

	clazz = (coo_list*)this;

	abs_pos = __coo_get_abs(this, pos);

	coo_return_val_if_true(abs_pos < 0, -1);

	iter = clazz->private->head;

	for (int i = 0; i < abs_pos; i++) {
		if (iter == NULL) {
			return -1;
		}

		iter = iter->next;
	}

	node = (coo_list_node*)iter;

	if (out) {
		*out = node->data;
	}

	return 1;
}

static int coo_list_remove(void *this, void *val)
{
	coo_list *clazz;
	coo_iter *iter;
	coo_list_node *node;
	int deleted_nodes = 0;

	coo_return_val_if_true(this == NULL, -1);
	coo_return_val_if_true(val == NULL, -1);

	clazz = (coo_list*)this;
	iter = clazz->private->head;

	while (iter != NULL) {
		bool ret;
		ret = __coo_list_compare(clazz, iter->value(iter), val);
		if (ret) {
			__coo_list_node_del(clazz, iter, NULL);
			deleted_nodes++;
		}

		iter = iter->next;
	}

	return deleted_nodes;
}

static int coo_list_replace(void *this, int pos, void *val)
{
	coo_list *clazz;
	coo_iter *iter;
	int abs_pos;

	coo_return_val_if_true(this == NULL, -1);

	clazz = (coo_list*)this;

	abs_pos = __coo_get_abs(this, pos);
	
	coo_return_val_if_true(abs_pos < 0, -1);

	iter = clazz->private->head;

	for (int i = 0; i < abs_pos; i++) {
		coo_return_val_if_true(iter == NULL, -1);

		iter = iter->next;
	}

	((coo_list_node*)iter)->data = val;

	return true;
}

static bool coo_list_erase(void *this, int pos, void **out)
{
	coo_list *clazz;
	coo_iter *iter;
	int abs_pos;

	coo_return_val_if_true(this == NULL, false);

	clazz = (coo_list*)this;
	
	abs_pos = __coo_get_abs(this, pos);
	
	coo_return_val_if_true(abs_pos < 0, -1);

	iter = clazz->private->head;

	for (int i = 0; i < abs_pos; i++) {
		coo_return_val_if_true(iter == NULL, false);
		iter = iter->next;
	}

	__coo_list_node_del(clazz, iter, out);

	return true;
}

static bool coo_list_erase_bt(void *this, int from, int to)
{
	coo_list *clazz;
	coo_iter *iter;

	coo_return_val_if_true(this == NULL, false);

	clazz = (coo_list*)this;
	
	coo_return_val_if_true(from > clazz->size(clazz), false);
	coo_return_val_if_true(from < 0, false);
	coo_return_val_if_true(to > clazz->size(clazz), false);
	coo_return_val_if_true(to < 0, false);
	coo_return_val_if_true(from > to, false);

	iter = clazz->private->head;

	for (int i = 0; i < to; i++) {
		coo_return_val_if_true(iter == NULL, false);
		
		if (i >= from & i <= to) {
			__coo_list_node_del(clazz, iter, NULL);
		}

		iter = iter->next;
	}

	return true;
}

static void coo_list_push_front(void *this, void *val)
{
	coo_list *clazz;

	coo_return_if_true(this == NULL);

	clazz = (coo_list*)this;

	clazz->insert(this, 0, val);
}

static void coo_list_pop_front(void *this, void **out)
{
	coo_list *clazz;

	coo_return_if_true(this == NULL);

	clazz = (coo_list*)this;

	clazz->erase(this, 0, out);
}

static void coo_list_push_back(void *this, void *val)
{
	coo_list *clazz;

	coo_return_if_true(this == NULL);

	clazz = (coo_list*)this;

	clazz->insert(this, -1, val);
}

static void coo_list_pop_back(void *this, void **out)
{
	coo_list *clazz;

	coo_return_if_true(this == NULL);

	clazz = (coo_list*)this;

	clazz->erase(this, -1, out);
}

static int coo_list_size(void *this)
{
	coo_list *clazz;

	coo_return_val_if_true(this == NULL, -1);

	clazz = (coo_list*)this;

	return clazz->private->length;
}

static void coo_list_reverse(void *this)
{
	coo_list *clazz;
	void *data;
	int size;

	coo_return_if_true(this == NULL);

	clazz = (coo_list*)this;

	size = clazz->size(clazz);

	for (int i = 0; i < size; i++) {
		clazz->pop_front(clazz, &data);
		clazz->push_back(clazz, data);
	}
}

static void coo_list_merge(void *this, void *list)
{
}

static void __coo_list_quicksort(void *this, int first, int last)
{
	coo_list *clazz;
	void *pivot;

	int left_mark;
	int right_mark;
	int splitpoint;

	void* left_val = 0;
	void* right_val = 0;

	coo_return_if_true(first >= last);

	clazz = (coo_list*)this;

	clazz->get(clazz, last, &pivot);
	left_mark = first;
	right_mark = last;
	splitpoint = left_mark;

	while (left_mark < right_mark) {
		// FIXME
		while (left_mark < right_mark) {
			clazz->get(clazz, left_mark, &left_val);

			if (left_val > pivot) {
				break;
			}

			left_mark += 1;
		}

		while (right_mark > left_mark) {
			clazz->get(clazz, right_mark, &right_val);

			if (right_val < pivot) {
				break;
			}

			right_mark -= 1;
		}

		if (left_mark >= right_mark) {
			splitpoint = left_mark;

			clazz->insert(this, splitpoint, pivot);
			clazz->erase(this, last + 1, NULL);
			break;
		}else if (left_val > right_val) {
			__coo_list_swap(this, left_mark, right_mark);
		}
	}

	__coo_list_quicksort(this, first, splitpoint - 1);	
	__coo_list_quicksort(this, splitpoint + 1, last);
}

static void coo_list_sort(void *this)
{
	coo_list *clazz;
	int first, last;

	coo_return_if_true(this == NULL);

	clazz = (coo_list*)this;

	coo_return_if_true(clazz->private->head == NULL);

	first = 0;
	last = clazz->size(clazz) - 1;

	__coo_list_quicksort(this, first, last);
}

static void coo_list_clear(void *this)
{
	coo_list *clazz;

	coo_return_if_true(this == NULL);

	clazz = (coo_list*)this;

	coo_return_if_true(clazz->private->head == NULL);

	while (!clazz->is_empty(clazz)) {
		clazz->pop_front(clazz, NULL);
	}
}

static void coo_list_print(void *this)
{
	coo_list *clazz;
	coo_iter *iter;
	void *data;

	coo_return_if_true(this == NULL);

	clazz = (coo_list*)this;

	printf("[%s]\n", __func__);
	printf("Size: %d\n", clazz->size(clazz));

	iter = clazz->private->head;
	
	while (iter != NULL) {
		data = iter->value(iter);
		iter = iter->next;

		if (clazz->data_type |= (COO_INT | COO_LONG)) {
			printf("%lu ", (long)data);
		}else if (clazz->data_type |= COO_CHAR) {
			printf("%c ", (char)data);
		}
	}

	printf("\n");
}

static bool coo_list_is_empty(void *this)
{
	coo_list *clazz;

	coo_return_val_if_true(this == NULL, true);

	clazz = (coo_list*)this;

	return !clazz->private->length;
}

static int coo_list_constructor(void *this)
{
	coo_list *clazz = (coo_list*)this;
	if (clazz->parent)
		clazz->parent->private->base.constructor((void*)clazz);

	clazz->front = coo_list_front;
	clazz->back = coo_list_back;
	clazz->rfront = coo_list_rfront;
	clazz->rback = coo_list_rback;
	clazz->insert = coo_list_insert;
	clazz->get = coo_list_get;
	clazz->remove = coo_list_remove;
	clazz->replace = coo_list_replace;
	clazz->erase = coo_list_erase;
	clazz->erase_bt = coo_list_erase_bt;
	clazz->push_front = coo_list_push_front;
	clazz->pop_front = coo_list_pop_front;
	clazz->push_back = coo_list_push_back;
	clazz->pop_back = coo_list_pop_back;
	clazz->size = coo_list_size;
	clazz->reverse = coo_list_reverse;
	clazz->merge = coo_list_merge;
	clazz->sort = coo_list_sort;
	clazz->clear = coo_list_clear;
	clazz->print = coo_list_print;
	clazz->is_empty = coo_list_is_empty;

	clazz->private = (coo_list_private*)malloc(sizeof(coo_list_private));
	clazz->private->base.class_type = COO_LIST;
	clazz->private->base.constructor = coo_list_constructor;
	clazz->private->base.destructor = coo_list_destructor;

	clazz->private->head = NULL;
	clazz->private->length = 0;

	return COO_OKAY;
}

static int coo_list_destructor(void *this)
{
	coo_list *clazz = (coo_list*)this;

	if (clazz->parent)
		clazz->parent->private->base.destructor((void*)clazz->parent);

	return COO_OKAY;
}

coo_list* coo_list_init(void)
{
	coo_list *clazz = (coo_list*)malloc(sizeof(coo_list));
	if (!clazz)
		goto OOM_ERROR;
	
	clazz->parent = coo_init(coo_class);
	if (!clazz->parent)
		goto OOM_ERROR;

	clazz->private->base.constructor(clazz);

	return clazz;

OOM_ERROR:
	return NULL;
}

coo_list* coo_list_new()
{
	coo_list *clazz;

	clazz = coo_list_init();
	if (!clazz)
		return NULL;

	return clazz;
}
