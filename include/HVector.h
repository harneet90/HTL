#pragma once
#include <cstddef>
#include <cstdint>
template<class T>
class HVector
{
    T *data;
    size_t count;
    size_t buff_size;
    static T* _allocate(size_t n_units)
    {
        return (T*)new uint8_t[n_units * sizeof(T)];
    }
    static void _copy(T *from, T *to, size_t in_s,size_t in_e, size_t out_s)
    {
        for(size_t i = in_s;i < in_e;i++, out_s++)
            new(&to[out_s]) T(from[i]);
    }
    static T* _allocateAndCopy(T *from, size_t n_units, size_t in_s, size_t in_e, size_t out_s)
    {
        T* to = _allocate(n_units);
        _copy(from, to, in_s, in_e, out_s);
        return to;
    }
    static void _deallocater(T* data, size_t n_units)
    {
        for(size_t i=0;i < n_units;i++)
        {
            data[i].~T();
        }
        delete[] (uint8_t*)data;
    }
    void _expandBuffer()
    {
        if(buff_size== 0)
            buff_size= 1;
        else
            buff_size*= 2;
        T *temp= _allocateAndCopy(data, buff_size,0,count,0);
        _deallocater(data,count);
        data = temp; 
    }
public:
    HVector():data(nullptr), count(0), buff_size(0){}
    HVector(size_t size):count(size), buff_size(size)
    {
        data = _allocate(size);
    }
    HVector(const HVector &other)
    {
        count = other.count;
        buff_size= other.buff_size;
        data = _allocateAndCopy(data, buff_size, 0, count, 0); 
    }
    HVector& operator=(const HVector &other)
    {
        if(this == &other)
        return *this;
        _deallocater(data, count);
        count = other.count;
        buff_size= other.buff_size;
        data = _allocateAndCopy(other.data, buff_size, 0, count, 0); 
        return *this;
    }
    T& operator[](size_t index) const
    {
        return data[index];
    }
    void push_back(T &&obj)
    {
        if(count == buff_size)
        {
            _expandBuffer();
        }
        new(&data[count++]) T(obj);
    }
    void push_back(const T &obj)
    {
        if(count == buff_size)
        {
            _expandBuffer();           
        }
        new(&data[count++]) T(obj);
    }
    void pop_back()
    {
        if(count == 0)
            return;
        data[count--].~T();
    }
    virtual ~HVector(){ 
        _deallocater(data, count);
    }
    size_t capacity() const {return buff_size;}
    size_t size() const {return count;}
    class iterator
    {
        long index;
        const HVector<T> *parent;
        iterator(const HVector<T> *ptr, long i):parent(ptr)
        {
            if(ptr == NULL || i < 0 || i > ptr->size())
            {
                index=-1;
            }
            else
            {
                index = i;
            }
        } 
        
    public:
        iterator():index(-1), parent(NULL){}
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
        long operator- (const iterator& other)
        {
            return (index - other.index);
        }
        iterator operator+ (long s)
        {
            return iterator(parent, index + s);
        }
        iterator& operator+= (long s)
        {
            index += s;
            return *this;
        }
        iterator operator- (long s)
        {
            return iterator(parent, index - s);
        }
        iterator& operator-= (long s)
        {
            index -= s;
            return *this;
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
    void reserve(size_t n)
    {
        if(n <= count)
            return;
        T* temp = _allocateAndCopy(data, n, 0, count, 0);
        _deallocater(data, count);
        data = temp;
        buff_size = n;
    }
    iterator insert(iterator pos, const T& ele)
    {
        T* temp = data;
        bool expanded = false;
        long l = pos-begin();
        long i;
        if(l < 0 || l > count)
        return end();
        if(buff_size <= count)
        {
            if(buff_size == 0)
                buff_size = 1;
            else
                buff_size *=2;
            temp = _allocateAndCopy(data, buff_size, 0, l, 0);
            expanded = true;
        }  
        for(i = count;i > l;i--)
            new(&temp[i]) T(data[i-1]);
        
        new(&temp[l]) T(ele);
        if(expanded)
            _deallocater(data, count);
        count++;
        data = temp;
        return iterator(this,l);
    }
};
