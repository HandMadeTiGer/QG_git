#include "../head/SqStack.h"

//˳��ջ(���������)
Status initStack(SqStack *s,int sizes)  //��ʼ��ջ
{
	if (s->elem == NULL)       //��elemΪ�����������Ԫ��
		s->elem = (ElemType *)malloc(sizes * sizeof(ElemType));
	else
		return ERROR;
    if(s->elem==NULL)    //�������ڴ�ʧ��
        return ERROR;
    s->top=-1;
    s->size=sizes;
    return SUCCESS;
}
Status isEmptyStack(SqStack *s)   //�ж�ջ�Ƿ�Ϊ��
{
    if(s->top==-1||s==NULL)
        return SUCCESS;
    return ERROR;
}
Status getTopStack(SqStack *s,ElemType *e)   //�õ�ջ��Ԫ��
{
    if(isEmptyStack(s))  //Ϊ�շ���ERROR
        return ERROR;
    *e=s->elem[s->top];
    return SUCCESS;
}
Status clearStack(SqStack *s)   //���ջ
{
    if(isEmptyStack(s))
        return ERROR;
    s->top=-1;   
    return SUCCESS;
}
Status destroyStack(SqStack *s)  //����ջ
{
    if(s==NULL)
        return ERROR;
	s->top = -1;
	s->size = 0;
	free(s->elem);   //�ͷ�s->elem
	s->elem=NULL;    //ʹs->elemָ����Խ��г�ʼ��
    return SUCCESS;
}
Status stackLength(SqStack *s,int *length)   //���ջ����
{
    if(isEmptyStack(s))
        return ERROR;
    *length=s->top+1;    //top��0��ʼ��+1��Ϊջ����
    return SUCCESS;
}
Status pushStack(SqStack *s,ElemType data)  //��ջ
{
    if(s==NULL||(s->top)>=(s->size-1)) //ջΪ�ջ�����ʱ������ջ
        return ERROR;
    s->top++;
    s->elem[s->top]=data;
    return SUCCESS;
}
Status popStack(SqStack *s,ElemType *data)   //��ջ
{
    if(isEmptyStack(s))
        return ERROR;
    *data=s->elem[s->top];
    s->top--;
    return SUCCESS;
}

