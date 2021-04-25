# Generic Containers in C
<p>
C programming language does not provide templates which are commonly used for generic container data types in other statically typed programming languages. This feature however can be implemented in C by the use of macros.<br><br>
C macros have been extensively used in implementing generic containers. This repository contains implementation of generic list in C language.
</p>
<br>

## List
<p>
Lists are sequence containers that allow for non contiguous memory allocation.
<br>
The library provides a generic list container that is compatible with standard types as well as user defined types.<br>
The internal implementation uses a singly linked list.<br>
</p>
<br>

> ### Methods

<div style="margin-left:20px;">
	<table>
		<tr>
			<th>Function</th>
			<th>Description</th>
		</tr>
		<tr>
			<td>gl_init</td>
			<td>initializes the list with user provided type</td>
		</tr>
		<tr>
			<td>gl_size</td>
			<td>returns the number of elements</td>
		</tr>
		<tr>
			<td>gl_find</td>
			<td>returns iterator to the element if found</td>
		</tr>
		<tr>
			<td>gl_push_back</td>
			<td>adds an element to the end</td>
		</tr>
		<tr>
			<td>gl_pop_back</td>
			<td>removes the last element</td>
		</tr>
		<tr>
			<td>gl_push_front</td>
			<td>inserts an element to the beginning</td>
		<tr>
			<td>gl_pop_front</td>
			<td>removes the first element</td>
		</tr>
		<tr>
			<td>gl_remove</td>
			<td>removes all occurences of the given element</td>
		</tr>
		<tr>
			<td>gl_clear</td>
			<td>clears the contents</td>
		</tr>
		<tr>
			<td>gl_sort</td>
			<td>sorts the elements (uses merge sort)</td>
		</tr>	
	</table>
</div>
<br>

> ### Usage
```c
	#include <stdio.h>
	#include "glist.h"

	glist(int) intlist;

	int main()
	{
		intlist l = gl_init(int); // []

		gl_push_front(l, 4);	// [4]
		gl_push_back(l, 3); 	// [4, 3]
		gl_push_back(l, 1);		// [4, 3, 1]
		gl_push_back(l, 2);		// [4, 3, 1, 2]
		gl_push_front(l, 4);	// [4, 4, 3, 1, 2]
		
		gl_remove(l, 4);		// [3, 1, 2]

		gl_sort(l);				// [1, 2, 3]

		iterator(int) it;
		init_iterator(int, one, &it);
		
		while(has_next_int(&it))
		{
			printf("%d ", next_int(&it));	// 1 2 3
		}
	}
```