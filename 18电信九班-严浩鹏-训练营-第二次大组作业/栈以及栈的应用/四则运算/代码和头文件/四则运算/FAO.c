#include "../head/FAO.h"
#include <stdlib.h>
#include <stdio.h>
//��ջ����
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
//������
Status InitList(LinkedList *L) {
	//	if(*L==NULL)  
	//		return ERROR;
	*L = NULL;
	return SUCCESS;
}
Status InsertList(LNode *p, LNode *q) {
	if (p == NULL)
		return ERROR;
	LNode *NodeNext2p = p->next; //��¼p��ԭ��һ�ڵ� 
	p->next = q;
	q->next = NodeNext2p;
	return SUCCESS;
}
void DestroyList(LinkedList *L) {
	LNode *CurrentNode = *L; //���� LNode* �ͱ����洢���ڽڵ��ַ��ͬʱ��L��ֵ��CurrentNode 
	while (*L) //ֱ������β�� 
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
		if (Rule2OperatorInp(L->next->data.Operator))//����������������OperatorΪ����������Operator
			printf("%c ", L->next->data.Operator);         
		else                                          //��Ϊ��������Num
			printf("%lf ", L->next->data.Num);
		L = L->next;
	}
}

//
Status Rule2OperatorInp(char inp)
{												//�ж��Ƿ�Ϊ�����
	if (inp == '(' || inp == ')' || inp == '+' || inp == '-' || inp == '*' || inp == '/')
		return SUCCESS;
	return ERROR;
}
Status PriorityRule(LinkStack *s, char inp) //��������ȼ��ж�
{
	if (s->top == NULL)					//ջΪ��ֱ��ѹջ
		return SUCCESS;
	char CurOP = s->top->data.Operator;     //�ݴ浱ǰ������
	if (inp == '*' || inp == '/')
	{
		if (CurOP == '*' || CurOP == '/')    //��ջ��Ϊ ��/���� ��*�� ���
			return ERROR;
		else                                 //����ѹջ
			return SUCCESS;

	}
	else if ((inp == '+' || inp == '-'))
	{
		if (s->top->data.Operator == '(')    //��ǰ����� ( ��ѹջ
			return SUCCESS;
		return ERROR;             //�������
	}
	else
		return ERROR;
}