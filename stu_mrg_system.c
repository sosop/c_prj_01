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
void Add(Link);
void Query(Link header);
void Del(Link header);
void Modify(Link header);

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


  while(1)
  {
    menu(); 
    tmp = cur;
    printf("open file success,the total records is: %d\n",count);
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
  printf("**************Eorro input,please input any key to continue!\n");
  getchar();
}
void NotFound()
{
  printf("*************there are no data that you found\n");
  getchar();
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
void Add(Link header)
{
  Node *cur,*tmp,*p;
  char flag,num[10],ch;

  cur = header;
  system("clear");
  Disp(header);
  //将移动链表尾
  while(cur->next != NULL)
    cur = cur->next;
  system("clear");
  while(1) 
  {
    stringInput(num,10,"input num(press 0 return:)");  
    if(strcmp(num,"0") == 0)
    {
      return;
    }
    flag = '0';
    tmp = header->next;
    while(tmp)
    {
      if(strcmp(num,tmp->data.num))
      {
        flag = '1';
        break;
      }
      tmp = tmp->next;
    }
    if(flag == '1')
    {
      getchar();
      printf("the num has exists,are you want to input another ome(y/n):");
      scanf("%c",&ch);
      if(ch == 'y' || ch == 'Y')
      {
        continue;
      }
      else
      {
        return;
      }
    }
    else
    {
      p = (Node*)malloc(sizeof(Node));
      p->next = NULL;
      strcpy(p->data.num,num);
      stringInput(p->data.name,15,"Name:");
      p->data.cgrade = numberInput("C grade:");
      p->data.mgrade = numberInput("math grade:");
      p->data.egrade = numberInput("English grade:");
      p->data.total = p->data.cgrade + p->data.mgrade + p->data.egrade;
      p->data.avg = (float)p->data.total / 3;
      p->data.level = 0;
      cur->next = p;
      cur = p;
      saveFlag = 1;
    }
  }
}
void Query(Link header)
{
  system("clear");
  if(!header->next)
  {
    printf("\n         ================>no student record \n");
    return;
  }
  int select;
  char search[15];
  Node *result;
  printf("\n ===============>1.search by num    2.search by name \n");
  printf("==================please choose [1,2]\n");

  scanf("%d",&select);

  if(select == 1)
  {
    result = locate(header,search,"num");     
    if(result)
    {
      printf(HEADER1);
      printf(HEADER2);
      printf(HEADER3);
      printDate(result);
      printf(END);
      getchar();
    }
    else
    {
      NotFound();
      getchar;
    }
  }
  else if(select == 2)
  {
    result = locate(header,search,"name");     
    if(result)
    {
      printf(HEADER1);
      printf(HEADER2);
      printf(HEADER3);
      printDate(result);
      printf(END);
      getchar();
    }
    else
    {
      NotFound();
      getchar;
    }
  }
  else
  {
    Wrong();
    getchar;
  }
}
void Del(Link header)
{
  system("clear");
  if(!header->next)
  {
    printf("\n         ================>no student record \n");
    return;
  }
  int select;
  char delete[15];
  Node *result,*tmp;
  printf("\n ===============>1.delete by num    2.delete by name \n");
  printf("==================please choose [1,2]\n");

  scanf("%d",&select);

  if(select == 1)
  {
    result = locate(header,delete,"num");     
    if(result)
    {
      tmp = header;
      while(tmp->next != result)
        tmp = tmp->next;
      tmp->next = result->next;
      free(result);
      saveFlag = 1;
      getchar();
    }
    else
    {
      NotFound();
      getchar;
    }
  }
  else if(select == 2)
  {
    result = locate(header,delete,"name");     
    if(result)
    {
      tmp = header;
      while(tmp->next != result)
        tmp = tmp->next;
      tmp->next = result->next;
      free(result);
      saveFlag = 1;
      getchar();
    }
    else
    {
      NotFound();
      getchar;
    }
  }
  else
  {
    Wrong();
    getchar;
  }
}
void Modify(Link header)
{
  system("clear");
  if(!header->next)
  {
    printf("\n         ================>no student record \n");
    return;
  }
  
  char num[10];
  Node *result;
  printf("==================please input the student num\n");

  scanf("%s",num);


  result = locate(header,num,"num");     
  if(result)
  {
    printf("Number: %s\n",result->data.num);
    printf("Name: %s,",result->data.name);
    stringInput(result->data.name,15,"input new Name:");
    printf("C language score: %d,",result->data.cgrade);
    result->data.cgrade = numberInput("input C language new score");
    printf("Math score: %d,",result->data.mgrade);
    result->data.cgrade = numberInput("input Math new score");
    printf("English score: %d,",result->data.egrade);
    result->data.cgrade = numberInput("input English new score");
    result->data.total = result->data.cgrade + result->data.mgrade + result->data.egrade;
    printf("total score: %d,",result->data.egrade);
    result->data.avg = (float)result->data.total/3;  
    printf("average score: %d,",result->data.egrade);
    saveFlag = 1;
    getchar();
  }
  else
  {
    NotFound();
    getchar;
  }
}

