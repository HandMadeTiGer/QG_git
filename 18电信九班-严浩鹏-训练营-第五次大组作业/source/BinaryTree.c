#include "../header/BinaryTree.h"
#include "../header/Queue.h"
#include "../header/calc.h"
#include "../header/Stack.h"
#include <stdlib.h>
Status InitBiTree(BiTree *T)
{
	if (*T == NULL)
		return ERROR;
	*T = NULL;   //������ֵ
	return SUCCESS;
}
//�������������ն�����T
Status DestroyBiTree(BiTree *T)    //ͨ���ݹ����ٶ�����
{
	if ((*T)->lchild == NULL && (*T)->rchild == NULL)
	{
		free(*T);
		*T = NULL;
		return SUCCESS;
	}
	if ( DestroyBiTree(&((*T)->lchild)) == DestroyBiTree(&((*T)->rchild)) )//ֱ���������нڵ�
	{
		free(*T);
		*T = NULL;
		return SUCCESS;
	}
	return ERROR;
}
//��ʼ������������T����
//����������ݻٶ�����T
Status CreateBiTree(BiTree *T, char* definition)
{
	char ch = nextToken(definition);  //��ȡ���ʽ��ĳһ�ַ�
	*T = malloc(sizeof(BiTNode));   //�����ڵ����ռ�
	(*T)->data = ch;      //��ʼ�����ڵ�
	(*T)->lchild = NULL;
	(*T)->rchild = NULL;
	if (!is_digistOrop(ch))   //�۲��֪ǰ׺���ʽ��ֻ��Ҷ�ӽڵ�Ϊ������
	{							//����Ϊ������ʱ���������ڵ�
		CreateBiTree(&((*T)->lchild), definition);
		CreateBiTree(&((*T)->rchild), definition);
	}
	return SUCCESS;
}
//��ʼ������ definition�����������Ķ���
//�����������definition���������T


//���²��ֺ�������δָ����������
Status PreOrderTraverse(BiTree T, Status(*visit)(TElemType e))  //ǰ��
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
//��ʼ������������T���ڣ�visitΪ�Խ��Ĳ�����Ӧ�ú���
//����������������T����ÿ��������visit����һ���ҽ�һ�Σ�һ��visitʧ�ܣ������ʧ��
Status InOrderTraverse(BiTree T, Status(*visit)(TElemType e))//�������
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
Status PostOrderTraverse(BiTree T, Status(*visit)(TElemType e))	//�������
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
Status LevelOrderTraverse(BiTree T, Status(*visit)(TElemType e))	//�������
{
	LQueue *LQ=malloc(sizeof(LQueue));
	InitQueue(LQ);    //��ʼ������
	EnLQueue(LQ, *T);   //���ڵ����
	while (LQ->length!=0)   
	{
		if (LQ->front->data.lchild != NULL)  //���ж�ͷ���Ľڵ�������
			EnLQueue(LQ,*(LQ->front->data.lchild));  //���
		if (LQ->front->data.rchild != NULL)   //���ж�ͷ���Ľڵ����Һ���
			EnLQueue(LQ,*(LQ->front->data.rchild));  //���
		visit(DeLQueue(LQ).data);   //��ͷ�ڵ���Ӳ����з���
	}
	DestoryLQueue(LQ);  //���ٶ���
	return SUCCESS;
}
Status visit(TElemType data)
{
/*	if (is_digistOrop(data) != 1 || is_digistOrop(data) != 0)
		return ERROR;   */
	printf("%c", data);
	return SUCCESS;
}
int Value(BiTree T)    //������Ķ�������ֵ
{
	static int result = 0;    //��Ž��
	if (T->lchild == NULL && T->rchild == NULL)  //������Ҷ�ӽڵ�
		return result;	
	if((Value(T->lchild) + Value(T->rchild)) || is_digistOrop(T->lchild->data) + is_digistOrop(T->rchild->data) == 2)
	{												//���ڵ�����Ӻ��к��Ӿ�Ϊ������ʱ����
		switch (T->data)
		{									//���ݽڵ������������ĺ��ӽ������ݴ���
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
				printf("���ʽ����\n");
				break;
		}
		T->data = result + '0';    //�������Ժ�ڵ㸳Ϊ���ӵ����ݴ�����
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

