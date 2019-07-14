#include "stdio.h"
#include "stdlib.h"								//����system()���� 
#include "string.h"

#define N 100									//�鼮�ṹ�嶨������
#define Nid 50
#define Nre 100

												//��������
void sign();									//��¼  
void menu();									//�˵���ҳ			//������					
void list();									//��ʾ���б� 		//���� 
void borrow();									//���� 				//�ػ���
void ret(); 									//���� 
void update();									//�޸�����Ϣ 		//��� 



void menu_yk(); 								//�ο�ģʽ�˵� 
void list_yk(); 								//�ο�ģʽ��ʾ 

void count();									//���ܺ����� 
void file_w();
void clear(); 
void list_print();
void refile_w(); 

struct bookk
{
	char name[100];								//���� 
	char author[100];							//���� 
	char publisher[100];						//������ 
	char ISBN[20];								//ISBN�� 
	int num_z;									//�ݲ��� 
	int num_x;									//�ɽ��� 
	char date[20];								//����(δ������÷���)
	char f_query;								//����ȫ��ģ����ѯ ��ǵ����Ƿ��ѳ��� 
};

struct bookk book[N]=
{{"��ԥ�����","���","��ѧ��ҵ������","330-7-250-25025-9",3,3,"2019.7.2",'0'}					//�鼮����ģ��
,{"C���Գ������","�߾���","�廪��ѧ������","978-7-302-22204-0",3,1,"2018.4.8",'0'}};				//�����ڳ�����ļ��н��� 


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
{{"C���Գ������","2018040072",0}
,{"��Ҫ��ԥ","2018040000",0}};


static int bookkinds=0,id_num=0,re_num=0;
int counter=0;
char name_r[100]={0}; 
int permission=0;
char account_now[20]={0};


FILE *fp_book,*fp_id,*fp_re;

 
void count() 													//ͳ���鱾����,����ȡ�ļ��е��鼮��Ϣд��ṹ������ 
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


void id_read() 													//ͳ���˺�����,����ȡ�ļ��е��˺���Ϣд��ṹ������ 
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


void re_read() 													//ͳ�ƽ�������,����ȡ�ļ��еĽ�����Ϣд��ṹ������ 		
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


void file_w() 													//���鼮�ṹ�����Ϣд���ļ� 
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

void clear()													//������鼮-����� 
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


void list_print()												//�������ʾ���ݵ�������������б� 
{	
	int i;
	count();
	for(i=0;i<bookkinds;i++)
	{	
		printf("\t\t\t\t||%d------��%s��\n",i+1,book[i].name);
	}
}


void refile_w()												//������ṹ�����Ϣд���ļ� 
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


