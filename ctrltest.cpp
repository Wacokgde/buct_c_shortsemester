#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define N 100									//�鼮�ṹ�嶨������ 


void menu();									//��������						
void list();
void borrow();
void update();				

void count();									//���ܺ����� 
void file_w();
void clear(); 

struct bookk
{
	char name[100];								//���� 
	char author[100];							//���� 
	char publisher[100];						//������ 
	char ISBN[20];								//ISBN�� 
	int num_z;									//�ݲ��� 
	int num_x;									//�ɽ��� 
	char date[20];								//����(δ������÷���) 
};
struct bookk book[N]={{"��ԥ�����","���","��ѧ��ҵ������","330-7-250-25025-9",3,3,"2019.7.2"}					//�鼮����ģ��
					,{"C���Գ������","�߾���","�廪��ѧ������","978-7-302-22204-0",3,1,"2018.4.8"}};				//�����ڳ�����ļ��н��� 

static int bookkinds=0;
int counter=0;
char name_r[100]={0};
 
FILE *fp;
 
void count() 													//ͳ���鱾����,����ȡ�ļ��е��鼮��Ϣд��ṹ������ 
{
	bookkinds=0;
	fp=fopen("booklist.txt","r+");	
	for(int i=0;i<N;i++)
	{
		fscanf(fp,"%s%s%s%s%d%d%s",book[i].name,book[i].author,book[i].publisher,book[i].ISBN,&book[i].num_z,&book[i].num_x,book[i].date); 
		if(book[i].num_z!=0)
		{
			bookkinds++;
		}	
	}
	fclose(fp);
}


void file_w() 													//���鼮�ṹ�����Ϣд���ļ� 
{
	fp=fopen("booklist.txt","w");
	for(int i=0;i<bookkinds+1;i++)
	{
		if(book[i].num_z!=0)
		{
			fprintf(fp,"%s %s %s %s %d %d %s\n",book[i].name,book[i].author,book[i].publisher,book[i].ISBN,book[i].num_z,book[i].num_x,book[i].date);	
		}	
	}
	fclose(fp);
}

void clear()														//������鼮-δ��� 
{
	for(int i=0;i<N;i++)
	{
		if(book[i].num_z==0)
		{
			for(int j=i;j<N-1;j++)
			{
				book[j]=book[j+1];
			}
		} 
	}
}

void menu()
{
	system("cls"); 
	int x;
	printf("1 : ---- �鿴�鼮�嵥\n");
	printf("2 : ---- �����鼮\n");
	printf("3 : ---- �޸�ͼ����Ϣ\n");
	printf("4 : ---- �˳�����\n");
	printf("��������Ҫʹ�õĹ��� : ");
	scanf("%d",&x);
	getchar();
	if(x==1)
	{
		list();
	}
	else if(x==2)
	{
		borrow();
	}
	else if(x==3)
	{
		update();
	}
	else if(x==4)
	{
		exit(0);
	}
	else
	{
		menu();
	}
}


void list()
{	
	int i;
	system("cls");
	count();
	for(i=0;i<bookkinds;i++)
	{	
		printf("%d------��%s��\n",i+1,book[i].name);
	}
	printf("��������ص������� : ");
	scanf("%s");
	menu();
}


