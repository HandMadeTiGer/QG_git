#include "../header/calc.h"
//前缀表达式数据处理
extern int funlen;
extern int treenode;
int is_digistOrop(char num)  //1为数字，0为操作符
{
	return num >= '0'&&num <= '9'; 
}
char nextToken(char* definition)   //取字符函数
{
	static int pos = 0;  //定义静态变量
	if (( strcmp(definition,"Init") == 0))  //满足条件则初始化变量
		pos = -1;
	while (definition[pos] != '\0'&&definition[pos] == ' ')  //跳过'\0'以及空格
		pos++;
	return definition[pos++];
}
Status CalcRule1(BiTree T)   //判断T里面的数值是否符合规则
{
	if (T->lchild == NULL && T->rchild == NULL)
	{	
		treenode++;
		return ERROR;
	}
	if ((CalcRule1(T->lchild)+CalcRule1(T->rchild))==2)
	{
		treenode++;
		return ERROR;
	}
	return ERROR;
}
Status CalcRule2(char *fun)
{
	int NumFlag = 0, OpFlag = 0;
	int len = strlen(fun);
	for (int i = 0; i < len; i++)
	{
		if (is_digistOrop(fun[i]))
			NumFlag++;
		else
			OpFlag++;
	}
	if (NumFlag - OpFlag)
		return ERROR;
	else
		return SUCCESS;
}

