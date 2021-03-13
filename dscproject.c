#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX_CACHE_SIZE 5
#define MAX_STRING_SIZE 200
#define MAX_STACK_SIZE 100

typedef struct info
{
  char country[MAX_STRING_SIZE];
  char capital[MAX_STRING_SIZE];
} information;

typedef struct caching *Pointer;
typedef struct caching
{
  information data;
  Pointer link;
} waste;

typedef struct node *treepointer;
typedef struct node
{
  information data;
  treepointer left, right;
} r;

typedef struct fnode *fptr;
typedef struct fnode
{
  char field[2 * MAX_STRING_SIZE];
} c;

fptr countries[100];
char icountry[MAX_STRING_SIZE];
char icapital[MAX_STRING_SIZE];
treepointer stack[MAX_STACK_SIZE];

void searchtree(treepointer, char[]);
void insert(char[], char[]);
void printmemory();
void pop();
void rearrange(char[], char[]);
void clear();
void print(Pointer);
int search(Pointer, char[]);
int searchqueue(Pointer, char[]);
void readfile(void);
treepointer gettree(int, int);
void display(treepointer);
void insert_new_node(treepointer);
void writefile(treepointer);
void pushs(treepointer);
treepointer pops();
int n = 0;
int node_num = 0;
int top = -1;
Pointer front, rear;
treepointer root;
int main()
{
  //Pointer front,rear;
  front = NULL;
  rear = NULL;

  int ch;

  readfile();
  root = gettree(0, n - 1);
  char str[MAX_STRING_SIZE];
  /*printf("\tCACHING MENU\t\n");
    printf("---------------------------\n");
    printf("1:Insert\n");
    printf("2:Clear All\n");
    printf("3:Print The Cache\n");
    printf("4:Exit\n");
    printf("---------------------------\n");*/
  do
  {
    printf("\n1.Search\n2.Exit\nChoice : ");
    scanf("%d", &ch);
    switch (ch)
    {
    case 0:
      display(root);
      break;
    case 1:
      printmemory(front);
      printf("Enter the field to be searched: ");
      scanf("%s", str);
      searchtree(root, str);
      break;
    case 2:
      exit(0);
    default:
      printf("Enter the correct choice: ");
    }
  } while (1);
}

void searchtree(treepointer ptr, char search[MAX_STRING_SIZE])
{
  int match = searchqueue(front, search);
  if (match == 1)
    return;
  while ((ptr))
  {
    if ((strcmp(search, (ptr)->data.country) == 0))
    { printf("The Node is found in the TREE......\n");
      printf("The capital of the node is %s ", (ptr)->data.capital);
      printf("\n");
      insert((ptr)->data.country, (ptr)->data.capital);
      return;
    }
    if ((strcmp(search, (ptr)->data.country) < 0))
    {

      (ptr) = (ptr)->left;
      //printf("%s",ptr->data.country);
    }
    else
    {
      (ptr) = (ptr)->right;
      //printf("%s",ptr->data.country);
    }
  }
  int ch;
  printf("Country Not Found.!!!\n");
  printf("Do you want to make a new entry(0/1)?\n");
  scanf("%d", &ch);
  if (ch)
  {
    strcpy(icountry, search);
    printf("Enter the capital of %s :", search);
    scanf("%s", icapital);

    insert_new_node(root);
    insert(icountry, icapital);
  }
}
void insert(char country[MAX_STRING_SIZE], char capital[MAX_STRING_SIZE])
{
  int match = 0;
  Pointer checkk = front;
  match = search(checkk, country);
  if (match == 1)
    rearrange(country, capital);
  else
  {
    Pointer temp = (Pointer)malloc(sizeof(Pointer *));
    strcpy(temp->data.country, country);
    strcpy(temp->data.capital, capital);
    temp->link = NULL;
    if (node_num == MAX_CACHE_SIZE)
      pop();
    if (!(front))
      (front) = temp;
    else
      (rear)->link = temp;
    (rear) = temp;
    ++node_num;
  }
}
//To pop the last found search word in the cache
void pop()
{
  Pointer temp;
  temp = (front);
  (front) = temp->link;
  free(temp);
  --node_num;
}
//To rearrange the position of the node in the cache if already present
void rearrange(char country[MAX_STRING_SIZE], char capital[MAX_STRING_SIZE])
{
  Pointer temp = (front);
  if (strcmp((rear)->data.country, country) == 0)
    return;
  if (strcmp(temp->data.country, country) == 0)
  {
    pop();
    insert(country, capital);
  }
  else
  {
    while (strcmp(temp->link->data.country, country))
      temp = temp->link;
    Pointer new = temp->link;
    temp->link = new->link;
    --node_num;
    insert(country, capital);
    free(new);
    printmemory(front);
  }
}

