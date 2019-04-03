#include "../head/SqStack.h"

//顺序栈(基于数组的)
Status initStack(SqStack *s,int sizes)  //初始化栈
{
	if (s->elem == NULL)       //若elem为空则给它分配元素
		s->elem = (ElemType *)malloc(sizes * sizeof(ElemType));
	else
		return ERROR;
    if(s->elem==NULL)    //若分配内存失败
        return ERROR;
    s->top=-1;
    s->size=sizes;
    return SUCCESS;
}
Status isEmptyStack(SqStack *s)   //判断栈是否为空
{
    if(s->top==-1||s==NULL)
        return SUCCESS;
    return ERROR;
}
Status getTopStack(SqStack *s,ElemType *e)   //得到栈顶元素
{
    if(isEmptyStack(s))  //为空返回ERROR
        return ERROR;
    *e=s->elem[s->top];
    return SUCCESS;
}
Status clearStack(SqStack *s)   //清空栈
{
    if(isEmptyStack(s))
        return ERROR;
    s->top=-1;   
    return SUCCESS;
}
Status destroyStack(SqStack *s)  //销毁栈
{
    if(s==NULL)
        return ERROR;
	s->top = -1;
	s->size = 0;
	free(s->elem);   //释放s->elem
	s->elem=NULL;    //使s->elem指向空以进行初始化
    return SUCCESS;
}
Status stackLength(SqStack *s,int *length)   //检测栈长度
{
    if(isEmptyStack(s))
        return ERROR;
    *length=s->top+1;    //top从0开始，+1即为栈长度
    return SUCCESS;
}
Status pushStack(SqStack *s,ElemType data)  //入栈
{
    if(s==NULL||(s->top)>=(s->size-1)) //栈为空或已满时不能入栈
        return ERROR;
    s->top++;
    s->elem[s->top]=data;
    return SUCCESS;
}
Status popStack(SqStack *s,ElemType *data)   //出栈
{
    if(isEmptyStack(s))
        return ERROR;
    *data=s->elem[s->top];
    s->top--;
    return SUCCESS;
}

