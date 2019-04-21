#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include <stdio.h>
#include "../header/BinaryTree.h"
#include <stdlib.h>
typedef struct node
{
	BiTNode data;                   //数据域指针
	struct node *next;            //指向当前结点的下一结点
} Node;

typedef struct Lqueue
{
	Node *front;                   //队头
	Node *rear;                    //队尾
	size_t length;            //队列长度
} LQueue;
void InitQueue(LQueue *Q);
void DestoryLQueue(LQueue *Q);
void EnLQueue(LQueue *Q, BiTNode data);
BiTNode DeLQueue(LQueue *Q);

#endif