//To clear the cache memory
void clear()
{
  Pointer temp = (front);
  (front) = NULL;
  (rear) = NULL;
  node_num = 0;
  free(temp);
}
//To print the content of the cache
void printmemory()
{
  Pointer temp = front;
  printf("CACHE MEMORY:\n");
  print(temp);
  printf("\n");
}
void print(Pointer front)
{
  if (front == NULL)
    return;

  // print the list after head node
  print(front->link);
  // After everything else is printed, print head
  printf("%s\n", front->data.country);
  //printf("%s\n",front->data.capital);
}
void readfile(void)
{
  FILE *fp;

  fp = fopen("DATA", "r");
  fscanf(fp, "%d", &n);
  for (int i = 0; i < n; i++)
  {
    countries[i] = (fptr)malloc(sizeof(c));
    fscanf(fp, "%s", countries[i]->field);
  }
  fclose(fp);
}

treepointer gettree(int start, int end)
{
  if (start > end)
    return NULL;
  int mid = ((start + end) / 2);
  treepointer temp = (treepointer)malloc(sizeof(r));
  int i = 0;
  char *token = strtok(countries[mid]->field, ":");
  while (i < 2)
  {
    if (i == 0)
    {
      strcpy(temp->data.country, token);
    }
    else if (i == 1)
    {
      strcpy(temp->data.capital, token);
    }
    token = strtok(NULL, ":");
    i++;
  }
  temp->left = gettree(start, mid - 1);
  temp->right = gettree(mid + 1, end);
  return temp;
}

void display(treepointer ptr)
{
  if (ptr)
  {
    display(ptr->left);
    printf("\n%s : %s", ptr->data.country, ptr->data.capital);
    display(ptr->right);
  }
}

void insert_new_node(treepointer ptr)
{
  n++;
  FILE *fp;
  fp = fopen("DATA", "w");
  fprintf(fp, "%d", (n));
  fclose(fp);
  writefile(ptr);
  readfile();
  root = gettree(0, (n)-1);
}

void writefile(treepointer ptr)
{
  FILE *fp;
  fp = fopen("DATA", "r+");
  fseek(fp, 0L, 2);
  top = -1;
  int flag = 0;
  for (;;)
  {

    for (; ptr; (ptr) = (ptr)->left)
      pushs((ptr));

    ptr = pops();

    if (!(ptr))
      break;
    if (((strcmp(icountry, (ptr)->data.country)) < 0) && (flag == 0))
    {
      fprintf(fp, " %s:%s", icountry, icapital);
      flag = 1;
    }
    fprintf(fp, " %s:%s", (ptr)->data.country, (ptr)->data.capital);
    ptr = (ptr)->right;
  }
  if (flag == 0)
  {
    fprintf(fp, " %s:%s", icountry, icapital);
  }
  fclose(fp);
}

void pushs(treepointer ptr)
{

  top = top + 1;

  stack[top] = ptr;
}

treepointer pops()
{
  if ((top) >= 0)
  {
    treepointer temp;
    temp = stack[top];
    top = top - 1;
    return temp;
  }
  else
    return NULL;
}
int searchqueue(Pointer check, char country[MAX_STRING_SIZE])
{
  for (; check; check = check->link)
  {
    //printf("%s\n",check->data.capital);
    if (strcmp(check->data.country, country) == 0)
    {  printf("The Node is found in the CACHE......\n");
      printf("The capital of the node is: %s\n", check->data.capital);
      insert(country, check->data.capital);
      return 1;
    }
  }
}
int search(Pointer check, char country[MAX_STRING_SIZE])
{
  for (; check; check = check->link)
  {
    if (strcmp(check->data.country, country) == 0)
    {
      return 1;
    }
  }
}
