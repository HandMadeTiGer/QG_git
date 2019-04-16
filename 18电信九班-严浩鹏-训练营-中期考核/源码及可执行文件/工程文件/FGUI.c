#include "FGUI.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LibraryInit.h"
extern char* RootPassword;  //管理员密码在main.c中定义
extern long long ReaderID;  //ReaderID需要在main.c中被使用
extern FILE *Logfp;  //此文件中部分
int Login()
{
	int Funcho=0;
	char *password=malloc(sizeof(char)*15);
	*password = 0;
login:printf("─────┬───────────────────────────┐		\n");
	  printf("  1  │        管理员登录         │		\n");
	  printf("─────┼───────────────────────────┤		\n");
	  printf("  2  │         读者登录          │		\n");
	  printf("─────┼───────────────────────────┤		\n");
	  printf("  0  │           退出	   	 │		\n");
	  printf("─────┴───────────────────────────┘		\n");
	printf("输入数字以选择功能:");
	fprintf(Logfp, "%s", "输入数字以选择功能:");
	while (!scanf("%d", &Funcho))  //如果没有接收到整型返回0
	{
		printf("\n请输入正确的数字:");  
		fprintf(Logfp, "%s", "请输入正确的数字:");
		char t[30];  //t暂存错误输入
		scanf("%s", t);  //取走缓冲区中的错误输入
		fprintf(Logfp, "%s", t);  //把错误输入写进文件log
		while (getchar() != '\n');   //取缓存区到发现换行符
	}
	fprintf(Logfp, "%d%c", Funcho, '\n');  //接收到正确输入，写入文件
	if (Funcho == 1)   //为1则是管理员登入模式
	{
		printf("请输入密码以登录(输入'0'退出登录):");
		fprintf(Logfp, "%s", "请输入密码以登录(输入'0'退出登录):");
		scanf("%s", password);  //要求输入密码
		fprintf(Logfp, "%s%c", password,'\n');  //将输入录入文件log
		while (strcmp(RootPassword, password) != 0)  //比较输入与密码
		{
			if (strcmp("0", password) != 0)  //如果输入不为0
			{
				printf("请输入正确的密码(输入‘0’退出登录):");
				fprintf(Logfp, "%s", "请输入正确的密码(输入'0'退出登录):");
				scanf("%s", password);    
				fprintf(Logfp, "%s%c", password, '\n');
			}
			else
			{
				printf("\n");   // 输入字符为‘0’，返回登录界面
				fprintf(Logfp, "%c", '\n');
				goto login;    //输入为0返回login
			}
		}
	}
	else if (Funcho == 2)  //输入为2为读者登录模式
	{
		ReaderID = 0;
		printf("请输入ID(输入‘0’退出登录)");
		printf("ID长度应小于等于10位:");
		fprintf(Logfp, "%s", "请输入ID(输入‘0’退出登录):");
		while (ReaderID > 1000000000||!scanf("%lld", &ReaderID)) //如果没有接收到长整型返回0
		{														
			printf("请输入正确的ID(输入‘0’退出登录):");
			fprintf(Logfp, "%s", "请输入正确的ID(输入‘0’退出登录):");
			char t[30];  //暂存错误ID
			scanf("%s", t);
			fprintf(Logfp, "%lld", ReaderID);
			fprintf(Logfp, "%s", t);  //输出错误ID到文件
			while (getchar() != '\n');  //取缓存区到发现换行符
		}
		fprintf(Logfp, "%lld%c", ReaderID,'\n');
		if (ReaderID == 0) // 输入为0则返回登录界面
		{
			printf("\n");
			fprintf(Logfp, "%c", '\n');
			goto login;
		}
	}
	else if (Funcho > 3)   //输入大于3则返回输入错误，回到登录界面
	{
		printf("输入错误\n");
		fprintf(Logfp, "%s", "输入错误\n");
		goto login;
	}
	else  //为0则退出程序
		fprintf(Logfp, "%s", "退出\n");
	return Funcho;  //返回值给其余函数以获取登录状态
}
void RootFGui()
{
	printf("┌┌───────────────────────────────────────────────┐┐\n");
	printf("││  0.  退出                    ROOT             ││\n");
	printf("││  ------------------------------------------   ││\n");
	printf("││  1.  入库图书              daipu新闻          ││\n");
	printf("││  ------------------------------------------   ││\n");
	printf("││  2.  清除图书     男子深夜不眠，竟在干这      ││\n");
	printf("││  ------------------------------------------   ││\n");
	printf("││  3.  作者索引     种事情！！！！必看          ││\n");
	printf("││  ------------------------------------------   ││\n");
	printf("││  4.  书本索引     蔡姓男子不堪重负，竟对同    ││\n");
	printf("││  ------------------------------------------   ││\n");
	printf("││  5.  全部图书     性交友网站下手              ││\n");
	printf("││  ------------------------------------------   ││\n");
	printf("││  日期:%lld                                ││\n", GetTime());
	printf("└└──────────────────┬─────┬──────────────────────┘┘\n");
	printf("	            │     │                      \n");
	printf("                   ─┴─────┴─                      \n");
}
void ReaderFGui()
{
	printf("┌┌───────────────────────────────────────────────┐┐\n");
	printf("││  0.  退出       ReaderID:%10lld           ││\n", ReaderID);
	printf("││  ------------------------------------------   ││\n");
	printf("││  1.  借阅图书     请不要更换壁纸              ││\n");
	printf("││  ------------------------------------------   ││\n");
	printf("││  2.  归还图书     不要关闭屏幕                ││\n");
	printf("││  ------------------------------------------   ││\n");
	printf("││  3.  作者索引     不要占座                    ││\n");
	printf("││  ------------------------------------------   ││\n");
	printf("││  4.  书本索引     扬正气，树新风              ││\n");
	printf("││  ------------------------------------------   ││\n");
	printf("││  5.  全部图书     争当一个新时代四有青年      ││\n");
	printf("││  ------------------------------------------   ││\n");
	printf("││  6.  图书预约     日期：%lld              ││\n",GetTime());
	printf("└└──────────────────┬─────┬──────────────────────┘┘\n");
	printf("	            │     │                      \n");
	printf("                   ─┴─────┴─                      \n");
}
