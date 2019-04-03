#ifndef FAO_H_INCLUDED
#define FAO_H_INCLUDED
//��ջ����
typedef enum Status {
	ERROR = 0, SUCCESS = 1
} Status;
//ջ��Ԫ������Ϊ������
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
Status initLStack(LinkStack *s);//��ʼ��ջ
Status isEmptyLStack(LinkStack *s);//�ж�ջ�Ƿ�Ϊ��
Status clearLStack(LinkStack *s);//���ջ
Status pushLStack(LinkStack *s, ElemType data);//��ջ
Status popLStack(LinkStack *s, ElemType *data);//��ջ

//������
// define struct of linked list
//����Ԫ������Ϊ����
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


