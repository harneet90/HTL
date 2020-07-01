#pragma once
template<class T>
class HVector
{
    T *data;
    size_t size;
    size_t buff_size;
    public:
    HVector():data(nullptr), size(0), buff_size(0){}
    HVector(size_t size):size(size), buff_size(size)
    {
        data = (T*)new uint8_t[sizeof(T)*size];
    }
    HVector(const HVector &other)
    {
        size = other.size;
        buff_size= other.buff_size;
        data = (T*)new uint8_t[sizeof(T)*buff_size];
        for(size_t i=0;i<other.size;i++)
        {
             new(&data[i]) T(other.data[i]);
        }
    }
    HVector& operator=(const HVector &other)
    {
        if(this == &other)
             return *this;
        for(size_t i=0;i < size;i++)
         {
	     data[i].~T();
         }
         delete[] (uint8_t*)data;
        size = other.size;
        buff_size= other.buff_size;
        data = new T[buff_size];
        for(size_t i=0;i<other.size;i++)
        {
             data[i] = other.data[i];
        }
        return *this;
    }
    void push_back(T &obj)
    {
         if(size == buff_size)
         {
              if(buff_size== 0)
		buff_size= 1;
	      else
		buff_size*= 2;
              T *temp= (T*)new uint8_t(sizeof(T) * buff_size);
	      for(size_t i=0;i < size;i++)
              {
                 new(&temp[i]) T(data[i]);
		 data[i].~T();
              }
              delete[] (uint8_t*)data;
              data = temp;
              new(&data[size++]) T(obj);              
         }
         else
	     new(&data[size++]) T(obj);
    }
    void pop_back()
    {
        if(size == 0)
            return;
        data[size--].~T();
    }
    virtual ~HVector(){ 
         for(size_t i=0;i < size;i++)
         {
	     data[i].~T();
         }
         delete[] (uint8_t*)data;
    }
    size_t capacity(){return buff_size;}
};
