#ifndef G_LIST_H
#define G_LIST_H

#include <stdlib.h>

/*wrappers for iterator functions*/
#define iterator(T) iterator_ ## T ## _t
#define init_iterator(T, lis, itr) init_iterator_ ## T (lis, itr)
// #define has_next(T, itr) has_next_ ## T (itr)
// #define next(T, itr) next_ ## T (itr)

#define has_next(itr) (itr)->fns->has_next(itr)
#define next(itr) (itr)->fns->next(itr)

#define GET_MACRO(_1,_2,NAME,...) NAME
#define glist(...) GET_MACRO(__VA_ARGS__, glist2, glist1)(__VA_ARGS__)

#define gl_sort(...) GET_MACRO(__VA_ARGS__, gl_sort2, gl_sort1)(__VA_ARGS__)

#define gl_init(T, l) g_list_ ## T ## _fns.init(l)
#define gl_clear(l) (l)->fns->clear(l)
#define gl_push_back(l, val) (l)->fns->push_back(l, val)
#define gl_pop_back(l) (l)->fns->pop_back(l)
#define gl_push_front(l, val) (l)->fns->push_front(l, val)
#define gl_pop_front(l) (l)->fns->pop_front(l)
#define gl_size(l) (l)->fns->size(l)
#define gl_find(l, val) (l)->fns->find(l, val)
#define gl_remove(l, val) (l)->fns->remove(l, val)
#define gl_sort1(l) (l)->fns->sort1(&(l)->head)
#define gl_sort2(l, compare) (l)->fns->sort2(&(l)->head, compare)

