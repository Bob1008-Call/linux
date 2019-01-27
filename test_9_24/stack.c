#include <stdio.h>
#include <malloc.h>
#define OK 1
#define ERROR 0
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int ElemType;
typedef int Status;

typedef struct SqStack
{
  ElemType *base;
  ElemType *top;
  int stacksize;
}SqStack;

Status initStack(SqStack *s)
{
  s->base = (ElemType*)malloc(STACK_INIT_SIZE*sizeof(ElemType));
  if(!(s->base))return ERROR;
  s->top = s->base;
  s->stacksize = STACK_INIT_SIZE;
  return OK;
}

Status GetTop(SqStack *s,ElemType *e)
{
  if(s->top == s->base)return ERROR;
  e = *(s->top-1);
  return;
}

Status Pop(SqStack *s,ElemType *e)
{
  if(s->top == s->base)return ERROR;
  e = *(--s->top);
  return OK;
}

Status Push(SqStack *s,ElemType *e)
{
  if(s->top-s->base >= s->stacksize)
  {
    s->base = (ElemType)realloc(s->base,(s->stacksize+STACKINCREMENT)*sizeof(ElemType));
    if(!(s->base))return ERROR;
    s->stacksize += STACKINCREMENT;
    s->top = s->base+s->stacksize;
  }
  *(s->base)++ = e;
  return OK;
}
