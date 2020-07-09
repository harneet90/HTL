#pragma once
template<class T>
class HVector
{
    T *data;
    size_t count;
    size_t buff_size;

    public:
    HVector():data(nullptr), count(0), buff_size(0){}
    HVector(size_t size):count(size), buff_size(size)
    {
        data = (T*)new uint8_t[sizeof(T)*count];
    }
    HVector(const HVector &other)
    {
        count = other.count;
        buff_size= other.buff_size;
        data = (T*)new uint8_t[sizeof(T)*buff_size];
        for(size_t i=0;i<other.count;i++)
        {
             new(&data[i]) T(other.data[i]);
        }
    }
    HVector& operator=(const HVector &other)
    {
        if(this == &other)
             return *this;
        for(size_t i=0;i < count;i++)
         {
	     data[i].~T();
         }
         delete[] (uint8_t*)data;
        count = other.count;
        buff_size= other.buff_size;
        data = new T[buff_size];
        for(size_t i=0;i<other.count;i++)
        {
             data[i] = other.data[i];
        }
        return *this;
    }
    T& operator[](size_t index)
    {
        return data[index];
    }
    void push_back(T &&obj)
    {
         if(count == buff_size)
         {
              if(buff_size== 0)
		buff_size= 1;
	      else
		buff_size*= 2;
              T *temp= (T*)new uint8_t(sizeof(T) * buff_size);
	      for(size_t i=0;i < count;i++)
              {
                 new(&temp[i]) T(data[i]);
		 data[i].~T();
              }
              delete[] (uint8_t*)data;
              data = temp;
              new(&data[count++]) T(obj);              
         }
         else
	     new(&data[count++]) T(obj);
    }
    void push_back(const T &obj)
    {
         if(count == buff_size)
         {
              if(buff_size== 0)
		buff_size= 1;
	      else
		buff_size*= 2;
              T *temp= (T*)new uint8_t(sizeof(T) * buff_size);
	      for(size_t i=0;i < count;i++)
              {
                 new(&temp[i]) T(data[i]);
		 data[i].~T();
              }
              delete[] (uint8_t*)data;
              data = temp;
              new(&data[count++]) T(obj);              
         }
         else
	     new(&data[count++]) T(obj);
    }
    void pop_back()
    {
        if(count == 0)
            return;
        data[count--].~T();
    }
    virtual ~HVector(){ 
         for(size_t i=0;i < count;i++)
         {
	     data[i].~T();
         }
         delete[] (uint8_t*)data;
    }
    size_t capacity(){return buff_size;}
    size_t size(){return count;}
    class iterator
    {
          long index;
          HVector<T> *parent;
          iterator(HVector<T> *ptr, long i)
          {
              if(ptr == NULL || i < 0 || i > parent->size())
              {
                  parent = NULL;
                  index=-1;
              }
              else
              {
                  parent = ptr;
                  index = i;
              }
          } 
		
          public:
          iterator():index(-1),parent(NULL){}
          T* operator() ()
          {
             if(parent == NULL || index < 0 || index >= parent->count)
                 throw std::out_of_range("index out of range");
             return &(parent->data[index]);
          }
          T& operator* ()
          {
             if(parent == NULL || index < 0 || index >= parent->count)
                 throw std::out_of_range("index out of range");
             return (parent->data[index]);
          }
          iterator operator++()
          {
              index++;
              return *this;
          }
          iterator operator++(int)
          {         
              index++;
              return iterator(parent, index);
          }
          bool operator== (const iterator& other)
          {
              return (parent == other.parent && index == other.index);
          } 
          bool operator!= (const iterator& other)
          {
              return (parent != other.parent || index != other.index);
          }
          friend HVector;
    };
    iterator begin()
    {
       if(count == 0)
          return iterator();
       return iterator(this, 0);
    }
    iterator end()
    {
       if(count == 0)
          return iterator();
       return iterator(this, count);
    }
    bool empty()
    {
        return count > 0;
    }
    T at(size_t index)
    {
        if(index >= count)
             throw std::out_of_range("index out of range");
        return data[index];
    }
    T front()
    {
       return data[0];
    }
    T back()
    {
       return data[count-1];
    }
};
