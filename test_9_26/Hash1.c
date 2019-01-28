#pragma once 

#include <stdint.h>
#include <malloc.h>


typedef int KeyType;

typedef size_t(*HashFuncType)(KeyType key,size_t capacity);

typedef enum 
{
  EXIST,
  DELETE,
  EMPTY
}State;

size_t mod(KeyType key,size_t capacity)
{
  return key%capacity;
}

typedef struct ItemType
{
  KeyType key;
  State state;
}ItemType;

typedef struct HashTable
{
  ItemType *array;
  size_t size;
  size_t capacity;
  HashFuncType hash;
}HashTable;

void HashTableDestroy(HashTable *pHT)
{
  free(pHT->array);
}

void HashTableInit(HashTable *pHT,size_t capacity)
{
  pHT->array = (ItemType*)malloc(sizeof(ItemType)*capacity);
  pHT->capacity = capacity;
  pHT->size = 0;
}

ssize_t HashSearch(HashTable *pHT,KeyType key)
{
  size_t index = pHT->hash(key,pHT->capacity);
  while(1)
  {
    if(pHT->array[index].state == EMPTY)
    {
      return -1;
    }
    if(pHT->array[index].state == EXIST&&
        pHT->array[index].key == key)//1.存在（排除DELETE状态） 2.值相等
    {
      return index;
    }
  }
}

int HashRemove(HashTable *pHT,KeyType key)
{
  size_t index = pHT->hash(key,pHT->capacity);
  while(pHT->array[index].state != EMPTY)
  {
    if(pHT->array[index].state == EXIST 
      &&pHT->array[index].key == key)
    {
      pHT->size--;
      pHT->array[index].state = DELETE;
      return index;
    }
    index = (index+1)%pHT->capacity; 
  }
  return -1;
}

void ExpandIfRequired(HashTable *pHT)
{
  if(pHT->size*10 / pHT->capacity < 8)
  {
    //不扩容
    return;
  }
  
  HashTable temp;
  HashTableInit(&temp,pHT->capacity*2,pHT->hash);

  for(int i = 0;i<pHT->capacity;i++)
  {
    if(pHT->array[i].state == EXIST)
    {
      HashInsert(&temp,pHT->array[i].key);
    }
  }
  free(pHT->array);
  pHT->array = temp.array;
  pHT->capacity = temp.capacity;

}

int HashInsert(HashTable *pHT,KeyType key)
{
  if(HashSearch(pHT,key) != -1)
  {
    return -1;
  }
  ExpandIfRequired(pHT);
  size_t index = pHT->hash(key,pHT->capacity);
  while(1)
  {
    if(pHT->array[index].state != EXIST)
    {
      break;
    }
    index = (index+1)%pHT;
  }
  
  pHT->size++;
  pHT->array[index].state = EXIST;
  pHT->array[index].key = key;

  return 0;
}
