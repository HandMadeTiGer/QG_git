#include <stdio.h>
#include "../head/SqStack.h"
void PrintTheTable()  //��ӡһ������ѡ���� 
{
	printf("��		�����������Щ�������������������������������������������������������		\n");
	printf("��		  1  ��         ��ʼ��˳��ջ      ��		\n");
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
int arr[5] = { 5,4,3,2,1 }; //װ�����ջ������
int main()
{
	int Len=0,FunNum=0,Sizes=0,Data2Push=0,LegalInputFlag=0,TopNum=0,Data2Pop=0; //LegalInputFlagΪ0ʱΪ�Ƿ�����
	printf("���ṩջ����ջ��Ϊ1 2 3 4 5��ջ�Խ��в��ԣ�������Ҫ��������\n");    //��0�Խ��빦�ܲ���ѭ����
	SqStack *pt = (SqStack*)malloc(sizeof(SqStack));
	//������һ�������������Ե�ջ
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
		printf("��������Ҫѡ��Ĺ���:");
		//����ѡ�񲿷�
		while (scanf("%d", &FunNum))
		{
			LegalInputFlag = 0;
			switch (FunNum)
			{
				case 0:
					goto EXIT;
				case 1:
					while(!LegalInputFlag)//��Ϊ�Ƿ�����
					{ 
						while (getchar()!='\n'); //ȡ������ֱ���س�
						printf("��������ȷ��ջ�Ĵ�С:");
						LegalInputFlag = scanf("%d", &Sizes);  //��û�ж���Ϸ���������LegalInputFlagΪ0���ٴν���ѭ��
						printf("\n");
					}
					if (initStack(pt, Sizes))
						printf("ջ��ʼ���ɹ�\n");
					else
						printf("ԭջδ���ٻ��ڴ�ռ䲻�㣬��ʼ��ʧ��\n");
					break;
				case 2:
					if (isEmptyStack(pt))
						printf("ջΪ��\n");
					else
						printf("ջ��Ϊ��\n");
					break;
				case 3:
					if (getTopStack(pt, &TopNum))
						printf("�ɹ���ȡջ��Ԫ��%d\n", TopNum);
					else
						printf("��ȡʧ��\n");
					break;
				case 4:
					if (clearStack(pt))
						printf("�������ɹ�\n");
					else
						printf("���ʧ�ܣ������ַ��Ч��ջΪ��\n");
					break;
				case 5:
					if (destroyStack(pt))
						printf("����ջ�ɹ�\n");
					else
						printf("����ʧ�ܣ������ַ��Ч��ջΪ��\n");
					break;
				case 6:
					if (stackLength(pt, &Len))
						printf("��ȡ����%d�ɹ�\n", Len);
					else
						printf("��ȡʧ��\n");
					break;
				case 7:
					while (!LegalInputFlag)
					{
						while (getchar()!='\n');
						printf("��������ȷ������:");
						LegalInputFlag = scanf("%d", &Data2Push);
						printf("\n");
					}
					if (pushStack(pt, Data2Push))
						printf("��ջ�ɹ�\n");
					else
						printf("��ջʧ��,����ջ����������Ҫ�ȴ���һ��ջ\n");
					while (getchar()!='\n');
					break;
				case 8:
					if (popStack(pt, &Data2Pop))
						printf("��ջ�ɹ�����ջԪ��Ϊ%d\n", Data2Pop);
					else
						printf("��ջʧ��,��ʱջ��û��Ԫ��\n");
					break;
				default:
					printf("��������ȷ��������ѡ����\n");
					break;
			}
			printf("��������Ҫѡ��Ĺ���:");
		}
		while (getchar()!='\n');
		printf("��������ȷ������\n");
	}
EXIT: return 0;
}
