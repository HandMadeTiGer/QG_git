#include "LQueue.h"
#include <stdio.h>
extern FILE *Queuefp;
Status AddReaderAppointment(LQueue *Q, AppointNode data)
{
	AppointNode *NewAppointer=malloc(sizeof(AppointNode));//创建新的节点
	NewAppointer->ReaderID = data.ReaderID;
	NewAppointer->BookID = data.BookID;
	NewAppointer->next = NULL;
	if (Q->front == NULL)
	{
		Q->front = NewAppointer;   //第一个元素记录在队首
		Q->length++;
		fwrite(Q->front, sizeof(AppointNode), 1, Queuefp);  //写入文件
	}
	else
	{
		Q->rear = NewAppointer;   //第一个之后的元素在队尾
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
	AppointNode *temp = Q->front;  //暂存队首地址
	Q->length--;
	Q->front = Q->front->next;  //队首后移一位
	free(temp);  //释放队首空间
	return SUCCESS;
}
