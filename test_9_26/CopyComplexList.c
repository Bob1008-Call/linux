#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef int Datatype;
typedef struct ListNode
{
  int data;
  struct ListNode* next;
  struct ListNode* radom;
}ListNode;

ListNode* BuyNode(Datatype data)
{
  ListNode* Node = (ListNode*)malloc(sizeof(ListNode));
  Node->next = NULL; 
  Node->data = data;
  Node->radom = NULL;
  return Node;
}
ListNode* CopyComplexList(ListNode* head)
{
  //插入新节点
  ListNode* cur = head;
  while(cur)
  {
    ListNode* Node = BuyNode(cur->data);
    Node->next = cur->next;
    cur->next = Node;
    cur = cur->next->next;
  }
  //确定随机节点的值
  cur = head;
  while(cur)
  {
    cur->next->radom = cur->radom->next;
    cur = cur->next->next;
  }
  //拆链表
  cur = head;
  ListNode* copy = cur->next;
  while(cur)
  {
    ListNode* node = cur->next;
    cur->next = node->next;
    if(cur->next)
    {
      node->next = cur->next->next;
    }
    else
    {
      node->next = NULL;
    }
    cur = cur->next;
  }
  return copy;
}

int main()
{
  ListNode* node1 = BuyNode(1);
  ListNode* node2 = BuyNode(2);
  ListNode* node3 = BuyNode(3);

  node1->next = node2;
  node2->next = node3;

  node1->radom = node3;
  node2->radom = node1;
  node3->radom = node3;

  ListNode* test = CopyComplexList(node1);
  ListNode* Node = test;
  printf("非随机节点:");
  while(Node)
  {
    printf("%d->",Node->data);
    Node = Node->next;
    if(Node == NULL)
    {
      printf("NULL");
      return 0;
    }
  }
   Node = test;
  printf("随机节点");
  while(Node)
  {
    printf("%d->%d ",Node->data,Node->radom);
    Node = Node->next;
    if(Node == NULL)
    {
      printf("NULL");
      return 0;
    }
  }
  return 0;

}
