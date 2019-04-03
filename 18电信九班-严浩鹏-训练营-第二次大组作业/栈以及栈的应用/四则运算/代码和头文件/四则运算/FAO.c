#include "../head/FAO.h"
#include <stdlib.h>
#include <stdio.h>
//链栈部分
Status initLStack(LinkStack *s)   //初始化
{
	if (s != NULL)  //s没有被销毁
		return ERROR;
	s->top = NULL;
	s->count = 0;
	return SUCCESS;
}
Status isEmptyLStack(LinkStack *s)  //判断链栈是否为空
{
	if (s->top == NULL || s->count == 0)  //s->top=NULL栈为空
		return SUCCESS;
	return ERROR;
}
Status clearLStack(LinkStack *s)   //清空栈
{
	if (s == NULL || isEmptyLStack(s))
		return ERROR;
	while (s->top != NULL)  //直到栈为空
	{
		s->top = s->top->next;  //将下一个结点的地址传给s->top
	}
	s->count = 0;  //元素数目置零
	return SUCCESS;
}
Status pushLStack(LinkStack *s, ElemType data)   //入栈
{
	if (s == NULL)
		return ERROR;
	StackNode *p = (StackNode*)malloc(sizeof(StackNode));  //p存放要入栈的结点
	s->count++;
	p->data = data;
	p->next = s->top;
	s->top = p;  //使top指向p，让p成为最上面的结点
	return SUCCESS;
}
Status popLStack(LinkStack *s, ElemType *data)   //出栈
{
	if (s == NULL || isEmptyLStack(s))
		return ERROR;
	StackNode *p = (StackNode*)malloc(sizeof(StackNode));  //p存放要出栈的结点
	s->count--;
	p = s->top;
	*data = p->data;
	s->top = s->top->next;		//top指向原来的下一个结点	
	free(p);
	return SUCCESS;
}
//链表部分
Status InitList(LinkedList *L) {
	//	if(*L==NULL)  
	//		return ERROR;
	*L = NULL;
	return SUCCESS;
}
Status InsertList(LNode *p, LNode *q) {
	if (p == NULL)
		return ERROR;
	LNode *NodeNext2p = p->next; //记录p的原下一节点 
	p->next = q;
	q->next = NodeNext2p;
	return SUCCESS;
}
void DestroyList(LinkedList *L) {
	LNode *CurrentNode = *L; //定义 LNode* 型变量存储现在节点地址，同时把L赋值给CurrentNode 
	while (*L) //直到链表尾部 
	{
		CurrentNode = *L;
		*L = CurrentNode->next;
		free(CurrentNode);
	}
}
void TraverseList(LinkedList L) {
//	L=L->next;
	while (L->next != NULL)
	{
		if (Rule2OperatorInp(L->next->data.Operator))//遍历链表，当联合中Operator为运算符，输出Operator
			printf("%c ", L->next->data.Operator);         
		else                                          //不为运算符输出Num
			printf("%lf ", L->next->data.Num);
		L = L->next;
	}
}

//
Status Rule2OperatorInp(char inp)
{												//判断是否为运算符
	if (inp == '(' || inp == ')' || inp == '+' || inp == '-' || inp == '*' || inp == '/')
		return SUCCESS;
	return ERROR;
}
Status PriorityRule(LinkStack *s, char inp) //运算符优先级判断
{
	if (s->top == NULL)					//栈为空直接压栈
		return SUCCESS;
	char CurOP = s->top->data.Operator;     //暂存当前操作符
	if (inp == '*' || inp == '/')
	{
		if (CurOP == '*' || CurOP == '/')    //若栈中为 ‘/’或 ‘*’ 输出
			return ERROR;
		else                                 //否则压栈
			return SUCCESS;

	}
	else if ((inp == '+' || inp == '-'))
	{
		if (s->top->data.Operator == '(')    //若前面存在 ( 则压栈
			return SUCCESS;
		return ERROR;             //否则输出
	}
	else
		return ERROR;
}