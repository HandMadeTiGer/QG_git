#include "../../ͷ�ļ�/LQueue.h"
#include <stdlib.h>
#include <stdio.h>
/**************************************************************
 *    Prototype Declare Section
 **************************************************************/


 /**
  *  @name        : void InitLQueue(LQueue *Q)
  *    @description : ��ʼ������
  *    @param         Q ����ָ��Q
  *  @notice      : None
  */
void InitLQueue(LQueue *Q)
{
	(*Q).front = malloc(sizeof(Node));    //��ͷβ����ռ�
	(*Q).rear = malloc(sizeof(Node));
	(*Q).rear->next = NULL;  //β����һ��ַΪ��
	(*Q).front->next = (*Q).rear;  //ͷ����һ��ַΪβ
	(*Q).front->data = NULL;   
	(*Q).length = 0;
}
/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *    @description : ���ٶ���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue *Q)
{
	Node *temp;    //temp��¼��ǰ�ڵ����һ�ڵ�
	while (Q->front != NULL)  //ֱ��Q->front����һ�ڵ�Ϊ��
	{
		temp = Q->front->next;
		free(Q->front);  //���ٵ�ǰ�Ľڵ�
		Q->front = NULL;
	}
//	free(Q->rear);  //����β�ڵ�
//	Q->rear = NULL;
	Q->length = 0;  
}
/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : �������Ƿ�Ϊ��
 *    @param         Q ����ָ��Q
 *    @return         : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue *Q)
{
	if (Q->front->data==NULL)  //Ϊ����ڵ���û�б������� dataΪ��
		return TRUE;
	else
		return FALSE;

}
/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : �鿴��ͷԪ��
 *    @param         Q e ����ָ��Q,��������ָ��e
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ��
 */
Status GetHeadLQueue(LQueue *Q, void **e) //����void*�ĵ�ַ�Ըı�void*��ָ��
{
	if (Q == NULL ||Q->front->data == NULL)   //����յ�ַ��û������ʱ���ܻ�ȡ��ͷ
		return FALSE;
	else
		*e = Q->front->data;  //��void* eָ�����Ԫ��
	return TRUE;
}
/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *    @description : ȷ�����г���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
int LengthLQueue(LQueue *Q)
{
	return Q->length;
}
/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : ��Ӳ���
 *    @param         Q ����ָ��Q,�������ָ��data
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ�Ϊ��
 */
Status EnLQueue(LQueue *Q, void *data)
{
	if (Q->front == NULL)   //�����׽ڵ�Ϊ��(�����в�����)ʱ�������
		return FALSE;
//	Node *temp,*temp1;
//	temp = malloc(sizeof(Node));
//	temp->next = NULL;
//	temp->data = data;
	if (Q->front->data == NULL)
	{
		Q->front->data = data;   //��һ��Ԫ�ؼ�¼�ڶ���
		Q->length++;
	}
	else
	{
		Q->rear->data = data;   //��һ��֮���Ԫ���ڶ�β
		Q->rear->next = malloc(sizeof(Node));
		Q->rear = Q->rear->next;   //�����ɺ󽫶�β�ƶ����ӵĺ���
		Q->rear->next = NULL;
		Q->length++;
	}
	return TRUE;
}
/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *    @description : ���Ӳ���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue *Q)
{
	if (Q == NULL||Q->front->data == NULL)
		return FALSE;
	Node *temp=Q->front;  //�ݴ���׵�ַ
	Q->length--;
	Q->front = Q->front->next;  //���׺���һλ
	free(temp);  //�ͷŶ��׿ռ�
	return TRUE;
}
/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *    @description : ��ն���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void ClearLQueue(LQueue *Q)
{
	Node *temp=Q->front;   //temp�ݴ���׵Ľڵ��ַ
	while (temp != Q->rear)  //ֱ��temp�ƶ���β����β��ָ���κ�Ԫ�أ���ʱ�Ѿ����������е�Ԫ��
	{
		temp->data = NULL;
		temp = temp->next;
	}
	Q->rear->data = NULL;  
	Q->length = 0;
}
/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *    @description : ������������
 *    @param         Q ����ָ��Q����������ָ��foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue *Q, void(*foo)(void *q))
{
	if (Q == NULL ||Q->front->data == NULL)
		return FALSE;
	Node *temp = Q->front;
	while (temp != Q->rear)
	{
		foo(temp->data);
		temp = temp->next;
	}
	return TRUE;
}
/**
 *  @name        : void LPrint(void *q)
 *    @description : ��������
 *    @param         q ָ��q

 *  @notice      : None
 */
void LPrint(void *q)
{
	elem_str *temp = (elem_str*)q;					//elem_str������Ϊ
	if (temp->elemtype == 0)						//void *data;
		printf("%d ", *((int*)(temp->data)));		//int elemtype;  elemtype
	else if (temp->elemtype == 1)					//Ϊ0 ���� Ϊ1 ���� Ϊ2 �ַ���
		printf("%lf ", *((double*)(temp->data)));
	else if (temp->elemtype == 2)
		printf("%s ", ((char*)(temp->data)));
}
/**************************************************************
 *    End-Multi-Include-Prevent Section
 **************************************************************/