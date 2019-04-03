#ifndef FAO_H_INCLUDED
#define FAO_H_INCLUDED
//链栈部分
typedef enum Status {
	ERROR = 0, SUCCESS = 1
} Status;
//栈的元素类型为该联合
union NUMandOP  
{
	double Num;
	char Operator;
};
typedef union NUMandOP ElemType;
//
typedef  struct StackNode
{
	union NUMandOP data;
	struct StackNode *next;
}StackNode, *LinkStackPtr;

typedef  struct  LinkStack {
	LinkStackPtr top;
	int	count;
}LinkStack;
Status initLStack(LinkStack *s);//初始化栈
Status isEmptyLStack(LinkStack *s);//判断栈是否为空
Status clearLStack(LinkStack *s);//清空栈
Status pushLStack(LinkStack *s, ElemType data);//入栈
Status popLStack(LinkStack *s, ElemType *data);//出栈

//链表部分
// define struct of linked list
//链表元素类型为联合
typedef struct LNode {
	ElemType data;
	struct LNode *next;
} LNode, *LinkedList;

// define Status
Status InitList(LinkedList *L);
Status InsertList(LNode *p, LNode *q);
void DestroyList(LinkedList *L);
void TraverseList(LinkedList L);
//
Status Rule2OperatorInp(char inp);
Status PriorityRule(LinkStack *s, char inp);
#endif // !FAO_H_INCLUDED


