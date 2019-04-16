#include "FGUI.h"
#include "LineList.h"
#include "LQueue.h"
#include "LibraryInit.h"
#include <stdio.h>
char* RootPassword = "whosyourdaddy";  //管理员密码
long long ReaderID;
FILE *Bookfp, *Logfp, *Readerfp, *Queuefp, *tempfp;
BookNode *Bookpt;
BookNode *FirstBook;
int main()
{
	if ((Bookfp = fopen("Book", "rb+")) == NULL)   
	{
		printf("无法打开文件\n");
		exit(0);
	}
	if ((Logfp = fopen("Log", "a")) == NULL)
	{
		printf("无法打开文件\n");
		exit(0);
	}
	if ((Readerfp = fopen("Reader", "rb+")) == NULL)
	{
		printf("无法打开文件\n");
		exit(0);
	}
	if ((Queuefp = fopen("Queue", "rb+")) == NULL)
	{
		printf("无法打开文件\n");
		exit(0);
	}
	int Cho = 0, Num=0;    //Cho记录功能选择，Num记录读者作品数
	char StrInp[30];      //处理输入的字符
	long long date = GetTime();  //获得系统时间
	printf("DATE:%lld\n", date);   
	Bookpt = malloc(sizeof(BookNode));  //创建头节点
	if (fgetc(Bookfp) == EOF)  //如果文件为空
	{
		strcpy(Bookpt->Book.Author, "yhp");  //初始化头节点
		Bookpt->Book.BookID=0;
		strcpy(Bookpt->Book.BookName, "LibraryManageSystem");
		(*Bookpt).Book.TotalNum = 1000;    
		(*Bookpt).Book.SpareNum = 1;   //头节点SpareNum存放书种类数目
		(*Bookpt).AppointerQueue = NULL;
		(*Bookpt).Reader = NULL;
		FirstBook = malloc(sizeof(BookNode));
		strcpy(FirstBook->Book.Author, "0");  //初始化FisrtBook
		FirstBook->Book.BookID=0;
		strcpy(FirstBook->Book.BookName, "0");
		(*FirstBook).Book.TotalNum = 0;
		(*FirstBook).Book.SpareNum = 0;
		(*FirstBook).AppointerQueue = NULL;
		(*FirstBook).Reader = NULL;
		Bookpt->next = FirstBook;
		Bookpt->Reader = NULL;
		FirstBook->next = NULL;
		rewind(Bookfp);
		fwrite(&(Bookpt->Book), sizeof(BookInf), 1, Bookfp);		 //将头结点书目写入文件
	}
	else
	{
		rewind(Bookfp);
		fread(&(Bookpt->Book), sizeof(BookInf), 1, Bookfp);  //读取文件中的头结点书目信息，写入内存
		Bookpt->next = malloc(sizeof(BookNode));
		Bookpt->next->next = NULL;
		Bookpt->AppointerQueue = malloc(sizeof(AppointNode));
		Bookpt->AppointerQueue->length = 0;
		Bookpt->Reader = NULL;
		LoadBook(Bookfp, Readerfp, Queuefp, Bookpt);   //加载上次程序结束后的书本状态
	}
	BookInf *Book;  //书本信息指针，用以处理书本的信息
	//文件
	fprintf(Logfp, "%lld", date);  //将时间写入文件
	fputc('\n', Logfp);
	//登录界面
	while(1)
	{
		Cho = Login();   //接收登录状态
		if (Cho == 1)
		{
			fprintf(Logfp, "%s", "管理员登录\n");
			while (Cho != 0)
			{
				RootFGui();  //输出管理员界面
				printf("请输入数字以选择功能:");
				fprintf(Logfp, "%s", "请输入数字以选择功能:");
				while (!scanf("%d", &Cho))  //没有接收到整型报错并要求重新输入
				{
					printf("请输入正确的数字:");
					fprintf(Logfp, "%s", "请输入正确的数字:");
					char t[30];
					scanf("%s", t);
					fprintf(Logfp, "%s", t);
					while (getchar() != '\n');
				}
				fprintf(Logfp, "%d", Cho);
				fputc('\n', Logfp);
				switch (Cho)
				{
					case 0:
						fprintf(Logfp, "%s", "退出\n");
						break;
					case 1:
						//添加书本
						Book = malloc(sizeof(BookInf));
						GetBookInf(Book);
						if (AddBook(Bookpt, *Book))
						{
							Bookpt->Book.SpareNum++;  //书目种类++
							long temp = ftell(Bookfp);
							rewind(Bookfp);  //回到头节点改变书目种类数
							fwrite(&(Bookpt->Book), sizeof(BookInf), 1, Bookfp);
							fseek(Bookfp, temp, 0);
							printf("添加成功\n");
							fprintf(Logfp, "%s", "添加成功\n");
						}
						else
						{
							printf("已增加书目库存\n");
							fprintf(Logfp, "%s", "已增加书目库存\n");
						}
						break;
					case 2:
						Book = malloc(sizeof(BookInf));  
						printf("输入要清除的书的书名:");
						fprintf(Logfp, "%s", "输入要清除的书的书名:");
						scanf("%s", StrInp);
						fprintf(Logfp, "%s%c", StrInp, '\n');
						if (DelBook(Bookpt, StrInp, Book))
						{
							long temp = ftell(Bookfp);   //改变书目种类
							rewind(Bookfp);
							fwrite(&(Bookpt->Book), sizeof(BookInf), 1, Bookfp);
							fseek(Bookfp, temp, 0);
							RelordBook(Bookpt);  //将变化写到文件
							printf("清除成功\n");
							fprintf(Logfp, "%s", "清除成功\n");
						}
						else
						{
							printf("清除失败，请等待所有的书本被归还\n");
							fprintf(Logfp, "%s", "清除失败\n");
						}
						break;
					case 3:
						printf("请输入要查找的作者名:");
						fprintf(Logfp, "%s", "请输入要查找的作者名:");
						scanf("%s", StrInp);
						fprintf(Logfp, "%s%c", StrInp, '\n');
						Num = AuthorIndex(Bookpt, StrInp);    //接收状态
						if (!Num)
						{
							printf("没有该作者的作品\n");
							fprintf(Logfp, "%s", "没有该作者的作品\n");
						}
						else
						{
							printf("总共有以上%d种该作者的作品\n", Num);
							fprintf(Logfp, "%s%d%s","总共有以上",Num, "种该作者的作品\n");
						}
						break;
					case 4:
						printf("输入要查看的书的书名:");
						fprintf(Logfp, "%s", "输入要查看的书的书名:");
						scanf("%s", StrInp);
						fprintf(Logfp, "%s%c", StrInp, '\n');
						if (!BookStatus(Bookpt, StrInp))   //没有获取到书本状态
						{
							printf("获取失败，书库中没此书\n");
							fprintf(Logfp, "%s", "获取失败，书库中没此书\n");
						}
						break;
					case 5:
						TravelLibray(Bookpt);
						break;
					default:
						printf("输入有误\n");
						fprintf(Logfp, "%s", "输入有误\n");
						break;
				}
			}
		}
		else if(Cho==2)
		{
			DealAppointment(Bookpt, ReaderID);  //处理用户预约
			fprintf(Logfp, "%s", "用户登录\n");
			while (Cho != 0)
			{
				ReaderFGui();		
				printf("请输入数字以选择功能:");
				fprintf(Logfp, "%s", "请输入数字以选择功能:");
				while (!scanf("%d", &Cho))
				{
					printf("请输入正确的数字:");
					fprintf(Logfp, "%s", "请输入正确的数字:");
					char t[30];
					scanf("%s", t);
					fprintf(Logfp, "%s", t);
					while (getchar() != '\n');
				}
				fprintf(Logfp, "%d%c", Cho, '\n');
				switch (Cho)
				{
				case 0:
					fprintf(Logfp, "%s", "退出\n");
					break;
				case 1:
					printf("输入要借阅的书的书名:");
					fprintf(Logfp, "%s", "输入要借阅的书的书名:");
					scanf("%s", StrInp);
					fprintf(Logfp, "%s%c", StrInp, '\n');
					if (BorrowBook(Bookpt, StrInp, ReaderID))
					{
						printf("借阅成功，请于%lld前归还\n", GetReturnTime());
						fprintf(Logfp, "%s%lld%s", "借阅成功，请于", GetReturnTime(), "前归还\n");
					}
					else
					{
						printf("借阅失败，现存图书库中没有此书\n");
						fprintf(Logfp, "%s", "借阅失败，现存图书库中没有此书\n");
					}
					break;
				case 2:
					printf("输入要归还的书的书名:");
					fprintf(Logfp, "%s", "输入要归还的书的书名:");
					scanf("%s", StrInp);
					fprintf(Logfp, "%s%c", StrInp, '\n');
					if (ReturnBook(Bookpt, StrInp, ReaderID))
					{
						printf("归还成功，请继续保持阅读习惯\n");
						fprintf(Logfp, "%s", "归还成功，请继续保持阅读习惯\n");
						RelordReader(Bookpt);
					}
					else
					{
						printf("归还失败，书本没有被借出或库中没有此书\n");
						fprintf(Logfp, "%s", "归还失败，书本没有被借出或库中没有此书\n");
					}
					break;
				case 3:
					printf("输入要查找的作者的名字:");
					fprintf(Logfp, "%s", "输入要查找的作者的名字:");
					scanf("%s", StrInp);
					fprintf(Logfp, "%s%c", StrInp, '\n');
					Num = AuthorIndex(Bookpt, StrInp);
					if (!Num)
					{
						printf("没有该作者的作品\n");
						fprintf(Logfp, "%s", "没有该作者的作品\n");
					}
					else
					{
						printf("总共有以上%d种该作者的作品\n", Num);
						fprintf(Logfp, "%s%d%s", "总共有以上", Num, "种该作者的作品\n");
					}
						break;
					case 4:
						printf("输入要查找的书名:");
						fprintf(Logfp, "%s", "输入要查找的书名:");
						scanf("%s", StrInp);
						fprintf(Logfp, "%s%c", StrInp, '\n');
						BookStatus(Bookpt, StrInp);
						break;
					case 5:
						TravelLibray(Bookpt);
						break;
					case 6:
						printf("输入要预约的书名:");
						fprintf(Logfp, "%s", "输入要预约的书名:");
						scanf("%s", StrInp);
						fprintf(Logfp, "%s%c", StrInp, '\n');
						if (BookAppointment(Bookpt, StrInp, ReaderID))
						{
							printf("预约成功\n");
							fprintf(Logfp, "%s", "预约成功\n");
						}
						else
							printf("库存中没有此书或此书库存量不为零\n");
						break;
					default:
						printf("请输入正确的数字:");
						break;
				}
			}
		}
		else			
			break;
	}
	fputc('\n', Logfp);
	fclose(Readerfp);
	fclose(Queuefp);
	fclose(Bookfp);
	fclose(Logfp);
	return 0;
}
