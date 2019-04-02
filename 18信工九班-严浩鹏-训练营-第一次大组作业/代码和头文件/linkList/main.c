#include "../head/linkedList.h"
#include<stdio.h>
#include<stdlib.h>
int NodeCounter=0;		//����һ��ȫ�ֱ�����¼�ڵ���� 
void PrintTheTable()  //��ӡһ������ѡ���� 
{
    printf("��		�����������Щ�������������������������������������������������������		\n");
    printf("��		  1  ��        ��ʼ������         ��		\n");		
    printf("��		�����������੤������������������������������������������������������		\n");
    printf("��		  2  ��         ��������          ��		\n");		
    printf("��		�����������੤������������������������������������������������������		\n");
    printf("׼		  3  ��         ����ڵ�          ��		\n");		
    printf("��		�����������੤������������������������������������������������������		\n");
    printf("��		  4  ��         ɾ���ڵ�          ��		\n");		
    printf("��		�����������੤������������������������������������������������������		\n");
    printf("��		  5  ��         ��������          ��		\n");		
    printf("��		�����������੤������������������������������������������������������		\n");
    printf("��		  6  ��         ���ҽڵ�          ��		\n");		
    printf("��		�����������੤������������������������������������������������������		\n");
    printf("��		  7  ��         ��ת����          ��		\n");		
    printf("��		�����������੤������������������������������������������������������		\n");
    printf("��		  8  ��     �ǲ��ǻ���������      ��		\n");
    printf("��		�����������੤������������������������������������������������������		\n");
    printf("׼		  9  ��     ��ת������ż���ڵ�    ��		\n");
    printf("��		�����������੤������������������������������������������������������		\n");
    printf("��		  10 ��      �ҵ��м�ڵ�         ��		\n");
    printf("��		�����������੤������������������������������������������������������		\n");
    printf("��		  11 ��         ��������          ��		\n");
    printf("��		�����������੤������������������������������������������������������		\n");
    printf("��		  12 �� �鿴e(���ɾ���Ľڵ��ֵ) ��		\n");
    printf("��		�����������੤������������������������������������������������������		\n");
    printf("��		  0  ��          �˳�             ��		\n");
    printf("��		�����������ة�������������������������������������������������������		\n");
}
LNode* CreatList()  //�����ڵ�ĺ��� 
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
	int status1,status=0,FunNum=0,e=0;  //status��ȡscanf����ֵ����¼����״̬  
	LNode *HEAD;				//e��¼��ɾ���ڵ��ֵ 
 //	HEAD=CreatList();
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
				LNode *CurrentNode=NULL; 
				int Num;
				case 0:
					goto EXIT; 
				case 1:
					if(InitList(&HEAD))
						printf("�ɹ���ʼ������\n");
					else
						printf("��ʼ��ʧ��\n"); 
					break;
				case 2:
					if(HEAD&&NodeCounter) //��������ͷָ���Լ���������Ľڵ������Ϊ0 
					{
						DestroyList(&HEAD);
						printf("�����Ѿ�������\n"); 
					}
					else
						printf("����ʧ�ܣ�Ҳ����ȴ���һ������\n");
					break; 
				case 3:
					if(HEAD&&NodeCounter)
					{	
						TraverseList(HEAD, PrintData);
						printf("\n�������ĸ��ڵ�������ڵ���(����ڵ������Լ��ڵ�����ݣ���1��ʼ):");
						LNode *InsedNode=HEAD,*InsNode=(LNode*)malloc(sizeof(LNode));
						scanf("%d %d", &Num, &(InsNode->data));
							if(Num>(NodeCounter+1))
							{
								Num=0;  //������Χ��Num��0���������Forѭ�� 
								printf("������Χ��\n"); 
							}
							for(;Num>0;Num--)
								 InsedNode=InsedNode->next;
							if(InsertList(InsedNode, InsNode))
							{
								NodeCounter++;  //�����ڵ���� 
								HEAD->data=NodeCounter;
							}
							else
								printf("����ʧ�ܣ�Ҳ����ȴ���һ���ǿ�����\n");
					}
					break;
				case 4:
					CurrentNode=HEAD;
					if(HEAD&&NodeCounter)
					{ 
						TraverseList(HEAD, PrintData);
						printf("\n����ɾ���ĸ��ڵ���(����ڵ����ţ���0��ʼ����ɾ�������ݻᱻ������e��):");
						if(scanf("%d", &Num))
						{
						 	getchar();
							if(Num>NodeCounter)
							{
								Num=0;
								printf("������Χ��\n");
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
									printf("ɾ��ʧ�ܣ������к���û������ڵ�"); 
						}
						else
							printf("��������ȷ������\n"); 
					//	}
					}
					else
						printf("ɾ��ʧ�ܣ�Ҳ����ȴ���һ���ǿ�����\n"); 
					break;
				case 5:
					if(HEAD&&NodeCounter)
					{
						printf("�����ɹ�,�������:"); 
					 	TraverseList(HEAD, PrintData);
					 	printf("\n");
					}
					else 
						printf("�������ɹ������ܸ��ȴ���һ���ǿ�����\n"); 
					 break;
				case 6: 
					if(HEAD&&NodeCounter)
					{ 
						printf("���������������ĸ�����:");
						if(scanf("%d", &Num))
						 {
						 	getchar();
							if(SearchList(HEAD,Num))
								printf("�ҵ���\n"); 
							else
								 printf("�����������û�������\n");
						}
						else 
							printf("��������ȷ����ֵ\n"); 
					}
					else 
						printf("���Ҳ��ɹ������ܸ��ȴ���һ���ǿ�����\n"); 	
					break; 
				case 7:
					if(HEAD&&NodeCounter)
					{ 
						if(ReverseList(&HEAD))
							printf("����ת�ɹ���\n");
						else
							printf("���˵�С���⣬��������ȴ���һ���ǿ�����\n");
					}
					else 
						printf("��ת���ɹ������ܸ��ȴ���һ������\n"); 
					break;
				case 8:
					if(HEAD&&NodeCounter)
					{
						if(IsLoopList(HEAD)) 
							printf("����һ����������\n");
						else
							printf("����������һ����������\n"); 
					}
					else 
						printf("�жϲ��ɹ������ܸ��ȴ���һ���ǿ�����\n"); 
					break;
				case 9:
					if(HEAD&&NodeCounter)
					{ 
						ReverseEvenList(&HEAD);
						printf("��ת�ɹ�\n"); 
					}
					else 
						printf("��ת���ɹ������ܸ��ȴ���һ���ǿ�����\n"); 
					break;
				case 10:
					if(HEAD!=NULL&&NodeCounter)
						printf("������е���%d\n", FindMidNode(&HEAD)->data); 
					else 
						printf("���Ҳ��ɹ������ܸ��ȴ���һ���ǿ�����\n"); 
				 	break;
				case 11: 
					if(!HEAD)
					{
						printf("��ʼ�������ݰ�(��������ͽ�������)\n"); 
						HEAD=CreatList(); 
						printf("�ɹ������������ڿ��Զ�%p���в���\n", HEAD);
					}
					else 
						printf("���������ɹ���Ӧ�Ƚ��г�ʼ��\n"); 
					break;
				case 12: 
					printf("e��ֵ��%d\n", e);
					break;
			}
		
		}
		else
			printf("��������ȷ������\n");
	}
	//����һ��������������ͽ�����������  //��¼�ڵ���� 
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
	getchar();   //ȡ�߻�������δ¼������� */
//	printf("%d\n", HEAD->next->next->data);
//	printf("%d\n", FindMidNode(&HEAD)->data);   //�� 
//	printf("%d", IsLoopList(HEAD));  // 
//	TraverseList(HEAD,PrintData);  //�� 
//	ReverseList(&HEAD); //��
/*	ReverseEvenList(&HEAD);
	HEAD->data=NodeCounter;
	printf("%d\n", HEAD->data);*/
//	TraverseList(HEAD,PrintData); //��  

/*	scanf("%d", &a);
	printf("%d\n", SearchList(HEAD, a));// �� */
/*	DestroyList(&HEAD);  // �� 
	printf("%d\n", HEAD->data);*/ 
/*	DeleteList(HEAD,&e); // �� 
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