#define glist1(T) \
	struct g_list_ ## T; \
	struct node_ ## T; \
	struct iterator_ ## T; \
	typedef struct g_list_ ## T gl_ ## T; \
	typedef struct node_ ## T node_ ## T ## _t; \
	typedef struct iterator_ ## T iterator_ ## T ## _t; \
	\
	struct node_ ## T { \
		T val; \
		node_ ## T ## _t * next; \
	}; \
	\
	struct iterator_ ## T ## _fns_t { \
		int (*has_next)(const iterator_ ## T ## _t *ptr_iterator); \
		T (*next)(iterator_ ## T ## _t *ptr_iterator); \
	}; \
	\
	struct iterator_ ## T \
	{ \
		node_ ## T ## _t* current; \
		struct iterator_ ## T ## _fns_t * fns;\
	}; \
	\
	struct g_list_ ## T ## _fns_t { \
		void (*init)(gl_ ## T *l); \
		void (*clear)(gl_ ## T *l); \
		void (*push_back)(gl_ ## T *l, T val); \
		void (*pop_back)(gl_ ## T *l); \
		void (*push_front)(gl_ ## T *l, T val); \
		void (*pop_front)(gl_ ## T *l); \
		size_t (*size)(gl_ ## T *l); \
		iterator_ ## T ## _t* (*find)(gl_ ## T *l, T val); \
		size_t (*remove)(gl_ ## T *l, T val); \
		void (*sort1)(node_ ## T ## _t**);\
		void (*sort2)(node_ ## T ## _t** l, int (*compare)(T a, T b));\
	}; \
	\
	struct g_list_ ## T { \
		size_t size; \
		struct node_ ## T * head; \
		struct node_ ## T * tail; \
		struct node_ ## T * end; \
		struct g_list_ ## T ## _fns_t * fns; \
	}; \
	\
	\
	static inline void g_list_ ## T ## _init (gl_ ## T *l); \
	static inline void g_list_ ## T ## _clear (gl_ ## T *l); \
	static inline void g_list_ ## T ## _push_back (gl_ ## T *l, T val); \
	static inline void g_list_ ## T ## _pop_back (gl_ ## T *l); \
	static inline void g_list_ ## T ## _push_front (gl_ ## T *l, T val); \
	static inline void g_list_ ## T ## _pop_front (gl_ ## T *l); \
	static inline size_t g_list_ ## T ## _size (gl_ ## T *l); \
	static inline iterator_ ## T ## _t* g_list_ ## T ## _find (gl_ ## T *l, T val); \
	static inline size_t g_list_ ## T ## _remove (gl_ ## T *l, T val); \
	static inline void g_list_ ## T ## _sort1 (node_ ## T ## _t** l); \
	static inline void g_list_ ## T ## _sort2 (node_ ## T ## _t** l,  int (*compare)(T a, T b)); \
	\
	struct g_list_ ## T ## _fns_t g_list_ ## T ## _fns = { \
		.init		= g_list_ ## T ## _init,	\
		.clear		= g_list_ ## T ## _clear,	\
		.push_back	= g_list_ ## T ## _push_back,	\
		.pop_back	= g_list_ ## T ## _pop_back,	\
		.push_front	= g_list_ ## T ## _push_front,	\
		.pop_front	= g_list_ ## T ## _pop_front,	\
		.size		= g_list_ ## T ## _size,	\
		.find		= g_list_ ## T ## _find,	\
		.remove		= g_list_ ## T ## _remove,	\
		.sort1		= g_list_ ## T ## _sort1, \
		.sort2		= g_list_ ## T ## _sort2 \
	}; \
	\
	\
	static void init_iterator_ ## T (gl_ ## T *ptr_list, iterator_ ## T ## _t *ptr_iterator); \
	static int has_next_ ## T (const iterator_ ## T ## _t *ptr_iterator); \
	static T next_ ## T (iterator_ ## T ## _t *ptr_iterator); \
	\
	struct iterator_ ## T ## _fns_t  iterator_ ## T ## _fns = { \
		.has_next		= has_next_ ## T,	\
		.next			= next_ ## T	\
	}; \
	\
	static void init_iterator_ ## T (gl_ ## T *ptr_list, iterator_ ## T ## _t *ptr_iterator) \
	{ \
		ptr_iterator->current = ptr_list->head; \
		ptr_iterator->fns = &iterator_ ## T ## _fns;\
	} \
	\
	static int has_next_ ## T (const iterator_ ## T ## _t *ptr_iterator) \
	{ \
		return ptr_iterator->current != 0; \
	} \
	\
	static T next_ ## T (iterator_ ## T ## _t *ptr_iterator) \
	{ \
		T key = ptr_iterator->current->val; \
		ptr_iterator->current = ptr_iterator->current->next; \
		return key; \
	} \
	\
	static inline void g_list_ ## T ## _init (gl_ ## T *l) { \
		/*gl_##T * l = calloc(1, sizeof(struct g_list_ ## T));*/ \
		l->fns = &g_list_ ## T ## _fns; \
		l->head = NULL;\
		l->tail = NULL;\
		l->end = NULL;\
		l->size = 0; \
		/*return l; */\
	} \
	\
	static inline void g_list_ ## T ## _clear (gl_##T* l) { \
		node_ ## T ## _t* elem = l->head; \
		\
		while (elem != l->end) { \
			node_ ## T ## _t* next = elem->next;\
			elem -> next = NULL; \
			free(elem);\
			elem = next;\
		}\
		\
		free(l); \
		l->head = NULL;\
	} \
	static inline int g_list_ ## T ## _cmp (T a, T b) { \
		return a == b;\
	} \
	\
	static inline void g_list_ ## T ## _push_back(gl_##T* l, T val) { \
		node_ ## T ## _t* elem = calloc(1, sizeof(node_ ## T ## _t)); \
		elem->val = val; \
		\
		if (l->size == 0) { \
			l->head = elem; \
			l->tail = elem; \
		} else { \
			l->tail->next = elem; \
			l->tail = elem; \
		} \
		\
		l->size += 1; \
		\
	} \
	\
	static inline void g_list_ ## T ## _pop_back(gl_##T* l) { \
		if (l->size == 0) { \
			return; \
		} \
		if (l->size == 1) { \
			free(l -> head); \
			l -> head = NULL; \
			l -> tail = NULL; \
			l -> size = 0; \
		} else { \
			node_ ## T ## _t* cur = l -> head; \
			while(cur -> next -> next != 0) \
			{ \
				cur = cur -> next; \
			} \
			free(cur -> next); \
			cur -> next = NULL; \
			l -> tail = cur; \
			l -> size -= 1; \
		} \
		\
	} \
	\
	\
	static inline void g_list_ ## T ## _push_front(gl_##T* l, T val) { \
		node_ ## T ## _t* elem = calloc(1, sizeof(node_ ## T ## _t)); \
		elem->val = val; \
		\
		if (l->size == 0) { \
			l->head = elem; \
			l->tail = elem; \
		} else { \
			elem -> next = l -> head; \
			l->head = elem; \
		} \
		\
		l->size += 1; \
		\
	} \
	\
	static inline void g_list_ ## T ## _pop_front(gl_##T* l) { \
		if (l->size == 0) { \
			return; \
		} \
		if (l->size == 1) { \
			free(l -> head); \
			l -> head = NULL; \
			l -> tail = NULL; \
			l -> size = 0; \
		} else { \
			node_ ## T ## _t* cur = l -> head; \
			l -> head = l->head -> next; \
			free(cur); \
			l -> size -= 1; \
		} \
		\
	} \
	\
	static inline iterator_ ## T ## _t* g_list_ ## T ## _find(gl_##T* l, T val) { \
		node_ ## T ## _t* elem = l->head; \
		/*size_t idx = 0;*/ \
		\
		iterator_ ## T ## _t *it = calloc(1,sizeof(iterator_ ## T ## _t)); \
		while (elem != l->end) { \
			if (g_list_ ## T ## _cmp(elem->val, val)) { \
				it -> current = elem; \
				break;\
				/*return idx; */\
			} else { \
				elem = elem->next; \
				/*idx++;*/ \
			} \
		} \
		\
		return it; \
		/*return -1;*/ \
	} \
	\
	\
	static inline size_t g_list_ ## T ## _remove(gl_##T* l, T val) { \
		size_t count = 0; \
		node_ ## T ## _t *temp = l -> head, *prev; \
		while (temp != NULL && g_list_ ## T ## _cmp(temp->val, val)) \
		{ \
			l->head = temp->next; \
			free(temp); \
			l->size -= 1; \
			++count; \
			temp = l->head; \
		} \
		while (temp != NULL) \
		{ \
			while (temp != NULL && !g_list_ ## T ## _cmp(temp->val, val)) \
			{ \
				prev = temp; \
				temp = temp->next; \
			} \
			if (temp == NULL) \
				return count; \
			prev->next = temp->next; \
			l->size -= 1; \
			++count; \
			if (temp == l->tail) \
				l->tail = prev; \
			free(temp); \
			temp = prev->next; \
		} \
		return count; \
	} \
	\
	static inline size_t g_list_ ## T ## _size(gl_##T* l) { \
		return l->size; \
	} \
	\
	static void FrontBackSplit_ ## T(node_ ## T ## _t* source, node_ ## T ## _t** frontRef, node_ ## T ## _t** backRef) \
	{ \
		node_ ## T ## _t* fast; \
		node_ ## T ## _t* slow; \
		slow = source; \
		fast = source->next; \
		while (fast != NULL) { \
			fast = fast->next; \
			if (fast != NULL) { \
				slow = slow->next; \
				fast = fast->next; \
			} \
		} \
		*frontRef = source; \
		*backRef = slow->next; \
		slow->next = NULL; \
	} \
	\
	static node_ ## T ## _t* SortedMerge_ ## T ## _1(node_ ## T ## _t*  a, node_ ## T ## _t*  b) \
	{ \
		node_ ## T ## _t* result = NULL; \
		if (a == NULL) \
			return (b); \
		else if (b == NULL) \
			return (a); \
		if (a->val <= b->val) { \
			result = a; \
			result->next = SortedMerge_## T ## _1(a->next, b); \
		} \
		else { \
			result = b; \
			result->next = SortedMerge_ ## T ## _1(a, b->next); \
		} \
		return (result); \
	} \
	\
	static void g_list_ ## T ## _sort1 (node_ ## T ## _t** l) \
	{ \
		node_ ## T ## _t* head = *l; \
		node_ ## T ## _t* a; \
		node_ ## T ## _t* b; \
		if ((head == NULL) || (head->next == NULL)) { \
			return; \
		} \
		FrontBackSplit_ ## T(head, &a, &b); \
		g_list_ ## T ## _sort1 (&a); \
		g_list_ ## T ## _sort1 (&b); \
		*l = SortedMerge_ ## T ## _1(a, b); \
	} \
	static node_ ## T ## _t* SortedMerge_ ## T ## _2(node_ ## T ## _t*  a, node_ ## T ## _t*  b, int (*compare)(T a, T b)) \
	{ \
		node_ ## T ## _t* result = NULL; \
		if (a == NULL) \
			return (b); \
		else if (b == NULL) \
			return (a); \
		if (compare(a->val, b->val)) { \
			result = a; \
			result->next = SortedMerge_ ## T ## _2(a->next, b, compare); \
		} \
		else { \
			result = b; \
			result->next = SortedMerge_ ## T ## _2(a, b->next, compare); \
		} \
		return (result); \
	} \
	\
	static void g_list_ ## T ## _sort2 (node_ ## T ## _t** l, int (*compare)(T a, T b)) \
	{ \
		node_ ## T ## _t* head = *l; \
		node_ ## T ## _t* a; \
		node_ ## T ## _t* b; \
		if ((head == NULL) || (head->next == NULL)) { \
			return; \
		} \
		FrontBackSplit_ ## T(head, &a, &b); \
		g_list_ ## T ## _sort2 (&a, compare); \
		g_list_ ## T ## _sort2 (&b, compare); \
		*l = SortedMerge_ ## T ## _2(a, b, compare); \
	} \
	typedef struct g_list_ ## T \



