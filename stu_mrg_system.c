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
}Node,*Link,*Statistic;

void menu();
void Disp(Link header);
void Add(Link);
void Query(Link header);
void Del(Link header);
void Modify(Link header);
void Insert(Link header);
void printData(Node *pp);


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
void printData(Node *pp)
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
    printData(p);
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
      printData(result);
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
      printData(result);
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
void Insert(Link header)
{
  Node *loc, *tmp,*p;

  char loc_num[10],flag,again;
  while(1)
  {
    tmp = header->next;
    flag = '0';
    stringInput(loc_num,10,"input the number after insert\n");

    while(tmp)
    {
      if(strcmp(tmp->data.num,loc_num) == 0)
      {
        loc = tmp;
        flag = '1';
        break;
      }
      tmp = tmp->next;
    }

    if(flag == '0')
    {
      getchar();
      printf("not found number,try again(y/n):\n");  
      scanf("%c",&again);
      if(again == 'Y' || again == 'y')
      {
        continue;
      }
    }
    else
    {
      p = (Node*)malloc(sizeof(Node));
      if(!p)
      {
        printf("memory allocate failure!");
        return;
      }
      printf("input the student info:\n");
      stringInput(p->data.num,10,"Number:");
      stringInput(p->data.name,15,"Name");
      p->data.cgrade = numberInput("C language score:");
      p->data.mgrade = numberInput("Math score:");
      p->data.egrade = numberInput("English score:");
      p->data.total = p->data.cgrade + p->data.mgrade + p->data.egrade;
      p->data.avg = (float)p->data.total / 3;
      p->data.level = 0;
      p->next = loc->next;
      loc->next = p;
    }
    break;
  }
}
void statistics(Link header)
{
  Node *tmp,*s_t_header,*s_c_header,*s_m_header,*s_e_header,*freeTmp;
  s_t_header = (Node*)malloc(sizeof(Node));
  s_t_header->next = NULL;
  s_c_header = (Node*)malloc(sizeof(Node));
  s_c_header->next = NULL;
  s_m_header = (Node*)malloc(sizeof(Node));
  s_m_header->next = NULL;
  s_e_header = (Node*)malloc(sizeof(Node));
  s_e_header->next = NULL;
  int max_t = -1,max_c = -1,max_m = -1,max_e = -1;
  Statistic s_t_tmp,s_c_tmp,s_m_tmp,s_e_tmp;
  tmp = header->next;
  if(!tmp)
  {
    printf("\n=============>No student data\n");
    return;
  }
  
  while(tmp)
  {
    if(max_t < tmp->data.total || max_t == -1)
    {
      max_t = tmp->data.total;
      s_t_tmp = s_t_header->next;
      while(s_t_tmp)
      {
        freeTmp = s_t_tmp;
        s_t_tmp = s_t_tmp->next;
        free(freeTmp);
      }
      s_t_tmp = (Node*)malloc(sizeof(Node));
      strcpy(s_t_tmp->data.num,tmp->data.num);
      strcpy(s_t_tmp->data.name,tmp->data.name);
      s_t_tmp->data.cgrade = tmp->data.cgrade;
      s_t_tmp->data.mgrade = tmp->data.mgrade;
      s_t_tmp->data.egrade = tmp->data.egrade;
      s_t_tmp->data.total = tmp->data.total;
      s_t_tmp->data.avg = tmp->data.avg;
      s_t_tmp->data.level = tmp->data.level;
      s_t_header->next = s_t_tmp;
      s_t_tmp->next = NULL;
    }
    else if(max_t == tmp->data.total)
    {
      s_t_tmp->next = (Node*)malloc(sizeof(Node));
      strcpy(s_t_tmp->next->data.num,tmp->data.num);
      strcpy(s_t_tmp->next->data.name,tmp->data.name);
      s_t_tmp->next->data.cgrade = tmp->data.cgrade;
      s_t_tmp->next->data.mgrade = tmp->data.mgrade;
      s_t_tmp->next->data.egrade = tmp->data.egrade;
      s_t_tmp->next->data.total = tmp->data.total;
      s_t_tmp->next->data.avg = tmp->data.avg;
      s_t_tmp->next->data.level = tmp->data.level;
      s_t_tmp = s_t_tmp->next;
    }

    if(max_c < tmp->data.cgrade || max_c == -1)
    {
      max_c = tmp->data.cgrade;
      s_c_tmp = s_c_header->next;
      while(s_c_tmp)
      {
        freeTmp = s_c_tmp;
        s_c_tmp = s_c_tmp->next;
        free(freeTmp);
      }
      s_c_tmp = (Node*)malloc(sizeof(Node));
      strcpy(s_c_tmp->data.num,tmp->data.num);
      strcpy(s_c_tmp->data.name,tmp->data.name);
      s_c_tmp->data.cgrade = tmp->data.cgrade;
      s_c_tmp->data.mgrade = tmp->data.mgrade;
      s_c_tmp->data.egrade = tmp->data.egrade;
      s_c_tmp->data.total = tmp->data.total;
      s_c_tmp->data.avg = tmp->data.avg;
      s_c_tmp->data.level = tmp->data.level;
      s_c_header->next = s_c_tmp;
      s_c_tmp->next = NULL;
    }
    else if(max_c == tmp->data.cgrade)
    {
      s_c_tmp->next = (Node*)malloc(sizeof(Node));
      strcpy(s_c_tmp->next->data.num,tmp->data.num);
      strcpy(s_c_tmp->next->data.name,tmp->data.name);
      s_c_tmp->next->data.cgrade = tmp->data.cgrade;
      s_c_tmp->next->data.mgrade = tmp->data.mgrade;
      s_c_tmp->next->data.egrade = tmp->data.egrade;
      s_c_tmp->next->data.total = tmp->data.total;
      s_c_tmp->next->data.avg = tmp->data.avg;
      s_c_tmp->next->data.level = tmp->data.level;
      s_c_tmp = s_c_tmp->next;
    }

    if(max_m < tmp->data.mgrade || max_m == -1)
    {
      max_m = tmp->data.mgrade;
      s_m_tmp = s_m_header->next;
      while(s_m_tmp)
      {
        freeTmp = s_m_tmp;
        s_m_tmp = s_m_tmp->next;
        free(freeTmp);
      }
      s_m_tmp = (Node*)malloc(sizeof(Node));
      strcpy(s_m_tmp->data.num,tmp->data.num);
      strcpy(s_m_tmp->data.name,tmp->data.name);
      s_m_tmp->data.cgrade = tmp->data.cgrade;
      s_m_tmp->data.mgrade = tmp->data.mgrade;
      s_m_tmp->data.egrade = tmp->data.egrade;
      s_m_tmp->data.total = tmp->data.total;
      s_m_tmp->data.avg = tmp->data.avg;
      s_m_tmp->data.level = tmp->data.level;
      s_m_header->next = s_m_tmp;
      s_m_tmp->next = NULL;
    }
    else if(max_m == tmp->data.mgrade)
    {
      s_m_tmp->next = (Node*)malloc(sizeof(Node));
      strcpy(s_m_tmp->next->data.num,tmp->data.num);
      strcpy(s_m_tmp->next->data.name,tmp->data.name);
      s_m_tmp->next->data.cgrade = tmp->data.cgrade;
      s_m_tmp->next->data.mgrade = tmp->data.mgrade;
      s_m_tmp->next->data.egrade = tmp->data.egrade;
      s_m_tmp->next->data.total = tmp->data.total;
      s_m_tmp->next->data.avg = tmp->data.avg;
      s_m_tmp->next->data.level = tmp->data.level;
      s_m_tmp = s_m_tmp->next;
    }
    
    if(max_e < tmp->data.egrade || max_e == -1)
    {
      max_e = tmp->data.egrade;
      s_e_tmp = s_e_header->next;
      while(s_e_tmp)
      {
        freeTmp = s_e_tmp;
        s_e_tmp = s_e_tmp->next;
        free(freeTmp);
      }
      s_e_tmp = (Node*)malloc(sizeof(Node));
      strcpy(s_e_tmp->data.num,tmp->data.num);
      strcpy(s_e_tmp->data.name,tmp->data.name);
      s_e_tmp->data.cgrade = tmp->data.cgrade;
      s_e_tmp->data.mgrade = tmp->data.mgrade;
      s_e_tmp->data.egrade = tmp->data.egrade;
      s_e_tmp->data.total = tmp->data.total;
      s_e_tmp->data.avg = tmp->data.avg;
      s_e_tmp->data.level = tmp->data.level;
      s_e_header->next = s_m_tmp;
      s_e_tmp->next = NULL;
    }
    else if(max_e == tmp->data.egrade)
    {
      s_e_tmp->next = (Node*)malloc(sizeof(Node));
      strcpy(s_e_tmp->next->data.num,tmp->data.num);
      strcpy(s_e_tmp->next->data.name,tmp->data.name);
      s_e_tmp->next->data.cgrade = tmp->data.cgrade;
      s_e_tmp->next->data.mgrade = tmp->data.mgrade;
      s_e_tmp->next->data.egrade = tmp->data.egrade;
      s_e_tmp->next->data.total = tmp->data.total;
      s_e_tmp->next->data.avg = tmp->data.avg;
      s_e_tmp->next->data.level = tmp->data.level;
      s_e_tmp = s_e_tmp->next;
    }
    tmp = tmp->next;
  }

  printf("the highest total score:\n");
  printf(HEADER2);
  s_t_tmp = s_t_header->next;
  while(s_t_tmp)
  {
    printf(HEADER3);
    printData(s_t_tmp);
    s_t_tmp = s_t_tmp->next;
  }
  printf(END);
  
  printf("the highest math score:\n");
  printf(HEADER2);
  s_m_tmp = s_m_header->next;
  while(s_m_tmp)
  {
    printf(HEADER3);
    printData(s_m_tmp);
    s_m_tmp = s_m_tmp->next;
  }
  printf(END);
  
  printf("the highest C language score:\n");
  printf(HEADER2);
  s_c_tmp = s_c_header->next;
  while(s_c_tmp)
  {
    printf(HEADER3);
    printData(s_c_tmp);
    s_c_tmp = s_c_tmp->next;
  }
  printf(END);
  
  printf("the highest English score:\n");
  printf(HEADER2);
  s_e_tmp = s_e_header->next;
  while(s_e_tmp)
  {
    printf(HEADER3);
    printData(s_e_tmp);
    s_e_tmp = s_e_tmp->next;
  }
  printf(END);
  
  s_t_tmp = s_t_header->next;
  s_c_tmp = s_c_header->next;
  s_m_tmp = s_m_header->next;
  s_e_tmp = s_e_header->next;

  free(s_t_header);
  free(s_c_header);
  free(s_m_header);
  free(s_e_header);

  while(s_t_tmp)
  {
    freeTmp = s_t_tmp;
    s_t_tmp = s_t_tmp->next;
    free(freeTmp);
  }
  while(s_c_tmp)
  {
    freeTmp = s_c_tmp;
    s_c_tmp = s_c_tmp->next;
    free(freeTmp);
  }
  while(s_m_tmp)
  {
    freeTmp = s_m_tmp;
    s_m_tmp = s_m_tmp->next;
    free(freeTmp);
  }
  while(s_e_tmp)
  {
    freeTmp = s_e_tmp;
    s_t_tmp = s_e_tmp->next;
    free(freeTmp);
  }
}
