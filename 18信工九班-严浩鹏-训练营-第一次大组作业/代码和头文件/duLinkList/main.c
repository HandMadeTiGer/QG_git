#include "../head/duLinkedList.h"
#include<stdio.h>
#include<stdlib.h>
int DuNodeCounter;
void PrintTheTable()  //打印一个功能选择表格 
{
    printf("密		─────┬───────────────────────────┐		\n");
    printf("封		  1  │        初始化链表         │		\n");		
    printf("线		─────┼───────────────────────────┤		\n");
    printf("内		  2  │         销毁链表          │		\n");		
    printf("不		─────┼───────────────────────────┤		\n");
    printf("准		  3  │        前面插入节点       │		\n");		
    printf("答		─────┼───────────────────────────┤		\n");
    printf("题		  4  │        后面插入节点       │		\n");		
    printf("│		─────┼───────────────────────────┤		\n");
    printf("│		  5  │         删除节点          │		\n");		
    printf("│		─────┼───────────────────────────┤		\n");
    printf("│		  6  │         遍历链表          │		\n");		
    printf("│		─────┼───────────────────────────┤		\n");
    printf("│		  7  │         创建链表          │		\n");
    printf("│		─────┴───────────────────────────┤		\n");
    printf("│		  8  │         输出e             │		\n");
    printf("│		─────┴───────────────────────────┤		\n");
    printf("│		  0  │          退出             │		\n");
    printf("│		─────┴───────────────────────────┘		\n");
}
/*DuLNode* CreatList()  //创建节点的函数 
{
	DuLNode *HEAD,*NODE,*Node2Ins,*EXTRACOST,*TAIL;
	int flag=0;
//	InitList(&HEAD);
	HEAD=(DuLNode*)malloc(sizeof(DuLNode)); 
	NODE=(DuLNode*)malloc(sizeof(DuLNode));
	TAIL=(DuLNode*)malloc(sizeof(DuLNode));
//	HEAD->next=NODE;
	HEAD->next=NULL;
	TAIL->prior=NULL;
	EXTRACOST=NODE;
	while(scanf("%d", &(NODE->data))!=0)
	{
		if(flag==0)
		{
			HEAD->next=NODE;
			flag=1;
		}
		Node2Ins=(DuLNode*)malloc(sizeof(DuLNode));
		InsertAfterList_DuL(NODE,Node2Ins);
		TAIL->prior=NODE;
		DuNodeCounter++;
		NODE=Node2Ins;
	}
	HEAD->data=DuNodeCounter;
	EXTRACOST->next=NULL;
	free(NODE);
	getchar();
	return HEAD;		
} */
int main()
{	
	int status=0,FunNum=0,e=0,flag=0;;  //status读取scanf返回值，记录输入状态  
	DuLNode *HEAD,*NODE,*TAIL,*Node2Ins,*EXTRACOST;				//e记录被删除节点的值 
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
				DuLNode *CurrentNode=NULL; 
				int Num,Sequence;
				case 0:
					goto EXIT; 
				case 1:
					if(InitList_DuL(&HEAD))
						printf("成功初始化链表\n");
					else
						printf("初始化失败\n"); 
					break;
				case 2:
					if(HEAD&&DuNodeCounter) //如果传入的头指针以及它的链表的节点个数不为0 
					{
						DestroyList_DuL(&HEAD);
						printf("链表已经被销毁\n"); 
					}
					else
						printf("销毁失败，也许该先创建一个链表\n");
					break; 
				case 3:
					if(HEAD&&DuNodeCounter)
					{	
						TraverseList_DuL(HEAD, PrintData);
						printf("\n你想在哪个节点前面插入节点呢(输入节点的序号以及节点的内容，从1开始):");
						DuLNode *InsedNode=HEAD,*InsNode=(DuLNode*)malloc(sizeof(DuLNode));
						scanf("%d %d", &Num, &(InsNode->data));
						if(Num>(DuNodeCounter+1))
						{
							Num=0;  //超出范围则Num置0跳过下面的For循环 
							printf("超出范围啦\n"); 
						}
						for(;Num>0;Num--)
							 InsedNode=InsedNode->next;
						if(InsertBeforeList_DuL(InsedNode, InsNode))
						{
							DuNodeCounter++;  //改正节点个数 
							HEAD->data=DuNodeCounter;
						}
					}
					else
						printf("插入失败，也许该先创建一个非空链表\n"); 
					break;
				case 4:
					if(HEAD&&DuNodeCounter)
					{	
						TraverseList_DuL(HEAD, PrintData);
						printf("\n你想在哪个节点后面插入节点呢(输入节点的序号以及节点的内容，从1开始):");
						DuLNode *InsedNode=HEAD,*InsNode=(DuLNode*)malloc(sizeof(DuLNode));
						InsNode->next=NULL; 
						scanf("%d %d", &Num, &(InsNode->data));
						if(Num>(DuNodeCounter))
						{
							Num=0;  //超出范围则Num置0跳过下面的For循环 
							printf("超出范围啦\n"); 
						}
						for(;Num>0;Num--)
							 InsedNode=InsedNode->next;
						if(InsertAfterList_DuL(InsedNode, InsNode))
						{
							DuNodeCounter++;  //改正节点个数 
							HEAD->data=DuNodeCounter;
						}
						else
							printf("插入失败，没有这样一个点\n"); 
					}
					else
						printf("插入失败，也许该先创建一个非空链表\n"); 
					break;
				case 5:
					CurrentNode=HEAD;
					if(HEAD&&DuNodeCounter)
					{ 
						TraverseList_DuL(HEAD, PrintData);
						printf("\n你想删除哪个节点呢(输入节点的序号，从0开始，被删除的数据会被储存在e中):");
						if(scanf("%d", &Num))
						{ 
							getchar();
							if(Num>DuNodeCounter)
							{
								Num=0;
								printf("超出范围啦\n");
							}
							for(int i=0;i<Num;i++)
								CurrentNode=CurrentNode->next;
						//if(CurrentNode->next->next!=NULL) 
					//	{
							if(DeleteList_DuL(CurrentNode, &e))
							{
								DuNodeCounter--;
								HEAD->data=DuNodeCounter;
							}
							else
								printf("删除失败，链表中好像没有这个节点");
						}
						else
							printf("请输入正确数值\n"); 
					//	}
					}
					else
						printf("删除失败，也许该先创建一个非空链表\n"); 
					break;
				case 6:
					if(HEAD&&DuNodeCounter)
					{
						printf("遍历成功,输出如下:"); 
					 	TraverseList_DuL(HEAD, PrintData);
					 	printf("\n");
					}
					else 
						printf("遍历不成功，可能该先创建一个非空链表\n"); 
					 break;
				case 7: 
					if(!HEAD)
					{
						printf("开始输入数据吧(输入非整型结束输入)\n"); 
						HEAD=(DuLNode*)malloc(sizeof(DuLNode)); 
						NODE=(DuLNode*)malloc(sizeof(DuLNode));
						TAIL=(DuLNode*)malloc(sizeof(DuLNode));
						NODE->prior=HEAD;
						NODE->next=TAIL;
						HEAD->next=NULL;
						TAIL->prior=NULL;
				//		EXTRACOST=NODE;
						while(scanf("%d", &(NODE->data))!=0)
						{
							if(flag==0)
							{
								HEAD->next=NODE;
								TAIL->prior=NODE;
						//		NODE->prior=NULL;
								flag=1;
							}
							Node2Ins=(DuLNode*)malloc(sizeof(DuLNode));
							InsertAfterList_DuL(NODE,Node2Ins);
					/*		Node2Ins->prior=NODE;
							TAIL->prior=Node2Ins;*/
							DuNodeCounter++;
							NODE=Node2Ins;
					//		EXTRACOST=NODE;
						}
						HEAD->data=DuNodeCounter;
						TAIL->data=DuNodeCounter;
	//					EXTRACOST->next=NULL;
	//					TAIL->prior->next=NULL;
						HEAD->prior=NULL;
						TAIL->next=NULL;
						NODE->next=NULL;
			//			free(NODE);
						getchar();
						printf("成功创建链表\n");
					}
					else 
						printf("创建链表不成功,应先进行初始化\n"); 
					break;
				case 8:
					printf("%d\n" ,e);
					break; 
			}
		
		}
		else
			printf("请输入正确的数字\n");
	}
EXIT:	return 0;
}
