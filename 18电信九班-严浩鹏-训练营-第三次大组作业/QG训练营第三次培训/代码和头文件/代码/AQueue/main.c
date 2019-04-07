#include "../../头文件/AQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
void PrintTheTable()  //打印一个功能选择表格 
{
	printf("密		─────┬───────────────────────────┐		\n");
	printf("封		  1  │        初始化队列         │		\n");
	printf("线		─────┼───────────────────────────┤		\n");
	printf("内		  2  │         销毁队列          │		\n");
	printf("不		─────┼───────────────────────────┤		\n");
	printf("准		  3  │      判断队列是否已满     │		\n");
	printf("答		─────┼───────────────────────────┤		\n");
	printf("题		  4  │      判断队列是否为空     │		\n");
	printf("│		─────┼───────────────────────────┤		\n");
	printf("│		  5  │        获取队头元素       │		\n");
	printf("│		─────┼───────────────────────────┤		\n");
	printf("│		  6  │        获取队列长度       │		\n");
	printf("密		─────┼───────────────────────────┤		\n");
	printf("封		  7  │            入队           │		\n");
	printf("线		─────┼───────────────────────────┤		\n");
	printf("内		  8  │            出队           │		\n");
	printf("不		─────┼───────────────────────────┤		\n");
	printf("准		  9  │          清空队列         │		\n");
	printf("答		─────┼───────────────────────────┤		\n");
	printf("题		  10 │          遍历队列         │		\n");
	printf("│		─────┼───────────────────────────┤		\n");
	printf("│		  0  │            退出           │		\n");
	printf("│		─────┴───────────────────────────┘		\n");
}
int main()
{
	int FunNum = 0; //存储功能选择数字
	double ERRORNUM = 0;
	void *frontdata; //存储队头元素
	AQueue *pt = NULL;
	int *IntInp=NULL;  //指向输入的整型
	double *FloatInp=NULL;//指向输入的浮点型
	char *StrInp=NULL;//指向输入的字符(串)
	int IntFlag = 0, FloatFlag = 0, StrFlag = 0, DotFlag = 0, MinFlag = 0; //记录输入状态，DotFlag记录小数点出现的位置
	elem_str* elem2Inp;  //输入到data[MAXQUEUE]中的元素
	PrintTheTable();
	while (1)
	{
		printf("请选择功能:");
		while (!scanf("%d", &FunNum))
		{
			printf("请输入正确的数字:");
			while (getchar() != '\n');
		}
		switch (FunNum)
		{
			case 0:
				goto EXIT;
			case 1:
				if (pt != NULL)
					printf("请先销毁队列\n");
				else
				{
					pt = malloc(sizeof(AQueue));  //给队列指针pt赋地址
					InitAQueue(pt);
					printf("初始化成功\n");
				}
				break;
			case 2:
				if (pt == NULL)
					printf("传入地址为空\n");
				else
				{
					DestoryAQueue(pt);
					printf("销毁成功\n");
					free(pt);   //销毁队列指针
					pt = NULL;   //指针清零
				}
				break;
			case 3:
				if (pt == NULL)
					printf("传入地址为空\n");
				else if (IsFullAQueue(pt))
				{
					printf("队列已满\n");
				}
				else
					printf("队列未满\n");
				break;
			case 4:
				if (pt == NULL)
					printf("传入地址为空\n");
				else if (IsEmptyAQueue(pt))
					printf("队列为空\n");
				else
					printf("队列不为空\n");
				break;
			case 5:
				if (GetHeadAQueue(pt, &frontdata))  //传入frontdata的指针以修改frontdata的指向
				{
					printf("队头的元素为:");
					elem_str *temp = (elem_str*)frontdata;  //temp记录frontdata void指针指向的内存
					if (temp->elemtype == 0)				
						printf("%d ", *((int*)(temp->data)));
					else if (temp->elemtype == 1)
						printf("%lf ", *((double*)(temp->data)));
					else if (temp->elemtype == 2)
						printf("%s ", ((char*)(temp->data)));
					printf("\n");
				}
				else
					printf("不能获取队头的元素\n");
				break;
			case 6:
				if (pt == NULL)
					printf("传入地址为空\n");
				else
					printf("队列的长度为%d\n", LengthAQueue(pt));
				break;
			case 7:
				//输入处理
				if(pt!=NULL)
				{
					getchar();  //取走换行符
					printf("请输入数据:");
					IntFlag = 0, FloatFlag = 0, StrFlag = 0, DotFlag = 0, MinFlag = 0;//出现小数点时DotFlag记录位置
					IntInp = malloc(sizeof(int));
					FloatInp = malloc(sizeof(double));
					StrInp = malloc(sizeof(char) * 100);
					elem2Inp = malloc(sizeof(elem_str));
					*IntInp = 0;
					*FloatInp = 0;
					*StrInp = 0;
					int i = 0;
					while ((StrInp[i] = getchar()) != '\n'&& i < 100)  //当输入不为换行符且长度不超过100时
					{
						i++;
						if (StrInp[i - 1] >= '0'&&StrInp[i - 1] <= '9')
						{
							IntFlag++;
							StrFlag++;
						}
						else if (StrInp[i - 1] == '.')
						{
							DotFlag = IntFlag;
							StrFlag++;
						}
						else if (StrInp[0] == '-')
						{
							MinFlag = 1;
							StrFlag++;
						}
						else
							StrFlag++;
					}
					StrInp[StrFlag] = '\0';
					if ((IntFlag > 0 && ((StrFlag - IntFlag) == 0 || (StrFlag - IntFlag) == 1)) || (IntFlag>1 && DotFlag>0 && ((StrFlag - IntFlag) == 1 || (StrFlag - IntFlag) == 2)))
					{  //当输入分别为  正整数   负整数     正浮点数   负浮点数   时的情况
						if (!DotFlag && IntFlag < 12) // int整型可存储的最长数据，超出则存储为字符串
						{
							for (int i = 0 + MinFlag; i < IntFlag + MinFlag; i++)  //输入为负时，MinFlag为1 跳过输入的字符串的第一个字符 为正时从第一个字符开始
								*IntInp += -((MinFlag%10)*2-1) * ((int)StrInp[i] - '0')*(int)pow(10, IntFlag + MinFlag - i - 1);
							elem2Inp->data = IntInp;    //-((MinFlag%10)*2-1) ，MinFlag 为1时等于-1，为0时等于1 pow()函数计算结果为字符对应整型的进位数，
							elem2Inp->elemtype = 0;     //如IntFlag=3, MinFlag=0， i=1 即十位 如果对应字符串的字符此时为'2' IntInp 应加 20
							free(StrInp);
						}
						else if (DotFlag && IntFlag < 16)  //  double双精度可存储的最长数据，超出则存储为字符串
						{
							for (int i = 0 + MinFlag; i < DotFlag + MinFlag; i++)
								*FloatInp += -((MinFlag%10)*2-1) * ((double)StrInp[i] - '0') * pow(10, DotFlag + MinFlag - i - 1);
							for (int i = DotFlag + 1 + MinFlag; i < IntFlag + 1+ MinFlag; i++)
								*FloatInp += -((MinFlag%10)*2-1) * ((double)StrInp[i] - '0') * pow(10, DotFlag + MinFlag - i);
							elem2Inp->data = FloatInp;                      //同上，以小数点为0位，小数点后一位为负个位
							elem2Inp->elemtype = 1;
							free(StrInp);
						}
						else
						{
							elem2Inp->data = StrInp;
							elem2Inp->elemtype = 2;
						}
					}
					else
					{
						elem2Inp->data = StrInp;
						elem2Inp->elemtype = 2;
					}
					if (EnAQueue(pt, elem2Inp))
					{
						printf("入队成功\n");
					}
					else
					{
						printf("入队失败,队列已满\n");
					}
				}
				else
					printf("入队失败\n");
				break;
			case 8:
				if (DeAQueue(pt))
					printf("出队成功\n");
				else
					printf("出队失败\n");
				break;
			case 9:
				if (pt != NULL)
				{
					ClearAQueue(pt);
					printf("成功清空队列\n");
				}
				else
					printf("清空队列失败\n");
				break;
			case 10:
				if (TraverseAQueue(pt, APrint))
					printf("\n遍历结果如以上所示\n");
				else
					printf("遍历失败\n");
				break;
			default:
				printf("请输入正确的数字\n");
				while (getchar() != '\n');
				break;
		}
	}
EXIT:return 0;
}

