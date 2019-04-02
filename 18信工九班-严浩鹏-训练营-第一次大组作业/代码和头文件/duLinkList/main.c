#include "../head/duLinkedList.h"
#include<stdio.h>
#include<stdlib.h>
int DuNodeCounter;
void PrintTheTable()  //��ӡһ������ѡ���� 
{
    printf("��		�����������Щ�������������������������������������������������������		\n");
    printf("��		  1  ��        ��ʼ������         ��		\n");		
    printf("��		�����������੤������������������������������������������������������		\n");
    printf("��		  2  ��         ��������          ��		\n");		
    printf("��		�����������੤������������������������������������������������������		\n");
    printf("׼		  3  ��        ǰ�����ڵ�       ��		\n");		
    printf("��		�����������੤������������������������������������������������������		\n");
    printf("��		  4  ��        �������ڵ�       ��		\n");		
    printf("��		�����������੤������������������������������������������������������		\n");
    printf("��		  5  ��         ɾ���ڵ�          ��		\n");		
    printf("��		�����������੤������������������������������������������������������		\n");
    printf("��		  6  ��         ��������          ��		\n");		
    printf("��		�����������੤������������������������������������������������������		\n");
    printf("��		  7  ��         ��������          ��		\n");
    printf("��		�����������ة�������������������������������������������������������		\n");
    printf("��		  8  ��         ���e             ��		\n");
    printf("��		�����������ة�������������������������������������������������������		\n");
    printf("��		  0  ��          �˳�             ��		\n");
    printf("��		�����������ة�������������������������������������������������������		\n");
}
/*DuLNode* CreatList()  //�����ڵ�ĺ��� 
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
	int status=0,FunNum=0,e=0,flag=0;;  //status��ȡscanf����ֵ����¼����״̬  
	DuLNode *HEAD,*NODE,*TAIL,*Node2Ins,*EXTRACOST;				//e��¼��ɾ���ڵ��ֵ 
    while(1)
 	{
		PrintTheTable();
		printf("���зǷ������ѭ����ӡ��������ĵȴ�\n");
		printf("��������Ҫѡ��Ĺ���ǰ������(1-12,����0�˳�)��");	
	//	printf("%d", status);
		status=scanf("%d", &FunNum); //scanf����ֵΪ��ȡ������ֵ����,����ȡ�������ͷ���0 
		getchar();//ȡ�߻��������� 
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
						printf("�ɹ���ʼ������\n");
					else
						printf("��ʼ��ʧ��\n"); 
					break;
				case 2:
					if(HEAD&&DuNodeCounter) //��������ͷָ���Լ���������Ľڵ������Ϊ0 
					{
						DestroyList_DuL(&HEAD);
						printf("�����Ѿ�������\n"); 
					}
					else
						printf("����ʧ�ܣ�Ҳ����ȴ���һ������\n");
					break; 
				case 3:
					if(HEAD&&DuNodeCounter)
					{	
						TraverseList_DuL(HEAD, PrintData);
						printf("\n�������ĸ��ڵ�ǰ�����ڵ���(����ڵ������Լ��ڵ�����ݣ���1��ʼ):");
						DuLNode *InsedNode=HEAD,*InsNode=(DuLNode*)malloc(sizeof(DuLNode));
						scanf("%d %d", &Num, &(InsNode->data));
						if(Num>(DuNodeCounter+1))
						{
							Num=0;  //������Χ��Num��0���������Forѭ�� 
							printf("������Χ��\n"); 
						}
						for(;Num>0;Num--)
							 InsedNode=InsedNode->next;
						if(InsertBeforeList_DuL(InsedNode, InsNode))
						{
							DuNodeCounter++;  //�����ڵ���� 
							HEAD->data=DuNodeCounter;
						}
					}
					else
						printf("����ʧ�ܣ�Ҳ����ȴ���һ���ǿ�����\n"); 
					break;
				case 4:
					if(HEAD&&DuNodeCounter)
					{	
						TraverseList_DuL(HEAD, PrintData);
						printf("\n�������ĸ��ڵ�������ڵ���(����ڵ������Լ��ڵ�����ݣ���1��ʼ):");
						DuLNode *InsedNode=HEAD,*InsNode=(DuLNode*)malloc(sizeof(DuLNode));
						InsNode->next=NULL; 
						scanf("%d %d", &Num, &(InsNode->data));
						if(Num>(DuNodeCounter))
						{
							Num=0;  //������Χ��Num��0���������Forѭ�� 
							printf("������Χ��\n"); 
						}
						for(;Num>0;Num--)
							 InsedNode=InsedNode->next;
						if(InsertAfterList_DuL(InsedNode, InsNode))
						{
							DuNodeCounter++;  //�����ڵ���� 
							HEAD->data=DuNodeCounter;
						}
						else
							printf("����ʧ�ܣ�û������һ����\n"); 
					}
					else
						printf("����ʧ�ܣ�Ҳ����ȴ���һ���ǿ�����\n"); 
					break;
				case 5:
					CurrentNode=HEAD;
					if(HEAD&&DuNodeCounter)
					{ 
						TraverseList_DuL(HEAD, PrintData);
						printf("\n����ɾ���ĸ��ڵ���(����ڵ����ţ���0��ʼ����ɾ�������ݻᱻ������e��):");
						if(scanf("%d", &Num))
						{ 
							getchar();
							if(Num>DuNodeCounter)
							{
								Num=0;
								printf("������Χ��\n");
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
								printf("ɾ��ʧ�ܣ������к���û������ڵ�");
						}
						else
							printf("��������ȷ��ֵ\n"); 
					//	}
					}
					else
						printf("ɾ��ʧ�ܣ�Ҳ����ȴ���һ���ǿ�����\n"); 
					break;
				case 6:
					if(HEAD&&DuNodeCounter)
					{
						printf("�����ɹ�,�������:"); 
					 	TraverseList_DuL(HEAD, PrintData);
					 	printf("\n");
					}
					else 
						printf("�������ɹ������ܸ��ȴ���һ���ǿ�����\n"); 
					 break;
				case 7: 
					if(!HEAD)
					{
						printf("��ʼ�������ݰ�(��������ͽ�������)\n"); 
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
						printf("�ɹ���������\n");
					}
					else 
						printf("���������ɹ�,Ӧ�Ƚ��г�ʼ��\n"); 
					break;
				case 8:
					printf("%d\n" ,e);
					break; 
			}
		
		}
		else
			printf("��������ȷ������\n");
	}
EXIT:	return 0;
}
