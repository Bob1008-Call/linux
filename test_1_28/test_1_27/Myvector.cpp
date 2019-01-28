#include <iostream>
#include <cstddef>
using namespace std;
template<class T>
class Vector
{
  public:
    typedef decltype(nullptr) nullptr_t;
    typedef T valueType;
    typedef valueType* Iterator;
    typedef const valueType* const_Iterator;
    typedef valueType& Reference;
    typedef const valueType& const_Reference;
    typedef size_t size_type;

  public:
    Vector()
      :_start(nullptr)
       ,_finish(nullptr)
       ,_end_of_storage(nullptr)
      {}

    Vector(size_type n,const T& value = T())
      :_start(new T[n])
    {
      for(size_type i = 0;i<n;i++)
      {
        _start[i] = value;
      }
      _finish = _start+n;
      _end_of_storage = _finish;
    }
    
    Vector(const Vector<T>& v)
    {
      size_type capacity = v._end_of_storage-v._start;
      size_type size = v._finish-v._start;
      _start = new T[capacity];
      for(size_type i = 0;i<size;i++)
        _start[i] = v._start[i];
      
      _finish = _start+size;
      _end_of_storage = _start+capacity;
    }

    Vector<T>& operator = (const Vector<T>& v)
    {
      if(this != &v)
      {
        size_type capacity = v._end_of_storage-_start;
        size_type size = v._finish-v._start;
        if(Capacity()<size)
        {
          _start = new T[capacity];
          for(size_type i = 0;i<size;i++)
          {
            _start[i] = v._start[i];
          }
          _finish = _start+size;
          _end_of_storage = _start+capacity;
        }
      }
      return *this;
    }

    ~Vector()
    {
      if(nullptr != _start)
      {
        delete[] _start;
        _start = nullptr;
        _finish = nullptr;
        _end_of_storage = nullptr;
      }
    }

    Iterator Begin()
    {
      return _start;
    }

    Iterator End()
    {
      return _finish;
    }

    const_Iterator End()const
    {
      return _finish;
    }

    const_Iterator Begin()const 
    {
      return _start;
    }

    size_type Size()const 
    {
      return _finish-_start;
    }

    size_type Capacity()const 
    {
      return _end_of_storage-_start;
    }

    bool Empty()const 
    {
      return Begin() == End();
    }

    Reference operator[](size_type index)
    {
      assert(index<Size());
      return _start[index];
    }

    const_Reference operator[](size_type index)const 
    {
      assert(index<Size());
      return _start[index];
    }

    Reference Front()
    {
      return *Begin();
    }

    Reference Back()
    {
      return *End();
    }

    void CheckCapacity()
    {
      if(_finish>=_end_of_storage)
      {
        int capacity = Capacity()*2+3;
        Iterator pTemp = new T[capacity];
        size_type size = Size();
        memcpy(pTemp,_start,sizeof(T)*size);
        if(_start != nullptr)
        {
          delete[] _start;
        }
        _start = pTemp;
        _finish = _start+size;
        _end_of_storage = _start+capacity;
      }
    }

    void PushBack(const T& value)
    {
      CheckCapacity();
      *(++_finish) = value;
    }

    void PopBack()
    {
      assert(0 != Size());
      --_finish;
    }

    Iterator Insert(Iterator pos,const T& value)
    {
      size_type position = pos-Begin();
      CheckCapacity();
      int count = Size()-position;
      int i = 0;
      while(count)
      {
        _start[Size()-i] = _start[Size()-i-1];
        i++;
        count--;
      }
      *pos = value;
      _finish++;
      return &(*pos);
    }
    
    Iterator Earse(Iterator pos)
    {
      size_type position = pos-Begin();
      assert(0 != Size());
      assert(position<Size());
      int count = Size() - position - 1;
      int i = 0;
      while(count)
      {
        _start[position+i] = _start[position+i+1];
        count--;
        i++;
      }
      _finish--;
      return pos;
    }

    void ReSize(size_type newSize,const T& value = T())
    {
      if(newSize < Size())
      {
        _finish = _finish - (Size()-newSize);
      }
      else
      {
        int count = newSize-Size();
        while(count)
        {
          CheckCapacity();
          _start[Size()] = value;
          ++_finish;
          count--;
        }
      }
    }

    void Clear()const 
    {
      _finish = _start;
    }

  private:
    Iterator _start;
    Iterator _finish;
    Iterator _end_of_storage;
};

void test1()
{
  Vector<int> v1();
  Vector<int> v2(10,4);
  Vector<int> v3(v2);
  Vector<int> v4;
  v4 = v2;

  cout<<v2.Capacity()<<endl;
  cout<<v2.Size()<<endl;
  Vector<int>::Iterator it = v2.Begin();
  while(it != v2.End())
  {
    cout<<*it<<" ";
    it++;
  }
  cout<<endl;
}

int main()
{
  test1();
  return 0;
}
