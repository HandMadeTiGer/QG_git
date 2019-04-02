#include "../head/LinkStack.h"
#include <stdlib.h>
//链栈(基于链表的)
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
Status getTopLStack(LinkStack *s, ElemType *e)  //得到栈顶元素
{
	if (s == NULL || isEmptyLStack(s))
		return ERROR;
	*e = s->top->data;    //将s->top->data的值传给e
	return SUCCESS;
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
Status destroyLStack(LinkStack *s)   //销毁栈
{
	if (s == NULL)  //先判断传入的地址是否存在栈
		return ERROR;
	StackNode *p = (StackNode*)malloc(sizeof(StackNode)); //p暂存s->top->next
	while (s->top != NULL)
	{
		s->top->data = 0;
		p = s->top->next;
		free(s->top);  //释放当前结点
		s->top = p;
	}
	s->count = 0;
	return SUCCESS;
}
Status LStackLength(LinkStack *s, int *length)    //检测栈长度
{
	if (s == NULL || s->top == NULL)
		return ERROR;
	*length=s->count;  //将count，即结点数量传给length
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