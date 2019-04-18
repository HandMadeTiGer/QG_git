#ifndef LQUEUE_H_INCLUDED
#define LQUEUE_H_INCLUDED
#include <stdlib.h>
typedef enum Status {
	ERROR,
	SUCCESS
} Status;
//队列实现预约借书
typedef struct AppointQNode
{
	long long ReaderID;			 //预约者ID
	int BookID;
	struct AppointQNode *next;
}AppointNode;
typedef struct LQueue
{
	AppointNode *front;                   //队头
	AppointNode *rear;                    //队尾
	size_t length;            //队列长度
}LQueue;
Status AddReaderAppointment(LQueue *Q, AppointNode data);
Status DeLReaderAppointment(LQueue *Q);
#endif
