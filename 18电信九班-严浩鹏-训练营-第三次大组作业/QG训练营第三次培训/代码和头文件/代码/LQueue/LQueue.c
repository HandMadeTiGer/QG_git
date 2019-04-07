#include "../../头文件/LQueue.h"
#include <stdlib.h>
#include <stdio.h>
/**************************************************************
 *    Prototype Declare Section
 **************************************************************/


 /**
  *  @name        : void InitLQueue(LQueue *Q)
  *    @description : 初始化队列
  *    @param         Q 队列指针Q
  *  @notice      : None
  */
void InitLQueue(LQueue *Q)
{
	(*Q).front = malloc(sizeof(Node));    //给头尾分配空间
	(*Q).rear = malloc(sizeof(Node));
	(*Q).rear->next = NULL;  //尾的下一地址为空
	(*Q).front->next = (*Q).rear;  //头的下一地址为尾
	(*Q).front->data = NULL;   
	(*Q).length = 0;
}
/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *    @description : 销毁队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue *Q)
{
	Node *temp;    //temp记录当前节点的下一节点
	while (Q->front != NULL)  //直到Q->front的下一节点为空
	{
		temp = Q->front->next;
		free(Q->front);  //销毁当前的节点
		Q->front = NULL;
	}
//	free(Q->rear);  //销毁尾节点
//	Q->rear = NULL;
	Q->length = 0;  
}
/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : 检查队列是否为空
 *    @param         Q 队列指针Q
 *    @return         : 空-TRUE; 未空-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue *Q)
{
	if (Q->front->data==NULL)  //为空则节点中没有保存数据 data为空
		return TRUE;
	else
		return FALSE;

}
/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : 查看队头元素
 *    @param         Q e 队列指针Q,返回数据指针e
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
 */
Status GetHeadLQueue(LQueue *Q, void **e) //传入void*的地址以改变void*的指向
{
	if (Q == NULL ||Q->front->data == NULL)   //传入空地址或没有数据时不能获取队头
		return FALSE;
	else
		*e = Q->front->data;  //让void* e指向队首元素
	return TRUE;
}
/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *    @description : 确定队列长度
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
int LengthLQueue(LQueue *Q)
{
	return Q->length;
}
/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : 入队操作
 *    @param         Q 队列指针Q,入队数据指针data
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否为空
 */
Status EnLQueue(LQueue *Q, void *data)
{
	if (Q->front == NULL)   //当队首节点为空(即队列不存在)时不能入队
		return FALSE;
//	Node *temp,*temp1;
//	temp = malloc(sizeof(Node));
//	temp->next = NULL;
//	temp->data = data;
	if (Q->front->data == NULL)
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
	return TRUE;
}
/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *    @description : 出队操作
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue *Q)
{
	if (Q == NULL||Q->front->data == NULL)
		return FALSE;
	Node *temp=Q->front;  //暂存队首地址
	Q->length--;
	Q->front = Q->front->next;  //队首后移一位
	free(temp);  //释放队首空间
	return TRUE;
}
/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *    @description : 清空队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void ClearLQueue(LQueue *Q)
{
	Node *temp=Q->front;   //temp暂存队首的节点地址
	while (temp != Q->rear)  //直到temp移动队尾，队尾不指向任何元素，此时已经遍历了所有的元素
	{
		temp->data = NULL;
		temp = temp->next;
	}
	Q->rear->data = NULL;  
	Q->length = 0;
}
/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *    @description : 遍历函数操作
 *    @param         Q 队列指针Q，操作函数指针foo
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
 *    @description : 操作函数
 *    @param         q 指针q

 *  @notice      : None
 */
void LPrint(void *q)
{
	elem_str *temp = (elem_str*)q;					//elem_str的内容为
	if (temp->elemtype == 0)						//void *data;
		printf("%d ", *((int*)(temp->data)));		//int elemtype;  elemtype
	else if (temp->elemtype == 1)					//为0 整型 为1 浮点 为2 字符串
		printf("%lf ", *((double*)(temp->data)));
	else if (temp->elemtype == 2)
		printf("%s ", ((char*)(temp->data)));
}
/**************************************************************
 *    End-Multi-Include-Prevent Section
 **************************************************************/