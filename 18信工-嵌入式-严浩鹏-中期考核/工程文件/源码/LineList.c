#include "../ͷ�ļ�/LineList.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "../ͷ�ļ�/LibraryInit.h"
extern FILE *Bookfp, *Logfp, *Readerfp, *Queuefp,*tempfp;  //����Ϊ���鱾��Ϣ����־�����ߡ�ԤԼ������Ϣ���޸�ʱ��ʱ���ļ�ָ��
extern BookNode* Bookpt;   //BookptΪȫ�ֱ��������е�SpareNumΪÿһ����������
Status IsLeapYear(int year)  //�����ж�
{
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 1 : 0;
}
long long GetReturnTime()  //��ȡ�������ڣ�һ�º�黹
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
	if (IsLeapYear(a) && (b == 1) && (c - 29 > 0))  //��Ϊ���괦�����
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
	fprintf(Logfp, "%lld", GetTime());  //��ʱ��д���ļ�
	int Sum = 0;         //SumΪУ�飬���������������Ԥ�裬��ȡ��Ϣ�ɹ�
	Book->BookID = Bookpt->Book.TotalNum;   //Ϊ����������
	fprintf(Logfp, "%d", Book->BookID);   //������ļ�
	fputc('\n', Logfp);             //����س�����
	printf("����������:");
	fprintf(Logfp, "%s", "����������:");
	Sum += scanf("%s", Book->BookName);
	fprintf(Logfp, "%s", Book->BookName);
	fputc('\n', Logfp);
	printf("����������:");
	fprintf(Logfp, "%s", "����������:");
	Sum += scanf("%s", Book->Author);
	fprintf(Logfp, "%s", Book->Author);
	fputc('\n', Logfp);
	printf("�����������:");
	fprintf(Logfp, "%s", "�����������:");
	if (scanf("%d", &(Book->TotalNum)))
		Sum++;
	else
		while (getchar() != '\n');
	fprintf(Logfp, "%d", Book->TotalNum);
	fputc('\n', Logfp);
	Book->SpareNum = Book->TotalNum;    
	if (Sum == 3) //���������ݵ���Ŀ����3���ɹ�
		return SUCCESS;
	return ERROR;
}
Status AddBook(BookNode *p, BookInf AddedBook)
{
	int counter = 0;  //��¼��Ĵ���
	if (p->next->Book.SpareNum == 0)   //��Ϊ��һ���飬����洢��ͷ����һ�ڵ�
	{
		p->next->Book = AddedBook;      //�޸�ͷ�ڵ����һ�ڵ������
		p->next->AppointerQueue = malloc(sizeof(LQueue));  //Ϊ���з���һ���ռ�
		p->next->AppointerQueue->front = NULL;   //��ʼ������
		p->next->AppointerQueue->rear = NULL;
		p->next->AppointerQueue->length = 0;
		p->next->Reader = NULL;
		fwrite(&(p->next->Book), sizeof(BookInf), 1, Bookfp);	//д���ļ�
	}
	else                     //�����½��ڵ㣬�������Ϣ������½ڵ�
	{
		while (p->next != NULL && strcmp(p->Book.BookName, AddedBook.BookName))
		{
			p = p->next;   //��ָ���ƶ���nextΪ�յ�λ�û��ҵ���ͬ����Ŀ
			counter++;   //���������++
		}
		if (p != NULL && strcmp(p->Book.BookName,AddedBook.BookName)==0) //�ҵ���ͬ��Ŀ
		{
			p->Book.TotalNum += AddedBook.TotalNum;  //�ܿ��������
			p->Book.SpareNum += AddedBook.TotalNum;  //�ִ�������
			long temp = ftell(Bookfp);     //�ݴ��鱾��Ϣ�ļ�ָ���λ��
			fseek(Bookfp, counter * sizeof(BookInf), 0);  //ת���޸���Ŀָ��λ��
			fwrite(&(p->Book), sizeof(BookInf), 1, Bookfp);  //�޸��ļ�����Ŀ�������Ϣ
			fseek(Bookfp, temp, 0);  //�ص�tempָ���λ��
			return ERROR;
		}
		else
		{
			BookNode *NewBook = malloc(sizeof(BookNode));  //Ϊ�������ռ�
			NewBook->Book = AddedBook;             //��ʼ��������Ϣ
			NewBook->Reader = NULL;
			NewBook->AppointerQueue = malloc(sizeof(LQueue));
			NewBook->AppointerQueue->front = NULL;
			NewBook->AppointerQueue->rear = NULL;
			NewBook->AppointerQueue->length = 0;
			p->next = NewBook;     //������鵽��ĿĿ¼���
			NewBook->next = NULL;    
			fwrite(&(NewBook->Book), sizeof(BookInf), 1, Bookfp);  //������д���ļ�
		}
	}
	return SUCCESS;
}
Status DelBook(BookNode *p, char* BookName, BookInf* DeledBook) 
{
	int counter = 0;    //��Ŀλ�ü�����
	while (p->next != NULL && strcmp(p->next->Book.BookName, BookName) != 0)
	{
		counter++;    //��Ŀλ�ü�����++
		p = p->next;					//����ֱ���Ҹ�������������û���ҵ�����
	}
	if (p->next == NULL || ( p->Book.SpareNum != p->Book.TotalNum ))           //���û���ҵ����� �����鱾�ִ����������鱾����
		return ERROR;
	BookNode *temp = p->next ;  //��¼�ڵ�ĵ�ַ�Է����ͷ��ڴ�
	*DeledBook = p->next->Book;    //��¼��ɾ�����鱾��Ϣ  
	p->next  = p->next->next;   //ָ����ĿĿ¼����һ�ڵ�
	free(temp);          //�ͷŸ��鱾
	temp = NULL;

	return SUCCESS;
}
Status BookStatus(BookNode *p, char* BookName)//��ȡ�鱾��Ϣ
{
	fprintf(Logfp, "%lld", GetTime());  //��ʱ��д���ļ�
	int counter = 0,i;
	int len = strlen(BookName);
	char temp1[30];
	char temp2[30];
	strcpy(temp1, BookName);
	p = p->next;
	while (p != NULL)   //ֱ���ҵ����е���
	{
		for (i = 0; i < len; i++)
			temp2[i] = (p->Book.BookName)[i];
		temp2[i] = '\0';
		if (!strcmp(temp1, temp2))
		{
			counter++;
			printf("��������������������������������������������������������������������������������������������������\n");
			printf("��   %30s �����", p->Book.BookName);
			printf("%7d��\n", p->Book.BookID);
			printf("��  ------------------------------------------   ��\n");
			printf("��   ����Ϊ %30s       ��\n", p->Book.Author);
			printf("��  ------------------------------------------   ��\n");
			printf("��   ʣ����ĿΪ %8d", p->Book.SpareNum);
			printf("   �ܹ���ĿΪ %8d   ��\n", p->Book.TotalNum);
			printf("��  ------------------------------------------   ��\n");
			if (p->Reader != NULL)
			{
				printf("��   ��һ��������δ�黹���� %10lld           ��\n", p->Reader->ReaderID);
				printf("��   Ӧ���� %lld ǰ�黹����                  ��\n", p->Reader->ReturnDate);
			}
			else
			{
				printf("��   ��û�����ڽ��Ȿ��                          ��\n");
			}
			printf("��  ------------------------------------------   ��\n");
			if (p->AppointerQueue->front == NULL)
			{
				printf("��   ��û����ԤԼ����                            ��\n");
			}
			else
			{
				printf("��   ��%10uλ����ԤԼ����                  ��\n", p->AppointerQueue->length);
			}
			printf("��������������������������������������������������������������������������������������������������\n");
		}
		p = p->next;
	}
	if (counter == 0)   //û���ҵ��������
		return ERROR;
	return SUCCESS;
}
int AuthorIndex(BookNode *p, char* AuthorName)  //����������
{
	int counter=0;   //��Ʒ������
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
		return ERROR;        //û���ҵ���Ʒ
	return counter;
}
void TravelLibray(BookNode *p)  
{
	p = p->next;
	while (p != NULL)  //�������ȫ����Ŀ
	{
		printf("��������������������������������������������������������������������������������������������������\n");
		printf("��   %30s �����", p->Book.BookName);
		printf("%7d��\n", p->Book.BookID);
		printf("��  ------------------------------------------   ��\n");
		printf("��   ����Ϊ %30s       ��\n", p->Book.Author);
		printf("��  ------------------------------------------   ��\n");
		printf("��   ʣ����ĿΪ %8d", p->Book.SpareNum);
		printf("   �ܹ���ĿΪ %8d   ��\n", p->Book.TotalNum);
		printf("��  ------------------------------------------   ��\n");
		if (p->Reader != NULL)
		{
			printf("��   ��һ��������δ�黹���� %10lld           ��\n", p->Reader->ReaderID);
			printf("��   Ӧ���� %lld ǰ�黹����                  ��\n", p->Reader->ReturnDate);
		}
		else
		{
			printf("��   ��û�����ڽ��Ȿ��                          ��\n");
		}
		printf("��  ------------------------------------------   ��\n");
		if (p->AppointerQueue->front == NULL)
		{
			printf("��   ��û����ԤԼ����                            ��\n");
		}
		else
		{
			printf("��   ��%10uλ����ԤԼ����                  ��\n", p->AppointerQueue->length);
		}
		printf("��������������������������������������������������������������������������������������������������\n");
		p = p->next;
	}
}
//��������
Status BorrowBook(BookNode *p, char* BookName,long long ID)
{
	long t = 0;      //t�ݴ���Ŀ���ļ��е�λ��
	int counter = 0;   //counter��¼�鱾�Ĵ���
	while (p != NULL && strcmp(p->Book.BookName, BookName) != 0)
	{
		p = p->next;       //ֱ���ҵ��鱾���ߵ��������鱾���
		counter++;
	}
	if (p == NULL|| p->Book.SpareNum == 0)  //û���ҵ��������Ϊ0
		return ERROR;
	else
	{
		if (p->Reader == NULL)  //����鱾��û���˽��ģ���������Ϣ����ͷ�ڵ㴦
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
			while (p->Reader->next != NULL)   //����ֱ���ҵ����һλ����Ķ���
				p->Reader = p->Reader->next;
			ReaderNode *temp = malloc(sizeof(ReaderNode));  //temp���������Ϣ
			temp->ReaderID = ID;
			temp->ReturnDate= GetReturnTime();
			temp->BookID = p->Book.BookID;
			temp->next = NULL;
			p->Reader->next = temp;
			fwrite(temp, sizeof(ReaderNode), 1, Readerfp);
		}
		p->Book.SpareNum--;   //�����鱾�ִ���
		t = ftell(Bookfp);   //���ִ����仯¼����Ŀ
		fseek(Bookfp, counter * sizeof(BookInf), 0);
		fwrite(&(p->Book), sizeof(BookInf), 1, Bookfp);
		fseek(Bookfp, t, 0);
	}
	return SUCCESS;
}
Status ReturnBook(BookNode *p, char* BookName, long long ID)
{
	int counter1=0;  //Ϊ�鱾���������
	long t;  //t��¼�ļ�ָ��λ��
	while (p != NULL && strcmp(p->Book.BookName, BookName) != 0)  //ֱ���ҵ��鱾
	{
		p = p->next;											//�������ȫ���鱾
		counter1++;
	}
	if (p == NULL || p->Book.SpareNum == p->Book.TotalNum)  //��������������鱾
		return ERROR;										//�����鱾û�б����
	else
	{
		while (p->Reader != NULL && p->Reader->ReaderID != ID)//ֱ���ҵ��ö���
			p->Reader = p->Reader->next;					//������������Ϣû���ҵ��ö���
		if (p->Reader == NULL)   //û���ҵ�����ERROR
			return ERROR;
		else
		{
			ReaderNode *temp = p->Reader;  //temp�ݴ�黹�鱾������Ϣ
			p->Reader = p->Reader->next;  
			p->Book.SpareNum++;  //�����++
			free(temp);  //�ͷŸôν����¼
			temp = NULL;
			t = ftell(Bookfp);   //���仯д����Ŀ
			fseek(Bookfp, sizeof(BookInf)*counter1, 0);
			fwrite(&(p->Book), sizeof(BookInf), 1, Bookfp);
			fseek(Bookfp, t, 0);
		}
	}
	return SUCCESS;
}
Status BorrowBook_sp(BookNode *p, char* BookName, long long ID,int counter)  //������ģ�����ԤԼ���飬�����p��ΪҪ�����Ŀ
{
	long t = 0;
	if (p->Reader == NULL)  //����鱾��û���˽��ģ���������Ϣ����ͷ�ڵ㴦
	{
		ReaderNode *temp = malloc(sizeof(ReaderNode));  //temp��¼������Ϣ
		temp->ReaderID = ID;
		temp->BookID = p->Book.BookID;
		temp->ReturnDate = GetReturnTime();
		temp->next = NULL;
		p->Reader = temp;
		fseek(Readerfp, 0, 2);  //��Reader�ļ�ָ������ĩβ
		fwrite(temp, sizeof(ReaderNode), 1, Readerfp); //���Reader��Ϣ
		p->Book.SpareNum--;   //�����鱾�ִ���
	}
	else
	{
		while (p->Reader->next != NULL)   //����ֱ���ҵ����һλ����Ķ���
			p->Reader = p->Reader->next;
		ReaderNode *temp = malloc(sizeof(ReaderNode));  //temp���������Ϣ
		temp->ReaderID = ID;
		temp->ReturnDate = GetReturnTime();
		temp->next = NULL;
		p->Reader->next = temp;
		fseek(Readerfp, 0, 2);
		fwrite(temp, sizeof(ReaderNode), 1, Readerfp);
		p->Book.SpareNum--;   //�����鱾�ִ���
	}
	t = ftell(Bookfp);   //��������仯д����Ŀ
	fseek(Bookfp, counter * sizeof(BookInf), 0);
	fwrite(&(p->Book), sizeof(BookInf), 1, Bookfp);
	fseek(Bookfp, t, 0);
	return SUCCESS;
}
Status BookAppointment(BookNode *p, char* BookName, long long ReaderID)
{
	while (p != NULL && strcmp(p->Book.BookName, BookName) != 0)  //ֱ���ҵ��鱾
		p = p->next;											//�������ȫ���鱾
	if (p == NULL||p->Book.SpareNum > 0)    //û���ҵ���Ŀ��������Ϊ0
		return ERROR;
	else
	{
		AppointNode Appointerinf;  //��¼��Ϣ
		Appointerinf.ReaderID = ReaderID;
		Appointerinf.BookID = p->Book.BookID;
		AddReaderAppointment(p->AppointerQueue, Appointerinf);  //���ԤԼ����LQueue�еķ���
	}
	return SUCCESS;
}
Status DealAppointment(BookNode* p,long long ReaderID)  //����ÿ�ε��봦��ԤԼ
{
	p = p->next;  //����ͷ�ڵ�
	int counter = 0;  //��¼�鱾����
	AppointNode *temp = malloc(sizeof(AppointNode));
	while (p != NULL)
	{	
		counter++;    //ʣ����Ŀ��Ϊ0��ԤԼ���Ȳ�Ϊ0��ReaderID��ȲŽ���ѭ��
		while (p->Book.SpareNum != 0 && p->AppointerQueue->length != 0 &&p->AppointerQueue->front->ReaderID== ReaderID)
		{
			BorrowBook_sp(p, p->Book.BookName, ReaderID,counter);//������Ĵ���
			DeLReaderAppointment(p->AppointerQueue); //ɾ��ԤԼ��Ϣ
		}
		p = p->next;
	}
	return SUCCESS;
}