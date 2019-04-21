#include "../header/Stack.h"
//非递归遍历需要用到栈
Status InitStack(LinkStack *s)
{
	if (s == NULL)
		return ERROR;
	s->count = 0;
	s->top = NULL;
	return SUCCESS;
}
Status destroyLStack(LinkStack *s)   //销毁栈
{
	if (s == NULL)  //先判断传入的地址是否存在栈
		return ERROR;
	StackNode *p = (StackNode*)malloc(sizeof(StackNode)); //p暂存s->top->next
	while (s->top != NULL)
	{
		p = s->top->next;
		free(s->top);  //释放当前结点
		s->top = p;
	}
	s->count = 0;
	return SUCCESS;
}
Status isEmptyLStack(LinkStack *s)  //判断链栈是否为空
{
	if (s->top == NULL || s->count == 0)  //s->top=NULL栈为空
		return SUCCESS;
	return ERROR;
}
Status pushLStack(LinkStack *s, BiTNode data)   //入栈
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
BiTNode popLStack(LinkStack *s)   //出栈
{
	BiTNode data;
	StackNode *p = (StackNode*)malloc(sizeof(StackNode));  //p存放要出栈的结点
	s->count--;
	p = s->top;
	data = p->data;
	s->top = s->top->next;		//top指向原来的下一个结点	
	free(p);
	return data;
}