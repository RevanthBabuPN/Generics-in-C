#include <stdio.h>
#include "glist.h"

glist(int) intlist;
glist(float) floatlist;

typedef struct
{
	int a;
	int b;
	float c;
} pkg;

int comp(pkg a, pkg b)
{
	return a.a == b.a;
}

int compare(pkg a, pkg b)
{
	return a.a <= b.a;
}

glist(pkg, comp) pkglist;

int main()
{
	#if 0
	intlist one = gl_init(int);
    gl_push_back(one, 1);
    gl_push_back(one, 2);
    gl_push_back(one, 3);
    gl_push_front(one, 4);
    gl_push_front(one, 5);
	gl_push_front(one, 5);
	gl_remove(one, 5);
	gl_remove(one, 3);
	gl_pop_front(one);
	iterator(int) it;
	init_iterator(int, one, &it);

	while(has_next_int(&it))
	{
		printf("%d ", next_int(&it));
	}
	iterator(int) *it2 = gl_find(one, 5);
	if(has_next_int(it2))
		printf("\nfound: %d\n", next_int(it2));
	else
		printf("\nnot found\n");
	printf("\n");
	#endif

	#if 0
	floatlist two = gl_init(float);
    gl_push_back(two, 1);
    gl_push_back(two, 2);
    gl_push_back(two, 3);
    gl_push_back(two, 4);
    gl_push_back(two, 5);
	gl_pop_back(two);
	gl_pop_back(two);
    gl_push_back(two, 4);
	gl_pop_front(two);
    gl_push_front(two, 5);
	gl_push_back(two, 5);
	gl_push_back(two, 4.5);
	gl_remove(two, 5);

	gl_sort(two);
	iterator(float) it3;

	init_iterator(float, two, &it3);

	while(has_next(float, &it3))
	{
		// printf("%f ", next_float(&it3));
		printf("%f ", next(float, &it3));
	}
	printf("\n\n");
	
	// gl_clear(two);
	// gl_push_back(two, 1);
    // gl_push_back(two, 2);
    // gl_push_back(two, 3);
    // gl_push_back(two, 4);

	// init_iterator(float, two, &it3);
	// while(has_next(float, &it3))
	// {
	// 	// printf("%f ", next_float(&it3));
	// 	printf("%f ", next(float, &it3));
	// }
	// printf("\n\n");
	#endif

	#if 1
	pkglist two = gl_init(pkg);

	pkg ob1 = {1,1,1.1};
    pkg ob2 = {2,2,2.1};
    pkg ob3 = {3,3,3.1};
    pkg ob4 = {4,4,4.1};
    pkg ob5 = {5,5,5.1};

    gl_push_back(two, ob1);
    gl_push_back(two, ob2);
    gl_push_back(two, ob3);
    gl_push_front(two, ob4);
    gl_push_front(two, ob5);

	gl_remove(two, ob1);
	// gl_sort(two);
	gl_sort(two, compare);
	iterator(pkg) it2;
	init_iterator(pkg, two, &it2);
	while(has_next(pkg, &it2))
	{
		printf("%f ", next(pkg, &it2).c);
	}
	printf("\n");
	#endif
}