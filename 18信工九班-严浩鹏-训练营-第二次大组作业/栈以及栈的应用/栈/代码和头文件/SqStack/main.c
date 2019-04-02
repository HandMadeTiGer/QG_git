#include <stdio.h>
#include "../head/SqStack.h"
void PrintTheTable()  //打印一个功能选择表格 
{
	printf("密		─────┬───────────────────────────┐		\n");
	printf("封		  1  │         初始化顺序栈      │		\n");
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
int arr[5] = { 5,4,3,2,1 }; //装入测试栈的内容
int main()
{
	int Len=0,FunNum=0,Sizes=0,Data2Push=0,LegalInputFlag=0,TopNum=0,Data2Pop=0; //LegalInputFlag为0时为非法输入
	printf("以提供栈顶到栈底为1 2 3 4 5的栈以进行测试，若不需要请先销毁\n");    //置0以进入功能部分循环中
	SqStack *pt = (SqStack*)malloc(sizeof(SqStack));
	//这里有一个可以用来测试的栈
	pt->top = -1;
	pt->elem = NULL;
	initStack(pt, 5);
	for (int i = 0; i < 5; i++)
	{
		pushStack(pt, arr[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		getTopStack(pt, &TopNum);
		printf("%d", TopNum);
		pt->top--;
	}
	//
	while (1)
	{
		PrintTheTable();
		printf("请输入你要选择的功能:");
		//功能选择部分
		while (scanf("%d", &FunNum))
		{
			LegalInputFlag = 0;
			switch (FunNum)
			{
				case 0:
					goto EXIT;
				case 1:
					while(!LegalInputFlag)//若为非法输入
					{ 
						while (getchar()!='\n'); //取缓冲区直至回车
						printf("请输入正确的栈的大小:");
						LegalInputFlag = scanf("%d", &Sizes);  //若没有读入合法的数字则LegalInputFlag为0，再次进入循环
						printf("\n");
					}
					if (initStack(pt, Sizes))
						printf("栈初始化成功\n");
					else
						printf("原栈未销毁或内存空间不足，初始化失败\n");
					break;
				case 2:
					if (isEmptyStack(pt))
						printf("栈为空\n");
					else
						printf("栈不为空\n");
					break;
				case 3:
					if (getTopStack(pt, &TopNum))
						printf("成功获取栈顶元素%d\n", TopNum);
					else
						printf("获取失败\n");
					break;
				case 4:
					if (clearStack(pt))
						printf("清空链表成功\n");
					else
						printf("清空失败，传入地址无效或栈为空\n");
					break;
				case 5:
					if (destroyStack(pt))
						printf("销毁栈成功\n");
					else
						printf("销毁失败，传入地址无效或栈为空\n");
					break;
				case 6:
					if (stackLength(pt, &Len))
						printf("获取长度%d成功\n", Len);
					else
						printf("获取失败\n");
					break;
				case 7:
					while (!LegalInputFlag)
					{
						while (getchar()!='\n');
						printf("请输入正确的数字:");
						LegalInputFlag = scanf("%d", &Data2Push);
						printf("\n");
					}
					if (pushStack(pt, Data2Push))
						printf("入栈成功\n");
					else
						printf("入栈失败,可能栈已满或者需要先创建一个栈\n");
					while (getchar()!='\n');
					break;
				case 8:
					if (popStack(pt, &Data2Pop))
						printf("出栈成功，出栈元素为%d\n", Data2Pop);
					else
						printf("出栈失败,此时栈中没有元素\n");
					break;
				default:
					printf("请输入正确的数字以选择功能\n");
					break;
			}
			printf("请输入你要选择的功能:");
		}
		while (getchar()!='\n');
		printf("请输入正确的数字\n");
	}
EXIT: return 0;
}
