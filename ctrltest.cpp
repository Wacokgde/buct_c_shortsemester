#include "stdio.h"
#include "stdlib.h"								//包含system()函数 
#include "string.h"

#define N 100									//书籍结构体定义数量
#define Nid 50
#define Nre 100

												//主功能区
void sign();									//登录  
void menu();									//菜单主页			//唐宇煊					
void list();									//显示书列表 		//喻兰 
void borrow();									//借书 				//贺怀宇
void ret(); 									//还书 
void update();									//修改书信息 		//杨凯鸿 



void menu_yk(); 								//游客模式菜单 
void list_yk(); 								//游客模式显示 

void count();									//功能函数区 
void file_w();
void clear(); 
void list_print();
void refile_w(); 

struct bookk
{
	char name[100];								//书名 
	char author[100];							//作者 
	char publisher[100];						//出版社 
	char ISBN[20];								//ISBN号 
	int num_z;									//馆藏数 
	int num_x;									//可借数 
	char date[20];								//日期(未完成作用分配)
	char f_query;								//用于全局模糊查询 标记单项是否已出现 
};

struct bookk book[N]=
{{"犹豫与迟疑","杨凯鸿","化学工业出版社","330-7-250-25025-9",3,3,"2019.7.2",'0'}					//书籍定义模板
,{"C语言程序设计","高敬阳","清华大学出版社","978-7-302-22204-0",3,1,"2018.4.8",'0'}};				//操作在程序或文件中进行 


struct idd
{
	char account[20];
	char password[20];
	int perm;
};

struct idd id[Nid]=
{{"2018040000","123456",0}
,{"2018040072","qwerty",1}};


struct ree													
{
	char retname[100];
	char belong[20];
	char r_query;
};

struct ree rebook[Nre]=
{{"C语言程序设计","2018040072",0}
,{"不要犹豫","2018040000",0}};


static int bookkinds=0,id_num=0,re_num=0;
int counter=0;
char name_r[100]={0}; 
int permission=0;
char account_now[20]={0};


FILE *fp_book,*fp_id,*fp_re;

 
void count() 													//统计书本数量,并读取文件中的书籍信息写入结构体数组 
{
	bookkinds=0;
	fp_book=fopen("booklist.txt","r+");
	for(int i=0;i<N;i++)
	{
		fscanf(fp_book,"%s%s%s%s%d%d%s",book[i].name,book[i].author,book[i].publisher,book[i].ISBN,&book[i].num_z,&book[i].num_x,book[i].date); 
		if(book[i].num_z!=0)
		{
			bookkinds++;
		}	
	}
	fclose(fp_book);
}


void id_read() 													//统计账号数量,并读取文件中的账号信息写入结构体数组 
{
	id_num=0;
	fp_id=fopen("idlist.txt","r+");
	for(int i=0;i<Nid;i++)
	{
		fscanf(fp_id,"%s%s%d",id[i].account,id[i].password,&id[i].perm); 
		if(id[i].perm==0||id[i].perm==1)
		{
			id_num++;
		}	
	}
	fclose(fp_id);
}


void re_read() 													//统计借书种数,并读取文件中的借书信息写入结构体数组 		
{
	re_num=0;
	fp_re=fopen("returnlist.txt","r+");
	for(int i=0;i<Nre;i++)
	{
		fscanf(fp_re,"%s%s",rebook[i].retname,rebook[i].belong); 
		if(strlen(rebook[i].retname)!=0)
		{
			re_num++;
		}	
	}
	fclose(fp_re);
}


void file_w() 													//将书籍结构体的信息写入文件 
{
	fp_book=fopen("booklist.txt","w");
	for(int i=0;i<bookkinds+1;i++)
	{
		if(book[i].num_z!=0)
		{
			fprintf(fp_book,"%s %s %s %s %d %d %s\n",book[i].name,book[i].author,book[i].publisher,book[i].ISBN,book[i].num_z,book[i].num_x,book[i].date);	
		}	
	}
	fclose(fp_book);
}

