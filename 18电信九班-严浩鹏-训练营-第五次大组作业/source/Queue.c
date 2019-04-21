#include "../header/Queue.h"
//��α�����Ҫ�õ��Ķ���
void InitQueue(LQueue *Q)
{
	Q->front = malloc(sizeof(Node));    //��ͷβ����ռ�
	Q->rear = malloc(sizeof(Node));
	Q->rear->next = NULL;  //β����һ��ַΪ��
	Q->front->next = Q->rear;  //ͷ����һ��ַΪβ
	Q->front->data.data = '\0';
	Q->front->data.lchild = NULL;
	Q->front->data.rchild = NULL;
	Q->length = 0;
}
void DestoryLQueue(LQueue *Q)
{
	Node *temp;    //temp��¼��ǰ�ڵ����һ�ڵ�
	while (Q->front != NULL)  //ֱ��Q->front����һ�ڵ�Ϊ��
	{
		temp = Q->front->next;
		free(Q->front);  //���ٵ�ǰ�Ľڵ�
		Q->front = NULL;
	}
	Q->length = 0;
}
void EnLQueue(LQueue *Q, BiTNode data)
{
	if (Q->length == 0)
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
}
BiTNode DeLQueue(LQueue *Q)
{
	Node *temp = Q->front;  //�ݴ���׵�ַ
	BiTNode t = Q->front->data;
	Q->length--;
	Q->front = Q->front->next;  //���׺���һλ
	free(temp);  //�ͷŶ��׿ռ�
	return t;
}