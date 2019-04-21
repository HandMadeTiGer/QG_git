#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "../header/BinaryTree.h"
#include <stdlib.h>
typedef  struct StackNode
{
	BiTNode data;
	struct StackNode *next;
}StackNode, *LinkStackPtr;

typedef  struct  LinkStack {
	LinkStackPtr top;
	int	count;
}LinkStack;
Status InitStack(LinkStack *s);
Status destroyLStack(LinkStack *s);
Status isEmptyLStack(LinkStack *s);
Status pushLStack(LinkStack *s, BiTNode data);
BiTNode popLStack(LinkStack *s);
#endif