#include <stdio.h>
#include "glist.h"

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
		gl_iterator(int) it1;	// Creating iterator
		gl_init_iterator(int, il, &it1); // Initialising iterator
		
		while(has_next(&it1))
		{
			printf("%d ", next(&it1));
		}

		gl_iterator(int) *it2 = gl_find(il, 2);
		if(has_next_int(it2))
			printf("\n%d: Found\n", next_int(it2));
		else
			printf("\n2: Not found\n");
		printf("\n---------------------------------------------\n");
	}
	
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
		gl_iterator(float) it3;	// Creating terator
		gl_init_iterator(float, &fl, &it3);	// Initialising iterator

		while(has_next(&it3))
		{
			printf("%0.2f\t", next_float(&it3));
		}
		
		gl_sort(&fl);	// sorting the elements of the container in ascending order.
		
		printf("\n\nAfter sorting:\n");

		gl_init_iterator(float, &fl, &it3);	// Re initialising the iterator to point to the beginning of container fl.
		while(has_next_float(&it3))
		{
			printf("%0.2f\t", next_float(&it3));
		}
		printf("\n");
	}
	#endif
}