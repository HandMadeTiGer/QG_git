#ifndef LQUEUE_H_INCLUDED
#define LQUEUE_H_INCLUDED
#include <stdlib.h>
typedef enum Status {
	ERROR,
	SUCCESS
} Status;
//����ʵ��ԤԼ����
typedef struct AppointQNode
{
	long long ReaderID;			 //ԤԼ��ID
	int BookID;
	struct AppointQNode *next;
}AppointNode;
typedef struct LQueue
{
	AppointNode *front;                   //��ͷ
	AppointNode *rear;                    //��β
	size_t length;            //���г���
}LQueue;
Status AddReaderAppointment(LQueue *Q, AppointNode data);
Status DeLReaderAppointment(LQueue *Q);
#endif
