#include "../head/LinkStack.h"
#include <stdlib.h>
#include <stdio.h>
void PrintTheTable()  //打印一个功能选择表格 
{
	printf("密		─────┬───────────────────────────┐		\n");
	printf("封		  1  │         初始化栈          │		\n");
	printf("线		─────┼───────────────────────────┤		\n");
	printf("内		  2  │         判断栈是否为空    │		\n");
	printf("不		─────┼───────────────────────────┤		\n");
	printf("准		  3  │	       找到栈顶元素      │		\n");
	printf("答		─────┼───────────────────────────┤		\n");
	printf("题		  4  │         清空链表栈        │		\n");
	printf("│		─────┼───────────────────────────┤		\n");
	printf("│		  5  │         销毁顺序栈        │		\n");
	printf("密		─────┼───────────────────────────┤		\n");
	printf("封		  6  │         检测栈的长度      │		\n");
	printf("线		─────┼───────────────────────────┤		\n");
	printf("内		  7  │         入栈              │		\n");
	printf("不		─────┼───────────────────────────┤		\n");
	printf("准		  8  │         出栈              │		\n");
	printf("答		─────┼───────────────────────────┤		\n");
	printf("题		  0  │         退出              │		\n");
	printf("│		─────┴───────────────────────────┘		\n");
}
void PrintStack(LinkStack pt) //获取栈中的内容
{
	printf("栈的内容由顶到底为:");
	for (int i = 0; i < pt.count; i++)
	{
		printf("%d ", pt.top->data);
		pt.top = pt.top->next;
	}
	printf("\n");
}
int arr[5] = { 1,2,3,4,5 };  //测试用的栈的内容
int main()
{
	LinkStack* pt= (LinkStack*)malloc(sizeof(LinkStack));
	int Len = 0,Data2Push=0,DataPoped=0,LegalInputFlag=0,FunNum=0,TopNum=0;  //LegalInputFlag为非法字符状态位 0为非法输入
	pt->count = 0;
	pt->top = NULL;
	printf("这里有一个栈以供测试\n");
	//这里提供一个用以测试的栈
	initLStack(pt);
	for (int i = 0; i < 5; i++)
	{
		pushLStack(pt, arr[i]);
	}
	PrintStack(*pt);
	//
	while (1)
	{
		PrintTheTable();
		printf("请输入你要选择的功能(输入非法字符返回功能表格):");
		//功能选择部分
		while (scanf("%d", &FunNum))
		{
			LegalInputFlag = 0;
			switch (FunNum)
			{
			case 0:
				goto EXIT;
			case 1:
				if (pt == NULL)    
					pt = (LinkStack*)malloc(sizeof(LinkStack));
				if (initLStack(pt))
					printf("栈初始化成功\n");
				else
					printf("原栈未销毁或内存空间不足，初始化失败\n");
				break;
			case 2:
				if (pt != NULL)  //先判断栈是否存在 pt->top为NULL时栈不存在 pt->top->next 为NULL时栈为空
				{
					if (isEmptyLStack(pt))
						printf("栈为空\n");
					else
						printf("栈不为空\n");
				}
				else
					printf("请先创建一个栈\n");
				break;
			case 3:
				printf("%p", pt);
				if (getTopLStack(pt, &TopNum))
					printf("成功获取栈顶元素%d\n", TopNum);
				else
					printf("获取失败，请确认栈是否被创建或者栈中有无元素\n");
				break;
			case 4:
				if (clearLStack(pt))
					printf("清空链表成功\n");
				else
					printf("清空失败，传入地址无效或栈为空\n");
				break;
			case 5:
				PrintStack(*pt);
				if (destroyLStack(pt))
				{	
					free(pt);
					pt = NULL;
					printf("%p", pt);
					printf("销毁栈成功\n");
				}
				else
					printf("销毁失败，传入地址无效或栈为空\n");
				break;
			case 6:
				if (LStackLength(pt, &Len))
				{
					printf("获取长度%d成功\n", Len);
					PrintStack(*pt);
				}
				else
					printf("获取失败，请先创建一个栈\n");
				break;
			case 7:
				while (!LegalInputFlag)  //若为非法输入
				{
					while (getchar() != '\n');  //取缓冲区直至回车
					printf("请输入正确的数字:");
					LegalInputFlag = scanf("%d", &Data2Push);  //若没有读入合法的数字则LegalInputFlag为0，再次进入循环
					printf("\n");
				}
				if (pushLStack(pt, Data2Push))
				{
					printf("入栈成功\n");
					PrintStack(*pt);
				}
				else
					printf("入栈失败,可能栈已满或者需要先创建一个栈\n");
				while (getchar() != '\n');
				break;
			case 8:
				if (popLStack(pt, &DataPoped))
				{
					printf("出栈成功，出栈元素为%d\n", DataPoped);
					PrintStack(*pt);
				}
				else
					printf("出栈失败,此时栈中没有元素\n");
				break;
			default:
				printf("请输入正确的数字以选择功能\n");
				break;
			}
			printf("请输入你要选择的功能(输入非法字符返回功能表格):");
		}
		while (getchar() != '\n');
		printf("请输入正确的数字\n");
	}
// 测试
//	printf("是否初始化%p %p %d ",pt, pt->top, initLStack(pt));
//	initLStack(pt);
//	printf("%d ", pushLStack(pt, 5));
//	printf("%d %d ", e, getTopLStack(pt, &e));
//	pushLStack(pt, 4);
//	printf("%d %d ", pt->top->data, pt->top->next->data);
//	printf("%d %d %d ", e, getTopLStack(pt,&e), isEmptyLStack(pt));
//	printf("%d %d ", Len, LStackLength(pt, &Len));
//	printf("%d ", destroyLStack(pt));
//	printf("%d %d ", Len, LStackLength(pt, &Len));
//	popLStack(pt, &DataPoped);
//	printf("%d ", DataPoped);
//	clearLStack(pt);  
//	printf("%d ", LStackLength(pt, &Len));
//	printf("%d ", Len);
//	printf("%d", destroyLStack(pt));
//	initLStack(pt);
	
//	printf("%d ", pushLStack(pt, 5));
//	pushLStack(pt, 4);
//	printf("%d", isEmptyLStack(pt));
//	LStackLength(pt, &Len);
//	printf("%d ", Len);
EXIT:return 0;
}