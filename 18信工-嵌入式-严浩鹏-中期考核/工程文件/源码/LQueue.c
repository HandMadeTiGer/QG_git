#include "../ͷ�ļ�/LQueue.h"
#include <stdio.h>
extern FILE *Queuefp;
//TODO  �����������
Status AddReaderAppointment(LQueue *Q, AppointNode data)
{
	AppointNode *NewAppointer = malloc(sizeof(AppointNode));//�����µĽڵ�
	NewAppointer->ReaderID = data.ReaderID;
	NewAppointer->BookID = data.BookID;
	NewAppointer->next = NULL;
	if (Q->front == NULL)
	{
		Q->front = NewAppointer;   //��һ��Ԫ�ؼ�¼�ڶ���
		Q->rear = malloc(sizeof(AppointNode));
		Q->rear->next = NULL;
		Q->front->next = Q->rear;
		Q->length++;
		fwrite(Q->front, sizeof(AppointNode), 1, Queuefp);  //д���ļ�
	//	Q->rear = NULL;
	//	Q->front->next = Q->rear;
	}
	else
	{
		Q->rear->BookID= data.BookID;   
		Q->rear->ReaderID = data.ReaderID;//��һ��֮���Ԫ���ڶ�β
		Q->rear->next = malloc(sizeof(AppointNode));
		fwrite(Q->rear, sizeof(AppointNode), 1, Queuefp);
		Q->rear = Q->rear->next;
		Q->rear->next = NULL;
		Q->length++;
	}
	return SUCCESS;
}
Status DeLReaderAppointment(LQueue *Q)
{
	if (Q->front == NULL)
		return ERROR;
	AppointNode *temp = Q->front;  //�ݴ���׵�ַ
	Q->length--;
	Q->front = Q->front->next;  //���׺���һλ
	free(temp);  //�ͷŶ��׿ռ�
	return SUCCESS;
}
