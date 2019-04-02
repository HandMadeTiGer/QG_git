#include "../head/duLinkedList.h"
#include<stdio.h>
#include<stdlib.h> 

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
 *  @name        : Status InitList_DuL(DuLinkedList *L)
 *	@description : initialize an empty linked list with only the head node
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList_DuL(DuLinkedList *L) {
	*L=NULL;
	return SUCCESS;	
}

/**
 *  @name        : void DestroyList_DuL(DuLinkedList *L)
 *	@description : destroy a linked list
 *	@param		 : L(the head node)
 *	@return		 : status
 *  @notice      : None
 */
void DestroyList_DuL(DuLinkedList *L) {
	DuLNode *CurrentNode=*L; //���� LNode* �ͱ����洢���ڽڵ��ַ��ͬʱ��L��ֵ��CurrentNode 
	while(*L) //ֱ������β�� 
	{
		CurrentNode=*L;
		*L=CurrentNode->next; 
		free(CurrentNode);
	}	
}

/**
 *  @name        : Status InsertBeforeList_DuL(DuLNode *p, LNode *q)
 *	@description : insert node q before node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertBeforeList_DuL(DuLNode *p, DuLNode *q) {
	if(p==NULL)
		return ERROR;
	DuLNode *NodePrior2p=p->prior; //��¼p��ԭ��һ�ڵ� 
	p->prior=q;
	q->prior=NodePrior2p;
	q->next=p;
	NodePrior2p->next=q; 
	return SUCCESS; 	
}

/**
 *  @name        : Status InsertAfterList_DuL(DuLNode *p, DuLNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertAfterList_DuL(DuLNode *p, DuLNode *q) {
	if(p==NULL)
		return ERROR;
	DuLNode *NodeNext2p=p->next; //��¼p��ԭ��һ�ڵ� 
	p->next=q;
	q->next=NodeNext2p;
	q->prior=p;
	NodeNext2p->prior=q; 
	return SUCCESS; 
}

/**
 *  @name        : Status DeleteList_DuL(DuLNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : status
 *  @notice      : None
 */
Status DeleteList_DuL(DuLNode *p, ElemType *e) {
	DuLNode *NodeNext2p=p->next;
	if(NodeNext2p==NULL)
		return ERROR;
	*e=p->next->data;
	p->next=p->next->next;
	free(NodeNext2p);
	return SUCCESS;	
}
 
/**
 *  @name        : void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit 
 *	@return		 : Status
 *  @notice      : None
 */
void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)) {
	L=L->next;
	while(L->next!=NULL)
	{
		visit(L->data);
		L=L->next;
	}	
}