void clear()													//整理空书籍-已完成 
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
	file_w();
}


void list_print()												//不清除显示内容的情况下输出书的列表 
{	
	int i;
	count();
	for(i=0;i<bookkinds;i++)
	{	
		printf("\t\t\t\t||%d------《%s》\n",i+1,book[i].name);
	}
}


void refile_w()												//将还书结构体的信息写入文件 
{
	fp_re=fopen("returnlist.txt","w");
	for(int i=0;i<Nre;i++)
	{
		if(strlen(rebook[i].retname)!=0)
		{
			fprintf(fp_re,"%s %s \n",rebook[i].retname,rebook[i].belong);	
		}	
	}
	fclose(fp_re);
}


void sign()														//登录页 
{
	system("cls"); 
	int n,a=0;
	char geta[20],getp[20]; 
	char zhanghu[2][10]={"管理员","学生"}; 
	id_read();
	printf("\n\n");
	printf("\t\t\t\t*****************************************************\n");
	printf("\t\t\t\t*    ------------欢迎使用图书管理系统------------   *\n"); 
	printf("\t\t\t\t*    \t\t1 : ---- 账号登录\t\t    *\n");
    printf("\t\t\t\t*    \t\t2 : ---- 游客系统\t\t    *\n");
    printf("\t\t\t\t*    \t\t3 : ---- 退出系统\t\t    *\n");
    printf("\t\t\t\t*****************************************************\n");
    printf("\t\t\t\t>>>输入您需要使用的功能，并按回车键 : ");
	scanf("%d",&n);
	getchar(); 
	if(n==1)
	{
		printf("\n\n\n\t\t\t\t请输入帐号：");
		scanf("%s",geta);
		printf("\t\t\t\t请输入密码：");
		scanf("%s",getp);
		for(int i=0;i<id_num;i++)
		{
			if(strcmp(geta,id[i].account)==0)
			{
				a=1; 
				if(strcmp(getp,id[i].password)==0)
				{
					permission=id[i].perm; 
					strcpy(account_now,id[i].account);
					printf("\t\t\t\t%s登录成功 ! \n\t\t\t\t输入任意字符进入菜单 : ",zhanghu[i]);
					scanf("%s"); 
					menu();
				}
				else
				{
					printf("\t\t\t\t>>>密码错误,请重新登录 ! \n\t\t\t\t>>>输入任意字符返回登录 : ");
					scanf("%s");	
					sign();
				}
			}
		} 
		if(a==0) 
		{
			printf("\t\t\t\t>>>账号不存在,请重新登录,或咨询图书管理员开通账号 ! \n\t\t\t\t>>>输入任意字符返回登录 : \n");
			sign();
		}
	}
	else if(n==2)
	{
		printf("\n\n\n\t\t\t\t确定使用游客登录,按y确认,输入其他字符回到登录页面 : ");
		scanf("%s",&a);
		if(a=='Y'||a=='y')
		{
			menu_yk(); 
		}
		else
		{
			sign(); 
		} 
	}
	else if(n==3)
	{
		exit(0);
	}
	else 
	{
		sign(); 
	}
} 




