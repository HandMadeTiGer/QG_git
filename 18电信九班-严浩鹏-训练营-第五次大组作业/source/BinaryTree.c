#include "../header/BinaryTree.h"
#include "../header/Queue.h"
#include "../header/calc.h"
#include "../header/Stack.h"
#include <stdlib.h>
Status InitBiTree(BiTree *T)
{
	if (*T == NULL)
		return ERROR;
	*T = NULL;   //树赋空值
	return SUCCESS;
}
//操作结果：构造空二叉树T
Status DestroyBiTree(BiTree *T)    //通过递归销毁二叉树
{
	if ((*T)->lchild == NULL && (*T)->rchild == NULL)
	{
		free(*T);
		*T = NULL;
		return SUCCESS;
	}
	if ( DestroyBiTree(&((*T)->lchild)) == DestroyBiTree(&((*T)->rchild)) )//直到销毁所有节点
	{
		free(*T);
		*T = NULL;
		return SUCCESS;
	}
	return ERROR;
}
//初始条件：二叉树T存在
//操作结果：摧毁二叉树T
Status CreateBiTree(BiTree *T, char* definition)
{
	char ch = nextToken(definition);  //获取表达式的某一字符
	*T = malloc(sizeof(BiTNode));   //给树节点分配空间
	(*T)->data = ch;      //初始化树节点
	(*T)->lchild = NULL;
	(*T)->rchild = NULL;
	if (!is_digistOrop(ch))   //观察可知前缀表达式树只有叶子节点为运算数
	{							//当不为运算数时继续创建节点
		CreateBiTree(&((*T)->lchild), definition);
		CreateBiTree(&((*T)->rchild), definition);
	}
	return SUCCESS;
}
//初始条件： definition给出二叉树的定义
//操作结果：按definition构造二叉树T


//以下部分函数定义未指定参数类型
Status PreOrderTraverse(BiTree T, Status(*visit)(TElemType e))  //前序
{
	if (T!= NULL)
	{
		visit(T->data);
		//	return ERROR;
		PreOrderTraverse(T->lchild,visit);
		PreOrderTraverse(T->rchild,visit);
		return SUCCESS;
	}
	return ERROR;
}
//初始条件：二叉树T存在，visit为对结点的操作的应用函数
//操作结果：先序遍历T，对每个结点调用visit函数一次且仅一次，一旦visit失败，则操作失败
Status InOrderTraverse(BiTree T, Status(*visit)(TElemType e))//中序遍历
{
	if (T!= NULL)
	{
		InOrderTraverse(T->lchild, visit);
		visit(T->data);
		InOrderTraverse(T->rchild, visit);
		return SUCCESS;
	}
	return ERROR;
}
Status PostOrderTraverse(BiTree T, Status(*visit)(TElemType e))	//后序遍历
{
	if (T!= NULL)
	{
		PostOrderTraverse(T->lchild, visit);
		PostOrderTraverse(T->rchild, visit);
		visit(T->data);
		//	return ERROR;
		return SUCCESS;
	}
	return ERROR;
}
Status LevelOrderTraverse(BiTree T, Status(*visit)(TElemType e))	//层序遍历
{
	LQueue *LQ=malloc(sizeof(LQueue));
	InitQueue(LQ);    //初始化队列
	EnLQueue(LQ, *T);   //根节点入队
	while (LQ->length!=0)   
	{
		if (LQ->front->data.lchild != NULL)  //若有队头树的节点有左孩子
			EnLQueue(LQ,*(LQ->front->data.lchild));  //入队
		if (LQ->front->data.rchild != NULL)   //若有队头树的节点有右孩子
			EnLQueue(LQ,*(LQ->front->data.rchild));  //入队
		visit(DeLQueue(LQ).data);   //队头节点出队并进行访问
	}
	DestoryLQueue(LQ);  //销毁队列
	return SUCCESS;
}
Status visit(TElemType data)
{
/*	if (is_digistOrop(data) != 1 || is_digistOrop(data) != 0)
		return ERROR;   */
	printf("%c", data);
	return SUCCESS;
}
int Value(BiTree T)    //构造出的二叉树求值
{
	static int result = 0;    //存放结果
	if (T->lchild == NULL && T->rchild == NULL)  //当到达叶子节点
		return result;	
	if((Value(T->lchild) + Value(T->rchild)) || is_digistOrop(T->lchild->data) + is_digistOrop(T->rchild->data) == 2)
	{												//当节点的左孩子和有孩子均为运算数时进入
		switch (T->data)
		{									//根据节点的运算符对它的孩子进行数据处理
			case '-':
				result = (T->lchild->data - T->rchild->data);
				break;
			case '+':
				result = (T->lchild->data + T->rchild->data - '0' - '0');
				break;
			case '*':
				result = ((T->lchild->data-'0') * (T->rchild->data - '0'));
				break;
			case '/':
				result = ((T->lchild->data - '0') / (T->rchild->data - '0'));
				break;
			default:
				printf("表达式错误\n");
				break;
		}
		T->data = result + '0';    //处理完以后节点赋为孩子的数据处理结果
		return result;
	}
}
/*Status InOrderTraverse_NonP(BiTree T)
{
	LinkStack LS;
	InitStack(&LS);
	while (T->lchild != NULL)
	{
		pushLStack(&LS, *(T->lchild));
		T = T->lchild;
	}
	while (T != NULL)
	{
		visit(T->data);
		if (T->rchild != NULL)
		{
			T = T->rchild;
			while (T->lchild != NULL)
			{
				pushLStack(&LS, *(T->lchild));
				T = T->lchild;
			}
		}
		else
		{
			if (isEmptyLStack(&LS))
			{
				*T = popLStack(&LS);
			}
			else
				break;
		}
	}
	destroyLStack(&LS);
	return SUCCESS;
}*/

