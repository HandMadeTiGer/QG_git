#ifndef LIBRARYINIT_H_INCLUDED
#define LIBRARYINIT_H_INCLUDED
#include <stdio.h>
#include "../Í·ÎÄ¼þ/LineList.h"
#include <time.h>
long long GetDate();
long long GetTime();
void LoadBook(FILE* BookPt, FILE* ReaderPt, FILE* QueuePt, BookNode* Bp);
void RelordBook(BookNode *Bp);
void RelordReader(BookNode *Rp);
void RelordQueue(BookNode *Qp);
#endif