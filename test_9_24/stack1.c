#include <stdio.h>
#include <assert.h>

typedef int SDataType;
#define MAXSIZE 100
typedef struct Stack
{
  SDataType array[MAXSIZE];
  int top;
}Stack;

typedef struct MinStack
{
  Stack data;
  Stack Min;
}MinStack;

typedef struct QueueBy2Stack
{
  Stack s1;
  Stack s2;
}QueueBy2Stack;

typedef struct SharedStack
{
  int array[MAXSIZE];
  int top1;
  int top2;
}SharedStack;

void StackInit(Stack* ps)
{
  assert(ps);
  ps->top = 0;
}
void StackPush(Stack* ps,SDataType data)
{
  assert(ps);
  if(MAXSIZE == ps->top)
    return;
  ps->array[ps->top++] = data;
}

int StackEmpty(Stack* ps)
{
  assert(ps);
  return 0 == ps->top;
}
void StackPop(Stack* ps)
{
  assert(ps);
  if(StackEmpty(ps))
    return;

  ps->top--;
}
SDataType StackTop(Stack* ps)
{
  assert(ps);
  return ps->array[ps->top-1];
}
int StackSize(Stack* ps)
{
  assert(ps);
  return ps->top;
}

////////////////////////////
//数组实现两个栈
///////////////////////////

void SharedStackInit(SharedStack *s)
{
  assert(s);
  s->top1 = 0;
  s->top2 = MAXSIZE-1;
}

void SharedStackPush(SharedStack *s,SDataType data,int which)
{
  assert(s);
  if(s->top1 >s->top2)
    return;
  if(1 == which)
  {
    s->array[s->top1++] = data;
  }
  else
  {
    s->array[s->top2--] = data;
  }
}

void SharedStackPop(SharedStack *s,int which)
{
  assert(s);
  if(1 == which)
  {
    if(s->top1 > 0)
      s->top1--;
  }
  else
  {
    if(s->top2 <MAXSIZE)
      s->top2++;  
  }
}

SDataType SharedStackTop(SharedStack *s,int which)
{
  assert(s);
  if(1 == which)
  {
    return s->array[s->top1-1];
  }
  else
  {
    return s->array[s->top2+1];
  }
}

int SharedStackSize(SharedStack *s,int which)
{
  assert(s);
  if(1 == which)
  {
    return s->top1;
  }
  else
  {
    return MAXSIZE-s->top2-1;
  }
}

int SharedStackEmpty(SharedStack *s,int which)
{
  return 0 == SharedStackSize(s,which);
}
////////////////////////////
//最小栈
////////////////////////////
void MinStackInit(MinStack* ms)
{
  assert(ms);
  StackInit(&ms->data);
  StackInit(&ms->Min);
}

void MinStackPush(MinStack* ms,SDataType data)
{
  assert(ms);
  StackPush(&ms->data,data);
  if(StackEmpty(&ms->Min) || StackTop(&ms->Min)>data)
    StackPush(&ms->Min,data);
}

int MinStackEmpty(MinStack* ms)
{
  return 0==StackEmpty(&ms->data);
}

void MinStackPop(MinStack* ms)
{
  if(StackEmpty(&ms->data))
    return;

  if(StackTop(&ms->Min) == StackTop(&ms->data))
    StackPop(&ms->Min);

  StackPop(&ms->data);
}

SDataType MinStackTop(MinStack* ms)
{
  return StackTop(&ms->data);
}

SDataType MinStackMin(MinStack* ms)
{
  return StackTop(&ms->Min);
}

int MinStackSize(MinStack* ms)
{
  return StackSize(&ms->data);
}
//////////////////////////////////
//判断元素入栈、出栈的合法性
//////////////////////////////////

int InAndOutIsLegal(int *in,int *out,int insz,int outsz)
{
  assert(in&&out);
  if(insz != outsz)
  {
    return 0;
  }
  Stack s;
  StackInit(&s);
  int in_index = 0;
  int out_index = 0;
  for(;in_index<insz;in_index++)
  {
    StackPush(&s,in[in_index]);
    while(StackSize(&s)&&StackTop(&s)==out[out_index])
    {
      StackPop(&s);
      out_index++;
    }
  }
  if(StackSize(&s))
  {
    printf("入栈序列与出栈序列不匹配");
  }
  else
  {
    printf("入栈序列与出栈序列匹配");
  }
}

///////////////////////////////////
//两个栈实现一个队列
///////////////////////////////////

void QueueBy2StackInit(QueueBy2Stack* q)
{
  assert(q);
  StackInit(&q->s1);
  StackInit(&q->s2);
}

void QueueBy2StackPush(QueueBy2Stack* q,SDataType data)
{
  assert(q);
  StackPush(&q->s1,data);
}

int QueueBy2StackEmpty(QueueBy2Stack* q)
{
  assert(q);
  return StackEmpty(&q->s1)&&StackEmpty(&q->s2);
}

void QueueBy2StackPop(QueueBy2Stack* q)
{
  if(QueueBy2StackEmpty(q))
    return;
  
  if(StackEmpty(&q->s2))
  {
    while(!StackEmpty(&q->s1))
    {
      StackPush(&q->s2,StackTop(&q->s1));
      StackPop(&q->s1); 
    }
  }
  StackPop(&q->s2);
}

SDataType QueueBy2StackFront(QueueBy2Stack* q)
{
  assert(!QueueBy2StackEmpty(q));
  if(StackEmpty(&q->s2))
  {
    while(!StackEmpty(&q->s1))
    {
      StackPush(&q->s2,StackTop(&q->s1));
      StackPop(&q->s1);
    }
  }
  return StackTop(&q->s2);
}

