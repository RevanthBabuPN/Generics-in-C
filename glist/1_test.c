#include <stdio.h>
#include "glist.h"

glist(int) intlist;
glist(float) floatlist;

int main()
{
	{
		intlist *il = malloc(sizeof(intlist));
		gl_init(int, il);
		gl_push_back(il, 1);	// [1]
		gl_push_back(il, 2);	// [1, 2]
		gl_push_back(il, 3);	// [1, 2, 3]
		gl_push_front(il, 4);	// [4, 1, 2, 3]
		gl_push_front(il, 5);	// [5, 4, 1, 2, 3]
		gl_push_front(il, 5);	// [5, 5, 4, 1, 2, 3]
		gl_remove(il, 5);		// [4, 1, 2, 3]
		gl_remove(il, 3);		// [4, 1, 2]
		gl_pop_front(il);		// [1, 2]

		printf("Intlist\n");
		iterator(int) it1;
		init_iterator(int, il, &it1);
		// while(has_next_int(&it1))
		while(has_next(&it1))
		{
			printf("%d ", next(&it1));
		}
		iterator(int) *it2 = gl_find(il, 2);
		if(has_next_int(it2))
			printf("\nfound: %d\n", next_int(it2));
		else
			printf("\nnot found");

		printf("\n-------------------------------------------\n\n");
	}
	
	#if 1
	{
		floatlist fl;
		gl_init(float, &fl);
		gl_push_back(&fl, 1);	// [1.00]
		gl_push_back(&fl, 2);	// [1.00, 2.00]
		gl_push_back(&fl, 3);	// [1.00, 2.00, 3.00]
		gl_push_back(&fl, 4);	// [1.00, 2.00, 3.00, 4.00]
		gl_push_back(&fl, 5);	// [1.00, 2.00, 3.00, 4.00, 5.00]
		gl_pop_back(&fl);		// [1.00, 2.00, 3.00, 4.00]
		gl_pop_back(&fl);		// [1.00, 2.00, 3.00]
		gl_push_back(&fl, 4);	// [1.00, 2.00, 3.00, 4.00]
		gl_pop_front(&fl);		// [2.00, 3.00, 4.00]
		gl_push_front(&fl, 5);	// [5.00, 2.00, 3.00, 4.00]
		gl_push_back(&fl, 5);	// [5.00, 2.00, 3.00, 4.00, 5.00]
		gl_push_back(&fl, 4.5);	// [5.00, 2.00, 3.00, 4.00, 5.00, 4.50]

		
		printf("FloatList\nBefore sorting:\n");
		iterator(float) it3;
		init_iterator(float, &fl, &it3);
		// while(has_next_float(&it3))
		while(has_next(&it3))
		{
			printf("%0.2f\t", next_float(&it3));
		}
		
		gl_sort(&fl);
		
		printf("\n\nAfter sorting:\n");
		init_iterator(float, &fl, &it3);
		while(has_next_float(&it3))
		{
			printf("%0.2f\t", next_float(&it3));
		}
		printf("\n\n");
	}
	#endif
}