#include "../../ͷ�ļ�/AQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
void PrintTheTable()  //��ӡһ������ѡ���� 
{
	printf("��		�����������Щ�������������������������������������������������������		\n");
	printf("��		  1  ��        ��ʼ������         ��		\n");
	printf("��		�����������੤������������������������������������������������������		\n");
	printf("��		  2  ��         ���ٶ���          ��		\n");
	printf("��		�����������੤������������������������������������������������������		\n");
	printf("׼		  3  ��      �ж϶����Ƿ�����     ��		\n");
	printf("��		�����������੤������������������������������������������������������		\n");
	printf("��		  4  ��      �ж϶����Ƿ�Ϊ��     ��		\n");
	printf("��		�����������੤������������������������������������������������������		\n");
	printf("��		  5  ��        ��ȡ��ͷԪ��       ��		\n");
	printf("��		�����������੤������������������������������������������������������		\n");
	printf("��		  6  ��        ��ȡ���г���       ��		\n");
	printf("��		�����������੤������������������������������������������������������		\n");
	printf("��		  7  ��            ���           ��		\n");
	printf("��		�����������੤������������������������������������������������������		\n");
	printf("��		  8  ��            ����           ��		\n");
	printf("��		�����������੤������������������������������������������������������		\n");
	printf("׼		  9  ��          ��ն���         ��		\n");
	printf("��		�����������੤������������������������������������������������������		\n");
	printf("��		  10 ��          ��������         ��		\n");
	printf("��		�����������੤������������������������������������������������������		\n");
	printf("��		  0  ��            �˳�           ��		\n");
	printf("��		�����������ة�������������������������������������������������������		\n");
}
int main()
{
	int FunNum = 0; //�洢����ѡ������
	double ERRORNUM = 0;
	void *frontdata; //�洢��ͷԪ��
	AQueue *pt = NULL;
	int *IntInp=NULL;  //ָ�����������
	double *FloatInp=NULL;//ָ������ĸ�����
	char *StrInp=NULL;//ָ��������ַ�(��)
	int IntFlag = 0, FloatFlag = 0, StrFlag = 0, DotFlag = 0, MinFlag = 0; //��¼����״̬��DotFlag��¼С������ֵ�λ��
	elem_str* elem2Inp;  //���뵽data[MAXQUEUE]�е�Ԫ��
	PrintTheTable();
	while (1)
	{
		printf("��ѡ����:");
		while (!scanf("%d", &FunNum))
		{
			printf("��������ȷ������:");
			while (getchar() != '\n');
		}
		switch (FunNum)
		{
			case 0:
				goto EXIT;
			case 1:
				if (pt != NULL)
					printf("�������ٶ���\n");
				else
				{
					pt = malloc(sizeof(AQueue));  //������ָ��pt����ַ
					InitAQueue(pt);
					printf("��ʼ���ɹ�\n");
				}
				break;
			case 2:
				if (pt == NULL)
					printf("�����ַΪ��\n");
				else
				{
					DestoryAQueue(pt);
					printf("���ٳɹ�\n");
					free(pt);   //���ٶ���ָ��
					pt = NULL;   //ָ������
				}
				break;
			case 3:
				if (pt == NULL)
					printf("�����ַΪ��\n");
				else if (IsFullAQueue(pt))
				{
					printf("��������\n");
				}
				else
					printf("����δ��\n");
				break;
			case 4:
				if (pt == NULL)
					printf("�����ַΪ��\n");
				else if (IsEmptyAQueue(pt))
					printf("����Ϊ��\n");
				else
					printf("���в�Ϊ��\n");
				break;
			case 5:
				if (GetHeadAQueue(pt, &frontdata))  //����frontdata��ָ�����޸�frontdata��ָ��
				{
					printf("��ͷ��Ԫ��Ϊ:");
					elem_str *temp = (elem_str*)frontdata;  //temp��¼frontdata voidָ��ָ����ڴ�
					if (temp->elemtype == 0)				
						printf("%d ", *((int*)(temp->data)));
					else if (temp->elemtype == 1)
						printf("%lf ", *((double*)(temp->data)));
					else if (temp->elemtype == 2)
						printf("%s ", ((char*)(temp->data)));
					printf("\n");
				}
				else
					printf("���ܻ�ȡ��ͷ��Ԫ��\n");
				break;
			case 6:
				if (pt == NULL)
					printf("�����ַΪ��\n");
				else
					printf("���еĳ���Ϊ%d\n", LengthAQueue(pt));
				break;
			case 7:
				//���봦��
				if(pt!=NULL)
				{
					getchar();  //ȡ�߻��з�
					printf("����������:");
					IntFlag = 0, FloatFlag = 0, StrFlag = 0, DotFlag = 0, MinFlag = 0;//����С����ʱDotFlag��¼λ��
					IntInp = malloc(sizeof(int));
					FloatInp = malloc(sizeof(double));
					StrInp = malloc(sizeof(char) * 100);
					elem2Inp = malloc(sizeof(elem_str));
					*IntInp = 0;
					*FloatInp = 0;
					*StrInp = 0;
					int i = 0;
					while ((StrInp[i] = getchar()) != '\n'&& i < 100)  //�����벻Ϊ���з��ҳ��Ȳ�����100ʱ
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
					{  //������ֱ�Ϊ  ������   ������     ��������   ��������   ʱ�����
						if (!DotFlag && IntFlag < 12) // int���Ϳɴ洢������ݣ�������洢Ϊ�ַ���
						{
							for (int i = 0 + MinFlag; i < IntFlag + MinFlag; i++)  //����Ϊ��ʱ��MinFlagΪ1 ����������ַ����ĵ�һ���ַ� Ϊ��ʱ�ӵ�һ���ַ���ʼ
								*IntInp += -((MinFlag%10)*2-1) * ((int)StrInp[i] - '0')*(int)pow(10, IntFlag + MinFlag - i - 1);
							elem2Inp->data = IntInp;    //-((MinFlag%10)*2-1) ��MinFlag Ϊ1ʱ����-1��Ϊ0ʱ����1 pow()����������Ϊ�ַ���Ӧ���͵Ľ�λ����
							elem2Inp->elemtype = 0;     //��IntFlag=3, MinFlag=0�� i=1 ��ʮλ �����Ӧ�ַ������ַ���ʱΪ'2' IntInp Ӧ�� 20
							free(StrInp);
						}
						else if (DotFlag && IntFlag < 16)  //  double˫���ȿɴ洢������ݣ�������洢Ϊ�ַ���
						{
							for (int i = 0 + MinFlag; i < DotFlag + MinFlag; i++)
								*FloatInp += -((MinFlag%10)*2-1) * ((double)StrInp[i] - '0') * pow(10, DotFlag + MinFlag - i - 1);
							for (int i = DotFlag + 1 + MinFlag; i < IntFlag + 1+ MinFlag; i++)
								*FloatInp += -((MinFlag%10)*2-1) * ((double)StrInp[i] - '0') * pow(10, DotFlag + MinFlag - i);
							elem2Inp->data = FloatInp;                      //ͬ�ϣ���С����Ϊ0λ��С�����һλΪ����λ
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
						printf("��ӳɹ�\n");
					}
					else
					{
						printf("���ʧ��,��������\n");
					}
				}
				else
					printf("���ʧ��\n");
				break;
			case 8:
				if (DeAQueue(pt))
					printf("���ӳɹ�\n");
				else
					printf("����ʧ��\n");
				break;
			case 9:
				if (pt != NULL)
				{
					ClearAQueue(pt);
					printf("�ɹ���ն���\n");
				}
				else
					printf("��ն���ʧ��\n");
				break;
			case 10:
				if (TraverseAQueue(pt, APrint))
					printf("\n���������������ʾ\n");
				else
					printf("����ʧ��\n");
				break;
			default:
				printf("��������ȷ������\n");
				while (getchar() != '\n');
				break;
		}
	}
EXIT:return 0;
}

