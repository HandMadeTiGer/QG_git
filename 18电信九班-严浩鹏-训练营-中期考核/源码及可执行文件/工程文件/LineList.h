#ifndef LINELIST_H_INCLUDED
#define LINELIST_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "LQueue.h"
//链表实现读者借阅
typedef struct ReaderNode
{
	long long ReaderID;
	long long ReturnDate;
	int BookID;
	struct ReaderNode *next;
}ReaderNode;
//链表实现书本信息
typedef struct Book
{
	char BookName[30];
	char Author[30];
	int BookID;
	int SpareNum;
	int TotalNum;
}BookInf;
typedef struct BookNode
{
	BookInf Book;
	ReaderNode *Reader;
	LQueue *AppointerQueue;
	struct BookNode *next;
}BookNode;

long long GetReturnTime();
Status GetBookInf(BookInf *Book);
Status AddBook(BookNode *p, BookInf AddedBook);
Status DelBook(BookNode *p, char* BookName, BookInf* DeledBook);
Status BookStatus(BookNode *p, char* BookName);
int AuthorIndex(BookNode *p, char* AuthorName);
void TravelLibray(BookNode *p);
Status BorrowBook(BookNode *p, char* BookName, long long ID);
Status ReturnBook(BookNode *p, char* BookName, long long ID);
Status BorrowBook_sp(BookNode *p, char* BookName, long long ID, int counter);
Status BookAppointment(BookNode *p, char* BookName, long long ReaderID);
Status DealAppointment(BookNode* p, long long ReaderID);
#endif