#define glist2(T, compare) \
	struct g_list_ ## T; \
	struct node_ ## T; \
	struct iterator_ ## T; \
	typedef struct g_list_ ## T gl_ ## T; \
	typedef struct node_ ## T node_ ## T ## _t; \
	typedef struct iterator_ ## T iterator_ ## T ## _t;\
	\
	struct node_ ## T { \
		T val; \
		node_ ## T ## _t * next; \
	}; \
	\
	struct iterator_ ## T ## _fns_t { \
		int (*has_next)(const iterator_ ## T ## _t *ptr_iterator); \
		T (*next)(iterator_ ## T ## _t *ptr_iterator); \
	}; \
	\
	struct iterator_ ## T \
	{ \
		node_ ## T ## _t* current; \
		struct iterator_ ## T ## _fns_t * fns;\
	}; \
	\
	struct g_list_ ## T ## _fns_t { \
		void (*init)(gl_ ## T *l); \
		void (*clear)(gl_ ## T *l); \
		void (*push_back)(gl_ ## T *l, T val); \
		void (*pop_back)(gl_ ## T *l); \
		void (*push_front)(gl_ ## T *l, T val); \
		void (*pop_front)(gl_ ## T *l); \
		size_t (*size)(gl_ ## T *l); \
		iterator_ ## T ## _t* (*find)(gl_ ## T *l, T val); \
		size_t (*remove)(gl_ ## T *l, T val); \
		void (*sort1)(node_ ## T ## _t**);\
		void (*sort2)(node_ ## T ## _t** l, int (*compare)(T a, T b));\
	}; \
	\
	struct g_list_ ## T { \
		size_t size; \
		struct node_ ## T * head; \
		struct node_ ## T * tail; \
		struct node_ ## T * end; \
		struct g_list_ ## T ## _fns_t * fns; \
	}; \
	\
	\
	static inline void g_list_ ## T ## _init (gl_ ## T *l); \
	static inline void g_list_ ## T ## _clear (gl_ ## T *l); \
	static inline void g_list_ ## T ## _push_back (gl_ ## T *l, T val); \
	static inline void g_list_ ## T ## _pop_back (gl_ ## T *l); \
	static inline void g_list_ ## T ## _push_front (gl_ ## T *l, T val); \
	static inline void g_list_ ## T ## _pop_front (gl_ ## T *l); \
	static inline size_t g_list_ ## T ## _size (gl_ ## T *l); \
	static inline iterator_ ## T ## _t* g_list_ ## T ## _find (gl_ ## T *l, T val); \
	static inline size_t g_list_ ## T ## _remove (gl_ ## T *l, T val); \
	static inline void g_list_ ## T ## _sort1 (node_ ## T ## _t** l); \
	static inline void g_list_ ## T ## _sort2 (node_ ## T ## _t** l,  int (*compare)(T a, T b)); \
	\
	struct g_list_ ## T ## _fns_t g_list_ ## T ## _fns = { \
		.init		= g_list_ ## T ## _init,	\
		.clear		= g_list_ ## T ## _clear,	\
		.push_back	= g_list_ ## T ## _push_back,	\
		.pop_back	= g_list_ ## T ## _pop_back,	\
		.push_front	= g_list_ ## T ## _push_front,	\
		.pop_front	= g_list_ ## T ## _pop_front,	\
		.size		= g_list_ ## T ## _size,	\
		.find		= g_list_ ## T ## _find,	\
		.remove		= g_list_ ## T ## _remove,	\
		.sort1		= g_list_ ## T ## _sort1, \
		.sort2		= g_list_ ## T ## _sort2 \
	}; \
	\
	\
	static void init_iterator_ ## T (gl_ ## T *ptr_list, iterator_ ## T ## _t *ptr_iterator); \
	static int has_next_ ## T (const iterator_ ## T ## _t *ptr_iterator); \
	static T next_ ## T (iterator_ ## T ## _t *ptr_iterator); \
	\
	struct iterator_ ## T ## _fns_t  iterator_ ## T ## _fns = { \
		.has_next		= has_next_ ## T,	\
		.next			= next_ ## T	\
	}; \
	\
	static void init_iterator_ ## T (gl_ ## T *ptr_list, iterator_ ## T ## _t *ptr_iterator) \
	{ \
		ptr_iterator->current = ptr_list->head; \
		ptr_iterator->fns = &iterator_ ## T ## _fns;\
	} \
	\
	static int has_next_ ## T (const iterator_ ## T ## _t *ptr_iterator) \
	{ \
		return ptr_iterator->current != 0; \
	} \
	\
	static T next_ ## T (iterator_ ## T ## _t *ptr_iterator) \
	{ \
		T key = ptr_iterator->current->val; \
		ptr_iterator->current = ptr_iterator->current->next; \
		return key; \
	} \
	\
	static inline void g_list_ ## T ## _init (gl_ ## T *l) { \
		/*gl_##T * l = calloc(1, sizeof(struct g_list_ ## T));*/ \
		l->fns = &g_list_ ## T ## _fns; \
		l->head = NULL;\
		l->tail = NULL;\
		l->end = NULL;\
		l->size = 0; \
		/*return l; */\
	} \
	\
	static inline void g_list_ ## T ## _clear (gl_##T* l) { \
		node_ ## T ## _t* elem = l->head; \
		\
		while (elem != l->end) { \
			node_ ## T ## _t* next = elem->next;\
			elem -> next = NULL; \
			free(elem);\
			elem = next;\
		}\
		\
		free(l); \
		l->head = NULL;\
	} \
	static inline int g_list_ ## T ## _cmp (T a, T b) { \
		return compare(a, b);\
	} \
	\
	static inline void g_list_ ## T ## _push_back(gl_##T* l, T val) { \
		node_ ## T ## _t* elem = calloc(1, sizeof(node_ ## T ## _t)); \
		elem->val = val; \
		\
		if (l->size == 0) { \
			l->head = elem; \
			l->tail = elem; \
		} else { \
			l->tail->next = elem; \
			l->tail = elem; \
		} \
		\
		l->size += 1; \
		\
	} \
	\
	static inline void g_list_ ## T ## _pop_back(gl_##T* l) { \
		if (l->size == 0) { \
			return; \
		} \
		if (l->size == 1) { \
			free(l -> head); \
			l -> head = NULL; \
			l -> tail = NULL; \
			l -> size = 0; \
		} else { \
			node_ ## T ## _t* cur = l -> head; \
			while(cur -> next -> next != 0) \
			{ \
				cur = cur -> next; \
			} \
			free(cur -> next); \
			cur -> next = NULL; \
			l -> tail = cur; \
			l -> size -= 1; \
		} \
		\
	} \
	\
	\
	static inline void g_list_ ## T ## _push_front(gl_##T* l, T val) { \
		node_ ## T ## _t* elem = calloc(1, sizeof(node_ ## T ## _t)); \
		elem->val = val; \
		\
		if (l->size == 0) { \
			l->head = elem; \
			l->tail = elem; \
		} else { \
			elem -> next = l -> head; \
			l->head = elem; \
		} \
		\
		l->size += 1; \
		\
	} \
	\
	static inline void g_list_ ## T ## _pop_front(gl_##T* l) { \
		if (l->size == 0) { \
			return; \
		} \
		if (l->size == 1) { \
			free(l -> head); \
			l -> head = NULL; \
			l -> tail = NULL; \
			l -> size = 0; \
		} else { \
			node_ ## T ## _t* cur = l -> head; \
			l -> head = l->head -> next; \
			free(cur); \
			l -> size -= 1; \
		} \
		\
	} \
	\
	static inline iterator_ ## T ## _t* g_list_ ## T ## _find(gl_##T* l, T val) { \
		node_ ## T ## _t* elem = l->head; \
		/*size_t idx = 0;*/ \
		\
		iterator_ ## T ## _t *it = calloc(1,sizeof(iterator_ ## T ## _t)); \
		while (elem != l->end) { \
			if (g_list_ ## T ## _cmp(elem->val, val)) { \
				it -> current = elem; \
				break;\
				/*return idx; */\
			} else { \
				elem = elem->next; \
				/*idx++;*/ \
			} \
		} \
		\
		return it; \
		/*return -1;*/ \
	} \
	\
	\
	static inline size_t g_list_ ## T ## _remove(gl_##T* l, T val) { \
		size_t count = 0; \
		node_ ## T ## _t *temp = l -> head, *prev; \
		while (temp != NULL && g_list_ ## T ## _cmp(temp->val, val)) \
		{ \
			l->head = temp->next; \
			free(temp); \
			l->size -= 1; \
			++count; \
			temp = l->head; \
		} \
		while (temp != NULL) \
		{ \
			while (temp != NULL && !g_list_ ## T ## _cmp(temp->val, val)) \
			{ \
				prev = temp; \
				temp = temp->next; \
			} \
			if (temp == NULL) \
				return count; \
			prev->next = temp->next; \
			l->size -= 1; \
			++count; \
			if (temp == l->tail) \
				l->tail = prev; \
			free(temp); \
			temp = prev->next; \
		} \
		return count; \
	} \
	\
	static inline size_t g_list_ ## T ## _size(gl_##T* l) { \
		return l->size; \
	} \
	\
	static void FrontBackSplit_ ## T(node_ ## T ## _t* source, node_ ## T ## _t** frontRef, node_ ## T ## _t** backRef) \
	{ \
		node_ ## T ## _t* fast; \
		node_ ## T ## _t* slow; \
		slow = source; \
		fast = source->next; \
		while (fast != NULL) { \
			fast = fast->next; \
			if (fast != NULL) { \
				slow = slow->next; \
				fast = fast->next; \
			} \
		} \
		*frontRef = source; \
		*backRef = slow->next; \
		slow->next = NULL; \
	} \
	\
	static node_ ## T ## _t* SortedMerge_ ## T ## _2(node_ ## T ## _t*  a, node_ ## T ## _t*  b, int (*compare)(T a, T b)) \
	{ \
		node_ ## T ## _t* result = NULL; \
		if (a == NULL) \
			return (b); \
		else if (b == NULL) \
			return (a); \
		if (compare(a->val, b->val)) { \
			result = a; \
			result->next = SortedMerge_ ## T ## _2(a->next, b, compare); \
		} \
		else { \
			result = b; \
			result->next = SortedMerge_ ## T ## _2(a, b->next, compare); \
		} \
		return (result); \
	} \
	\
	static void g_list_ ## T ## _sort1 (node_ ## T ## _t** l) \
	{ \
		printf("Too few arguments for 'gl_sort'\ngl_sort(l);\n"); \
		exit(1); \
	} \
	\
	static void g_list_ ## T ## _sort2 (node_ ## T ## _t** l, int (*compare)(T a, T b)) \
	{ \
		node_ ## T ## _t* head = *l; \
		node_ ## T ## _t* a; \
		node_ ## T ## _t* b; \
		if ((head == NULL) || (head->next == NULL)) { \
			return; \
		} \
		FrontBackSplit_ ## T(head, &a, &b); \
		g_list_ ## T ## _sort2 (&a, compare); \
		g_list_ ## T ## _sort2 (&b, compare); \
		*l = SortedMerge_ ## T ## _2(a, b, compare); \
	} \
	typedef struct g_list_ ## T \

#endif