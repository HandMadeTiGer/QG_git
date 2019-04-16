#include "LibraryInit.h"
extern FILE *Bookfp, *Logfp, *Readerfp, *Queuefp,*tempfp;
long long GetTime()
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
void LoadBook(FILE* BookPt, FILE* ReaderPt, FILE* QueuePt, BookNode* Bp)
{
	int counter=0;   //��Ŀ���������
	int Num = Bp->Book.SpareNum;  //��ȡ��Ŀ��+1
	BookInf temp;
	BookNode* NewNode = malloc(sizeof(BookNode));
	ReaderNode *t1 = malloc(sizeof(ReaderNode)),*tempR;
	AppointNode *t2 = malloc(sizeof(AppointNode));
	LQueue *NewQueue = malloc(sizeof(LQueue));
	fseek(BookPt, sizeof(BookInf), 0);  //����ͷ�ڵ�
	while (counter < Num-1)   //����Ŀû�е���ĩβ
	{
		int flag = 0;  //��־λ�Ƿ���Ϣд��ͷ���
		counter++;    //������Ŀ��counter�Լ�
		fread(&temp, sizeof(BookInf), 1, BookPt);    //temp��¼��Ŀ��Ϣ
		NewNode = malloc(sizeof(BookNode));        //��ʼ������Ŀ�ڵ�
		NewNode->Book = temp;
		NewNode->next = NULL;
		NewNode->Reader = NULL;
		Bp->next = NewNode;
		LQueue *NewQueue = malloc(sizeof(LQueue));
		NewQueue->front = NULL;
		NewQueue->rear = NULL;
		NewQueue->length = 0;
		Bp->next->AppointerQueue = NewQueue;
		rewind(Readerfp);   //ʹ�ص��ļ���ͷ���Զ�ȡȫ������
		while (fread(t1, sizeof(ReaderNode), 1, Readerfp))
		{
			if ((*t1).BookID == NewNode->Book.BookID)  //���ָ���Ķ��߽�������鱾�Ķ�������
			{
				if (flag == 0)   //��־λΪ�㽫������Ϣ����ͷ�ڵ�
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
					NewQueue->front = t2;   //��һ��Ԫ�ؼ�¼�ڶ���
					NewQueue->length++;
				}
				else
				{
					NewQueue->rear = t2;   //��һ��֮���Ԫ���ڶ�β
					NewQueue->rear = NewQueue->rear->next;
					NewQueue->length++;
				}
				t2 = malloc(sizeof(AppointNode));
				fread(t2, sizeof(AppointNode), 1, Queuefp);
			}
		}
		Bp = Bp->next;
	}
}
//�ֱ���Ŀ��Ϣ��������Ϣ��ԤԼ��Ϣ����д���ļ��Խ��仯�����ļ�
void RelordBook(BookNode *Bp)   
{
	tempfp = fopen("Booktemp", "wb");   //��һ����ʱ�ļ�
	while (Bp != NULL)             //����ֱ����Ŀĩβ
	{
		fwrite(&(Bp->Book), sizeof(BookInf), 1, tempfp);   //����Ŀ��Ϣд���ļ�
		Bp = Bp->next;
	}
	fclose(tempfp);   //�ر���ʱ�ļ�
	fclose(Bookfp);   //�ر���Ŀ��Ϣ�ļ�
	remove("Book");   //�Ƴ���Ŀ��Ϣ�ļ�
	rename("Booktemp", "Book");  //����ʱ�ļ�����Ϊ��Ŀ��Ϣ�ļ�
	Bookfp = fopen("Bookfp", "ab+");   //����Ŀ��Ϣ�ļ�
	fseek(Bookfp, 0, 2);  //����Ŀ��Ϣ�ļ�ָ���Ƶ���󷽱������µ���Ŀ
}
void RelordReader(BookNode *Rp)
{
	tempfp = fopen("Readertemp", "wb");
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
	remove("Reader");
	rename("Readertemp", "Reader");
	Readerfp = fopen("Reader", "ab+");
	fseek(Readerfp, 0, 2);
}
void RelordQueue(BookNode *Qp)
{
	tempfp = fopen("Queuetemp", "wb");
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
	remove("Queue");
	rename("Queuetemp", "Queue");
	Readerfp = fopen("Queue", "ab+");
}