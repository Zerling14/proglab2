#include <stdio.h>
#include "IntVector.h"
#define endl printf("\n");
void print_vector(IntVector *v)
{
	printf("Printing IntVector\n");
	printf("data_pointer:%p size:%d capacity:%d\n", v->data, (int)v->size, (int)v->capacity);
	if((v->data == NULL) || (v->capacity == 0)){
		return;
	}
	printf("data:\n");
	for(int i = 0; i < v->capacity; i++) {
		printf(i == v->capacity - 1 ? "%d\n" : "%d, " , v->data[i]);
	}
}

int main()
{
	IntVector *z = NULL;

	int_vector_free(z);	
	
	printf("Create new IntVector\n");
	IntVector *v = int_vector_new(5);
	if (v == NULL){
		printf("Error initialization IntVector\n");
		printf("Last error code: %d\n", get_last_error());
		return 1;
	}
	print_vector(v);
	
	endl
	
	printf("Create copy of v\n");
	IntVector *n = int_vector_copy(v);
	if (n == NULL) {
		printf("Error copy IntVector\n");
		printf("Last error code: %d\n", get_last_error());
		return 1;
	}
	print_vector(n);
	
	int_vector_free(n);
	
	endl
	
	printf("Set 4 index\n");
	//int_vector_set_item(v, 4, 5);
	print_vector(v);
	printf("error:%d\n", get_last_error());
	
	endl
	
	printf("get item 3:%d\n",int_vector_get_item(v, 3));
	printf("error:%d\n", get_last_error());
	printf("get item 5:%d\n",int_vector_get_item(v, 5));
	printf("error:%d\n", get_last_error());
	
	endl
	
	printf("size: %zu capacity:%d\n", int_vector_get_size(v), (int)int_vector_get_capacity(v));
	
	endl
	
	if (int_vector_push_back(v, 6) == 0) {
		print_vector(v);
	}
	int_vector_push_back(v, 6);
	int_vector_push_back(v, 6);
	int_vector_push_back(v, 6);
	int_vector_push_back(v, 6);
	int_vector_push_back(v, 6);
	int_vector_push_back(v, 6);
	print_vector(v);
	
	int_vector_pop_back(v);
	print_vector(v);
	
	endl
	
	int_vector_shrink_to_fit(v);
	print_vector(v);

	int_vector_free(v);
	
	endl
	return 0;
}
