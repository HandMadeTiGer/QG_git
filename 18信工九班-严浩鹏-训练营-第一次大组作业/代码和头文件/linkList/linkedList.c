#include "../head/linkedList.h"
#include<stdlib.h>
#include<stdio.h> 

/**
 * @name		 : void visit(ElemType e);
 * @description  : print the element twice times 
 * @param        : e
 * @return       : void
 * @notice       : None
 */
void PrintData(ElemType e)
{
	printf("%d\t", e);
} 

/**
 *  @name        : Status InitList(LinkList *L);
 *	@description : initialize an empty linked list with only the head node without value
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList(LinkedList *L) {
//	if(*L==NULL)  
//		return ERROR;
	*L=NULL;
	return SUCCESS;
}

/**
 *  @name        : void DestroyList(LinkedList *L)
 *	@description : destroy a linked list, free all the nodes
 *	@param		 : L(the head node)
 *	@return		 : None
 *  @notice      : None
 */
void DestroyList(LinkedList *L) {
	LNode *CurrentNode=*L; //定义 LNode* 型变量存储现在节点地址，同时把L赋值给CurrentNode 
	while(*L) //直到链表尾部 
	{
		CurrentNode=*L;
		*L=CurrentNode->next; 
		free(CurrentNode);
	}
}

/**
 *  @name        : Status InsertList(LNode *p, LNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : Status
 *  @notice      : None
 */
Status InsertList(LNode *p, LNode *q) {
	if(p==NULL)
		return ERROR;
	LNode *NodeNext2p=p->next; //记录p的原下一节点 
	p->next=q;
	q->next=NodeNext2p;
	return SUCCESS; 
}
/**
 *  @name        : Status DeleteList(LNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : Status
 *  @notice      : None
 */
Status DeleteList(LNode *p, ElemType *e) {
	LNode *NodeNext2p=p->next;
	if(NodeNext2p==NULL)
		return ERROR;
	*e=p->next->data;
	p->next=p->next->next;
	free(NodeNext2p);
	return SUCCESS;
}

/**
 *  @name        : void TraverseList(LinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit 
 *	@return		 : None
 *  @notice      : None
 */
void TraverseList(LinkedList L, void (*visit)(ElemType e)) {
//	L=L->next;
	while(L->next!=NULL)
	{
		visit(L->next->data);
		L=L->next;
	}	
}

/**
 *  @name        : Status SearchList(LinkedList L, ElemType e)
 *	@description : find the first node in the linked list according to e 
 *	@param		 : L(the head node), e
 *	@return		 : Status
 *  @notice      : None
 */
Status SearchList(LinkedList L, ElemType e) {
	while(L)
	{
		if(L->data==e)
			return SUCCESS;
		L=L->next;
	}
	return ERROR;	
} 

/**
 *  @name        : Status ReverseList(LinkedList *L)
 *	@description : reverse the linked list 
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status ReverseList(LinkedList *L) {
	if(*L==NULL||(*L)->next==NULL)
		return ERROR;
	LNode *NextNode=(*L)->next;
	LNode *CurrentNode=NextNode->next;
	LNode *Head=(LNode*)malloc(sizeof(LNode)); //定义一个假的头指针 
	while(CurrentNode)
	{
		NextNode->next=CurrentNode->next;
		CurrentNode->next=(*L)->next;
		(*L)->next=CurrentNode;
		CurrentNode=NextNode->next;
	}
	Head->next=NextNode;  //使假的头指针的next指向反转后最后一个节点 
	L=&Head; //纠正头指针的指向 
	return SUCCESS;	
}   

/**
 *  @name        : Status IsLoopList(LinkedList L)
 *	@description : judge whether the linked list is looped
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status IsLoopList(LinkedList L) {
	LNode *Fast_Pt=L,*Slow_Pt=L;
	if(L->next==NULL)
		return ERROR;
	while(Fast_Pt&&Fast_Pt->next)
	{
		Fast_Pt=Fast_Pt->next->next;
		Slow_Pt=Slow_Pt->next; 
		if(Fast_Pt==Slow_Pt)
			return SUCCESS;
	}	
	return ERROR;
}

/**
 *  @name        : LNode* ReverseEvenList(LinkedList *L)
 *	@description : reverse the nodes which value is an even number in the linked list, input: 1 -> 2 -> 3 -> 4  output: 2 -> 1 -> 4 -> 3
 *	@param		 : L(the head node)
 *	@return		 : LNode(the new head node)
 *  @notice      : choose to finish 
 */
LNode* ReverseEvenList(LinkedList *L) {
	LNode *CurrentNode,*NextNextNode,*NextNode;
	CurrentNode=*L;
	while(CurrentNode->next&&CurrentNode->next->next)
	{	
		NextNode=CurrentNode->next;
		NextNextNode=NextNode->next;
		NextNode->next=NextNextNode->next;
		NextNextNode->next=NextNode;
		CurrentNode->next=NextNextNode;
		CurrentNode=NextNode;
//		CurrentNode=CurrentNode->next->next;
	}
	return *L;	
}

/**
 *  @name        : LNode* FindMidNode(LinkedList *L)
 *	@description : find the middle node in the linked list
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : choose to finish 
 */
LNode* FindMidNode(LinkedList *L) {
	LNode *Fast_Pt=(*L),*Slow_Pt=(*L);
	while(Fast_Pt&&Fast_Pt->next)
	{
	/*	if(Fast_pt->next->next==NULL)
			return Slow_pt;*/
		if(Fast_Pt->next==NULL&&(!Fast_Pt))
			return Slow_Pt;
		else if(Fast_Pt==NULL)
			return Slow_Pt; 
		Fast_Pt=Fast_Pt->next->next;
		Slow_Pt=Slow_Pt->next;   
	}
	return Slow_Pt;
}
