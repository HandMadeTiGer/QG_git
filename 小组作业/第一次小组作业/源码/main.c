#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a,b) a>b?a:b  
int result=1;
int main() 
{	
	char *p=(char*) malloc(1000*sizeof(char));
	int TEMP=0;
	printf("请输入要测试的字符串:"); 
	while(scanf("%s", p)!=EOF)
	{
		//先找到最长回文字符串的中点，由于不确定在字符的哪个位置以及不知道它的长度的奇偶性
		//使用遍历找到中点 
		//查找部分 
		int LEN=0,BEG=0,MID=0,END=0,OEflag=0;  //OEflag 奇偶标志位 1为偶  0为奇 
		LEN=strlen(p);
		TEMP=0; 			    //暂存 END-BEG+ 即当前最长长度 
		for(MID=1;MID<LEN;MID++) //长度为奇数时的遍历 
		{
			BEG=END=MID;   // 奇数  
			while(p[BEG]==p[END]&&BEG&&(LEN-1-END)) //查找直到该字符串片段的第一位不等与最后一位														 
			{									//当BEG移动p的开头或者END移到LEN时停止查找	 
				if(p[BEG-1]!=p[END+1])
					break; 
				BEG--;
				END++;
			}
			if(END-BEG+1>TEMP)   //判断长度是否比前一次遍历找到的字符串长 
			{
				result=MID;      //用result记录此时的中点位置 
				TEMP=END-BEG+1;  //将新的长度移入TEMP 
			}
		}
		for(MID=1;MID<LEN;MID++) //长度为偶数时的遍历
		{
			BEG=MID-1;    //偶数 
			END=MID;
			while(p[BEG]==p[END]&&BEG&&(LEN-1-END))
			{
				if(p[BEG-1]!=p[END+1])
					break; 
				BEG--;
				END++;
			}
			if(END-BEG+1>=TEMP&&(p[BEG]==p[END])) 
			{
				OEflag=1;   //偶数长度超过奇数  奇偶标志位置1 
				result=MID;
				TEMP=END-BEG+1;
			}
		}
		//输出部分 
		MID=result;   
		if(!OEflag)      //如果不为偶 
			BEG=END=MID;
		else
		{
			BEG=MID-1;
			END=MID;
		}
		while(p[BEG]==p[END]&&BEG&&(LEN-1-END))
		{
			if(p[BEG-1]!=p[END+1])
				break; 
			BEG--;
			END++;
		}
		printf("结果如下:"); 
		for(int i=BEG;i<END+1;i++)
		{
			if(BEG==END)
			{
				printf("没有找到回文字符串\n");
				break;
			}
			else 
				printf("%c", p[i]);
		}
		printf("\n");
		result=1;
	}
	return 0;
}
