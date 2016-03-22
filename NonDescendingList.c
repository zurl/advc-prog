#include <stdio.h>
#include <stdlib.h>

typedef struct __LinkList {
	int value;
	struct __LinkList * prev;
}LinkList;

LinkList * getList() {
	int temp; LinkList * ret = NULL;
	scanf("%d", &temp);
	while (temp != -1) {
		LinkList * a = (LinkList *)malloc(sizeof(LinkList));
		a->prev = ret;
		a->value = temp;
		ret = a;
		scanf("%d", &temp);
	}
	return ret;
}

LinkList * merge(LinkList * l1, LinkList * l2) {
	LinkList * ret = NULL;
	while (l1 != NULL && l2 != NULL) {
		if ( l1->value > l2->value ) {
			LinkList * tmp = l1->prev;
			l1->prev = ret;
			ret = l1;
			l1 = tmp;
		}
		else {
			LinkList * tmp = l2->prev;
			l2->prev = ret;
			ret = l2;
			l2 = tmp;
		}
	}
	while (l1 != NULL) {
		LinkList * tmp = l1->prev;
		l1->prev = ret;
		ret = l1;
		l1 = tmp;
	}
	while (l2 != NULL) {
		LinkList * tmp = l2->prev;
		l2->prev = ret;
		ret = l2;
		l2 = tmp;
	}
	return ret;
}
void printList(LinkList * r) {
	if (r == NULL)
		printf("NULL");
	while (r != NULL) {
		printf("%d ", r->value);
		r = r->prev;
	}
	printf("\n");
}
int main() {
	LinkList *l1 = getList();
	LinkList *l2 = getList();
	LinkList *ret = merge(l1, l2);
	printList(ret);
	return 0;
}