#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a,b) a>b?a:b  
int result=1;
int main() 
{	
	char *p=(char*) malloc(1000*sizeof(char));
	int TEMP=0;
	printf("������Ҫ���Ե��ַ���:"); 
	while(scanf("%s", p)!=EOF)
	{
		//���ҵ�������ַ������е㣬���ڲ�ȷ�����ַ����ĸ�λ���Լ���֪�����ĳ��ȵ���ż��
		//ʹ�ñ����ҵ��е� 
		//���Ҳ��� 
		int LEN=0,BEG=0,MID=0,END=0,OEflag=0;  //OEflag ��ż��־λ 1Ϊż  0Ϊ�� 
		LEN=strlen(p);
		TEMP=0; 			    //�ݴ� END-BEG+ ����ǰ����� 
		for(MID=1;MID<LEN;MID++) //����Ϊ����ʱ�ı��� 
		{
			BEG=END=MID;   // ����  
			while(p[BEG]==p[END]&&BEG&&(LEN-1-END)) //����ֱ�����ַ���Ƭ�εĵ�һλ���������һλ														 
			{									//��BEG�ƶ�p�Ŀ�ͷ����END�Ƶ�LENʱֹͣ����	 
				if(p[BEG-1]!=p[END+1])
					break; 
				BEG--;
				END++;
			}
			if(END-BEG+1>TEMP)   //�жϳ����Ƿ��ǰһ�α����ҵ����ַ����� 
			{
				result=MID;      //��result��¼��ʱ���е�λ�� 
				TEMP=END-BEG+1;  //���µĳ�������TEMP 
			}
		}
		for(MID=1;MID<LEN;MID++) //����Ϊż��ʱ�ı���
		{
			BEG=MID-1;    //ż�� 
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
				OEflag=1;   //ż�����ȳ�������  ��ż��־λ��1 
				result=MID;
				TEMP=END-BEG+1;
			}
		}
		//������� 
		MID=result;   
		if(!OEflag)      //�����Ϊż 
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
		printf("�������:"); 
		for(int i=BEG;i<END+1;i++)
		{
			if(BEG==END)
			{
				printf("û���ҵ������ַ���\n");
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
