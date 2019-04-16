#ifndef LIBRARYINIT_H_INCLUDED
#define LIBRARYINIT_H_INCLUDED
#include <stdio.h>
#include "LineList.h"
#include <time.h>
long long GetTime();
void LoadBook(FILE* BookPt, FILE* ReaderPt, FILE* QueuePt, BookNode* Bp);
void RelordBook(BookNode *Bp);
void RelordReader(BookNode *Rp);
void RelordQueue(BookNode *Qp);
#endif