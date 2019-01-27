#define StackSize 100
#define true 1
#define false 0
#include <stdio.h>
#include <stdlib.h>

typedef char DataType;
typedef struct SeqStack
{
  DataType data[StackSize];
  int top;
}SeqStack;

void InitStack(SeqStack *S)
{
  S->top = -1;
}

int StackEmpty(SeqStack *S)
{
  if(S->top == -1)
    return true;
  else
    return false;
}

int Size(SeqStack *S)
{
  return S->top+1;
}

int StackFull(SeqStack *S)
{
  return S->top == StackSize-1;
}

int StackPush(SeqStack *S,DataType x)
{
  if(S->top == StackSize-1)
    return false;
  else
  {
    S->top++;
    S->data[S->top] = x;
    return true;
  }
}

int StackPop(SeqStack *S)
{
  if(S->top == -1)
    return false;
  else
  {
    S->top--;
    return true;
  }
}

int GetTop(SeqStack *S,DataType *x)
{
  if(S->top == -1)
  {
    return false;
  }
  else
  {
    *x = S->data[S->top];
    return true;
  }
}

int main()
{
  SeqStack Seq;
  SeqStack *S = &Seq;
  DataType a;
  DataType *e = &a;
  InitStack(S);
  printf("栈%s\n",(StackEmpty(S) == true?"空":"不空"));
  printf("a进栈\n");
  StackPush(S,'a');
  printf("b进栈\n");
  StackPush(S,'b');
  GetTop(S,e);
  while(!StackEmpty(S))
  {
    printf("栈中的元素有%d个",Size(S));
    StackPop(S,e);
    printf("%c\n",a);
  }
  printf("\n");
  return 0;
}