void sign()														//��¼ҳ 
{
	system("cls"); 
	int n,a=0;
	char geta[20],getp[20]; 
	char zhanghu[2][10]={"����Ա","ѧ��"}; 
	id_read();
	printf("\n\n");
	printf("\t\t\t\t*****************************************************\n");
	printf("\t\t\t\t*    ------------��ӭʹ��ͼ�����ϵͳ------------   *\n"); 
	printf("\t\t\t\t*    \t\t1 : ---- �˺ŵ�¼\t\t    *\n");
    printf("\t\t\t\t*    \t\t2 : ---- �ο�ϵͳ\t\t    *\n");
    printf("\t\t\t\t*    \t\t3 : ---- �˳�ϵͳ\t\t    *\n");
    printf("\t\t\t\t*****************************************************\n");
    printf("\t\t\t\t>>>��������Ҫʹ�õĹ��ܣ������س��� : ");
	scanf("%d",&n);
	getchar(); 
	if(n==1)
	{
		printf("\n\n\n\t\t\t\t�������ʺţ�");
		scanf("%s",geta);
		printf("\t\t\t\t���������룺");
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
					printf("\t\t\t\t%s��¼�ɹ� ! \n\t\t\t\t���������ַ�����˵� : ",zhanghu[i]);
					scanf("%s"); 
					menu();
				}
				else
				{
					printf("\t\t\t\t>>>�������,�����µ�¼ ! \n\t\t\t\t>>>���������ַ����ص�¼ : ");
					scanf("%s");	
					sign();
				}
			}
		} 
		if(a==0) 
		{
			printf("\t\t\t\t>>>�˺Ų�����,�����µ�¼,����ѯͼ�����Ա��ͨ�˺� ! \n\t\t\t\t>>>���������ַ����ص�¼ : \n");
			sign();
		}
	}
	else if(n==2)
	{
		printf("\n\n\n\t\t\t\tȷ��ʹ���ο͵�¼,��yȷ��,���������ַ��ص���¼ҳ�� : ");
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




void menu()														//�˵�ҳ 
{
	system("cls"); 
	int x;
	printf("\n\n\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*1 : ---- �鿴�鼮�嵥                                *\n");
	printf("\t\t\t\t*2 : ---- �����鼮                                    *\n");
	printf("\t\t\t\t*3 : ---- �黹�鼮                                    *\n");
	if(permission==0)
	{
		printf("\t\t\t\t*4 : ---- �޸�ͼ����Ϣ                                *\n");	
	}
	else if(permission==1)
	{
		printf("\t\t\t\t*4 : ---- �޸�ͼ����Ϣ(������Ա����)                  *\n");
	}
	printf("\t\t\t\t*5 : ---- �˳�����                                    *\n");
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t>>>��������Ҫʹ�õĹ��� : ");
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
			printf("\t\t\t�ǹ���Ա�˺�,�޷��޸� ! \n\t\t\t\t\t\t\t������������ѯͼ�����Ա ! \n\t\t\t\t\t\t\t����������ز˵� : ");
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


void menu_yk() 													//�����ο�ģʽ�Ĳ˵�-�������˵���֤��ȫ 
{
	system("cls"); 
	int x;
	printf("\n\n\t\t\t\t*********************************************************\n");
	printf("\t\t\t\t**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**\n");
	printf("\t\t\t\t*|     \t\t�ο��˺ŵ�¼�ɹ� !                     |*\n\t\t\t\t**     \t\t���ɲ鿴�鼮�嵥                       **\n");
	printf("\t\t\t\t*|     \t\t1 : ---- �鿴�鼮�嵥                  |*\n");
	printf("\t\t\t\t**     \t\t2 : ---- �ص���¼����                  **\n");
	printf("\t\t\t\t*|     \t\t3 : ---- �˳�����                      |*\n");
	printf("\t\t\t\t**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**\n");
	printf("\t\t\t\t>>>��������Ҫʹ�õĹ��� : ");
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


void list()														//�鼮�嵥ҳ 
{	
	int i;
	system("cls");
	count();
	printf("\n\n\t\t\t\t****************************\n");
	for(i=0;i<bookkinds;i++)
	{	
		printf("\t\t\t\t||%d------��%s��\n",i+1,book[i].name);	
	}
	printf("\t\t\t\t****************************\n");
	printf("\t\t\t\t>>>��������ص������� : ");
	scanf("%s");
	menu();
}
 
void list_yk()													//�ο�ģʽ���鼮�嵥Ҳ,���ڻص��ο�ģʽ���˵�,����Ȩ��й¶ 
{
	int i;
	system("cls");
	count();
	printf("\n\n\t\t\t\t****************************\n");
	for(i=0;i<bookkinds;i++)
	{	
		printf("\t\t\t\t||%d------��%s��\n",i+1,book[i].name);
	}
	printf("\t\t\t\t****************************\n");
	printf("\t\t\t\t>>>��������ص������� : ");
	scanf("%s");
	menu_yk();
} 

void borrow()															//����bug ���볤�����ϸ�С������ ------�ѽ�� 
{
	system("cls");
	count(); 
	for(int i=0;i<bookkinds;i++)										//��ѯ״̬���� 
	{
		book[i].f_query=0;	
	} 
	int zt=0,kz=0,bbb=0;
	printf(">>>������Ҫ������鼮(��ģ����ѯ) : ");
	scanf("%s",name_r);
	int lens=strlen(name_r);
	char b[bookkinds][100][lens+1];
	for(int u=0;u<bookkinds;u++)										//��Ƭ 
	{
		if(strlen(book[u].name)<lens)									//�����ѯ���ݴ��������������
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
	printf("\t\t����\t\t����\t\t\t������\t\t�ݲ���\t�ɽ���\n");	
	for(int i=0;i<bookkinds;i++)										//ģ����ѯ 
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

	
	if(lens>=4)															//�����볤�ȴ���2������ʱ�������������Ҳ����ģ����ѯ 
	{
		for(int u=0;u<bookkinds;u++)									//����ģ����ѯ   //��Ƭ 
		{
			if(strlen(book[u].author)<lens)								//�����ѯ���ݴ����������������
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
			
		for(int i=0;i<bookkinds;i++)									//ģ����ѯ 
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
		
			for(int u=0;u<bookkinds;u++)								//������ģ����ѯ   //��Ƭ 
		{
			if(strlen(book[u].publisher)<lens)							//�����ѯ���ݴ��ڳ��������������
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
			
		for(int i=0;i<bookkinds;i++)									//ģ����ѯ 
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
		printf(">>>�������鼮���ȷ��(����0�������˵�) : "); 
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
			printf("\t\t\t\t>>>���ָ���˲���ȷ���鼮,������������ϲ�˵� : "); 
			scanf("%s");
			borrow(); 
		}
		system("cls");
		printf("\n\n\t\t\t\t*********************************\n");
		printf("\t\t\t\t||���� : %s\n\t\t\t\t||���� : %s\n\t\t\t\t||������ : %s\n\t\t\t\t||ISBN : %s\n\t\t\t\t||�ݲ��� : %d\n\t\t\t\t||�ɽ��� : %d\n",
		book[kz].name,book[kz].author,book[kz].publisher,book[kz].ISBN,book[kz].num_z,book[kz].num_x);
		printf("\t\t\t\t*********************************\n");
		printf("\t\t\t\t>>>��˶��鼮��Ϣ��ȷ���Ƿ����(Y/N)");
		scanf("%c",&bbb);
		getchar();  
		if(bbb=='Y'||bbb=='y')
		{
			if(book[kz].num_x>0)
			{
				printf("\t\t\t\t>>>����ɹ�!\n\t\t\t\t>>>���ڹ涨�����ڻ���!\n\t\t\t\t>>>���������밴y���س�,������������ص���ҳ : ");
				book[kz].num_x -= 1;				//����ɹ�,��ȥ����ͼ��һ��
				file_w();							//����д���ļ� 
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
				printf("\n\n\t\t\t\t>>>�ǳ���Ǹ,����ʧ��,ͼ���治��,����ϵͼ�����Ա����ͼ��\n");		
				printf("\t\t\t\t*********************************\n");
				printf("\t\t\t\t||1: -------- ��������\n\t\t\t\t||2: -------- �ص���ҳ\n");
				printf("\t\t\t\t*********************************\n");
				printf("\t\t\t\t>>>��������Ҫʹ�õĹ��� : ");
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
			printf("\t\t\t\t||1: -------- ��������\n\t\t\t\t||2: -------- �ص���ҳ\n");
			printf("\t\t\t\t*********************************\n");
			printf("\t\t\t\t>>>��������Ҫʹ�õĹ��� : ");
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
		printf(">>>δ��ѯ������ͼ��,��Y�س�������ѯ,������������ص���ҳ : "); 
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
		printf("��Ŀǰû����Ҫ�黹���鼮 ! "); 
		printf("�밴������������˵� ! ");
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
	printf("\n�������鼮���ȷ�ϻ���(����0�������˵�) : "); 
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
		printf("\n���ָ���˲���ȷ���鼮,������������ϲ�˵� : "); 
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
		printf("����ɹ�!");
		printf("��y��������,��������������˵� : ");
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
	printf("\t\t\t\t*     \t\t1------���һ���鼮��Ϣ                  *\n\t\t\t\t*     \t\t2------�޸�һ���鼮��Ϣ                  *\n\t\t\t\t*     \t\t3------ɾ��һ���鼮��Ϣ                  *\n\t\t\t\t*     \t\t4------������һ��                        *\n");
	printf("\t\t\t\t**********************************************************\n");
	printf("\t\t\t\t>>>��������Ҫʹ�õĹ��� : ");
	scanf("%d",&k);
	count();
	if(k==1)
	{	
		system("cls");
		s=bookkinds;
		book[s].num_z=0;
		book[s].num_x=0;
		printf("\n\n\t\t\t\t*********************************");
		printf("\n\t\t\t\t||������������鼮������ : ");
		scanf("%s",book[s].name);
		printf("\n\t\t\t\t||������������鼮������ : ");
		scanf("%s",book[s].author);
		printf("\n\t\t\t\t||������������鼮�ĳ����� : ");
		scanf("%s",book[s].publisher);
		printf("\n\t\t\t\t||������������鼮��ISBN��� : ");
		scanf("%s",book[s].ISBN);
		printf("\n\t\t\t\t||������������鼮���ܿ���� : ");
		scanf("%d",&book[s].num_z);
		printf("\n\t\t\t\t||������������鼮�����п���� : ");
		scanf("%d",&book[s].num_x);
		printf("\n\t\t\t\t||������������鼮��������� : ");
		scanf("%s",book[s].date);
		printf("\n\t\t\t\t>>>�鼮��ӳɹ���");
		printf("\n\t\t\t\t*********************************\n");
		file_w();
		printf("\t\t\t\t>>>��y�鿴�鼮�嵥��������������������� : ");
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
		printf("\n\n\t\t\t\t>>>��������Ҫ�޸ĵ��鼮�����(1~%d) : ",bookkinds);
		scanf("%d",&m);
		if(m<1||m>bookkinds)
		{	
			printf("\t\t\t\t>>>��Χ������󣡰������������һ�� : ");
			scanf("%s");
			update();
		}
		else
		{	
			printf("\n\n\t\t\t\t*********************************");
			printf("\n\t\t\t\t||���������޸ĵ��鼮������ : ");
			scanf("%s",book[m-1].name);
			printf("\n\t\t\t\t||���������޸��鼮������ : ");
			scanf("%s",book[m-1].author);
			printf("\n\t\t\t\t||���������޸��鼮�ĳ����� : ");
			scanf("%s",book[m-1].publisher);
			printf("\n\t\t\t\t||���������޸��鼮��ISBN��� : ");
			scanf("%s",book[m-1].ISBN);
			printf("\n\t\t\t\t||���������޸��鼮���ܿ����(�ڴ˴�����0������ñ�ͼ��) : n");
			scanf("%d",&book[m-1].num_z);
			printf("\n\t\t\t\t||���������޸��鼮�����п���� : ");
			scanf("%d",&book[m-1].num_x);
			printf("\n\t\t\t\t||���������޸��鼮���޸����� : ");
			scanf("%s",book[m-1].date);
			printf("\n\t\t\t\t||�鼮�޸ĳɹ���");
			printf("\n\t\t\t\t*********************************\n");
			clear();
			printf("\t\t\t\t>>>��y�鿴�鼮�嵥��������������������� : ");
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
		printf("\n\t\t\t\t>>>��������Ҫɾ�����鼮�����(1~%d),����������ȡ������ : ",bookkinds); 
		scanf("%d",&m);
		getchar(); 
		if(m>=1&&m<=bookkinds)
		{
			book[m-1].num_z=0;
			clear();
			printf("\t\t\t\t>>>ɾ���ɹ�!");
		}
		else
		{
			printf("\t\t\t\t>>>ȡ��ɾ�� ! \n");
		} 
		printf("\n\t\t\t\t>>>��y�鿴�鼮�嵥��������������������� : ");
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
//��Ϊ�����ʽ���㸴�� 
