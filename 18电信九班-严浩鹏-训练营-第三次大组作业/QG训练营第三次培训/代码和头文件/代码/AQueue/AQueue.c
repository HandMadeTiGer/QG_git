#include "../../头文件/AQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**************************************************************
 *    Prototype Define Section
 **************************************************************/

/**
 *  @name        : void InitAQueue(AQueue *Q)
 *    @description : 初始化队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void InitAQueue(AQueue *Q)   
{
	Q->front = 0;
    Q->rear = 0;
    Q->length = 0;
}

/**
 *  @name        : void DestoryAQueue(AQueue *Q)
 *    @description : 销毁队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void DestoryAQueue(AQueue *Q)
{
	for (int i = Q->front; i < Q->front + Q->length; i++)
	{
		free(Q->data[i]);
		Q->data[i] = NULL;
	}
	Q->front = 0;
	Q->rear = 0;
	Q->length = 0;
}
/**
 *  @name        : Status IsFullAQueue(const AQueue *Q)
 *    @description : 检查队列是否已满
 *    @param         Q 队列指针Q
 *    @return         : 满-TRUE; 未满-FALSE
 *  @notice      : None
 */
Status IsFullAQueue(const AQueue *Q)
{
	if ((Q->rear+1)% MAXQUEUE == Q->front)   //循环队列判满条件
		return TRUE;
	else
		return FALSE;
}
/**
 *  @name        : Status IsEmptyAQueue(const AQueue *Q)
 *    @description : 检查队列是否为空
 *    @param         Q 队列指针Q
 *    @return         : 空-TRUE; 未空-FALSE
 *  @notice      : None
 */
Status IsEmptyAQueue(const AQueue *Q)
{
	if (Q->rear == Q->front)
		return TRUE;
	else
		return FALSE;
}


/**
 *  @name        : Status GetHeadAQueue(AQueue *Q, void *e)
 *    @description : 查看队头元素
 *    @param         Q 队列指针Q，存放元素e
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
 */
Status GetHeadAQueue(AQueue *Q, void **e)
{
	if (Q == NULL||IsEmptyAQueue(Q))
		return FALSE;
	else
		*e = Q->data[Q->front];
	return TRUE;
}

/**
 *  @name        : int LengthAQueue(AQueue *Q)
 *    @description : 确定队列长度
 *    @param         Q 队列指针Q
 *    @return         : 队列长度count
 *  @notice      : None
 */
int LengthAQueue(AQueue *Q)
{
	return ((Q->rear - Q->front + MAXQUEUE) % MAXQUEUE);  //循环队列的长度
}

/**
 *  @name        : Status EnAQueue(AQueue *Q, void *data)
 *    @description : 入队操作
 *    @param         Q 队列指针Q,入队数据指针data
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否满了或为空
 */
Status EnAQueue(AQueue *Q, void *data)
{
	if (Q == NULL || IsFullAQueue(Q))
		return FALSE;
	else
	{
		Q->data[Q->rear] = data;  //Q->data[Q->rear]为一个 void*指针，
		Q->rear++;
		Q->length++;
		if (Q->rear == MAXQUEUE)   //如果Q->rear 加1后等于MAXQUEUE，为规避假溢出情况，将它赋为0
			Q->rear = 0;
	}
	return TRUE;
}


/**
 *  @name        : Status DeAQueue(AQueue *Q)
 *    @description : 出队操作
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status DeAQueue(AQueue *Q)
{
	if (Q == NULL || IsEmptyAQueue(Q))
		return FALSE;
	else
	{
		free(Q->data[Q->front]);
		Q->data[Q->front] = NULL;
		Q->front++;
		Q->length--;
		if (Q->front == MAXQUEUE)   //如果Q->front 加1后等于MAXQUEUE，为规避假溢出情况，将它赋为0
			Q->front = 0;
	}
	return TRUE;
}


/**
 *  @name        : void ClearAQueue(Queue *Q)
 *    @description : 清空队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void ClearAQueue(AQueue *Q)
{
	for (int i = Q->front; i < (Q->front + Q->length); i++)
	{
		Q->data[i] = NULL;
	}
	Q->front = 0;
	Q->rear = 0;
	Q->length = 0;
}

/**
 *  @name        : Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q))
 *    @description : 遍历函数操作
 *    @param         Q 队列指针Q，操作函数指针foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q))  
{
	if (Q->data == NULL)
		return FALSE;
	for (int i = Q->front; i < (Q->front + Q->length); i++)
	{
		foo(Q->data[i]);
	}
	return TRUE;
}


/**
 *  @name        : void APrint(void *q)
 *    @description : 操作函数
 *    @param         q 指针q
 *  @notice      : None
 */
/*void APrint(void *q)     //对某些值会失效
{
	double Type = (*(double*)q / *(int*)q );
	if (((char*)q)[strlen((char*)q)-1] == 's')
		Type = 0;
	if (Type < 0)
	{
		if ((Type < 0 && *(double*)q>0))
			printf("%lf ", *(double*)q);
		else if ((Type < 0 && *(int*)q>0))
			printf("%d ", *(int*)q);
	}
	else if (Type > 0)
	{
		if (*(double*)q < 0)
			printf("%lf ", *(double*)q);
		else if (*(int*)q < 0)
			printf("%d ", *(int*)q);
	}
	else
	{
		for(int i=0;i< strlen((char*)q) - 1;i++)
			printf("%c", ((char*)q)[i]);
		printf(" ");
	}
}*/
void APrint(void *q)                            //elem_str的内容为												
{												//void *data;
	elem_str *temp = (elem_str*)q;				//int elemtype;  elemtype
	if (temp->elemtype == 0)					//为0 整型 为1 浮点 为2 字符串
		printf("%d ", *((int*)(temp->data)));
	else if (temp->elemtype == 1)
		printf("%lf ", *((double*)(temp->data)));
	else if (temp->elemtype == 2)
		printf("%s ", ((char*)(temp->data)));
}

