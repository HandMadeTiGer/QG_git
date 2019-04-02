#include "../head/linkedList.h"
#include<stdio.h>
#include<stdlib.h>
int NodeCounter=0;		//定义一个全局变量记录节点个数 
void PrintTheTable()  //打印一个功能选择表格 
{
    printf("密		─────┬───────────────────────────┐		\n");
    printf("封		  1  │        初始化链表         │		\n");		
    printf("线		─────┼───────────────────────────┤		\n");
    printf("内		  2  │         销毁链表          │		\n");		
    printf("不		─────┼───────────────────────────┤		\n");
    printf("准		  3  │         插入节点          │		\n");		
    printf("答		─────┼───────────────────────────┤		\n");
    printf("题		  4  │         删除节点          │		\n");		
    printf("│		─────┼───────────────────────────┤		\n");
    printf("│		  5  │         遍历链表          │		\n");		
    printf("│		─────┼───────────────────────────┤		\n");
    printf("│		  6  │         查找节点          │		\n");		
    printf("密		─────┼───────────────────────────┤		\n");
    printf("封		  7  │         反转链表          │		\n");		
    printf("线		─────┼───────────────────────────┤		\n");
    printf("内		  8  │     是不是环形链表呢      │		\n");
    printf("不		─────┼───────────────────────────┤		\n");
    printf("准		  9  │     反转链表中偶数节点    │		\n");
    printf("答		─────┼───────────────────────────┤		\n");
    printf("题		  10 │      找到中间节点         │		\n");
    printf("│		─────┼───────────────────────────┤		\n");
    printf("│		  11 │         创建链表          │		\n");
    printf("│		─────┼───────────────────────────┤		\n");
    printf("│		  12 │ 查看e(最近删除的节点的值) │		\n");
    printf("│		─────┼───────────────────────────┤		\n");
    printf("│		  0  │          退出             │		\n");
    printf("│		─────┴───────────────────────────┘		\n");
}
LNode* CreatList()  //创建节点的函数 
{
	LNode *HEAD1,*NODE,*Node2Ins,*EXTRACOST;
	int flag=0;
//	InitList(&HEAD);
	HEAD1=(LNode*)malloc(sizeof(LNode)); 
	NODE=(LNode*)malloc(sizeof(LNode)); 
//	HEAD->next=NODE;
	HEAD1->next=NULL;
	EXTRACOST=NODE;
	while(scanf("%d", &(NODE->data))!=0)
	{
		if(flag==0)
		{
			HEAD1->next=NODE;
			flag=1;
		}
		Node2Ins=(LNode*)malloc(sizeof(LNode));
		InsertList(NODE,Node2Ins);
		NodeCounter++;
		EXTRACOST=NODE;
		NODE=Node2Ins;
	}
	HEAD1->data=NodeCounter;
	//	free(NODE);
//	EXTRACOST->next=NULL;
	EXTRACOST->next=NULL;
	free(NODE);
	getchar();
	return HEAD1;		
} 
int main()
{	
	int status1,status=0,FunNum=0,e=0;  //status读取scanf返回值，记录输入状态  
	LNode *HEAD;				//e记录被删除节点的值 
 //	HEAD=CreatList();
    while(1)
 	{
		PrintTheTable();
		printf("若有非法输入会循环打印表格，请耐心等待\n");
		printf("请输入你要选择的功能前的数字(1-12,输入0退出)：");	
	//	printf("%d", status);
		status=scanf("%d", &FunNum); //scanf返回值为读取到的数值个数,若读取到非整型返回0 
		getchar();//取走缓冲区内容 
		if(status)
		{
			switch(FunNum)
			{
				LNode *CurrentNode=NULL; 
				int Num;
				case 0:
					goto EXIT; 
				case 1:
					if(InitList(&HEAD))
						printf("成功初始化链表\n");
					else
						printf("初始化失败\n"); 
					break;
				case 2:
					if(HEAD&&NodeCounter) //如果传入的头指针以及它的链表的节点个数不为0 
					{
						DestroyList(&HEAD);
						printf("链表已经被销毁\n"); 
					}
					else
						printf("销毁失败，也许该先创建一个链表\n");
					break; 
				case 3:
					if(HEAD&&NodeCounter)
					{	
						TraverseList(HEAD, PrintData);
						printf("\n你想在哪个节点后面插入节点呢(输入节点的序号以及节点的内容，从1开始):");
						LNode *InsedNode=HEAD,*InsNode=(LNode*)malloc(sizeof(LNode));
						scanf("%d %d", &Num, &(InsNode->data));
							if(Num>(NodeCounter+1))
							{
								Num=0;  //超出范围则Num置0跳过下面的For循环 
								printf("超出范围啦\n"); 
							}
							for(;Num>0;Num--)
								 InsedNode=InsedNode->next;
							if(InsertList(InsedNode, InsNode))
							{
								NodeCounter++;  //改正节点个数 
								HEAD->data=NodeCounter;
							}
							else
								printf("插入失败，也许该先创建一个非空链表\n");
					}
					break;
				case 4:
					CurrentNode=HEAD;
					if(HEAD&&NodeCounter)
					{ 
						TraverseList(HEAD, PrintData);
						printf("\n你想删除哪个节点呢(输入节点的序号，从0开始，被删除的数据会被储存在e中):");
						if(scanf("%d", &Num))
						{
						 	getchar();
							if(Num>NodeCounter)
							{
								Num=0;
								printf("超出范围啦\n");
							}
							for(int i=0;i<Num;i++)
								CurrentNode=CurrentNode->next;
						//if(CurrentNode->next->next!=NULL) 
					//	{
								if(DeleteList(CurrentNode, &e))
								{
									NodeCounter--;
									HEAD->data=NodeCounter;
								}
								else
									printf("删除失败，链表中好像没有这个节点"); 
						}
						else
							printf("请输入正确的数据\n"); 
					//	}
					}
					else
						printf("删除失败，也许该先创建一个非空链表\n"); 
					break;
				case 5:
					if(HEAD&&NodeCounter)
					{
						printf("遍历成功,输出如下:"); 
					 	TraverseList(HEAD, PrintData);
					 	printf("\n");
					}
					else 
						printf("遍历不成功，可能该先创建一个非空链表\n"); 
					 break;
				case 6: 
					if(HEAD&&NodeCounter)
					{ 
						printf("你想在链表中找哪个数呢:");
						if(scanf("%d", &Num))
						 {
						 	getchar();
							if(SearchList(HEAD,Num))
								printf("找到啦\n"); 
							else
								 printf("链表里面好像没有这个数\n");
						}
						else 
							printf("请输入正确的数值\n"); 
					}
					else 
						printf("查找不成功，可能该先创建一个非空链表\n"); 	
					break; 
				case 7:
					if(HEAD&&NodeCounter)
					{ 
						if(ReverseList(&HEAD))
							printf("链表反转成功哒\n");
						else
							printf("出了点小问题，或许你该先创建一个非空链表？\n");
					}
					else 
						printf("反转不成功，可能该先创建一个链表\n"); 
					break;
				case 8:
					if(HEAD&&NodeCounter)
					{
						if(IsLoopList(HEAD)) 
							printf("这是一个环形链表\n");
						else
							printf("不，它不是一个环形链表\n"); 
					}
					else 
						printf("判断不成功，可能该先创建一个非空链表\n"); 
					break;
				case 9:
					if(HEAD&&NodeCounter)
					{ 
						ReverseEvenList(&HEAD);
						printf("反转成功\n"); 
					}
					else 
						printf("反转不成功，可能该先创建一个非空链表\n"); 
					break;
				case 10:
					if(HEAD!=NULL&&NodeCounter)
						printf("链表的中点是%d\n", FindMidNode(&HEAD)->data); 
					else 
						printf("查找不成功，可能该先创建一个非空链表\n"); 
				 	break;
				case 11: 
					if(!HEAD)
					{
						printf("开始输入数据吧(输入非整型结束输入)\n"); 
						HEAD=CreatList(); 
						printf("成功创建链表，现在可以对%p进行操作\n", HEAD);
					}
					else 
						printf("创建链表不成功，应先进行初始化\n"); 
					break;
				case 12: 
					printf("e的值是%d\n", e);
					break;
			}
		
		}
		else
			printf("请输入正确的数字\n");
	}
	//创建一个链表，输入非整型结束创建链表  //记录节点个数 
/*	LNode *NODE,*Node2Ins,*EXTRACOST;
	InitList(&HEAD);
//	HEAD=(LNode*)malloc(sizeof(LNode)); 
	NODE=(LNode*)malloc(sizeof(LNode)); 
//	HEAD->next=NODE;
	HEAD->next=NULL;
	EXTRACOST=NODE;
	while(scanf("%d", &(NODE->data))!=0)
	{
		if(flag==0)
		{
			HEAD->next=NODE;
			flag=1;
		}
		Node2Ins=(LNode*)malloc(sizeof(LNode));
		InsertList(NODE,Node2Ins);
		NodeCounter++;
		EXTRACOST=NODE;
		NODE=Node2Ins;
	}
	HEAD->data=NodeCounter;
	EXTRACOST->next=NULL;
	free(NODE);
	getchar();   //取走缓冲区中未录入的数据 */
//	printf("%d\n", HEAD->next->next->data);
//	printf("%d\n", FindMidNode(&HEAD)->data);   //√ 
//	printf("%d", IsLoopList(HEAD));  // 
//	TraverseList(HEAD,PrintData);  //√ 
//	ReverseList(&HEAD); //√
/*	ReverseEvenList(&HEAD);
	HEAD->data=NodeCounter;
	printf("%d\n", HEAD->data);*/
//	TraverseList(HEAD,PrintData); //√  

/*	scanf("%d", &a);
	printf("%d\n", SearchList(HEAD, a));// √ */
/*	DestroyList(&HEAD);  // √ 
	printf("%d\n", HEAD->data);*/ 
/*	DeleteList(HEAD,&e); // √ 
	printf("%d\n", e);
	TraverseList(HEAD,PrintData); */
//	printf("%d\n", HEAD->data);
/*	for(int i=0;i<NodeCounter;i++)
	{
		printf("%d\n", HEAD->next->data);
		HEAD=HEAD->next; 
	} */ 
EXIT:	return 0;
} 