void menu()														//菜单页 
{
	system("cls"); 
	int x;
	printf("\n\n\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*1 : ---- 查看书籍清单                                *\n");
	printf("\t\t\t\t*2 : ---- 借阅书籍                                    *\n");
	printf("\t\t\t\t*3 : ---- 归还书籍                                    *\n");
	if(permission==0)
	{
		printf("\t\t\t\t*4 : ---- 修改图书信息                                *\n");	
	}
	else if(permission==1)
	{
		printf("\t\t\t\t*4 : ---- 修改图书信息(仅管理员可用)                  *\n");
	}
	printf("\t\t\t\t*5 : ---- 退出程序                                    *\n");
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t>>>请输入您要使用的功能 : ");
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
		ret();
	}
	else if(x==4)
	{
		if(permission==1)
		{
			system("cls"); 
			printf("\t\t\t**************************************************************************\n");
			printf("\t\t\t*********************************   **************************************\n");
			printf("\t\t\t*******************************       ************************************\n");
			printf("\t\t\t*******************************       ************************************\n");
			printf("\t\t\t*******************************       ************************************\n");
			printf("\t\t\t********************************     *************************************\n");
			printf("\t\t\t********************************     *************************************\n");
			printf("\t\t\t*********************************   **************************************\n");
			printf("\t\t\t********************************** ***************************************\n");
			printf("\t\t\t********************************** ***************************************\n");
			printf("\t\t\t**************************************************************************\n");
			printf("\t\t\t*********************************   **************************************\n");
			printf("\t\t\t*********************************   **************************************\n");
			printf("\t\t\t**************************************************************************\n");
			printf("\t\t\t非管理员账号,无法修改 ! \n\t\t\t\t\t\t\t如有需求请咨询图书管理员 ! \n\t\t\t\t\t\t\t按任意键返回菜单 : ");
			scanf("%s"); 
			menu();
		}
		if(permission==0)
		{
			update();
		}
	}
	else if(x==5)
	{
		exit(0);
	}
	else
	{
		menu();
	}
}


void menu_yk() 													//用于游客模式的菜单-隔离主菜单保证安全 
{
	system("cls"); 
	int x;
	printf("\n\n\t\t\t\t*********************************************************\n");
	printf("\t\t\t\t**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**\n");
	printf("\t\t\t\t*|     \t\t游客账号登录成功 !                     |*\n\t\t\t\t**     \t\t仅可查看书籍清单                       **\n");
	printf("\t\t\t\t*|     \t\t1 : ---- 查看书籍清单                  |*\n");
	printf("\t\t\t\t**     \t\t2 : ---- 回到登录界面                  **\n");
	printf("\t\t\t\t*|     \t\t3 : ---- 退出程序                      |*\n");
	printf("\t\t\t\t**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**\n");
	printf("\t\t\t\t>>>请输入您要使用的功能 : ");
	scanf("%d",&x);
	getchar();
	if(x==1)
	{
		list_yk();
	}
	if(x==2)
	{
		sign();
	}
	else if(x==3)
	{
		exit(0);
	}
	else
	{
		menu_yk();
	}
} 


void list()														//书籍清单页 
{	
	int i;
	system("cls");
	count();
	printf("\n\n\t\t\t\t****************************\n");
	for(i=0;i<bookkinds;i++)
	{	
		printf("\t\t\t\t||%d------《%s》\n",i+1,book[i].name);	
	}
	printf("\t\t\t\t****************************\n");
	printf("\t\t\t\t>>>按任意键回到主界面 : ");
	scanf("%s");
	menu();
}
 
void list_yk()													//游客模式的书籍清单也,用于回到游客模式主菜单,避免权限泄露 
{
	int i;
	system("cls");
	count();
	printf("\n\n\t\t\t\t****************************\n");
	for(i=0;i<bookkinds;i++)
	{	
		printf("\t\t\t\t||%d------《%s》\n",i+1,book[i].name);
	}
	printf("\t\t\t\t****************************\n");
	printf("\t\t\t\t>>>按任意键回到主界面 : ");
	scanf("%s");
	menu_yk();
} 

