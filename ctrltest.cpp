#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define N 100									//书籍结构体定义数量 


void menu();									//主功能区						
void list();
void borrow();
void update();				

void count();									//功能函数区 
void file_w();
void clear(); 

struct bookk
{
	char name[100];								//书名 
	char author[100];							//作者 
	char publisher[100];						//出版社 
	char ISBN[20];								//ISBN号 
	int num_z;									//馆藏数 
	int num_x;									//可借数 
	char date[20];								//日期(未完成作用分配) 
};
struct bookk book[N]={{"犹豫与迟疑","杨凯鸿","化学工业出版社","330-7-250-25025-9",3,3,"2019.7.2"}					//书籍定义模板
					,{"C语言程序设计","高敬阳","清华大学出版社","978-7-302-22204-0",3,1,"2018.4.8"}};				//操作在程序或文件中进行 

static int bookkinds=0;
int counter=0;
char name_r[100]={0};
 
FILE *fp;
 
void count() 													//统计书本数量,并读取文件中的书籍信息写入结构体数组 
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


void file_w() 													//将书籍结构体的信息写入文件 
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

void clear()														//整理空书籍-未完成 
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
	printf("1 : ---- 查看书籍清单\n");
	printf("2 : ---- 借阅书籍\n");
	printf("3 : ---- 修改图书信息\n");
	printf("4 : ---- 退出程序\n");
	printf("请输入您要使用的功能 : ");
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
		printf("%d------《%s》\n",i+1,book[i].name);
	}
	printf("按任意键回到主界面 : ");
	scanf("%s");
	menu();
}


void borrow()
{
	int zt=0,kz=0,bbb=0;
	system("cls");
	count(); 
	printf("请输入要借出的书籍(可模糊查询) : ");
	scanf("%s",&name_r);
	int lens=strlen(name_r);
	char b[bookkinds][100][lens+1];
	for(int u=0;u<bookkinds;u++)									//切片 
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
	
	for(int i=0;i<bookkinds;i++)									//模糊查询 
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
		printf("请输入书籍编号确认 : "); 
		scanf("%d",&kz);
		getchar();
		kz-=1; 
		system("cls");
		printf("书名 : %s\n作者 : %s\n出版社 : %s\nISBN : %s\n馆藏数 : %d\n可借数 : %d\n请核对书籍信息并确认是否借书(Y/N)",
		book[kz].name,book[kz].author,book[kz].publisher,book[kz].ISBN,book[kz].num_z,book[kz].num_x);
		scanf("%c",&bbb);
		getchar(); 
		if(bbb=='Y'||bbb=='y')
		{
			printf("借书成功!\n请在规定期限内还书!\n继续借书请按y并回车,按其他任意键回到主页 : ");
			book[kz].num_x -= 1;				//借书成功,减去现有图书一本 
			file_w();							//操作写入文件 
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
			printf("1 : -------- 继续借书\n2 : -------- 回到主页\n");
			printf("请输入您要使用的功能 : ");
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
		printf("未查询到类似图书,按Y回车继续查询,按其他任意键回到主页 : "); 
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
	printf("1------添加一本书籍信息\n2------修改一本书籍信息\n3------返回上一级\n"); 
	printf("请输入您要使用的功能 : ");
	scanf("%d",&k);
	count();
	if(k==1)
	{	
		system("cls");
		s=bookkinds;
		book[s].num_z=0;
		book[s].num_x=0;
		printf("请输入所添加书籍的名称 : ");
		scanf("%s",book[s].name);
		printf("\n请输入所添加书籍的作者 : ");
		scanf("%s",book[s].author);
		printf("\n请输入所添加书籍的出版社 : ");
		scanf("%s",book[s].publisher);
		printf("\n请输入所添加书籍的ISBN编号 : ");
		scanf("%s",book[s].ISBN);
		printf("\n请输入所添加书籍的总库存量 : ");
		scanf("%d",&book[s].num_z);
		printf("\n请输入所添加书籍的现有库存量 : ");
		scanf("%d",&book[s].num_x);
		printf("\n请输入所添加书籍的借阅日期 : ");
		scanf("%s",book[s].date);
		printf("\n书籍添加成功！");
		file_w();
		printf("\n按y查看书籍清单，其它任意键返回主界面 : ");
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
		printf("请输入您要修改的书籍的序号(1~%d) : ",bookkinds);
		scanf("%d",&m);
		if(m<1||m>bookkinds)
		{	
			printf("\n范围输入错误！按任意键返回上一级 : ");
			scanf("%s");
			update();
		}
		else
		{	
			printf("请输入所修改的书籍的名称 : ");
			scanf("%s",book[m-1].name);
			printf("\n请输入所修改书籍的作者 : ");
			scanf("%s",book[m-1].author);
			printf("\n请输入所修改书籍的出版社 : ");
			scanf("%s",book[m-1].publisher);
			printf("\n请输入所修改书籍的ISBN编号 : ");
			scanf("%s",book[m-1].ISBN);
			printf("\n请输入所修改书籍的总库存量 : ");
			scanf("%d",&book[m-1].num_z);
			printf("\n请输入所修改书籍的现有库存量 : ");
			scanf("%d",&book[m-1].num_x);
			printf("\n请输入所修改书籍的借阅日期 : ");
			scanf("%s",book[m-1].date);
			printf("\n书籍修改成功！");
			file_w();
			printf("\n按y查看书籍清单，其它任意键返回主界面 : ");
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
//上为输出格式方便复制 
