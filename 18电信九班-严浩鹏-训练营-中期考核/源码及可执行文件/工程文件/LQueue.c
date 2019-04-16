#include "LQueue.h"
#include <stdio.h>
extern FILE *Queuefp;
Status AddReaderAppointment(LQueue *Q, AppointNode data)
{
	AppointNode *NewAppointer=malloc(sizeof(AppointNode));//�����µĽڵ�
	NewAppointer->ReaderID = data.ReaderID;
	NewAppointer->BookID = data.BookID;
	NewAppointer->next = NULL;
	if (Q->front == NULL)
	{
		Q->front = NewAppointer;   //��һ��Ԫ�ؼ�¼�ڶ���
		Q->length++;
		fwrite(Q->front, sizeof(AppointNode), 1, Queuefp);  //д���ļ�
	}
	else
	{
		Q->rear = NewAppointer;   //��һ��֮���Ԫ���ڶ�β
		Q->rear->next = Q->rear;
		Q->length++;
		fwrite(Q->front, sizeof(AppointNode), 1, Queuefp);
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
