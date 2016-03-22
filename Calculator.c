#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAX 1000

enum OPE {
	REAL,
	SIN, COS, TAN, POW, ABS
};
typedef struct __Inode {
	int v;
	struct __Inode *prev;
}Inode;
typedef struct __Dnode {
	double v;
	struct __Dnode *prev;
}Dnode;
Dnode * ValueNode = NULL;
Inode * TokenNode = NULL;
void pushValueNode(double x) {
	Dnode * temp = ValueNode;
	ValueNode = (Dnode *)malloc(sizeof(Dnode));
	ValueNode->v = x;
	ValueNode->prev = temp;
}
void pushTokenNode(char x) {
	Inode * temp = TokenNode;
	TokenNode = (Inode *)malloc(sizeof(Inode));
	TokenNode->v = x;
	TokenNode->prev = temp;
}
void input(char * expr, int length) {
	char buffer[100];
	int onInteger = 0, onReal = 0 , onWord  = 0,tmpInteger = 0,tmpRealPos = 0,bufferNow = -1;
	for (int i = 0; i <= length ; i++) {
		if (expr[i] >= '0'&&expr[i] <= '9') {
			if (onInteger) {
				tmpInteger = tmpInteger * 10 + expr[i] - '0';
			}
			else if(onReal){
				tmpInteger = tmpInteger * 10 + expr[i] - '0';
				tmpRealPos *= 10;
			}
			else {
				tmpInteger = expr[i] - '0';
				onInteger = 1;
			}
		}
		else if (expr[i] >= 'a' && expr[i] <= 'z') {
			if (onWord) {
				buffer[++bufferNow] = expr[i];
			}
			else {
				bufferNow = 0;
				buffer[0] = expr[i];
				onWord = 1;
			}
		}
		else if (expr[i] == '.') {
			if (onInteger) {
				onInteger = 0;
				onReal = 1;
				tmpRealPos = 1;
			}
			else {
				//error
			}
		}
		else {
			//num deal
			if (onInteger) {
				pushValueNode(tmpInteger* 1.00);
				pushTokenNode('0');
				onInteger = 0;
			}
			else if (onReal) {
				pushValueNode(tmpInteger * 1.00 / tmpRealPos);
				pushTokenNode('0');
				onReal = 0;
			}
			else if (onWord) {
				if (buffer[0] == 's' && buffer[1] == 'i' && buffer[2] == 'n') {
					pushTokenNode(SIN);
				}
				else if (buffer[0] == 'c' && buffer[1] == 'o' && buffer[2] == 's') {
					pushTokenNode(COS);
				}
				else if (buffer[0] == 't' && buffer[1] == 'a' && buffer[2] == 'n') {
					pushTokenNode(TAN);
				}
				else if (buffer[0] == 'a' && buffer[1] == 'b' && buffer[2] == 's') {
					pushTokenNode(ABS);
				}
				onWord = 0;
			}
			else {
				//
			}
			//ope deal
			pushTokenNode(expr[i]);
		}
	}
}
Inode * OpeStackTail = NULL;
Dnode * ValStackTail = NULL;
void popValStack() {
	Dnode * temp = ValStackTail->prev;
	free(ValStackTail);
	ValStackTail = temp;
}
void popOpeStack() {
	Inode * temp = OpeStackTail->prev;
	free(OpeStackTail);
	OpeStackTail = temp;
}
void pushOpeStack(char x) {
	Inode * temp = OpeStackTail;
	OpeStackTail = (Inode *)malloc(sizeof(Inode));
	OpeStackTail->v = x;
	OpeStackTail->prev = temp;
}
void pushValStack(double x) {
	Dnode * temp = ValStackTail;
	ValStackTail = (Dnode *)malloc(sizeof(Dnode));
	ValStackTail->v = x;
	ValStackTail->prev = temp;
}
void popstack() {
	switch (OpeStackTail->v) {
	case '+':
		ValStackTail->prev->v += ValStackTail->v; popValStack(); break;
	case '-':
		ValStackTail->prev->v -= ValStackTail->v; popValStack(); break;
	case '*':
		ValStackTail->prev->v *= ValStackTail->v; popValStack(); break;
	case '/':
		ValStackTail->prev->v /= ValStackTail->v; popValStack(); break;
	case SIN:
		ValStackTail->v = sin(ValStackTail->v); break;
	case COS:
		ValStackTail->v = cos(ValStackTail->v); break;
	case TAN:
		ValStackTail->v = tan(ValStackTail->v); break;
	case ABS:
		ValStackTail->v = fabs(ValStackTail->v); break;
	}
	popOpeStack();
}
double work() {
	int numnow = -1;
	for (Inode * i = TokenNode; i != NULL;i=i->prev) {
		switch (i->v) {
		case '+':
		case '-':
			while (OpeStackTail != NULL && OpeStackTail->v != '(' )popstack();
			pushOpeStack(i->v);
			break;
		case '*':
		case '/':
			while (OpeStackTail != NULL  && OpeStackTail->v != '(' && OpeStackTail->v != '+' && OpeStackTail->v != '-')popstack();
			pushOpeStack(i->v);
			break;
		case '(':
			pushOpeStack(i->v);
			break;
		case ')':
			while (OpeStackTail != NULL && OpeStackTail->v != '(')popstack();
			popOpeStack();
			break;
		case SIN:
		case COS:
		case ABS:
		case TAN:
			pushOpeStack(i->v);
			break;
		case '0':
			pushValStack(ValueNode->v);
			ValueNode = ValueNode->prev;
			break;
		}
	}
	while(OpeStackTail != NULL)popstack();
	return ValStackTail->v;
}
void reverseLinkedList() {
	Dnode * result = NULL;
	while (ValueNode != NULL ) {
		Dnode * temp = result;
		result = (Dnode *)malloc(sizeof(Dnode));
		result->v = ValueNode->v;
		result->prev = temp;
		temp = ValueNode;
		ValueNode = ValueNode->prev;
		free(temp);
	}
	ValueNode = result;
	Inode * result2 = NULL;
	while (TokenNode != NULL) {
		Inode * temp = result2;
		result2 = (Inode *)malloc(sizeof(Inode));
		result2->v = TokenNode->v;
		result2->prev = temp;
		temp = TokenNode;
		TokenNode = TokenNode->prev;
		free(temp);
	}
	TokenNode = result2;
}
int main() {
	//main function
	char buffer[10000]; int now = -1;
	printf("Please input the expression :\n");
	while ((buffer[++now] = getchar()) != '\n');
	buffer[++now] = 0;
	input(buffer, now);
	reverseLinkedList();
	printf("result : %0.2lf", work());
 	return 0;
}