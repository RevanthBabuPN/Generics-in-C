#include <stdio.h>
#include "glist.h"

// Generic find function
#define myfind(first, last, key)\
{ \
	while(!gl_iterator_eq(first, last) && (get_val(first) != key)) \
	{ \
		next(first); \
	} \
} 

glist(int) intlist;		// defines the linked list structures and functions for int
glist(float) floatlist;	// defines the linked list structures and functions for float

int main()
{
	{
		printf("Intlist\n-------\n");
		intlist *il = malloc(sizeof(intlist));	// creating a intlist object.
		gl_init(int, il);		// initialising the list
		
		gl_push_back(il, 1);	// [1]
		gl_push_back(il, 2);	// [1, 2]
		gl_push_back(il, 3);	// [1, 2, 3]
		gl_push_front(il, 4);	// [4, 1, 2, 3]
		gl_push_front(il, 5);	// [5, 4, 1, 2, 3]
		gl_push_front(il, 6);	// [5, 5, 4, 1, 2, 3]
		gl_remove(il, 3);		// [4, 1, 2]
		gl_pop_front(il);		// [1, 2]

		printf("Elements:\n");
		gl_iterator(int) it;	// Creating iterator
		gl_init_iterator(int, il, &it); // Initialising iterator
		
		while(has_next(&it))
		{
			printf("%d ", next(&it));
		}

		gl_iterator(int) *beg = gl_begin(il);
		gl_iterator(int) *end = gl_end(il);

		myfind(beg, end, 2);	//	using the generic find function
		if(!gl_iterator_eq(beg, end))
			printf("\n%d: Found", get_val(beg));
		else
			printf("Not Found");
	}

	printf("\n\n=============================================\n\n");
	#if 1
	{
		printf("Floatlist\n----------\n");
		floatlist fl;	// creating an object of floatlist.
		gl_init(float, &fl);	// initialising the floatlist object.
		gl_push_back(&fl, 1.0);	// [1.00]
		gl_push_back(&fl, 2.0);	// [1.00, 2.00]
		gl_push_back(&fl, 3.0);	// [1.00, 2.00, 3.00]
		gl_push_back(&fl, 4.0);	// [1.00, 2.00, 3.00, 4.00]
		gl_push_back(&fl, 5.0);	// [1.00, 2.00, 3.00, 4.00, 5.00]
		gl_pop_back(&fl);		// [1.00, 2.00, 3.00, 4.00]
		gl_pop_back(&fl);		// [1.00, 2.00, 3.00]
		gl_push_back(&fl, 4.0);	// [1.00, 2.00, 3.00, 4.00]
		gl_pop_front(&fl);		// [2.00, 3.00, 4.00]
		gl_push_front(&fl, 5.0);	// [5.00, 2.00, 3.00, 4.00]
		gl_push_back(&fl, 5.0);	// [5.00, 2.00, 3.00, 4.00, 5.00]
		gl_push_back(&fl, 4.5);	// [5.00, 2.00, 3.00, 4.00, 5.00, 4.50]

		printf("Elements before sorting:\n");
		gl_iterator(float) it;	// Creating terator
		gl_init_iterator(float, &fl, &it);	// Initialising iterator

		while(has_next(&it))
		{
			printf("%0.2f\t", next_float(&it));
		}
		
		
		gl_sort(&fl);	// sorting the elements of the container in ascending order.
		printf("\n\nAfter sorting:\n");
		gl_init_iterator(float, &fl, &it);	// Re initialising the iterator to point to the beginning of container fl.
		while(has_next(&it))
		{
			printf("%0.2f\t", next(&it));
		}
		printf("\n");


		gl_unique(&fl);
		printf("\nAfter removing duplicates using gl_unique:\n");
		gl_init_iterator(float, &fl, &it);	// Re initialising the iterator to point to the beginning of container fl.
		while(has_next(&it))
		{
			printf("%0.2f\t", next(&it));
		}
		printf("\n");


		gl_iterator(float) *beg = gl_begin(&fl);
		gl_iterator(float) *end = gl_end(&fl);

		myfind(beg, end, 4.55);
		if(!gl_iterator_eq(beg, end))
			printf("\n%0.2f: Found\n", get_val(beg));
		else
			printf("\nNot Found\n");

		
		gl_clear(&fl);
		printf("\nAfter clearing the list:\n");
		printf("Size: %ld\n", gl_size(&fl));
	}
	#endif
}