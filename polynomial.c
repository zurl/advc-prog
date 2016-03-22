#include <stdio.h>
#include <stdlib.h>

typedef struct __LinkList {
	int a,n;
	struct __LinkList * prev;
}LinkList;

LinkList * addNode(int a, int n, LinkList * prev) {
	LinkList * t = (LinkList *)malloc(sizeof(LinkList));
	t->a = a;
	t->n = n;
	t->prev = prev;
	return t;
}

LinkList * getList() {
	LinkList * ret = NULL;
	char str[1000],n=0;
	while ((str[n] = getchar()) != '\n')n++;
	int status = 1, tempInt = -1, symbol = 1,savedInt;
	//- spec
	int i = 0;
	if (str[i] == '-') { i++; symbol = -1; }
	for (; i <= n; i++) {
		if (str[i] >= '0' && str[i] <= '9') {
			if (tempInt == -1) {
				//last is not 0-9
				tempInt = str[i] - '0';
			}
			else {
				tempInt = tempInt * 10 + str[i] - '0';
			}
		}
		else if (str[i] == '+' || str[i] == '-') {
			if (status == 1) {
				//error
			}
			else {
				if (tempInt == -1)ret = addNode(savedInt, 1, ret);
				else ret = addNode(savedInt, tempInt, ret);
			}
			tempInt = -1;
			status = 1;
			symbol = str[i] == '-' ? -1 : 1;
		}
		else if (str[i] == 'x') {
			if (status == 1) {
				savedInt = tempInt * symbol;
				symbol = 1;
				tempInt = -1;
				status = 2;
			}
			else {
				//error
			}
		}
		else if (str[i] == '\n') {
			if (status == 1) {
				//const
				ret = addNode(tempInt * symbol, 0, ret);
			}
			else {
				//more
				if(tempInt == -1)ret = addNode(savedInt, 1, ret);
				else ret = addNode(savedInt, tempInt, ret);
			}
		}
		else {
			//error
		}
	}
	return ret;
}
void printList(LinkList * r) {
	if (r == NULL)
		printf("NULL");
	int flag = 0;
	while (r != NULL) {
		if (flag != 0 && r->a > 0)printf("+");
		if (!(r->n >= 1 && (r->a == 1 || r->a == -1)))printf("%d", r->a);
		if (r->n >= 1)printf("x");
		if (r->n > 1)printf("%d", r->n);
		r = r->prev;
		flag = 1;
	}
	printf("\n");
}
LinkList * add(LinkList * l1, LinkList * l2) {
	LinkList * ret = NULL;
	while (l1 != NULL && l2 != NULL) {
		if ( l1->n == l2->n ) {
			LinkList * t = addNode(l1->a + l2->a, l1->n, ret);
			if (t->a == 0)free(t);
			else ret = t;
			l1 = l1->prev;
			l2 = l2->prev;
		}
		else if(l1->n > l2->n) {
			ret = addNode(l2->a,l2->n,ret);
			l2 = l2->prev;
		}
		else {
			ret = addNode(l1->a, l1->n, ret);
			l1 = l1->prev;
		}
	}
	while (l1 != NULL) {
		ret = addNode(l1->a, l1->n, ret);
		l1 = l1->prev;
	}
	while (l2 != NULL) {
		ret = addNode(l2->a, l2->n, ret);
		l2 = l2->prev;
	}
	return ret;
}
void dfsFree(LinkList * l) {
	if (l->prev != NULL)dfsFree(l->prev);
	free(l);
}
LinkList * reverse(LinkList * l) {
	LinkList * ret = NULL;
	while (l != NULL) {
		LinkList * t = l->prev;
		l->prev = ret;
		ret = l;
		l = t;
	}
	return ret;
}
LinkList * mul(LinkList * l1, LinkList * l2) {
	LinkList * tmpret = NULL, * ret = NULL;
	while (l1 != NULL ) {
		LinkList * l3 = l2;
		while (l3 != NULL) {
			tmpret = addNode(l3->a * l1->a, l3->n + l1->n, tmpret);
			l3 = l3->prev;
		}
		tmpret = reverse(tmpret);
		printList(tmpret);
		ret = reverse(add(ret, tmpret));
		if(tmpret!=NULL)dfsFree(tmpret);
		tmpret = NULL;
		l1 = l1->prev;
	}
	return reverse(ret);
}
int main() {
	LinkList *l1 = getList();
	LinkList *l2 = getList();
	//LinkList *ret = merge(l1, l2);
	LinkList *sum = add(l1, l2);
	LinkList *product = mul(l1, l2);
	printList(sum);
	printList(product);
	return 0;
}