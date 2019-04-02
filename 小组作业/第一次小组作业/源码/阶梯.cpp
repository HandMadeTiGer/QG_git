#include<stdio.h>
#include<stdlib.h>
//到第46个阶梯精准 
unsigned long long Res=0;
long double CBT(double num1,double num2)  //计算组合  num1为C的下标  num2为C的上标 
{
	if(num2==0)
		return 1;
	if(num2>0)
		return (num1/num2)*CBT(num1-1,num2-1);
}
int main()
{
	printf("到第46个阶梯精准(大概)\n");
    int StairsNum=0;
    printf("请输入阶梯数目:\n");
    while(scanf("%d", &StairsNum)!=EOF)
    {
    	int Temp=StairsNum/2+StairsNum%2;   //Temp+i等于StairsNum 
        int i=StairsNum/2;    //此时i为可走两步步数的最大值 
        while(i+1)  //当可走两步步数大于等于0时计算组合 
        {
        	Res+=(unsigned long long)CBT((double)Temp,(double)i); //组合相加即为走法 
        	Temp++;    //使Temp+i总等于StairsNum 
        	i--;   //每循环一次让可走两步步数减一 
        }
        printf("走法有%u种\n",Res);
        Res=0;
    }
    return 0;
}