void borrow()															//发现bug 输入长必须严格小于书名 ------已解决 
{
	system("cls");
	count(); 
	for(int i=0;i<bookkinds;i++)										//查询状态归零 
	{
		book[i].f_query=0;	
	} 
	int zt=0,kz=0,bbb=0;
	printf(">>>请输入要借出的书籍(可模糊查询) : ");
	scanf("%s",name_r);
	int lens=strlen(name_r);
	char b[bookkinds][100][lens+1];
	for(int u=0;u<bookkinds;u++)										//切片 
	{
		if(strlen(book[u].name)<lens)									//处理查询内容大于书名长的情况
		{
			continue; 
		} 
		for(int i=0;i<strlen(book[u].name)-lens+1;i++)
		{
			for(int j=0;j<lens;j++)
			{
				b[u][i][j]=book[u].name[j+i];
			}
			b[u][i][lens]=0; 
		}
	}
	
	printf("*************************************\n");
	printf("\t\t书名\t\t作者\t\t\t出版社\t\t馆藏数\t可借数\n");	
	for(int i=0;i<bookkinds;i++)										//模糊查询 
	{
		for(int k=0;k<strlen(book[i].name);k++)
		{
			if(strcmp(name_r,b[i][k])==0)
			{
				printf("  %d--------%s\t\t%s\t\t%s\t\t%d\t%d\n",i+1,book[i].name,book[i].author,book[i].publisher,book[i].num_z,book[i].num_x);
				book[i].f_query=1; 
				zt=1;
				break; 
			}
		}	
	}

	
	if(lens>=4)															//在输入长度大于2个汉字时对作者与出版社也进行模糊查询 
	{
		for(int u=0;u<bookkinds;u++)									//作者模糊查询   //切片 
		{
			if(strlen(book[u].author)<lens)								//处理查询内容大于作者名长的情况
			{
				continue; 
			} 
			for(int i=0;i<strlen(book[u].author)-lens+1;i++)
			{
				for(int j=0;j<lens;j++)
				{
					b[u][i][j]=book[u].author[j+i];
				}
				b[u][i][lens]=0; 
			}
		}
			
		for(int i=0;i<bookkinds;i++)									//模糊查询 
		{
			for(int k=0;k<strlen(book[i].author);k++)
			{
				if(strcmp(name_r,b[i][k])==0&&book[i].f_query!=1)
				{
					printf("  %d--------%s\t\t%s\t\t%s\t\t%d\t%d\n",i+1,book[i].name,book[i].author,book[i].publisher,book[i].num_z,book[i].num_x);
					book[i].f_query=1; 
					zt=1;
					break; 
				}
			}	
		}
		
			for(int u=0;u<bookkinds;u++)								//出版社模糊查询   //切片 
		{
			if(strlen(book[u].publisher)<lens)							//处理查询内容大于出版社名长的情况
			{
				continue; 
			} 
			for(int i=0;i<strlen(book[u].publisher)-lens+1;i++)
			{
				for(int j=0;j<lens;j++)
				{
					b[u][i][j]=book[u].publisher[j+i];
				}
				b[u][i][lens]=0; 
			}
		}
			
		for(int i=0;i<bookkinds;i++)									//模糊查询 
		{
			for(int k=0;k<strlen(book[i].publisher);k++)
			{
				if(strcmp(name_r,b[i][k])==0&&book[i].f_query!=1)
				{
					printf("  %d--------%s\t\t%s\t\t%s\t\t%d\t%d\n",i+1,book[i].name,book[i].author,book[i].publisher,book[i].num_z,book[i].num_x);
					book[i].f_query=1; 
					zt=1;
					break; 
				}
			}	
		}
	}
	printf("*************************************\n");
	
	if(zt==1)
	{
		printf(">>>请输入书籍编号确认(输入0返回主菜单) : "); 
		scanf("%d",&kz); 
		getchar();
		if(kz==0)
		{
			menu();
		} 
		kz-=1;
		if(book[kz].f_query!=1)
		{
			system("cls");
			printf("\t\t\t\t>>>序号指向了不正确的书籍,按任意键返回上层菜单 : "); 
			scanf("%s");
			borrow(); 
		}
		system("cls");
		printf("\n\n\t\t\t\t*********************************\n");
		printf("\t\t\t\t||书名 : %s\n\t\t\t\t||作者 : %s\n\t\t\t\t||出版社 : %s\n\t\t\t\t||ISBN : %s\n\t\t\t\t||馆藏数 : %d\n\t\t\t\t||可借数 : %d\n",
		book[kz].name,book[kz].author,book[kz].publisher,book[kz].ISBN,book[kz].num_z,book[kz].num_x);
		printf("\t\t\t\t*********************************\n");
		printf("\t\t\t\t>>>请核对书籍信息并确认是否借书(Y/N)");
		scanf("%c",&bbb);
		getchar();  
		if(bbb=='Y'||bbb=='y')
		{
			if(book[kz].num_x>0)
			{
				printf("\t\t\t\t>>>借书成功!\n\t\t\t\t>>>请在规定期限内还书!\n\t\t\t\t>>>继续借书请按y并回车,按其他任意键回到主页 : ");
				book[kz].num_x -= 1;				//借书成功,减去现有图书一本
				file_w();							//操作写入文件 
				re_read();
				strcpy(rebook[re_num].retname,book[kz].name);
				strcpy(rebook[re_num].belong,account_now);
				refile_w();
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
			else
			{
				system("cls");
				printf("\n\n\t\t\t\t>>>非常抱歉,借书失败,图书库存不足,请联系图书管理员补充图书\n");		
				printf("\t\t\t\t*********************************\n");
				printf("\t\t\t\t||1: -------- 继续借书\n\t\t\t\t||2: -------- 回到主页\n");
				printf("\t\t\t\t*********************************\n");
				printf("\t\t\t\t>>>请输入您要使用的功能 : ");
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
		else if(bbb=='N'||bbb=='n')
		{
			system("cls");
			printf("\n\n\t\t\t\t*********************************\n");
			printf("\t\t\t\t||1: -------- 继续借书\n\t\t\t\t||2: -------- 回到主页\n");
			printf("\t\t\t\t*********************************\n");
			printf("\t\t\t\t>>>请输入您要使用的功能 : ");
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
		printf(">>>未查询到类似图书,按Y回车继续查询,按其他任意键回到主页 : "); 
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



void ret()
{
	system("cls");
	int zt=0,kz=0;
	char bbb=0; 
	re_read();
	for(int i=0;i<Nre;i++)
	{
		rebook[i].r_query=0;
	}
	for(int i=0;i<Nre;i++)																	//aaaaaaaaa yu pan duan
	{
		if(strcmp(rebook[i].belong,account_now)==0)
		{
			zt=1;
		}
	}
	if(zt!=1)
	{
		system("cls");
		printf("您目前没有需要归还的书籍 ! "); 
		printf("请按任意键返回主菜单 ! ");
		scanf("%s");
		menu(); 
	}
	for(int i=0;i<Nre;i++)
	{
		if(strcmp(rebook[i].belong,account_now)==0)
		{
			rebook[i].r_query=1;
			printf("\n%d--------%s",i+1,rebook[i].retname);
		}
	}
	printf("\n请输入书籍编号确认还书(输入0返回主菜单) : "); 
	scanf("%d",&kz); 
	getchar();
	if(kz==0)
	{
		menu();
	} 
	kz-=1;
	if(rebook[kz].r_query!=1)
	{
		system("cls");
		printf("\n序号指向了不正确的书籍,按任意键返回上层菜单 : "); 
		scanf("%s");
		ret(); 
	}
	else
	{
		for(int i=0;i<Nre;i++)
		{
			if(strcmp(rebook[kz].retname,book[i].name)==0)
			{
				book[i].num_x+=1;
			}	
		}
		file_w();
		for(int i=kz;i<Nre-1;i++)
		{
			rebook[i]=rebook[i+1];
		}
		refile_w();
		printf("还书成功!");
		printf("按y继续还书,按任意键返回主菜单 : ");
		scanf("%c",&bbb); 
		getchar();
		if(bbb=='Y'||bbb=='y')
		{
			ret();
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
	printf("\n\n\t\t\t\t**********************************************************\n");
	printf("\t\t\t\t*     \t\t1------添加一本书籍信息                  *\n\t\t\t\t*     \t\t2------修改一本书籍信息                  *\n\t\t\t\t*     \t\t3------删除一本书籍信息                  *\n\t\t\t\t*     \t\t4------返回上一级                        *\n");
	printf("\t\t\t\t**********************************************************\n");
	printf("\t\t\t\t>>>请输入您要使用的功能 : ");
	scanf("%d",&k);
	count();
	if(k==1)
	{	
		system("cls");
		s=bookkinds;
		book[s].num_z=0;
		book[s].num_x=0;
		printf("\n\n\t\t\t\t*********************************");
		printf("\n\t\t\t\t||请输入所添加书籍的名称 : ");
		scanf("%s",book[s].name);
		printf("\n\t\t\t\t||请输入所添加书籍的作者 : ");
		scanf("%s",book[s].author);
		printf("\n\t\t\t\t||请输入所添加书籍的出版社 : ");
		scanf("%s",book[s].publisher);
		printf("\n\t\t\t\t||请输入所添加书籍的ISBN编号 : ");
		scanf("%s",book[s].ISBN);
		printf("\n\t\t\t\t||请输入所添加书籍的总库存量 : ");
		scanf("%d",&book[s].num_z);
		printf("\n\t\t\t\t||请输入所添加书籍的现有库存量 : ");
		scanf("%d",&book[s].num_x);
		printf("\n\t\t\t\t||请输入所添加书籍的添加日期 : ");
		scanf("%s",book[s].date);
		printf("\n\t\t\t\t>>>书籍添加成功！");
		printf("\n\t\t\t\t*********************************\n");
		file_w();
		printf("\t\t\t\t>>>按y查看书籍清单，其它任意键返回主界面 : ");
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
		printf("\n\n\t\t\t\t>>>请输入您要修改的书籍的序号(1~%d) : ",bookkinds);
		scanf("%d",&m);
		if(m<1||m>bookkinds)
		{	
			printf("\t\t\t\t>>>范围输入错误！按任意键返回上一级 : ");
			scanf("%s");
			update();
		}
		else
		{	
			printf("\n\n\t\t\t\t*********************************");
			printf("\n\t\t\t\t||请输入所修改的书籍的名称 : ");
			scanf("%s",book[m-1].name);
			printf("\n\t\t\t\t||请输入所修改书籍的作者 : ");
			scanf("%s",book[m-1].author);
			printf("\n\t\t\t\t||请输入所修改书籍的出版社 : ");
			scanf("%s",book[m-1].publisher);
			printf("\n\t\t\t\t||请输入所修改书籍的ISBN编号 : ");
			scanf("%s",book[m-1].ISBN);
			printf("\n\t\t\t\t||请输入所修改书籍的总库存量(在此处输入0可清除该本图书) : n");
			scanf("%d",&book[m-1].num_z);
			printf("\n\t\t\t\t||请输入所修改书籍的现有库存量 : ");
			scanf("%d",&book[m-1].num_x);
			printf("\n\t\t\t\t||请输入所修改书籍的修改日期 : ");
			scanf("%s",book[m-1].date);
			printf("\n\t\t\t\t||书籍修改成功！");
			printf("\n\t\t\t\t*********************************\n");
			clear();
			printf("\t\t\t\t>>>按y查看书籍清单，其它任意键返回主界面 : ");
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
		system("cls"); 
		printf("\n\n\t\t\t\t*********************************\n");
		list_print(); 
		printf("\t\t\t\t*********************************");
		printf("\n\t\t\t\t>>>请输入您要删除的书籍的序号(1~%d),输入其他数取消操作 : ",bookkinds); 
		scanf("%d",&m);
		getchar(); 
		if(m>=1&&m<=bookkinds)
		{
			book[m-1].num_z=0;
			clear();
			printf("\t\t\t\t>>>删除成功!");
		}
		else
		{
			printf("\t\t\t\t>>>取消删除 ! \n");
		} 
		printf("\n\t\t\t\t>>>按y查看书籍清单，其它任意键返回主界面 : ");
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
	else if(k==4)
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
	re_read();
	count();	
	sign(); 
}
//printf("%s\n%s\n%s\n%s\n%d\n%d\n%s\n",book[i].name,book[i].author,book[i].publisher,book[i].ISBN,book[i].num_z,book[i].num_x,book[i].date);
//上为输出格式方便复制 
