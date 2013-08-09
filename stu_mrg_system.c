#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEADER1 "----------------------------------------STUDENT----------------------------------------\n"
#define HEADER2 "  |   number   |   name   |   Comp | Math | Eng |   sum   |   avg   |   level  |\n"
#define HEADER3 "  |------------|----------|--------|------|-----|---------|---------|---------|\n"
#define FORMAT  "  |   %-10s    |   %-10s  |   %4d  | %4d  | %4d |   %4d   |   %.2f  |   %4d   |\n"
#define DATA    p->data.num,p->data.name,p->data.cgrade,p->data.mgrade,p->data.egrade,p->data.total,p->data.avg,p->data.level
#define END     "---------------------------------------------------------------------------------------"


//存盘的标志位
int saveFlag = 0;

struct student
{
  char num[10];
  char name[15];
  int cgrade;
  int mgrade;
  int egrade;
  int total;
  float avg;
  int level;
};

typedef struct node
{
  struct student data;
  struct node *next;
}Node,*Link;

void menu();
void Disp(Link header);

int main()
{
  //=====================从文件中取出数据begin==========================
  Link header;
  FILE *fp;
  int select;
  char isSave;
  int count = 0;
  Node *tmp,*cur;
  header = (Node *)malloc(sizeof(Node));
  if(!header)
  {
    printf("memory allocate failure!\n");
    return;
  }
  header->next = NULL;
  cur = header;

  fp = fopen("./studentInfo","ab+");
  if(fp == NULL)
  {
    printf("cat't open file!\n");
    exit(0);
  }

  while(!feof(fp))
  {
    tmp = (Node*)malloc(sizeof(Node));
    if(!tmp)
    {
      printf("memory allocate failure!\n");
      return;
    }

    if(fread(tmp,sizeof(tmp),1,fp) == 1)
    {
      tmp->next = NULL;
      cur->next = tmp;
      cur = tmp;
      count++;
    }

  }
  fclose(fp);
  //=====================从文件中取出数据end==========================

  printf("open file success,the total records is: %d\n",count);


  while(1)
  {
    menu(); 
    tmp = cur;
    printf("please input your choice(0-9):");
    scanf("%d",&select);
    if(select == 0)
    {
      if(saveFlag == 1)
      {
        getchar();
        printf("=========> whether save the modified record to file(y/n):");
        scanf("%c",&isSave);
        //if(isSave == 'Y' || isSave = 'y')//保存
      }
      printf("=============>thank you for your useness!\n");
      getchar();
      break;
    }
    switch(select)
    {
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
      case 6:
        break;
      case 7:
        break;
      case 8:
        break;
      case 9:Disp(header);
             break;
      default:
             break;
    }
  }
  return 0;
}

void menu()
{
  system("clear");
  printf("          The Student's Grade Manage System\n");
  printf("********************************************************\n");
  printf("     * 1.input   record       * 2.delete record\n");
  printf("     * 3.search  record       * 4.modify record\n");
  printf("     * 5.insert  record       * 6.count  record\n");
  printf("     * 7.sort    record       * 8.save   record\n");
  printf("     * 9.display record       * 0.quit   system\n");
  printf("********************************************************\n");
}
void printDate(Node *pp)
{
  Node *p;
  p = pp;
  printf(FORMAT,DATA);
}
void Wrong()
{
  printf("**************8Eorro input,please input any key to continue!\n");
  getchar();
}
void NotFound()
{
  printf("*************there are no data that you found");
}
void Disp(Link header)
{
  Node *p;
  p = header->next;
  if(!p)
  {
    printf("there is no record!\n");
    getchar();
    return;
  }

  printf(HEADER1);  
  printf(HEADER2);  

  while(p)
  {
    printDate(p);
    p = p->next;
    printf(HEADER3);
  }

  printf(END);
  getchar();
}
void stringInput(char *realV,int len,char *notice)
{
  char tmpInput[255];
  do{
    printf(notice);
    scanf("%s",tmpInput);
    if(strlen(tmpInput) > len)printf("\n input beyond required \n");
  }while(strlen(tmpInput) > len);
  strcpy(realV,tmpInput);
}
int numberInput(char *notice)
{
  int tmpInput = 0;
  do{
    printf(notice);
    scanf("%d",&tmpInput);
    if(tmpInput > 100 || tmpInput < 0)printf("\n THE SCORE MUST IN [0,100] \n");
  }while(tmpInput > 100 || tmpInput < 0);
  return tmpInput;
}
Node * locate(Link header,char condition[],char nameornum[])
{
  Node *p;
  p = header->next;
  if(strcmp(nameornum,"num") == 0)
  {
    while(p)
    {
      if(strcmp(p->data.num,condition))
      {
        return p;
      }
      p = p->next;
    }
  }
  else if(strcmp(nameornum,"name") == 0)
  {
    while(p)
    {
      if(strcmp(p->data.name,condition))
      {
        return p;
      }
      p = p->next;
    }
  }
  return NULL;
}
