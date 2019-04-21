#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED
#include "../header/BinaryTree.h"
#include <stdlib.h>
#include <string.h>
int is_digistOrop(char num);
char nextToken(char* definition);
Status CalcRule1(Tree, fun);
Status CalcRule2(char *fun);
#endif
