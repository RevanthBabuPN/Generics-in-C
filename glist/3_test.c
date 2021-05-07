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

glist(complex, complex_equal) complexlist;

int main()
{
	complexlist l1 = gl_init(complex);

	complex c1 = {11, 9};
	complex c2 = {2, 4};
	complex c3 = {26, 11};
	complex c4 = {30, 1};
	complex c5 = {26, 12};

	gl_push_back(l1, c1);
    gl_push_back(l1, c2);
    gl_push_back(l1, c3);
    gl_push_front(l1, c4);
    gl_push_front(l1, c5);

	iterator(complex) it;
	init_iterator(complex, l1, &it);

	printf("Elements:\n");
	while(has_next(complex, &it))
	{
		complex temp = next(complex, &it);
		printf("%d : %d\n", temp.rp, temp.ip);
	}

	gl_sort(l1, by_rp);
	printf("\n------------------------\nAfter sorting by rp:\n");
	iterator(complex) it3;
	init_iterator(complex, l1, &it3);
	while(has_next(complex, &it3))
	{
		complex temp = next(complex, &it3);
		printf("%d : %d\n", temp.rp, temp.ip);
	}
}