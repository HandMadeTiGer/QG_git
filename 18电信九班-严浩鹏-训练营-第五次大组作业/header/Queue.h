#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include <stdio.h>
#include "../header/BinaryTree.h"
#include <stdlib.h>
typedef struct node
{
	BiTNode data;                   //������ָ��
	struct node *next;            //ָ��ǰ������һ���
} Node;

typedef struct Lqueue
{
	Node *front;                   //��ͷ
	Node *rear;                    //��β
	size_t length;            //���г���
} LQueue;
void InitQueue(LQueue *Q);
void DestoryLQueue(LQueue *Q);
void EnLQueue(LQueue *Q, BiTNode data);
BiTNode DeLQueue(LQueue *Q);

#endif