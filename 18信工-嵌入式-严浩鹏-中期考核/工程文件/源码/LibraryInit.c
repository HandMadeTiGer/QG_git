#include "../头文件/LibraryInit.h"
extern FILE *Bookfp, *Logfp, *Readerfp, *Queuefp,*tempfp;
long long GetDate()
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
	TIME = a * 10000 + b * 100 + c;
	return TIME;
}
long long GetTime()
{
	int d, e, f;
	long long TIME;
	time_t temp;
	struct tm *t;
	time(&temp);
	t = localtime(&temp);
	d = t->tm_hour;
	e = t->tm_min;
	f = t->tm_sec;
	TIME = d * 10000 + e * 100 + f;
	return TIME;
}
void LoadBook(FILE* BookPt, FILE* ReaderPt, FILE* QueuePt, BookNode* Bp)
{
	int counter=0;   //书目次序计数器
	int Num = Bp->Book.SpareNum;  //获取书目数+1
	BookInf temp;
	BookNode* NewNode = malloc(sizeof(BookNode));
	ReaderNode *t1 = malloc(sizeof(ReaderNode)),*tempR;
	AppointNode *t2 = malloc(sizeof(AppointNode));
	LQueue *NewQueue = malloc(sizeof(LQueue));
	fseek(BookPt, sizeof(BookInf), 0);  //跳过头节点
	while (counter < Num-1)   //当书目没有到达末尾
	{
		int flag = 0;  //标志位是否将信息写入头结点
		counter++;    //发现书目，counter自加
		fread(&temp, sizeof(BookInf), 1, BookPt);    //temp记录书目信息
		NewNode = malloc(sizeof(BookNode));        //初始化新书目节点
		NewNode->Book = temp;
		NewNode->next = NULL;
		NewNode->Reader = NULL;
		Bp->next = NewNode;
		LQueue *NewQueue = malloc(sizeof(LQueue));
		NewQueue->front = NULL;
		NewQueue->rear = NULL;
		NewQueue->length = 0;
		Bp->next->AppointerQueue = NewQueue;
		rewind(Readerfp);   //使回到文件的头部以读取全部内容
		while (fread(t1, sizeof(ReaderNode), 1, Readerfp))
		{
			if ((*t1).BookID == NewNode->Book.BookID)  //发现该书的读者将其放入书本的读者链表
			{
				if (flag == 0)   //标志位为零将读者信息放入头节点
				{
					flag = 1;            
					Bp->next->Reader = t1;
					t1->next = NULL;
					tempR = t1;
				}
				else
				{
					tempR->next = t1;
					t1->next = NULL;
					tempR = t1;
				}
				t1 = malloc(sizeof(ReaderNode));
			}
		}
		rewind(Queuefp);
		while(fread(t2, sizeof(AppointNode), 1, Queuefp))
		{
			if ((*t2).BookID == NewNode->Book.BookID)
			{
				if (NewQueue->front == NULL)
				{
					NewQueue->front = t2;   //第一个元素记录在队首
					NewQueue->rear = malloc(sizeof(AppointNode));
					NewQueue->rear->next = NULL;
					NewQueue->front->next = NewQueue->rear;
					NewQueue->length++;
				}
				else
				{
					NewQueue->rear->BookID = t2->BookID;
					NewQueue->rear->ReaderID = t2->ReaderID;
					NewQueue->rear->next = malloc(sizeof(AppointNode));
					NewQueue->rear = NewQueue->rear->next;//第一个之后的元素在队尾
					NewQueue->rear->next = NULL;
					NewQueue->length++;
				}
				t2 = malloc(sizeof(AppointNode));
		//		fread(t2, sizeof(AppointNode), 1, Queuefp);
			}
		}
		Bp = Bp->next;
	}
}
//分别将书目信息、读者信息、预约信息重新写入文件以将变化传入文件
void RelordBook(BookNode *Bp)   
{
	tempfp = fopen("../可执行文件/Booktemp", "wb");   //打开一个暂时文件
	while (Bp != NULL)             //遍历直到书目末尾
	{
		fwrite(&(Bp->Book), sizeof(BookInf), 1, tempfp);   //将书目信息写入文件
		Bp = Bp->next;
	}
	fclose(tempfp);   //关闭暂时文件
	fclose(Bookfp);   //关闭书目信息文件
	remove("../可执行文件/Book");   //移除书目信息文件
	rename("../可执行文件/Booktemp", "../可执行文件/Book");  //将暂时文件改名为书目信息文件
	Bookfp = fopen("../可执行文件/Book", "ab+");   //打开书目信息文件
	fseek(Bookfp, 0, 2);  //将书目信息文件指针移到最后方便输入新的书目
}
void RelordReader(BookNode *Rp)
{
	tempfp = fopen("../可执行文件/Readertemp", "wb");
	while (Rp != NULL)
	{
		while (Rp->Reader != NULL)
		{
			fwrite(Rp->Reader, sizeof(ReaderNode), 1, tempfp);
			Rp->Reader = Rp->Reader->next;
		}
		Rp = Rp->next;
	}
	fclose(tempfp);
	fclose(Readerfp);
	remove("../可执行文件/Reader");
	rename("../可执行文件/Readertemp", "../可执行文件/Reader");
	Readerfp = fopen("../可执行文件/Reader", "ab+");
	fseek(Readerfp, 0, 2);
}
void RelordQueue(BookNode *Qp)
{
	tempfp = fopen("../可执行文件/Queuetemp", "wb");
	rewind(Queuefp);
	while (Qp != NULL)
	{
		while (Qp->AppointerQueue->front != Qp->AppointerQueue->rear)
		{
			fwrite(Qp->AppointerQueue->front, sizeof(ReaderNode), 1, tempfp);
			Qp->AppointerQueue->front = Qp->AppointerQueue->front->next;
		}
		Qp = Qp->next;
	}
	fclose(tempfp);
	fclose(Queuefp);
	remove("../可执行文件/Queue");
	rename("../可执行文件/Queuetemp", "../可执行文件/Queue");
	Readerfp = fopen("../可执行文件/Queue", "ab+");
}