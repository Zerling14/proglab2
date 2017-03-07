#include <stdlib.h>
#include "IntVector.h"
#include <String.h>

int num_error = 0;	

//  NO_ERROR 0
//	READ_ERROR 1
//	WRITE_ERROR 2
//	MEM_ALLOC_ERROR 3

int get_last_error() //0 - no error | 1 - read error | 2 - write error | 3 - memory allocation error | 
{ 
	return num_error;
}

void set_last_error(int error_code)
{
	num_error = error_code;
}

IntVector *int_vector_new(size_t initial_capacity)
{
	IntVector *v = malloc(sizeof(IntVector));
	if (v == NULL) {
		set_last_error(MEM_ALLOC_ERROR);
		return NULL;
	}
	v->data = malloc(initial_capacity * sizeof(int));
	if (v->data == NULL) {
		free(v);
		set_last_error(MEM_ALLOC_ERROR);
		return NULL;
	}
	memset(v->data, 0, initial_capacity * sizeof(int));
	v->size = 0;
	v->capacity = initial_capacity;
	set_last_error(NO_ERROR);
	return v;
}

IntVector *int_vector_copy(const IntVector *v_original)
{
	IntVector *v = int_vector_new(v_original->capacity);
	if (v == NULL)
	{
		set_last_error(MEM_ALLOC_ERROR);
		return NULL;
	}
	memcpy(v->data, v_original->data, v_original->capacity);
	v->size = v_original->size;
	v->capacity = v_original->capacity;
	set_last_error(NO_ERROR);
	return v;
}

void int_vector_free(IntVector *v)
{
	free(v->data);
	free(v);
}

int int_vector_get_item(const IntVector *v, size_t index)
{
	if (index >= v->capacity) {
		set_last_error(READ_ERROR);
		return 0;
	}
	set_last_error(NO_ERROR);
	return v->data[index];
}

void int_vector_set_item(IntVector *v, size_t index, int item)
{
	if (index >= v->capacity) {
		set_last_error(WRITE_ERROR);
		return;
	}
	v->data[index] = item;
	set_last_error(NO_ERROR);
}

size_t int_vector_get_size(const IntVector *v)
{
	return v->size;
}

size_t int_vector_get_capacity(const IntVector *v)
{
	return v->capacity;
}

int int_vector_push_back(IntVector *v, int item)
{
	int exp_ratio = 2;
	if(v->size == v->capacity)
	{
		if(int_vector_reserve(v, v->capacity * exp_ratio))
		{
			set_last_error(MEM_ALLOC_ERROR);
			return -1;
		}
		// int *tmp_data = realloc(v->data, v->capacity * exp_ratio * sizeof(int));
		// if (tmp_data == NULL) {
			// set_last_error(MEM_ALLOC_ERROR);
			// return -1;
		// }
		// v->data = tmp_data;
		// memset(v->data + v->capacity, 0, v->capacity * sizeof(int));
		// v->capacity *= exp_ratio;
	}
	v->data[v->size] = item;
	v->size++;
	set_last_error(NO_ERROR);
	return 0;
}

void int_vector_pop_back(IntVector *v)
{
	if (v->size == 0) {
		return;
	}
	v->size--;
	v->data[v->size] = 0;
}

int int_vector_shrink_to_fit(IntVector *v)
{
	int *tmp_data = realloc(v->data, v->size * sizeof(int));
	if (tmp_data == NULL) {
		set_last_error(MEM_ALLOC_ERROR);
		return -1;
	}
	v->data = tmp_data;
	v->capacity = v->size;	
	return 0;
}

int int_vector_resize(IntVector *v, size_t new_size)
{
	if (new_size > v->size) {
		
		// int *tmp_data = realloc(v->data, new_size * sizeof(int));
		// if (tmp_data == NULL) {
			// set_last_error(MEM_ALLOC_ERROR);
			// return -1;
		// }
		// v->data = tmp_data;
		 memset(v->data + v->size, 0, (new_size - v->size) * sizeof(int));
		 v->size = new_size;
	}
	if (new_size < v->size) {
		if (int_vector_shrink_to_fit(v)) {
			set_last_error(MEM_ALLOC_ERROR);
			return -1;
		}
	}
	set_last_error(NO_ERROR);
	return 0;
}

int int_vector_reserve(IntVector *v, size_t new_capacity)
{
	if (new_capacity > v->capacity) {
		int *tmp_data = realloc(v->data, new_capacity * sizeof(int));
		if (tmp_data == NULL) {
			set_last_error(MEM_ALLOC_ERROR);
			return -1;
		}
		v->data = tmp_data;
		memset(v->data + v->capacity, 0, (new_capacity - v->capacity) * sizeof(int));
		v->capacity = new_capacity;
	}
	set_last_error(NO_ERROR);
	return 0;
}

