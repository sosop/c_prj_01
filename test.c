#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct User
{
  int id;
  char name[15];
  int age;
};

typedef struct Node
{
  struct User user;
  struct Node * next;
} node,*Link;



void StringInput(char *str,int maxLen,char *notice)
{
  do{
    printf("%s: ",notice);
    scanf("%s",str);
    if(strlen(str) > maxLen)printf("\n Input beyond required! \n");
  }while(strlen(str) > maxLen);
}

int NumberInput(char *notice)
{
  int num;
  printf("%s: ",notice);
  scanf("%d",&num);
  return num;
}

void Read(Link head)
{
  node *cur,*tmp;
  cur = head;
  FILE *fp = fopen("./userInfo","ab+");
  while(feof(fp) == 0)
  {
    tmp = (node*)malloc(sizeof(node));
    if(fread(tmp,sizeof(node),1,fp) == 1)
    {
      tmp->next = NULL;
      cur->next = tmp;
      cur = tmp;
    }
  }
  fclose(fp);
  cur->next = NULL;
}

void Save(Link head)
{
  node *tmp;
  FILE *fp;
  fp = fopen("./userInfo","wb+");
  int count = 0;
  tmp = head->next;
  while(tmp)
  {
    fwrite(tmp,sizeof(node),1,fp);
    //fprintf(fp,"%d %s %d",tmp->user.id,tmp->user.name,tmp->user.age);
    tmp = tmp->next;
  }
  fclose(fp);
}

void ShowUsers(Link head)
{
  node *tmp;
  tmp = head->next;
  system("clear");
  if(!tmp)
  {
    printf("NO RECORDS\n");
    getchar();
    return;
  }
  while(tmp)
  {
    printf("id: %d  name: %s  age: %d\n",tmp->user.id,tmp->user.name,tmp->user.age);
    tmp = tmp->next;
  }
  printf("按任意键返回...");
  getchar();
}

void AddUser(Link head)
{
  node *tmp,*cur;
  char exit;
  cur = head;
  while(cur->next)cur = cur->next;
  system("clear");
  while(1)
  {
    tmp = (node*)malloc(sizeof(node));
    tmp->user.id = NumberInput("请输入ID");
    StringInput(tmp->user.name,15,"请输入姓名");
    tmp->user.age = NumberInput("请输入年龄");
    tmp->next = NULL;
    cur->next = tmp;
    cur = tmp;
    printf("添加成功,按0结束添加，按s键保存并退出，按任意键继续添加:");
    getchar();
    scanf("%c",&exit);
    if(exit == '0')
    {
      return;
    }
    else if(exit == 's' || exit == 'S')
    {
      Save(head);
      return;
    }
  }

}

int main()
{
  Link head = (node*)malloc(sizeof(node));
  Read(head);
  int select;
  while(1)
  {
    system("clear");
    printf("========================\n");
    printf("1.添加用户   2.查看全部\n");
    printf("0.退出系统             \n");
    printf("请输入选择:");
    scanf("%d",&select);
    getchar();
    switch(select)
    {
      case 1:AddUser(head);break;
      case 2:ShowUsers(head);break;
      case 0:system("clear");return;
      default:break;
    }
  }
  return 0;
}