SDataType QueueBy2StackBack(QueueBy2Stack* q)
{
  assert(!QueueBy2StackEmpty(q));

  if(StackEmpty(&q->s1))
  {
    while(!StackEmpty(&q->s2))
    {
      StackPush(&q->s1,StackTop(&q->s2));
      StackPop(&q->s2);
    }
  }
  return StackTop(&q->s1);
}

int QueueBy2StackSize(QueueBy2Stack* q)
{
  return StackSize(&q->s1)+StackSize(&q->s2);
}

int main()
{
  SharedStack s;
  SharedStackInit(&s);
  SharedStackPush(&s,1,1);
  SharedStackPush(&s,2,1);
  SharedStackPush(&s,3,1);
  SharedStackPush(&s,4,1);
  SharedStackPush(&s,5,1);
  SharedStackPush(&s,3,2);
  SharedStackPush(&s,4,2);
  printf("stack1: top = %d",SharedStackTop(&s,1));
  printf("stack2: top = %d",SharedStackTop(&s,2));
  return 0;
}

//
//int main()
//{
//  int in[] = {1,2,3,4,5};
//  int out[] = {5,4,3,2,1};
//  int print = InAndOutIsLegal(in,out,sizeof(in)/sizeof(in[0]),sizeof(out)/sizeof(out[0]));
//  if(print == 1)
//  {
//    printf("合法\n");
//  }
//  else
//  {
//    printf("不合法\n");
//  }
//  return 0;
//}

//int main()
//{
//  QueueBy2Stack q;
//  QueueBy2StackInit(&q);
//  QueueBy2StackPush(&q,1);
//  QueueBy2StackPush(&q,2);
//  QueueBy2StackPush(&q,3);
//  QueueBy2StackPush(&q,4);
//
//  printf("%d\n",QueueBy2StackFront(&q));
//  printf("%d\n",QueueBy2StackBack(&q));
//  printf("%d\n",QueueBy2StackSize(&q));
//
//  QueueBy2StackPop(&q);
//  QueueBy2StackPop(&q);
//  QueueBy2StackPop(&q);
//
//  printf("%d\n",QueueBy2StackFront(&q));
//  printf("%d\n",QueueBy2StackBack(&q));
//  printf("%d\n",QueueBy2StackSize(&q));
//
//
//  return 0;
//}
#if 0
#include <string.h>
int IsBrackets(char ch)
{
  if(('(' == ch||')' == ch)||
    ('[' == ch||']' == ch)||
    ('{' == ch||'}' == ch))
    {
    return 1;
    }   
  return 0;
}

void MatchBrackets(const char* str)
{
  int i = 0;
  int size = 0;
  Stack s;
  if(NULL == str)
    return ;
  StackInit(&s);
  size = strlen(str);
  for(;i<size;++i)
  {
    if(IsBrackets(str[i]))
    {
      if('(' == str[i]||'[' == str[i]||'{' == str[i])
      {
        StackPush(&s,str[i]);
      }
      else
      {
        if(StackEmpty(&s))
        {
          printf("右括号比左括号多!!!\n");
          return;
        }
        char ch = StackTop(&s);
        if(!(('(' == ch&&')' == str[i])||
        ('[' == ch&&']' == str[i])||
        ('{' == ch&&'}' == str[i])))
        {
          printf("左右括号次序匹配出错!!!\n");
          return;
        }
        StackPop(&s);
      }
    }
  }
  if(StackEmpty(&s))
    printf("匹配括号正确\n");
  else
    printf("左括号比右括号多\n");
}

int main()
{
  char a[] = "(())abc{[(])}";
  char b[] = "(()))abc{[]}";
  char c[] = "(()()abc{[]}";
  char d[] = "(())abc{[]()}";

  MatchBrackets(a);
  MatchBrackets(b);
  MatchBrackets(c);
  MatchBrackets(d);
  return 0;
}
#endif
//typedef enum
//{
//  ADD,
//  SUB,
//  MUL,
//  DIV,
//  DATA
//}OPERATOR;
//typedef struct Cell
//{
//  OPERATOR op;
//  int data;
//}Cell;
//
//int CalcRPN(Cell *PRN,int size)
//{
//  int i = 0;
//  Stack s;
//  StackInit(&s);
//  for(i = 0;i<size;++i)
//  {
//    if(DATA == PRN[i].op)
//    {
//      StackPush(&s,PRN[i].op);
//    }
//    else
//    {
//      int left = 0,right = 0;
//      right = StackTop(&s);
//      StackPop(&s);
//      left = StackTop(&s);
//      switch(PRN[i].op)
//      {
//        case ADD:
//          StackPush(&s,left + right);
//          break;
//        case SUB:
//          StackPush(&s,left - right);
//          break;
//        case MUL:
//          StackPush(&s,left * right);
//        case DIV:
//          if(0 == right)
//          {
//            printf("除数为0非法!!!\n");
//            return 0;
//          }
//          StackPush(&s,left / right);
//          break;
//      }
//    }
//  }
//  return StackTop(&s);
//}
//
//int main()
//{
//  Cell RPN[] = {{DATA,12},{DATA,3},{DATA,4},{DATA,4},{ADD,0},{MUL,0},{DATA,6},{SUB,0},{DATA,8},{DATA,2},{DIV,0},{ADD,0}};
//  printf("%d\n",CalcRPN(RPN,sizeof(RPN)/sizeof(RPN[0])));
//  return 0;
//}
