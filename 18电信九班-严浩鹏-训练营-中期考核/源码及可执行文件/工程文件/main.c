#include "FGUI.h"
#include "LineList.h"
#include "LQueue.h"
#include "LibraryInit.h"
#include <stdio.h>
char* RootPassword = "whosyourdaddy";  //����Ա����
long long ReaderID;
FILE *Bookfp, *Logfp, *Readerfp, *Queuefp, *tempfp;
BookNode *Bookpt;
BookNode *FirstBook;
int main()
{
	if ((Bookfp = fopen("Book", "rb+")) == NULL)   
	{
		printf("�޷����ļ�\n");
		exit(0);
	}
	if ((Logfp = fopen("Log", "a")) == NULL)
	{
		printf("�޷����ļ�\n");
		exit(0);
	}
	if ((Readerfp = fopen("Reader", "rb+")) == NULL)
	{
		printf("�޷����ļ�\n");
		exit(0);
	}
	if ((Queuefp = fopen("Queue", "rb+")) == NULL)
	{
		printf("�޷����ļ�\n");
		exit(0);
	}
	int Cho = 0, Num=0;    //Cho��¼����ѡ��Num��¼������Ʒ��
	char StrInp[30];      //����������ַ�
	long long date = GetTime();  //���ϵͳʱ��
	printf("DATE:%lld\n", date);   
	Bookpt = malloc(sizeof(BookNode));  //����ͷ�ڵ�
	if (fgetc(Bookfp) == EOF)  //����ļ�Ϊ��
	{
		strcpy(Bookpt->Book.Author, "yhp");  //��ʼ��ͷ�ڵ�
		Bookpt->Book.BookID=0;
		strcpy(Bookpt->Book.BookName, "LibraryManageSystem");
		(*Bookpt).Book.TotalNum = 1000;    
		(*Bookpt).Book.SpareNum = 1;   //ͷ�ڵ�SpareNum�����������Ŀ
		(*Bookpt).AppointerQueue = NULL;
		(*Bookpt).Reader = NULL;
		FirstBook = malloc(sizeof(BookNode));
		strcpy(FirstBook->Book.Author, "0");  //��ʼ��FisrtBook
		FirstBook->Book.BookID=0;
		strcpy(FirstBook->Book.BookName, "0");
		(*FirstBook).Book.TotalNum = 0;
		(*FirstBook).Book.SpareNum = 0;
		(*FirstBook).AppointerQueue = NULL;
		(*FirstBook).Reader = NULL;
		Bookpt->next = FirstBook;
		Bookpt->Reader = NULL;
		FirstBook->next = NULL;
		rewind(Bookfp);
		fwrite(&(Bookpt->Book), sizeof(BookInf), 1, Bookfp);		 //��ͷ�����Ŀд���ļ�
	}
	else
	{
		rewind(Bookfp);
		fread(&(Bookpt->Book), sizeof(BookInf), 1, Bookfp);  //��ȡ�ļ��е�ͷ�����Ŀ��Ϣ��д���ڴ�
		Bookpt->next = malloc(sizeof(BookNode));
		Bookpt->next->next = NULL;
		Bookpt->AppointerQueue = malloc(sizeof(AppointNode));
		Bookpt->AppointerQueue->length = 0;
		Bookpt->Reader = NULL;
		LoadBook(Bookfp, Readerfp, Queuefp, Bookpt);   //�����ϴγ����������鱾״̬
	}
	BookInf *Book;  //�鱾��Ϣָ�룬���Դ����鱾����Ϣ
	//�ļ�
	fprintf(Logfp, "%lld", date);  //��ʱ��д���ļ�
	fputc('\n', Logfp);
	//��¼����
	while(1)
	{
		Cho = Login();   //���յ�¼״̬
		if (Cho == 1)
		{
			fprintf(Logfp, "%s", "����Ա��¼\n");
			while (Cho != 0)
			{
				RootFGui();  //�������Ա����
				printf("������������ѡ����:");
				fprintf(Logfp, "%s", "������������ѡ����:");
				while (!scanf("%d", &Cho))  //û�н��յ����ͱ���Ҫ����������
				{
					printf("��������ȷ������:");
					fprintf(Logfp, "%s", "��������ȷ������:");
					char t[30];
					scanf("%s", t);
					fprintf(Logfp, "%s", t);
					while (getchar() != '\n');
				}
				fprintf(Logfp, "%d", Cho);
				fputc('\n', Logfp);
				switch (Cho)
				{
					case 0:
						fprintf(Logfp, "%s", "�˳�\n");
						break;
					case 1:
						//����鱾
						Book = malloc(sizeof(BookInf));
						GetBookInf(Book);
						if (AddBook(Bookpt, *Book))
						{
							Bookpt->Book.SpareNum++;  //��Ŀ����++
							long temp = ftell(Bookfp);
							rewind(Bookfp);  //�ص�ͷ�ڵ�ı���Ŀ������
							fwrite(&(Bookpt->Book), sizeof(BookInf), 1, Bookfp);
							fseek(Bookfp, temp, 0);
							printf("��ӳɹ�\n");
							fprintf(Logfp, "%s", "��ӳɹ�\n");
						}
						else
						{
							printf("��������Ŀ���\n");
							fprintf(Logfp, "%s", "��������Ŀ���\n");
						}
						break;
					case 2:
						Book = malloc(sizeof(BookInf));  
						printf("����Ҫ������������:");
						fprintf(Logfp, "%s", "����Ҫ������������:");
						scanf("%s", StrInp);
						fprintf(Logfp, "%s%c", StrInp, '\n');
						if (DelBook(Bookpt, StrInp, Book))
						{
							long temp = ftell(Bookfp);   //�ı���Ŀ����
							rewind(Bookfp);
							fwrite(&(Bookpt->Book), sizeof(BookInf), 1, Bookfp);
							fseek(Bookfp, temp, 0);
							RelordBook(Bookpt);  //���仯д���ļ�
							printf("����ɹ�\n");
							fprintf(Logfp, "%s", "����ɹ�\n");
						}
						else
						{
							printf("���ʧ�ܣ���ȴ����е��鱾���黹\n");
							fprintf(Logfp, "%s", "���ʧ��\n");
						}
						break;
					case 3:
						printf("������Ҫ���ҵ�������:");
						fprintf(Logfp, "%s", "������Ҫ���ҵ�������:");
						scanf("%s", StrInp);
						fprintf(Logfp, "%s%c", StrInp, '\n');
						Num = AuthorIndex(Bookpt, StrInp);    //����״̬
						if (!Num)
						{
							printf("û�и����ߵ���Ʒ\n");
							fprintf(Logfp, "%s", "û�и����ߵ���Ʒ\n");
						}
						else
						{
							printf("�ܹ�������%d�ָ����ߵ���Ʒ\n", Num);
							fprintf(Logfp, "%s%d%s","�ܹ�������",Num, "�ָ����ߵ���Ʒ\n");
						}
						break;
					case 4:
						printf("����Ҫ�鿴���������:");
						fprintf(Logfp, "%s", "����Ҫ�鿴���������:");
						scanf("%s", StrInp);
						fprintf(Logfp, "%s%c", StrInp, '\n');
						if (!BookStatus(Bookpt, StrInp))   //û�л�ȡ���鱾״̬
						{
							printf("��ȡʧ�ܣ������û����\n");
							fprintf(Logfp, "%s", "��ȡʧ�ܣ������û����\n");
						}
						break;
					case 5:
						TravelLibray(Bookpt);
						break;
					default:
						printf("��������\n");
						fprintf(Logfp, "%s", "��������\n");
						break;
				}
			}
		}
		else if(Cho==2)
		{
			DealAppointment(Bookpt, ReaderID);  //�����û�ԤԼ
			fprintf(Logfp, "%s", "�û���¼\n");
			while (Cho != 0)
			{
				ReaderFGui();		
				printf("������������ѡ����:");
				fprintf(Logfp, "%s", "������������ѡ����:");
				while (!scanf("%d", &Cho))
				{
					printf("��������ȷ������:");
					fprintf(Logfp, "%s", "��������ȷ������:");
					char t[30];
					scanf("%s", t);
					fprintf(Logfp, "%s", t);
					while (getchar() != '\n');
				}
				fprintf(Logfp, "%d%c", Cho, '\n');
				switch (Cho)
				{
				case 0:
					fprintf(Logfp, "%s", "�˳�\n");
					break;
				case 1:
					printf("����Ҫ���ĵ��������:");
					fprintf(Logfp, "%s", "����Ҫ���ĵ��������:");
					scanf("%s", StrInp);
					fprintf(Logfp, "%s%c", StrInp, '\n');
					if (BorrowBook(Bookpt, StrInp, ReaderID))
					{
						printf("���ĳɹ�������%lldǰ�黹\n", GetReturnTime());
						fprintf(Logfp, "%s%lld%s", "���ĳɹ�������", GetReturnTime(), "ǰ�黹\n");
					}
					else
					{
						printf("����ʧ�ܣ��ִ�ͼ�����û�д���\n");
						fprintf(Logfp, "%s", "����ʧ�ܣ��ִ�ͼ�����û�д���\n");
					}
					break;
				case 2:
					printf("����Ҫ�黹���������:");
					fprintf(Logfp, "%s", "����Ҫ�黹���������:");
					scanf("%s", StrInp);
					fprintf(Logfp, "%s%c", StrInp, '\n');
					if (ReturnBook(Bookpt, StrInp, ReaderID))
					{
						printf("�黹�ɹ�������������Ķ�ϰ��\n");
						fprintf(Logfp, "%s", "�黹�ɹ�������������Ķ�ϰ��\n");
						RelordReader(Bookpt);
					}
					else
					{
						printf("�黹ʧ�ܣ��鱾û�б���������û�д���\n");
						fprintf(Logfp, "%s", "�黹ʧ�ܣ��鱾û�б���������û�д���\n");
					}
					break;
				case 3:
					printf("����Ҫ���ҵ����ߵ�����:");
					fprintf(Logfp, "%s", "����Ҫ���ҵ����ߵ�����:");
					scanf("%s", StrInp);
					fprintf(Logfp, "%s%c", StrInp, '\n');
					Num = AuthorIndex(Bookpt, StrInp);
					if (!Num)
					{
						printf("û�и����ߵ���Ʒ\n");
						fprintf(Logfp, "%s", "û�и����ߵ���Ʒ\n");
					}
					else
					{
						printf("�ܹ�������%d�ָ����ߵ���Ʒ\n", Num);
						fprintf(Logfp, "%s%d%s", "�ܹ�������", Num, "�ָ����ߵ���Ʒ\n");
					}
						break;
					case 4:
						printf("����Ҫ���ҵ�����:");
						fprintf(Logfp, "%s", "����Ҫ���ҵ�����:");
						scanf("%s", StrInp);
						fprintf(Logfp, "%s%c", StrInp, '\n');
						BookStatus(Bookpt, StrInp);
						break;
					case 5:
						TravelLibray(Bookpt);
						break;
					case 6:
						printf("����ҪԤԼ������:");
						fprintf(Logfp, "%s", "����ҪԤԼ������:");
						scanf("%s", StrInp);
						fprintf(Logfp, "%s%c", StrInp, '\n');
						if (BookAppointment(Bookpt, StrInp, ReaderID))
						{
							printf("ԤԼ�ɹ�\n");
							fprintf(Logfp, "%s", "ԤԼ�ɹ�\n");
						}
						else
							printf("�����û�д�������������Ϊ��\n");
						break;
					default:
						printf("��������ȷ������:");
						break;
				}
			}
		}
		else			
			break;
	}
	fputc('\n', Logfp);
	fclose(Readerfp);
	fclose(Queuefp);
	fclose(Bookfp);
	fclose(Logfp);
	return 0;
}
