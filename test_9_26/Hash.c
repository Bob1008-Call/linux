#include <malloc.h>
#include <stdio.h>
typedef int KeyType;
typedef size_t(*HashFuncType)(KeyType key,size_t capacity);
typedef enum
{
  EMPTY,
  EXIST,
  DELETE
}State;

typedef struct
{
  KeyType key;
  State state;
}ItemType;

typedef struct HashTable
{
  ItemType* array;
  size_t size;
  size_t capacity;
  HashFuncType hash;
}HashTable;

void HashTableInit(HashTable* pHT,size_t capacity,HashFuncType hash)
{
  pHT->array = (ItemType*)malloc(sizeof(ItemType)*capacity);
  pHT->size = 0;
  pHT->capacity = capacity;
  pHT->hash = hash;
  int i = 0;
  for(i = 0;i<capacity;i++)
  {
    pHT->array[i].state = EMPTY;
  }
}

void HashTableDestroy(HashTable *pHT)
{
  free(pHT->array);
  pHT->capacity = 0;
  pHT->size = 0;
  pHT->hash = NULL;
}

size_t mod(KeyType key,size_t capacity)
{
  return key%capacity;
}

int HashRemove(HashTable *pHT,KeyType key)
{
  size_t index = pHT->hash(key,pHT->capacity);
  while(pHT->array[index].state != EMPTY)
  {
    if(pHT->array[index].state == EXIST
        &&pHT->array[index].key == key)
    {
      pHT->array[index].state = DELETE;
      pHT->size--;
      return index;
    }
    index = (index + 1)%pHT->capacity;
  }
  return -1;
}

int HashSearch(const HashTable* pHT,KeyType key)
{
  size_t index = pHT->hash(key,pHT->capacity);
  while(1)
  {
    if(pHT->array[index].state == EMPTY)
    {
      return -1;
    }
    if(pHT->array[index].key == key
        &&pHT->array[index].state == EXIST)
      return index;
  //线性探测法
  index = (index+1)%pHT->capacity;
  }
}

void HashInsert(HashTable *pHT, KeyType key)

{
  if(pHT == NULL)
  {
    return;
  }
  if(pHT->size >= pHT->capacity*0.8)
  {
    printf("满了");
    return;
  }
  size_t index = mod(key,pHT->capacity);

  while(1)
  {
    if(pHT->array[index].state == EXIST)
    {
      if(pHT->array[index].key == key)
      {
        return;
      }
      ++index;
      if(index >= pHT->capacity)
      {
        index -= pHT->capacity;
      }
    }
    else
    {
      pHT->array[index].key = key;
      pHT->array[index].state = EXIST;
      ++pHT->size;
      return;
    }
  }
  return;
}

int main()
{
  HashTable pt;
  HashTableInit(&pt,7,mod);
  HashInsert(&pt,1);
  return 0;
}

