#include "../../ͷ�ļ�/AQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**************************************************************
 *    Prototype Define Section
 **************************************************************/

/**
 *  @name        : void InitAQueue(AQueue *Q)
 *    @description : ��ʼ������
 *    @param         Q ����ָ��Q
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
 *    @description : ���ٶ���
 *    @param         Q ����ָ��Q
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
 *    @description : �������Ƿ�����
 *    @param         Q ����ָ��Q
 *    @return         : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsFullAQueue(const AQueue *Q)
{
	if ((Q->rear+1)% MAXQUEUE == Q->front)   //ѭ��������������
		return TRUE;
	else
		return FALSE;
}
/**
 *  @name        : Status IsEmptyAQueue(const AQueue *Q)
 *    @description : �������Ƿ�Ϊ��
 *    @param         Q ����ָ��Q
 *    @return         : ��-TRUE; δ��-FALSE
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
 *    @description : �鿴��ͷԪ��
 *    @param         Q ����ָ��Q�����Ԫ��e
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ��
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
 *    @description : ȷ�����г���
 *    @param         Q ����ָ��Q
 *    @return         : ���г���count
 *  @notice      : None
 */
int LengthAQueue(AQueue *Q)
{
	return ((Q->rear - Q->front + MAXQUEUE) % MAXQUEUE);  //ѭ�����еĳ���
}

/**
 *  @name        : Status EnAQueue(AQueue *Q, void *data)
 *    @description : ��Ӳ���
 *    @param         Q ����ָ��Q,�������ָ��data
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ����˻�Ϊ��
 */
Status EnAQueue(AQueue *Q, void *data)
{
	if (Q == NULL || IsFullAQueue(Q))
		return FALSE;
	else
	{
		Q->data[Q->rear] = data;  //Q->data[Q->rear]Ϊһ�� void*ָ�룬
		Q->rear++;
		Q->length++;
		if (Q->rear == MAXQUEUE)   //���Q->rear ��1�����MAXQUEUE��Ϊ��ܼ���������������Ϊ0
			Q->rear = 0;
	}
	return TRUE;
}


/**
 *  @name        : Status DeAQueue(AQueue *Q)
 *    @description : ���Ӳ���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
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
		if (Q->front == MAXQUEUE)   //���Q->front ��1�����MAXQUEUE��Ϊ��ܼ���������������Ϊ0
			Q->front = 0;
	}
	return TRUE;
}


/**
 *  @name        : void ClearAQueue(Queue *Q)
 *    @description : ��ն���
 *    @param         Q ����ָ��Q
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
 *    @description : ������������
 *    @param         Q ����ָ��Q����������ָ��foo
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
 *    @description : ��������
 *    @param         q ָ��q
 *  @notice      : None
 */
/*void APrint(void *q)     //��ĳЩֵ��ʧЧ
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
void APrint(void *q)                            //elem_str������Ϊ												
{												//void *data;
	elem_str *temp = (elem_str*)q;				//int elemtype;  elemtype
	if (temp->elemtype == 0)					//Ϊ0 ���� Ϊ1 ���� Ϊ2 �ַ���
		printf("%d ", *((int*)(temp->data)));
	else if (temp->elemtype == 1)
		printf("%lf ", *((double*)(temp->data)));
	else if (temp->elemtype == 2)
		printf("%s ", ((char*)(temp->data)));
}

