#include "../header/Queue.h"
//层次遍历需要用到的队列
void InitQueue(LQueue *Q)
{
	Q->front = malloc(sizeof(Node));    //给头尾分配空间
	Q->rear = malloc(sizeof(Node));
	Q->rear->next = NULL;  //尾的下一地址为空
	Q->front->next = Q->rear;  //头的下一地址为尾
	Q->front->data.data = '\0';
	Q->front->data.lchild = NULL;
	Q->front->data.rchild = NULL;
	Q->length = 0;
}
void DestoryLQueue(LQueue *Q)
{
	Node *temp;    //temp记录当前节点的下一节点
	while (Q->front != NULL)  //直到Q->front的下一节点为空
	{
		temp = Q->front->next;
		free(Q->front);  //销毁当前的节点
		Q->front = NULL;
	}
	Q->length = 0;
}
void EnLQueue(LQueue *Q, BiTNode data)
{
	if (Q->length == 0)
	{
		Q->front->data = data;   //第一个元素记录在队首
		Q->length++;
	}
	else
	{
		Q->rear->data = data;   //第一个之后的元素在队尾
		Q->rear->next = malloc(sizeof(Node));
		Q->rear = Q->rear->next;   //入队完成后将队尾移动到队的后面
		Q->rear->next = NULL;
		Q->length++;
	}
}
BiTNode DeLQueue(LQueue *Q)
{
	Node *temp = Q->front;  //暂存队首地址
	BiTNode t = Q->front->data;
	Q->length--;
	Q->front = Q->front->next;  //队首后移一位
	free(temp);  //释放队首空间
	return t;
}