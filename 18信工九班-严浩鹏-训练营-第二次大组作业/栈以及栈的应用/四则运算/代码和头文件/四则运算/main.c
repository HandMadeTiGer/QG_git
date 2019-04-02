#include "../head/FAO.h"
#include <stdlib.h>
#include <stdio.h>
void PrintStack(LinkStack pt)        //获取栈中的内容
{
	printf("栈的内容由顶到底为:");
	for (int i = 0; i < pt.count; i++)
	{
		if (Rule2OperatorInp(pt.top->data.Operator))  //  当联合中Operator为运算符，输出Operator
			printf("%c ", pt.top->data.Operator);		
		else                                          //不为运算符输出Num
			printf("%lf ", pt.top->data.Num);
		pt.top = pt.top->next;
	}
	printf("\n");
}
double CalcResult(LinkStack* p, LinkedList l, ElemType * data)   //后缀表达式储存在链表l中
{
	double result = 0;
	while (l->next != NULL)    //计算取到链表中最后一个元素
	{
		if (Rule2OperatorInp(l->next->data.Operator))      //判断是否为运算符
		{
			switch (l->next->data.Operator)
			{
			case'+':
				p->top->next->data.Num = (p->top->data.Num + p->top->next->data.Num);  //将栈顶元素与栈顶下的一个元素相加
				popLStack(p, data);     //将栈顶元素出栈
				break;
			case'-':
				p->top->next->data.Num = (p->top->next->data.Num - p->top->data.Num);  //将栈顶下的一个元素与栈顶元素相减
				popLStack(p, data);  //将栈顶元素出栈
				break;
			case'*':
				p->top->next->data.Num = (p->top->data.Num * p->top->next->data.Num);   //将栈顶元素与栈顶下的一个元素相乘
				popLStack(p, data);  //将栈顶元素出栈
				break;
			case'/':
				p->top->next->data.Num = (p->top->next->data.Num / p->top->data.Num);   ////将栈顶下的一个元素与栈顶元素相除
				popLStack(p, data);  //将栈顶元素出栈
				break;
			default:
				break;
			}
		}
		else                           //为数字则进栈
			pushLStack(p, l->next->data); 
		l = l->next;    //l移向下一位
	}
	result = p->top->data.Num;   //最后的栈顶元素即为结果
	return result;
}
int main()
{
	printf("支持负数，浮点数(小数点后六位)，多位数运算\n");
	while(1)
	{
		//链表部分初始化
		LNode *HEAD = (LNode*)malloc(sizeof(LNode));
		LNode* NODE = (LNode*)malloc(sizeof(LNode));
		LNode* TEMP = HEAD;
		HEAD->next = NULL;
		//
		//链栈部分初始化
		LinkStack *pt = (LinkStack*)malloc(sizeof(LinkStack));
		initLStack(pt);
		pt->count = 0;
		pt->top = NULL;
		//
		double CurNum = 0;
		int BracketFlag = 0;  // 遇到(++,遇到)--，最后不为0则为非法输入
		int LegalInputFlag = 0;  //为合法输入判断 遇到数字++，遇到非括号运算符--，若最后不为1则为非法输入
		char CurOperator = 0;
		ElemType DataPoped, Data2push;
		printf("若输入表达式中没有数字则结束程序\n");
		printf("请输入表达式(输入等于结束输入):");
INPUT:  if (BracketFlag != 0 || LegalInputFlag != 1)  //若有非法输入则转到INPUT
		{
			clearLStack(pt);						//再次执行初始化操作
			DestroyList(&HEAD);
			HEAD = (LNode*)malloc(sizeof(LNode));
			HEAD->next = NULL;
			TEMP = HEAD;
			BracketFlag = 0;
			LegalInputFlag = 0;
		}
		while (1)
		{
			if (scanf("%lf", &CurNum))   //输入浮点数，没有被读入的非浮点数会留在缓冲区
			{
				Data2push.Num = CurNum;
				//	pushLStack(pt, Data2push);
				printf("%lf", CurNum);
				//链表存储后缀表达式
				LNode* NODE = (LNode*)malloc(sizeof(LNode));
				NODE->data.Num = CurNum;
				InsertList(TEMP, NODE);
				TEMP = NODE;
				//
				LegalInputFlag++;    //数字，++
			}
			//	while (Rule2OperatorInp(CurOperator = getchar()))
			if (scanf(" %c", &CurOperator))  //输入字符，没有被读入的非字符会留在缓冲区
			{
				if (Rule2OperatorInp(CurOperator))  //判断是否是运算符
				{
					Data2push.Operator = CurOperator;
					if (CurOperator == '(')    
					{
						BracketFlag++;  //左括号++
						pushLStack(pt, Data2push);  //左括号直接压栈
						printf("%c", CurOperator);
					}
					else if (CurOperator == ')')
					{
						BracketFlag--;  //右括号--
						if (BracketFlag < 0)  //如果此时BracketFlag小于0， 左括号数多于右括号数，为非法输入
							goto INPUT;
						printf("%c", CurOperator);
						while (CurOperator != '(')    //出栈直至发现(
						{
							popLStack(pt, &DataPoped);
							//链表存储后缀表达式
							LNode* NODE = (LNode*)malloc(sizeof(LNode));
							NODE->data.Operator = DataPoped.Operator;
							InsertList(TEMP, NODE);
							TEMP = NODE;
							//
							CurOperator = pt->top->data.Operator;  //赋值当前运算符为栈顶的运算符
						}
						popLStack(pt, &DataPoped); //最后将(出栈
					}
					else  //如果不为 ( )
					{
						printf("%c", CurOperator);
						LegalInputFlag--;  //遇到运算符--
						if (PriorityRule(pt, CurOperator))  //如果该运算符优先级大于栈顶的运算符
							pushLStack(pt, Data2push);  //压栈
						else
						{
							while (!PriorityRule(pt, CurOperator))   //否则将栈中的运算符出栈
							{										// 至优先级大于该运算符
								popLStack(pt, &DataPoped);
								//链表存储后缀表达式
								LNode* NODE = (LNode*)malloc(sizeof(LNode));
								NODE->data.Operator = DataPoped.Operator;
								InsertList(TEMP, NODE);
								TEMP = NODE;
								//
							}
							pushLStack(pt, Data2push);   //最后将该运算符压栈
						}
					}
				}
				else if (CurOperator == '=')  //‘=’标志输入结束
				{
					if (HEAD->next == NULL)   //判断是否为空的输入，是则结束程序
						goto END;
					if (BracketFlag != 0||LegalInputFlag != 1)  //非法输入转到INPUT
					{
						printf("\n请输入正确的表达式(输入等于结束输入):");
						goto INPUT;
					}
					while (pt->top != NULL)   //将栈中剩余的运算符转到链表中
					{
						popLStack(pt, &DataPoped);
						LNode* NODE = (LNode*)malloc(sizeof(LNode));
						NODE->data.Operator = DataPoped.Operator;
						InsertList(TEMP, NODE);
						TEMP = NODE;
					}
					NODE->next = NULL;   
					goto RESULT;    //无异常转到RESULT求和
				}
			}
		}
RESULT:	printf("<-中缀表达式\n");
		TraverseList(HEAD);   //输出后缀表达式
		printf("<-后缀表达式\n");
		printf("结果为%lf\n", CalcResult(pt, HEAD, &DataPoped));  //输出结果
	}
END:return 0;
}