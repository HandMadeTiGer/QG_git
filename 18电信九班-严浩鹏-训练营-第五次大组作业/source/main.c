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
		BiTree Tree = malloc(sizeof(BiTree));  //定义树
		char fun[30];     //存放表达式
		printf("请输入一个前缀表达式(输入0结束程序):");
		scanf("%s", fun);  //读取表达式
		treenode = 0;
		funlen = strlen(fun);
		if (!strcmp(fun, "0"))  //退出程序条件
			break;
		InitBiTree(&Tree);    //初始化树
		if (CalcRule2(fun))
		{
			CreateBiTree(&Tree, fun);  //创建表达式树
			CalcRule1(Tree, fun);
			if (funlen == treenode)  //判断表达式是否符合规则
			{
				printf("其前序遍历结果为:");
				PreOrderTraverse(Tree, visit);  //前序遍历
				printf("\n");
				printf("其中序遍历结果为:");
				InOrderTraverse(Tree, visit); //中序遍历
				printf("\n");
				printf("其后序遍历结果为:");
				PostOrderTraverse(Tree, visit); //后序遍历
				printf("\n");
				printf("其层次序遍历结果为:");
				LevelOrderTraverse(Tree, visit); //层次遍历
				printf("\n");
				printf("其得数为:");
				printf("%d\n", Value(Tree));  //求出数值
				DestroyBiTree(&Tree);   //销毁树
			}
			else
				printf("输入前缀表达式错误\n");
			nextToken("Init");    //初始化静态变量
		}
		else
			printf("输入前缀表达式错误\n");
	}
	return 0;
}