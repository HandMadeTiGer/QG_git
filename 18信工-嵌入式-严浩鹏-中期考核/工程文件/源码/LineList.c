#include "../头文件/LineList.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "../头文件/LibraryInit.h"
extern FILE *Bookfp, *Logfp, *Readerfp, *Queuefp,*tempfp;  //依次为存书本信息、日志、读者、预约队列信息、修改时暂时的文件指针
extern BookNode* Bookpt;   //Bookpt为全局变量，其中的SpareNum为每一本书分配书号
Status IsLeapYear(int year)  //闰年判断
{
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 1 : 0;
}
long long GetReturnTime()  //获取还书日期，一月后归还
{
	int a, b, c;
	long long TIME;
	time_t temp;
	struct tm *t;
	time(&temp);
	t = localtime(&temp);
	a = t->tm_year + 1900;
	b = t->tm_mon + 1; 
	c = t->tm_mday;
	if (IsLeapYear(a) && (b == 1) && (c - 29 > 0))  //若为闰年处理情况
	{
		b += 2;
		c = c - 29;
	}
	else if (!IsLeapYear(a) && (b == 1) && (c - 28 > 0))
	{
		b += 2;
		c = c - 28;
	}
	else if (c == 31)
	{
		b += 2;
		c = 1;
	}
	else
		b += 1;
	TIME = a * 10000 + b * 100 + c;
	return TIME;
}
Status GetBookInf(BookInf *Book)
{
	fprintf(Logfp, "%lld", GetTime());  //将时间写入文件
	int Sum = 0;         //Sum为校验，若输入数据项等于预设，获取信息成功
	Book->BookID = Bookpt->Book.TotalNum;   //为新书分配书号
	fprintf(Logfp, "%d", Book->BookID);   //输出到文件
	fputc('\n', Logfp);             //输出回车换行
	printf("请输入书名:");
	fprintf(Logfp, "%s", "请输入书名:");
	Sum += scanf("%s", Book->BookName);
	fprintf(Logfp, "%s", Book->BookName);
	fputc('\n', Logfp);
	printf("请输入作者:");
	fprintf(Logfp, "%s", "请输入作者:");
	Sum += scanf("%s", Book->Author);
	fprintf(Logfp, "%s", Book->Author);
	fputc('\n', Logfp);
	printf("请输入入库数:");
	fprintf(Logfp, "%s", "请输入入库数:");
	if (scanf("%d", &(Book->TotalNum)))
		Sum++;
	else
		while (getchar() != '\n');
	fprintf(Logfp, "%d", Book->TotalNum);
	fputc('\n', Logfp);
	Book->SpareNum = Book->TotalNum;    
	if (Sum == 3) //若输入数据的数目等于3入库成功
		return SUCCESS;
	return ERROR;
}
Status AddBook(BookNode *p, BookInf AddedBook)
{
	int counter = 0;  //记录书的次序
	if (p->next->Book.SpareNum == 0)   //若为第一本书，将其存储在头的下一节点
	{
		p->next->Book = AddedBook;      //修改头节点的下一节点的数据
		p->next->AppointerQueue = malloc(sizeof(LQueue));  //为队列分配一个空间
		p->next->AppointerQueue->front = NULL;   //初始化队列
		p->next->AppointerQueue->rear = NULL;
		p->next->AppointerQueue->length = 0;
		p->next->Reader = NULL;
		fwrite(&(p->next->Book), sizeof(BookInf), 1, Bookfp);	//写入文件
	}
	else                     //否则新建节点，将相关信息存放在新节点
	{
		while (p->next != NULL && strcmp(p->Book.BookName, AddedBook.BookName))
		{
			p = p->next;   //将指针移动到next为空的位置或找到相同的书目
			counter++;   //次序计数器++
		}
		if (p != NULL && strcmp(p->Book.BookName,AddedBook.BookName)==0) //找到相同书目
		{
			p->Book.TotalNum += AddedBook.TotalNum;  //总库存量增加
			p->Book.SpareNum += AddedBook.TotalNum;  //现存量增加
			long temp = ftell(Bookfp);     //暂存书本信息文件指针的位置
			fseek(Bookfp, counter * sizeof(BookInf), 0);  //转到修改书目指针位置
			fwrite(&(p->Book), sizeof(BookInf), 1, Bookfp);  //修改文件中书目的相关信息
			fseek(Bookfp, temp, 0);  //回到temp指向的位置
			return ERROR;
		}
		else
		{
			BookNode *NewBook = malloc(sizeof(BookNode));  //为新书分配空间
			NewBook->Book = AddedBook;             //初始化新书信息
			NewBook->Reader = NULL;
			NewBook->AppointerQueue = malloc(sizeof(LQueue));
			NewBook->AppointerQueue->front = NULL;
			NewBook->AppointerQueue->rear = NULL;
			NewBook->AppointerQueue->length = 0;
			p->next = NewBook;     //添加新书到书目目录最后
			NewBook->next = NULL;    
			fwrite(&(NewBook->Book), sizeof(BookInf), 1, Bookfp);  //将新书写入文件
		}
	}
	return SUCCESS;
}
Status DelBook(BookNode *p, char* BookName, BookInf* DeledBook) 
{
	int counter = 0;    //书目位置计数器
	while (p->next != NULL && strcmp(p->next->Book.BookName, BookName) != 0)
	{
		counter++;    //书目位置计数器++
		p = p->next;					//遍历直到找个该书或遍历完库存没有找到该书
	}
	if (p->next == NULL || ( p->Book.SpareNum != p->Book.TotalNum ))           //如果没有找到该书 或者书本现存数不等于书本总数
		return ERROR;
	BookNode *temp = p->next ;  //记录节点的地址以方便释放内存
	*DeledBook = p->next->Book;    //记录被删除的书本信息  
	p->next  = p->next->next;   //指向书目目录的下一节点
	free(temp);          //释放该书本
	temp = NULL;

	return SUCCESS;
}
Status BookStatus(BookNode *p, char* BookName)//获取书本信息
{
	fprintf(Logfp, "%lld", GetTime());  //将时间写入文件
	int counter = 0,i;
	int len = strlen(BookName);
	char temp1[30];
	char temp2[30];
	strcpy(temp1, BookName);
	p = p->next;
	while (p != NULL)   //直到找到所有的书
	{
		for (i = 0; i < len; i++)
			temp2[i] = (p->Book.BookName)[i];
		temp2[i] = '\0';
		if (!strcmp(temp1, temp2))
		{
			counter++;
			printf("┌───────────────────────────────────────────────┐\n");
			printf("│   %30s 书号是", p->Book.BookName);
			printf("%7d│\n", p->Book.BookID);
			printf("│  ------------------------------------------   │\n");
			printf("│   作者为 %30s       │\n", p->Book.Author);
			printf("│  ------------------------------------------   │\n");
			printf("│   剩余数目为 %8d", p->Book.SpareNum);
			printf("   总共数目为 %8d   │\n", p->Book.TotalNum);
			printf("│  ------------------------------------------   │\n");
			if (p->Reader != NULL)
			{
				printf("│   第一个借书且未归还的是 %10lld           │\n", p->Reader->ReaderID);
				printf("│   应该在 %lld 前归还此书                  │\n", p->Reader->ReturnDate);
			}
			else
			{
				printf("│   还没有人在借这本书                          │\n");
			}
			printf("│  ------------------------------------------   │\n");
			if (p->AppointerQueue->front == NULL)
			{
				printf("│   还没有在预约此书                            │\n");
			}
			else
			{
				printf("│   有%10u位读者预约此书                  │\n", p->AppointerQueue->length);
			}
			printf("└───────────────────────────────────────────────┘\n");
		}
		p = p->next;
	}
	if (counter == 0)   //没有找到输入的书
		return ERROR;
	return SUCCESS;
}
int AuthorIndex(BookNode *p, char* AuthorName)  //按读者索引
{
	int counter=0;   //作品计数器
	while (p != NULL)
	{
		if (strcmp(p->Book.Author, AuthorName)==0)
		{
			printf("%s\n", p->Book.BookName);
			fprintf(Logfp, "%s%c", p->Book.BookName, '\n');
			counter++;
		}
		p = p->next;
	}
	if (counter == 0)
		return ERROR;        //没有找到作品
	return counter;
}
void TravelLibray(BookNode *p)  
{
	p = p->next;
	while (p != NULL)  //遍历输出全部书目
	{
		printf("┌───────────────────────────────────────────────┐\n");
		printf("│   %30s 书号是", p->Book.BookName);
		printf("%7d│\n", p->Book.BookID);
		printf("│  ------------------------------------------   │\n");
		printf("│   作者为 %30s       │\n", p->Book.Author);
		printf("│  ------------------------------------------   │\n");
		printf("│   剩余数目为 %8d", p->Book.SpareNum);
		printf("   总共数目为 %8d   │\n", p->Book.TotalNum);
		printf("│  ------------------------------------------   │\n");
		if (p->Reader != NULL)
		{
			printf("│   第一个借书且未归还的是 %10lld           │\n", p->Reader->ReaderID);
			printf("│   应该在 %lld 前归还此书                  │\n", p->Reader->ReturnDate);
		}
		else
		{
			printf("│   还没有人在借这本书                          │\n");
		}
		printf("│  ------------------------------------------   │\n");
		if (p->AppointerQueue->front == NULL)
		{
			printf("│   还没有在预约此书                            │\n");
		}
		else
		{
			printf("│   有%10u位读者预约此书                  │\n", p->AppointerQueue->length);
		}
		printf("└───────────────────────────────────────────────┘\n");
		p = p->next;
	}
}
//读者链表
Status BorrowBook(BookNode *p, char* BookName,long long ID)
{
	long t = 0;      //t暂存书目中文件中的位置
	int counter = 0;   //counter记录书本的次序
	while (p != NULL && strcmp(p->Book.BookName, BookName) != 0)
	{
		p = p->next;       //直到找到书本或者到遍历完书本库存
		counter++;
	}
	if (p == NULL|| p->Book.SpareNum == 0)  //没有找到该书或库存为0
		return ERROR;
	else
	{
		if (p->Reader == NULL)  //如果书本还没有人借阅，将读者信息记入头节点处
		{
			ReaderNode *temp = malloc(sizeof(ReaderNode));    
			temp->ReaderID = ID;
			temp->BookID = p->Book.BookID;
			temp->ReturnDate = GetReturnTime();
			temp->next = NULL;
			p->Reader = temp;
			fwrite(temp, sizeof(ReaderNode), 1, Readerfp);
		}
		else
		{
			while (p->Reader->next != NULL)   //遍历直到找到最后一位借书的读者
				p->Reader = p->Reader->next;
			ReaderNode *temp = malloc(sizeof(ReaderNode));  //temp保存读者信息
			temp->ReaderID = ID;
			temp->ReturnDate= GetReturnTime();
			temp->BookID = p->Book.BookID;
			temp->next = NULL;
			p->Reader->next = temp;
			fwrite(temp, sizeof(ReaderNode), 1, Readerfp);
		}
		p->Book.SpareNum--;   //减少书本现存量
		t = ftell(Bookfp);   //将现存量变化录入书目
		fseek(Bookfp, counter * sizeof(BookInf), 0);
		fwrite(&(p->Book), sizeof(BookInf), 1, Bookfp);
		fseek(Bookfp, t, 0);
	}
	return SUCCESS;
}
Status ReturnBook(BookNode *p, char* BookName, long long ID)
{
	int counter1=0;  //为书本次序计数器
	long t;  //t记录文件指针位置
	while (p != NULL && strcmp(p->Book.BookName, BookName) != 0)  //直到找到书本
	{
		p = p->next;											//或遍历完全部书本
		counter1++;
	}
	if (p == NULL || p->Book.SpareNum == p->Book.TotalNum)  //如果遍历完所有书本
		return ERROR;										//或者书本没有被借出
	else
	{
		while (p->Reader != NULL && p->Reader->ReaderID != ID)//直到找到该读者
			p->Reader = p->Reader->next;					//或遍历完读者信息没有找到该读者
		if (p->Reader == NULL)   //没有找到返回ERROR
			return ERROR;
		else
		{
			ReaderNode *temp = p->Reader;  //temp暂存归还书本读者信息
			p->Reader = p->Reader->next;  
			p->Book.SpareNum++;  //库存量++
			free(temp);  //释放该次借书记录
			temp = NULL;
			t = ftell(Bookfp);   //将变化写入书目
			fseek(Bookfp, sizeof(BookInf)*counter1, 0);
			fwrite(&(p->Book), sizeof(BookInf), 1, Bookfp);
			fseek(Bookfp, t, 0);
		}
	}
	return SUCCESS;
}
Status BorrowBook_sp(BookNode *p, char* BookName, long long ID,int counter)  //特殊借阅，用于预约借书，传入的p即为要借的书目
{
	long t = 0;
	if (p->Reader == NULL)  //如果书本还没有人借阅，将读者信息记入头节点处
	{
		ReaderNode *temp = malloc(sizeof(ReaderNode));  //temp记录读者信息
		temp->ReaderID = ID;
		temp->BookID = p->Book.BookID;
		temp->ReturnDate = GetReturnTime();
		temp->next = NULL;
		p->Reader = temp;
		fseek(Readerfp, 0, 2);  //将Reader文件指针移向末尾
		fwrite(temp, sizeof(ReaderNode), 1, Readerfp); //添加Reader信息
		p->Book.SpareNum--;   //减少书本现存量
	}
	else
	{
		while (p->Reader->next != NULL)   //遍历直到找到最后一位借书的读者
			p->Reader = p->Reader->next;
		ReaderNode *temp = malloc(sizeof(ReaderNode));  //temp保存读者信息
		temp->ReaderID = ID;
		temp->ReturnDate = GetReturnTime();
		temp->next = NULL;
		p->Reader->next = temp;
		fseek(Readerfp, 0, 2);
		fwrite(temp, sizeof(ReaderNode), 1, Readerfp);
		p->Book.SpareNum--;   //减少书本现存量
	}
	t = ftell(Bookfp);   //将库存量变化写入书目
	fseek(Bookfp, counter * sizeof(BookInf), 0);
	fwrite(&(p->Book), sizeof(BookInf), 1, Bookfp);
	fseek(Bookfp, t, 0);
	return SUCCESS;
}
Status BookAppointment(BookNode *p, char* BookName, long long ReaderID)
{
	while (p != NULL && strcmp(p->Book.BookName, BookName) != 0)  //直到找到书本
		p = p->next;											//或遍历完全部书本
	if (p == NULL||p->Book.SpareNum > 0)    //没有找到书目或库存量不为0
		return ERROR;
	else
	{
		AppointNode Appointerinf;  //记录信息
		Appointerinf.ReaderID = ReaderID;
		Appointerinf.BookID = p->Book.BookID;
		AddReaderAppointment(p->AppointerQueue, Appointerinf);  //添加预约，在LQueue中的方法
	}
	return SUCCESS;
}
Status DealAppointment(BookNode* p,long long ReaderID)  //读者每次登入处理预约
{
	p = p->next;  //跳过头节点
	int counter = 0;  //记录书本次序
	AppointNode *temp = malloc(sizeof(AppointNode));
	while (p != NULL)
	{	
		counter++;    //剩余书目不为0且预约长度不为0且ReaderID相等才进入循环
		while (p->Book.SpareNum != 0 && p->AppointerQueue->length != 0 &&p->AppointerQueue->front->ReaderID== ReaderID)
		{
			BorrowBook_sp(p, p->Book.BookName, ReaderID,counter);//特殊借阅处理
			DeLReaderAppointment(p->AppointerQueue); //删除预约信息
		}
		p = p->next;
	}
	return SUCCESS;
}