void borrow()
{
	int zt=0,kz=0,bbb=0;
	system("cls");
	count(); 
	printf("������Ҫ������鼮(��ģ����ѯ) : ");
	scanf("%s",&name_r);
	int lens=strlen(name_r);
	char b[bookkinds][100][lens+1];
	for(int u=0;u<bookkinds;u++)									//��Ƭ 
	{ 
		for(int i=0;i<strlen(book[u].name)-lens+1;i++)
		{
			for(int j=0;j<lens;j++)
			{
				b[u][i][j]=book[u].name[j+i];
			}
			b[u][i][lens]=0;

		}
	}
	
	for(int i=0;i<bookkinds;i++)									//ģ����ѯ 
	{
		for(int k=0;k<strlen(book[i].name);k++)
		{
			if(strcmp(name_r,b[i][k])==0)
			{
				printf("%d--------%s\n",i+1,book[i].name);
				zt=1;
				break; 
			}
		}	
	}
	if(zt==1)
	{
		printf("�������鼮���ȷ�� : "); 
		scanf("%d",&kz);
		getchar();
		kz-=1; 
		system("cls");
		printf("���� : %s\n���� : %s\n������ : %s\nISBN : %s\n�ݲ��� : %d\n�ɽ��� : %d\n��˶��鼮��Ϣ��ȷ���Ƿ����(Y/N)",
		book[kz].name,book[kz].author,book[kz].publisher,book[kz].ISBN,book[kz].num_z,book[kz].num_x);
		scanf("%c",&bbb);
		getchar(); 
		if(bbb=='Y'||bbb=='y')
		{
			printf("����ɹ�!\n���ڹ涨�����ڻ���!\n���������밴y���س�,������������ص���ҳ : ");
			book[kz].num_x -= 1;				//����ɹ�,��ȥ����ͼ��һ�� 
			file_w();							//����д���ļ� 
			scanf("%c",&bbb); 
			getchar();
			if(bbb=='Y'||bbb=='y')
			{
				borrow();
			}
			else
			{
				menu();
			}
		}
		else if(bbb=='N'||bbb=='n')
		{
			system("cls");
			printf("1 : -------- ��������\n2 : -------- �ص���ҳ\n");
			printf("��������Ҫʹ�õĹ��� : ");
			scanf("%d",&bbb);
			getchar();
			if(bbb==1)
			{
				borrow();
			}
			else if(bbb==2)
			{
				menu();
			}
		}
	}
	else
	{
		printf("δ��ѯ������ͼ��,��Y�س�������ѯ,������������ص���ҳ : "); 
		scanf("%s",&bbb);
		if(bbb=='Y'||bbb=='y')
		{
			borrow();
		}
		else
		{
			menu();
		}
	}	
}

void update()
{	
	system("cls");
	int i,k,s,m;
	printf("1------���һ���鼮��Ϣ\n2------�޸�һ���鼮��Ϣ\n3------������һ��\n"); 
	printf("��������Ҫʹ�õĹ��� : ");
	scanf("%d",&k);
	count();
	if(k==1)
	{	
		system("cls");
		s=bookkinds;
		book[s].num_z=0;
		book[s].num_x=0;
		printf("������������鼮������ : ");
		scanf("%s",book[s].name);
		printf("\n������������鼮������ : ");
		scanf("%s",book[s].author);
		printf("\n������������鼮�ĳ����� : ");
		scanf("%s",book[s].publisher);
		printf("\n������������鼮��ISBN��� : ");
		scanf("%s",book[s].ISBN);
		printf("\n������������鼮���ܿ���� : ");
		scanf("%d",&book[s].num_z);
		printf("\n������������鼮�����п���� : ");
		scanf("%d",&book[s].num_x);
		printf("\n������������鼮�Ľ������� : ");
		scanf("%s",book[s].date);
		printf("\n�鼮��ӳɹ���");
		file_w();
		printf("\n��y�鿴�鼮�嵥��������������������� : ");
		scanf("%s",&k);
		if(k=='y'||k=='Y')
		{
			list();
		}
		else
		{
			menu();
		}
	}
	else if(k==2)
	{	
		system("cls");
		printf("��������Ҫ�޸ĵ��鼮�����(1~%d) : ",bookkinds);
		scanf("%d",&m);
		if(m<1||m>bookkinds)
		{	
			printf("\n��Χ������󣡰������������һ�� : ");
			scanf("%s");
			update();
		}
		else
		{	
			printf("���������޸ĵ��鼮������ : ");
			scanf("%s",book[m-1].name);
			printf("\n���������޸��鼮������ : ");
			scanf("%s",book[m-1].author);
			printf("\n���������޸��鼮�ĳ����� : ");
			scanf("%s",book[m-1].publisher);
			printf("\n���������޸��鼮��ISBN��� : ");
			scanf("%s",book[m-1].ISBN);
			printf("\n���������޸��鼮���ܿ���� : ");
			scanf("%d",&book[m-1].num_z);
			printf("\n���������޸��鼮�����п���� : ");
			scanf("%d",&book[m-1].num_x);
			printf("\n���������޸��鼮�Ľ������� : ");
			scanf("%s",book[m-1].date);
			printf("\n�鼮�޸ĳɹ���");
			file_w();
			printf("\n��y�鿴�鼮�嵥��������������������� : ");
			scanf("%s",&k);
			if(k=='y'||k=='Y')
			{
				list();
			}
			else
			{
				menu();		
			} 
		}
	}
	else if(k==3)
	{
		menu();
	}
	else 
	{
		update();	
	}		
}

int main()
{
	count();	
	menu();
}
//printf("%s\n%s\n%s\n%s\n%d\n%d\n%s\n",book[i].name,book[i].author,book[i].publisher,book[i].ISBN,book[i].num_z,book[i].num_x,book[i].date);
//��Ϊ�����ʽ���㸴�� 
