#include <stdio.h>
#include "glist.h"

typedef struct
{
	int rp;
	int ip;
} complex;

int complex_equal(complex c1, complex c2)
{
	return c1.rp == c2.rp && c1.ip == c2.ip;
}

int by_rp(complex c1, complex c2)
{
	return c1.rp < c2.rp;
}

// defines the linked list structures and functions for complex, uses complex_equal for ==
glist(complex, complex_equal) complexlist;	

int main()
{
	complexlist clist;
	gl_init(complex, &clist);

	complex c1 = {11, 9};
	complex c2 = {2, 4};
	complex c3 = {26, 11};
	complex c4 = {30, 1};
	complex c5 = {26, 12};

	gl_push_back(&clist, c1);
    gl_push_back(&clist, c2);
    gl_push_back(&clist, c3);
    gl_push_front(&clist, c4);
    gl_push_front(&clist, c5);
	gl_push_front(&clist, c4);

	gl_iterator(complex) it;
	gl_init_iterator(complex, &clist, &it);

	printf("Elements:\n----------\n");
	while(has_next(&it))
	{
		complex temp = next(&it);
		printf("%d : %d\n", temp.rp, temp.ip);
	}

	gl_unique(&clist);
	printf("\nAfter removing duplicates using gl_unique:\n-------------------------------------------\n");
	
	gl_init_iterator(complex, &clist, &it);
	while(has_next(&it))
	{
		complex temp = next(&it);
		printf("%d : %d\n", temp.rp, temp.ip);
	}

	gl_sort(&clist, by_rp);
	printf("\nAfter sorting by rp:\n--------------------\n");

	gl_init_iterator(complex, &clist, &it);
	while(has_next(&it))
	{
		complex temp = next(&it);
		printf("%d : %d\n", temp.rp, temp.ip);
	}
}