#include<stdio.h>
#include<stdlib.h>
//����46�����ݾ�׼ 
unsigned long long Res=0;
long double CBT(double num1,double num2)  //�������  num1ΪC���±�  num2ΪC���ϱ� 
{
	if(num2==0)
		return 1;
	if(num2>0)
		return (num1/num2)*CBT(num1-1,num2-1);
}
int main()
{
	printf("����46�����ݾ�׼(���)\n");
    int StairsNum=0;
    printf("�����������Ŀ:\n");
    while(scanf("%d", &StairsNum)!=EOF)
    {
    	int Temp=StairsNum/2+StairsNum%2;   //Temp+i����StairsNum 
        int i=StairsNum/2;    //��ʱiΪ�����������������ֵ 
        while(i+1)  //�����������������ڵ���0ʱ������� 
        {
        	Res+=(unsigned long long)CBT((double)Temp,(double)i); //�����Ӽ�Ϊ�߷� 
        	Temp++;    //ʹTemp+i�ܵ���StairsNum 
        	i--;   //ÿѭ��һ���ÿ�������������һ 
        }
        printf("�߷���%u��\n",Res);
        Res=0;
    }
    return 0;
}
