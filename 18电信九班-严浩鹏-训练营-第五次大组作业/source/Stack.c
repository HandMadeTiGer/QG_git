#include "../header/Stack.h"
//�ǵݹ������Ҫ�õ�ջ
Status InitStack(LinkStack *s)
{
	if (s == NULL)
		return ERROR;
	s->count = 0;
	s->top = NULL;
	return SUCCESS;
}
Status destroyLStack(LinkStack *s)   //����ջ
{
	if (s == NULL)  //���жϴ���ĵ�ַ�Ƿ����ջ
		return ERROR;
	StackNode *p = (StackNode*)malloc(sizeof(StackNode)); //p�ݴ�s->top->next
	while (s->top != NULL)
	{
		p = s->top->next;
		free(s->top);  //�ͷŵ�ǰ���
		s->top = p;
	}
	s->count = 0;
	return SUCCESS;
}
Status isEmptyLStack(LinkStack *s)  //�ж���ջ�Ƿ�Ϊ��
{
	if (s->top == NULL || s->count == 0)  //s->top=NULLջΪ��
		return SUCCESS;
	return ERROR;
}
Status pushLStack(LinkStack *s, BiTNode data)   //��ջ
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
BiTNode popLStack(LinkStack *s)   //��ջ
{
	BiTNode data;
	StackNode *p = (StackNode*)malloc(sizeof(StackNode));  //p���Ҫ��ջ�Ľ��
	s->count--;
	p = s->top;
	data = p->data;
	s->top = s->top->next;		//topָ��ԭ������һ�����	
	free(p);
	return data;
}