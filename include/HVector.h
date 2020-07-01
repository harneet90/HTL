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
        if(index >= count)
             throw std::out_of_range("index out of range");
        return data[index];
    }
    void push_back(T &obj)
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
};
