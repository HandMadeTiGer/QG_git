#include <stdio.h>
#include "../header/BinaryTree.h"
#include "../header/Stack.h"
#include "../header/Queue.h"
#include "../header/calc.h"
int funlen;
int treenode;
int main()
{
	while (1)
	{
		BiTree Tree = malloc(sizeof(BiTree));  //������
		char fun[30];     //��ű��ʽ
		printf("������һ��ǰ׺���ʽ(����0��������):");
		scanf("%s", fun);  //��ȡ���ʽ
		treenode = 0;
		funlen = strlen(fun);
		if (!strcmp(fun, "0"))  //�˳���������
			break;
		InitBiTree(&Tree);    //��ʼ����
		if (CalcRule2(fun))
		{
			CreateBiTree(&Tree, fun);  //�������ʽ��
			CalcRule1(Tree, fun);
			if (funlen == treenode)  //�жϱ��ʽ�Ƿ���Ϲ���
			{
				printf("��ǰ��������Ϊ:");
				PreOrderTraverse(Tree, visit);  //ǰ�����
				printf("\n");
				printf("������������Ϊ:");
				InOrderTraverse(Tree, visit); //�������
				printf("\n");
				printf("�����������Ϊ:");
				PostOrderTraverse(Tree, visit); //�������
				printf("\n");
				printf("������������Ϊ:");
				LevelOrderTraverse(Tree, visit); //��α���
				printf("\n");
				printf("�����Ϊ:");
				printf("%d\n", Value(Tree));  //�����ֵ
				DestroyBiTree(&Tree);   //������
			}
			else
				printf("����ǰ׺���ʽ����\n");
			nextToken("Init");    //��ʼ����̬����
		}
		else
			printf("����ǰ׺���ʽ����\n");
	}
	return 0;
}