#include "../head/LinkStack.h"
#include <stdlib.h>
#include <stdio.h>
void PrintTheTable()  //��ӡһ������ѡ���� 
{
	printf("��		�����������Щ�������������������������������������������������������		\n");
	printf("��		  1  ��         ��ʼ��ջ          ��		\n");
	printf("��		�����������੤������������������������������������������������������		\n");
	printf("��		  2  ��         �ж�ջ�Ƿ�Ϊ��    ��		\n");
	printf("��		�����������੤������������������������������������������������������		\n");
	printf("׼		  3  ��	       �ҵ�ջ��Ԫ��      ��		\n");
	printf("��		�����������੤������������������������������������������������������		\n");
	printf("��		  4  ��         �������ջ        ��		\n");
	printf("��		�����������੤������������������������������������������������������		\n");
	printf("��		  5  ��         ����˳��ջ        ��		\n");
	printf("��		�����������੤������������������������������������������������������		\n");
	printf("��		  6  ��         ���ջ�ĳ���      ��		\n");
	printf("��		�����������੤������������������������������������������������������		\n");
	printf("��		  7  ��         ��ջ              ��		\n");
	printf("��		�����������੤������������������������������������������������������		\n");
	printf("׼		  8  ��         ��ջ              ��		\n");
	printf("��		�����������੤������������������������������������������������������		\n");
	printf("��		  0  ��         �˳�              ��		\n");
	printf("��		�����������ة�������������������������������������������������������		\n");
}
void PrintStack(LinkStack pt) //��ȡջ�е�����
{
	printf("ջ�������ɶ�����Ϊ:");
	for (int i = 0; i < pt.count; i++)
	{
		printf("%d ", pt.top->data);
		pt.top = pt.top->next;
	}
	printf("\n");
}
int arr[5] = { 1,2,3,4,5 };  //�����õ�ջ������
int main()
{
	LinkStack* pt= (LinkStack*)malloc(sizeof(LinkStack));
	int Len = 0,Data2Push=0,DataPoped=0,LegalInputFlag=0,FunNum=0,TopNum=0;  //LegalInputFlagΪ�Ƿ��ַ�״̬λ 0Ϊ�Ƿ�����
	pt->count = 0;
	pt->top = NULL;
	printf("������һ��ջ�Թ�����\n");
	//�����ṩһ�����Բ��Ե�ջ
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
		printf("��������Ҫѡ��Ĺ���(����Ƿ��ַ����ع��ܱ��):");
		//����ѡ�񲿷�
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
					printf("ջ��ʼ���ɹ�\n");
				else
					printf("ԭջδ���ٻ��ڴ�ռ䲻�㣬��ʼ��ʧ��\n");
				break;
			case 2:
				if (pt != NULL)  //���ж�ջ�Ƿ���� pt->topΪNULLʱջ������ pt->top->next ΪNULLʱջΪ��
				{
					if (isEmptyLStack(pt))
						printf("ջΪ��\n");
					else
						printf("ջ��Ϊ��\n");
				}
				else
					printf("���ȴ���һ��ջ\n");
				break;
			case 3:
				printf("%p", pt);
				if (getTopLStack(pt, &TopNum))
					printf("�ɹ���ȡջ��Ԫ��%d\n", TopNum);
				else
					printf("��ȡʧ�ܣ���ȷ��ջ�Ƿ񱻴�������ջ������Ԫ��\n");
				break;
			case 4:
				if (clearLStack(pt))
					printf("�������ɹ�\n");
				else
					printf("���ʧ�ܣ������ַ��Ч��ջΪ��\n");
				break;
			case 5:
				PrintStack(*pt);
				if (destroyLStack(pt))
				{	
					free(pt);
					pt = NULL;
					printf("%p", pt);
					printf("����ջ�ɹ�\n");
				}
				else
					printf("����ʧ�ܣ������ַ��Ч��ջΪ��\n");
				break;
			case 6:
				if (LStackLength(pt, &Len))
				{
					printf("��ȡ����%d�ɹ�\n", Len);
					PrintStack(*pt);
				}
				else
					printf("��ȡʧ�ܣ����ȴ���һ��ջ\n");
				break;
			case 7:
				while (!LegalInputFlag)  //��Ϊ�Ƿ�����
				{
					while (getchar() != '\n');  //ȡ������ֱ���س�
					printf("��������ȷ������:");
					LegalInputFlag = scanf("%d", &Data2Push);  //��û�ж���Ϸ���������LegalInputFlagΪ0���ٴν���ѭ��
					printf("\n");
				}
				if (pushLStack(pt, Data2Push))
				{
					printf("��ջ�ɹ�\n");
					PrintStack(*pt);
				}
				else
					printf("��ջʧ��,����ջ����������Ҫ�ȴ���һ��ջ\n");
				while (getchar() != '\n');
				break;
			case 8:
				if (popLStack(pt, &DataPoped))
				{
					printf("��ջ�ɹ�����ջԪ��Ϊ%d\n", DataPoped);
					PrintStack(*pt);
				}
				else
					printf("��ջʧ��,��ʱջ��û��Ԫ��\n");
				break;
			default:
				printf("��������ȷ��������ѡ����\n");
				break;
			}
			printf("��������Ҫѡ��Ĺ���(����Ƿ��ַ����ع��ܱ��):");
		}
		while (getchar() != '\n');
		printf("��������ȷ������\n");
	}
// ����
//	printf("�Ƿ��ʼ��%p %p %d ",pt, pt->top, initLStack(pt));
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