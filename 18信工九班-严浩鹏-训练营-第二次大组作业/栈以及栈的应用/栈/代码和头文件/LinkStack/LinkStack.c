#include "../head/LinkStack.h"
#include <stdlib.h>
//��ջ(���������)
Status initLStack(LinkStack *s)   //��ʼ��
{
	if (s != NULL)  //sû�б�����
		return ERROR;
	s->top = NULL;
	s->count = 0;
	return SUCCESS;
}
Status isEmptyLStack(LinkStack *s)  //�ж���ջ�Ƿ�Ϊ��
{
	if (s->top == NULL || s->count == 0)  //s->top=NULLջΪ��
		return SUCCESS;
	return ERROR;
}
Status getTopLStack(LinkStack *s, ElemType *e)  //�õ�ջ��Ԫ��
{
	if (s == NULL || isEmptyLStack(s))
		return ERROR;
	*e = s->top->data;    //��s->top->data��ֵ����e
	return SUCCESS;
}
Status clearLStack(LinkStack *s)   //���ջ
{
	if (s == NULL || isEmptyLStack(s))
		return ERROR;
	while (s->top != NULL)  //ֱ��ջΪ��
	{
		s->top = s->top->next;  //����һ�����ĵ�ַ����s->top
	}
	s->count = 0;  //Ԫ����Ŀ����
	return SUCCESS;
}
Status destroyLStack(LinkStack *s)   //����ջ
{
	if (s == NULL)  //���жϴ���ĵ�ַ�Ƿ����ջ
		return ERROR;
	StackNode *p = (StackNode*)malloc(sizeof(StackNode)); //p�ݴ�s->top->next
	while (s->top != NULL)
	{
		s->top->data = 0;
		p = s->top->next;
		free(s->top);  //�ͷŵ�ǰ���
		s->top = p;
	}
	s->count = 0;
	return SUCCESS;
}
Status LStackLength(LinkStack *s, int *length)    //���ջ����
{
	if (s == NULL || s->top == NULL)
		return ERROR;
	*length=s->count;  //��count���������������length
	return SUCCESS;
}
Status pushLStack(LinkStack *s, ElemType data)   //��ջ
{
	if (s == NULL)
		return ERROR;
	StackNode *p = (StackNode*)malloc(sizeof(StackNode));  //p���Ҫ��ջ�Ľ��
	s->count++;
	p->data = data;
	p->next = s->top;
	s->top = p;  //ʹtopָ��p����p��Ϊ������Ľ��
	return SUCCESS;
}
Status popLStack(LinkStack *s, ElemType *data)   //��ջ
{
	if (s == NULL || isEmptyLStack(s))
		return ERROR;
	StackNode *p = (StackNode*)malloc(sizeof(StackNode));  //p���Ҫ��ջ�Ľ��
	s->count--;
	p = s->top;		
	*data = p->data;	
	s->top = s->top->next;		//topָ��ԭ������һ�����	
	free(p);
	return SUCCESS;
}