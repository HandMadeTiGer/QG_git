#include "../header/calc.h"
//ǰ׺���ʽ���ݴ���
extern int funlen;
extern int treenode;
int is_digistOrop(char num)  //1Ϊ���֣�0Ϊ������
{
	return num >= '0'&&num <= '9'; 
}
char nextToken(char* definition)   //ȡ�ַ�����
{
	static int pos = 0;  //���徲̬����
	if (( strcmp(definition,"Init") == 0))  //�����������ʼ������
		pos = -1;
	while (definition[pos] != '\0'&&definition[pos] == ' ')  //����'\0'�Լ��ո�
		pos++;
	return definition[pos++];
}
Status CalcRule1(BiTree T)   //�ж�T�������ֵ�Ƿ���Ϲ���
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

