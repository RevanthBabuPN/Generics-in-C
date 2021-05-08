#include <stdio.h>
#include "glist.h"

typedef struct
{
	int dd;
	int mm;
	int yy;
} date;

int date_equal(date d1, date d2)
{
	return d1.dd == d2.dd && d1.mm == d2.mm && d1.yy == d2.yy;
}

int by_year(date d1, date d2)
{
	return d1.yy < d2.yy;
}

int by_month(date d1, date d2)
{
	return d1.mm < d2.mm;
}

// defines the linked list structures and functions for date, uses date_equal for ==
glist(date, date_equal) datelist;

int main()
{
	datelist l1;
	gl_init(date, &l1);

	date d1 = {11, 9, 2001};
	date d2 = {2, 4, 2011};
	date d3 = {26, 11, 2008};
	date d4 = {30, 1, 1948};
	date d5 = {26, 12, 2004};

	gl_push_back(&l1, d1);
    gl_push_back(&l1, d2);
    gl_push_back(&l1, d3);
    gl_push_front(&l1, d4);
    gl_push_front(&l1, d5);

	gl_iterator(date) it1;
	gl_init_iterator(date, &l1, &it1);

	printf("Elements:\n----------\n");
	while(has_next_date(&it1))
	{
		date temp = next_date(&it1);
		printf("%d - %d - %d\n", temp.dd, temp.mm, temp.yy);
	}

	gl_sort(&l1, by_year);
	printf("\nSorting by year:\n----------------\n");

	gl_init_iterator(date, &l1, &it1);
	while(has_next_date(&it1))
	{
		date temp = next_date(&it1);
		printf("%d - %d - %d\n", temp.dd, temp.mm, temp.yy);
	}

	gl_sort(&l1, by_month);
	printf("\nSorting by month:\n------------------\n");

	gl_init_iterator(date, &l1, &it1);
	while(has_next_date(&it1))
	{
		date temp = next_date(&it1);
		printf("%d - %d - %d\n", temp.dd, temp.mm, temp.yy);
	}

	date d = {11, 9, 2001};
	gl_remove(&l1, d);
	printf("\nRemoved {11, 9, 2001}\n----------------------\n");
	
	gl_init_iterator(date, &l1, &it1);
	while(has_next_date(&it1))
	{
		date temp = next_date(&it1);
		printf("%d - %d - %d\n", temp.dd, temp.mm, temp.yy);
	}
}