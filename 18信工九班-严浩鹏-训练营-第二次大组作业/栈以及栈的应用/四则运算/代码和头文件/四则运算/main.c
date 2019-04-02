#include "../head/FAO.h"
#include <stdlib.h>
#include <stdio.h>
void PrintStack(LinkStack pt)        //��ȡջ�е�����
{
	printf("ջ�������ɶ�����Ϊ:");
	for (int i = 0; i < pt.count; i++)
	{
		if (Rule2OperatorInp(pt.top->data.Operator))  //  ��������OperatorΪ����������Operator
			printf("%c ", pt.top->data.Operator);		
		else                                          //��Ϊ��������Num
			printf("%lf ", pt.top->data.Num);
		pt.top = pt.top->next;
	}
	printf("\n");
}
double CalcResult(LinkStack* p, LinkedList l, ElemType * data)   //��׺���ʽ����������l��
{
	double result = 0;
	while (l->next != NULL)    //����ȡ�����������һ��Ԫ��
	{
		if (Rule2OperatorInp(l->next->data.Operator))      //�ж��Ƿ�Ϊ�����
		{
			switch (l->next->data.Operator)
			{
			case'+':
				p->top->next->data.Num = (p->top->data.Num + p->top->next->data.Num);  //��ջ��Ԫ����ջ���µ�һ��Ԫ�����
				popLStack(p, data);     //��ջ��Ԫ�س�ջ
				break;
			case'-':
				p->top->next->data.Num = (p->top->next->data.Num - p->top->data.Num);  //��ջ���µ�һ��Ԫ����ջ��Ԫ�����
				popLStack(p, data);  //��ջ��Ԫ�س�ջ
				break;
			case'*':
				p->top->next->data.Num = (p->top->data.Num * p->top->next->data.Num);   //��ջ��Ԫ����ջ���µ�һ��Ԫ�����
				popLStack(p, data);  //��ջ��Ԫ�س�ջ
				break;
			case'/':
				p->top->next->data.Num = (p->top->next->data.Num / p->top->data.Num);   ////��ջ���µ�һ��Ԫ����ջ��Ԫ�����
				popLStack(p, data);  //��ջ��Ԫ�س�ջ
				break;
			default:
				break;
			}
		}
		else                           //Ϊ�������ջ
			pushLStack(p, l->next->data); 
		l = l->next;    //l������һλ
	}
	result = p->top->data.Num;   //����ջ��Ԫ�ؼ�Ϊ���
	return result;
}
int main()
{
	printf("֧�ָ�����������(С�������λ)����λ������\n");
	while(1)
	{
		//�����ֳ�ʼ��
		LNode *HEAD = (LNode*)malloc(sizeof(LNode));
		LNode* NODE = (LNode*)malloc(sizeof(LNode));
		LNode* TEMP = HEAD;
		HEAD->next = NULL;
		//
		//��ջ���ֳ�ʼ��
		LinkStack *pt = (LinkStack*)malloc(sizeof(LinkStack));
		initLStack(pt);
		pt->count = 0;
		pt->top = NULL;
		//
		double CurNum = 0;
		int BracketFlag = 0;  // ����(++,����)--�����Ϊ0��Ϊ�Ƿ�����
		int LegalInputFlag = 0;  //Ϊ�Ϸ������ж� ��������++�����������������--�������Ϊ1��Ϊ�Ƿ�����
		char CurOperator = 0;
		ElemType DataPoped, Data2push;
		printf("��������ʽ��û���������������\n");
		printf("��������ʽ(������ڽ�������):");
INPUT:  if (BracketFlag != 0 || LegalInputFlag != 1)  //���зǷ�������ת��INPUT
		{
			clearLStack(pt);						//�ٴ�ִ�г�ʼ������
			DestroyList(&HEAD);
			HEAD = (LNode*)malloc(sizeof(LNode));
			HEAD->next = NULL;
			TEMP = HEAD;
			BracketFlag = 0;
			LegalInputFlag = 0;
		}
		while (1)
		{
			if (scanf("%lf", &CurNum))   //���븡������û�б�����ķǸ����������ڻ�����
			{
				Data2push.Num = CurNum;
				//	pushLStack(pt, Data2push);
				printf("%lf", CurNum);
				//����洢��׺���ʽ
				LNode* NODE = (LNode*)malloc(sizeof(LNode));
				NODE->data.Num = CurNum;
				InsertList(TEMP, NODE);
				TEMP = NODE;
				//
				LegalInputFlag++;    //���֣�++
			}
			//	while (Rule2OperatorInp(CurOperator = getchar()))
			if (scanf(" %c", &CurOperator))  //�����ַ���û�б�����ķ��ַ������ڻ�����
			{
				if (Rule2OperatorInp(CurOperator))  //�ж��Ƿ��������
				{
					Data2push.Operator = CurOperator;
					if (CurOperator == '(')    
					{
						BracketFlag++;  //������++
						pushLStack(pt, Data2push);  //������ֱ��ѹջ
						printf("%c", CurOperator);
					}
					else if (CurOperator == ')')
					{
						BracketFlag--;  //������--
						if (BracketFlag < 0)  //�����ʱBracketFlagС��0�� ����������������������Ϊ�Ƿ�����
							goto INPUT;
						printf("%c", CurOperator);
						while (CurOperator != '(')    //��ջֱ������(
						{
							popLStack(pt, &DataPoped);
							//����洢��׺���ʽ
							LNode* NODE = (LNode*)malloc(sizeof(LNode));
							NODE->data.Operator = DataPoped.Operator;
							InsertList(TEMP, NODE);
							TEMP = NODE;
							//
							CurOperator = pt->top->data.Operator;  //��ֵ��ǰ�����Ϊջ���������
						}
						popLStack(pt, &DataPoped); //���(��ջ
					}
					else  //�����Ϊ ( )
					{
						printf("%c", CurOperator);
						LegalInputFlag--;  //���������--
						if (PriorityRule(pt, CurOperator))  //�������������ȼ�����ջ���������
							pushLStack(pt, Data2push);  //ѹջ
						else
						{
							while (!PriorityRule(pt, CurOperator))   //����ջ�е��������ջ
							{										// �����ȼ����ڸ������
								popLStack(pt, &DataPoped);
								//����洢��׺���ʽ
								LNode* NODE = (LNode*)malloc(sizeof(LNode));
								NODE->data.Operator = DataPoped.Operator;
								InsertList(TEMP, NODE);
								TEMP = NODE;
								//
							}
							pushLStack(pt, Data2push);   //��󽫸������ѹջ
						}
					}
				}
				else if (CurOperator == '=')  //��=����־�������
				{
					if (HEAD->next == NULL)   //�ж��Ƿ�Ϊ�յ����룬�����������
						goto END;
					if (BracketFlag != 0||LegalInputFlag != 1)  //�Ƿ�����ת��INPUT
					{
						printf("\n��������ȷ�ı��ʽ(������ڽ�������):");
						goto INPUT;
					}
					while (pt->top != NULL)   //��ջ��ʣ��������ת��������
					{
						popLStack(pt, &DataPoped);
						LNode* NODE = (LNode*)malloc(sizeof(LNode));
						NODE->data.Operator = DataPoped.Operator;
						InsertList(TEMP, NODE);
						TEMP = NODE;
					}
					NODE->next = NULL;   
					goto RESULT;    //���쳣ת��RESULT���
				}
			}
		}
RESULT:	printf("<-��׺���ʽ\n");
		TraverseList(HEAD);   //�����׺���ʽ
		printf("<-��׺���ʽ\n");
		printf("���Ϊ%lf\n", CalcResult(pt, HEAD, &DataPoped));  //������
	}
END:return 0;
}