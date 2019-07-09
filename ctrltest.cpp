#include "stdio.h"
#include "stdlib.h"								//����system()���� 
#include "string.h"

#define N 100									//�鼮�ṹ�嶨������
#define Nid 50

												//��������
void sign();									//��¼  
void menu();									//�˵���ҳ			//������					
void list();									//��ʾ���б� 		//���� 
void borrow();									//���� 				//�ػ��� 
void update();									//�޸�����Ϣ 		//��� 


void menu_yk(); 								//�ο�ģʽ�˵� 
void list_yk(); 								//�ο�ģʽ��ʾ 

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
{{"2018040000","123456",2}
,{"2018040072","qwerty",1}};


static int bookkinds=0,id_num=0;
int counter=0;
char name_r[100]={0}; 
int permission=0;


FILE *fp_book,*fp_id;

 
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
		printf("%d------��%s��\n",i+1,book[i].name);
	}
}



void sign()														//��¼ҳ 
{
	system("cls"); 
	int n,a=0;
	char geta[20],getp[20]; 
	char zhanghu[2][10]={"����Ա","ѧ��"}; 
	id_read();
	printf("*****��ӭʹ��ͼ�����ϵͳ*****\n"); 
	printf("1 : ---- �˺ŵ�¼\n");
    printf("2 : ---- �ο�ϵͳ\n");
    printf("3 : ---- �˳�ϵͳ\n");
    printf("��������Ҫʹ�õĹ��ܣ������س��� : ");
	scanf("%d",&n);
	getchar(); 
	if(n==1)
	{
		printf("�������ʺţ�");
		scanf("%s",geta);
		printf("���������룺");
		scanf("%s",getp);
		for(int i=0;i<id_num;i++)
		{
			if(strcmp(geta,id[i].account)==0)
			{
				a=1; 
				if(strcmp(getp,id[i].password)==0)
				{
					permission=id[i].perm; 
					printf("%s��¼�ɹ� ! \n���������ַ�����˵� : ",zhanghu[i]);
					scanf("%s"); 
					menu();
				}
				else
				{
					printf("�������,�����µ�¼ ! \n���������ַ����ص�¼ : ");	
					sign();
				}
			}
		} 
		if(a==0) 
		{
			printf("�˺Ų�����,�����µ�¼,����ѯͼ�����Ա��ͨ�˺� ! \n���������ַ����ص�¼ : \n");
			sign();
		}
	}
	else if(n==2)
	{
		printf("ȷ��ʹ���ο͵�¼,��yȷ��,���������ַ��ص���¼ҳ�� : ");
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
	printf("1 : ---- �鿴�鼮�嵥\n");
	printf("2 : ---- �����鼮\n");
	if(permission==0)
	{
		printf("3 : ---- �޸�ͼ����Ϣ\n");	
	}
	else if(permission==1)
	{
		printf("3 : ---- �޸�ͼ����Ϣ(������Ա����)\n");
	}
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
		if(permission==1)
		{
			system("cls"); 
			printf("�ǹ���Ա�˺�,�޷��޸� ! \n������������ѯͼ�����Ա ! \n����������ز˵� : ");
			scanf("%s"); 
			menu();
		}
		if(permission==0)
		{
			update();
		}
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


void menu_yk() 													//�����ο�ģʽ�Ĳ˵�-�������˵���֤��ȫ 
{
	system("cls"); 
	int x;
	printf("�ο��˺ŵ�¼�ɹ� ! \n���ɲ鿴�鼮�嵥\n");
	printf("1 : ---- �鿴�鼮�嵥\n");
	printf("2 : ---- �ص���¼����\n");
	printf("3 : ---- �˳�����\n");
	printf("��������Ҫʹ�õĹ��� : ");
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
	for(i=0;i<bookkinds;i++)
	{	
		printf("%d------��%s��\n",i+1,book[i].name);
	}
	printf("��������ص������� : ");
	scanf("%s");
	menu();
}
 
void list_yk()													//�ο�ģʽ���鼮�嵥Ҳ,���ڻص��ο�ģʽ���˵�,����Ȩ��й¶ 
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
	printf("������Ҫ������鼮(��ģ����ѯ) : ");
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
		
	for(int i=0;i<bookkinds;i++)										//ģ����ѯ 
	{
		for(int k=0;k<strlen(book[i].name);k++)
		{
			if(strcmp(name_r,b[i][k])==0)
			{
				printf("%d--------%s\n",i+1,book[i].name);
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
					printf("%d--------%s\n",i+1,book[i].name);
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
					printf("%d--------%s\n",i+1,book[i].name);
					book[i].f_query=1; 
					zt=1;
					break; 
				}
			}	
		}
	}

	if(zt==1)
	{
		printf("�������鼮���ȷ��(����0�������˵�) : "); 
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
			printf("���ָ���˲���ȷ���鼮,������������ϲ�˵� : "); 
			scanf("%s");
			borrow(); 
		}
		system("cls");
		printf("���� : %s\n���� : %s\n������ : %s\nISBN : %s\n�ݲ��� : %d\n�ɽ��� : %d\n��˶��鼮��Ϣ��ȷ���Ƿ����(Y/N)",
		book[kz].name,book[kz].author,book[kz].publisher,book[kz].ISBN,book[kz].num_z,book[kz].num_x);
		scanf("%c",&bbb);
		getchar();  
		if(bbb=='Y'||bbb=='y')
		{
			if(book[kz].num_x>0)
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
			else
			{
				system("cls");
				printf("�ǳ���Ǹ,����ʧ��,ͼ���治��,����ϵͼ�����Ա����ͼ��\n");
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
	printf("1------���һ���鼮��Ϣ\n2------�޸�һ���鼮��Ϣ\n3------ɾ��һ���鼮��Ϣ\n4------������һ��\n"); 
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
			printf("\n���������޸��鼮���ܿ����(�ڴ˴�����0������ñ�ͼ��) : ");
			scanf("%d",&book[m-1].num_z);
			printf("\n���������޸��鼮�����п���� : ");
			scanf("%d",&book[m-1].num_x);
			printf("\n���������޸��鼮�Ľ������� : ");
			scanf("%s",book[m-1].date);
			printf("\n�鼮�޸ĳɹ���");
			clear();
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
		system("cls"); 
		list_print(); 
		printf("��������Ҫɾ�����鼮�����(1~%d),����������ȡ������ : ",bookkinds); 
		scanf("%d",&m);
		getchar(); 
		if(m>=1&&m<=bookkinds)
		{
			book[m-1].num_z=0;
			clear();
		}
		else
		{
			printf("ȡ��ɾ�� ! \n");
		} 
		printf("��y�鿴�鼮�嵥��������������������� : ");
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
	count();	
	sign(); 
}
//printf("%s\n%s\n%s\n%s\n%d\n%d\n%s\n",book[i].name,book[i].author,book[i].publisher,book[i].ISBN,book[i].num_z,book[i].num_x,book[i].date);
//��Ϊ�����ʽ���㸴�� 
