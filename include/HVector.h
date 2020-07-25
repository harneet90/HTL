#pragma once
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
template<class T>
class HVector
{
    T *_data;
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
    static void _clear(T* _data, size_t n_units)
    {
        for(size_t i=0;i < n_units;i++)
        {
            _data[i].~T();
        }
    }
    static void _deallocater(T* _data, size_t n_units)
    {
        _clear(_data, n_units);
        delete[] (uint8_t*)_data;
    }
    void _expandBuffer()
    {
        if(buff_size== 0)
            buff_size= 1;
        else
            buff_size*= 2;
        T *temp= _allocateAndCopy(_data, buff_size,0,count,0);
        _deallocater(_data,count);
        _data = temp; 
    }
public:
    HVector():_data(nullptr), count(0), buff_size(0){}
    HVector(size_t size):count(size), buff_size(size)
    {
        _data = _allocate(size);
        for(int i=0;i < size;i++)
            new(&_data[i]) T();
    }
    HVector(size_t size, const T &val):count(size), buff_size(size)
    {
        _data = _allocate(size);
        for(int i=0;i < size;i++)
            new(&_data[i]) T(val);
    }
    HVector(const HVector &other):count(other.size), buff_size(other.size)
    {
        _data = _allocateAndCopy(other._data, buff_size, 0, count, 0); 
    }
    HVector(HVector &&other):count(other.size), buff_size(other.size), _data(other._data)
    {
    }
    
    HVector(std::initializer_list<T> list):count(list.size()),buff_size(list.size())
    {
        _data = _allocate(buff_size);
        int i=0;
        for(auto ele:list)
            new(&_data[i++]) T(ele);
    }
    HVector& operator=(const HVector &other)
    {
        if(this == &other)
        return *this;
        _deallocater(_data, count);
        count = other.count;
        buff_size= other.buff_size;
        _data = _allocateAndCopy(other._data, buff_size, 0, count, 0); 
        return *this;
    }
    T& operator[](size_t index) const
    {
        return _data[index];
    }
    void push_back(T &&obj)
    {
        if(count == buff_size)
        {
            _expandBuffer();
        }
        new(&_data[count++]) T(obj);
    }
    void push_back(const T &obj)
    {
        if(count == buff_size)
        {
            _expandBuffer();           
        }
        new(&_data[count++]) T(obj);
    }
    void pop_back()
    {
        if(count == 0)
            return;
        _data[--count].~T();
    }
    virtual ~HVector(){ 
        _deallocater(_data, count);
    }
    size_t capacity() const {return buff_size;}
    size_t size() const {return count;}
    class iterator
    {
        T *parent;
        iterator(T *ptr):parent(ptr)
        {
        } 
        
    public:
        typedef iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;
        iterator(): parent(NULL){}
        T* operator() ()
        {
            return parent;
        }
        T& operator* ()
        {
            return *parent;
        }
        iterator operator++()
        {
            parent++;
            return *this;
        }
        iterator operator++(int)
        {         
            T* p = parent++;
            return iterator(p);
        }
        iterator operator--()
        {
            parent--;
            return *this;
        }
        iterator operator--(int)
        {         
            T* p = parent--;
            return iterator(p);
        }
        bool operator== (const iterator& other)
        {
            return (parent == other.parent);
        } 
        bool operator!= (const iterator& other)
        {
            return (parent != other.parent);
        }
        bool operator< (const iterator& other)
        {
            return (parent < other.parent);
        } 
        long operator- (const iterator& other)
        {
            return (parent - other.parent);
        }
        iterator operator+ (long s)
        {
            return iterator(parent+s);
        }
        iterator& operator+= (long s)
        {
            parent += s;
            return *this;
        }
        iterator operator- (long s)
        {
            return iterator(parent - s);
        }
        iterator& operator-= (long s)
        {
            parent -= s;
            return *this;
        }
        friend HVector;
    };
    iterator begin()
    {
        return iterator(_data);
    }
    iterator end()
    {
        return iterator(_data + count);
    }
    bool empty()
    {
        return count > 0;
    }
    T at(size_t index)
    {
        if(index >= count)
        throw std::out_of_range("index out of range");
        return _data[index];
    }
    T front()
    {
        return _data[0];
    }
    T back()
    {
        return _data[count-1];
    }
    void reserve(size_t n)
    {
        if(n <= count)
            return;
        T* temp = _allocateAndCopy(_data, n, 0, count, 0);
        _deallocater(_data, count);
        _data = temp;
        buff_size = n;
    }
    iterator insert(iterator pos, const T& ele)
    {
        T* temp = _data;
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
            temp = _allocateAndCopy(_data, buff_size, 0, l, 0);
            expanded = true;
        }  
        for(i = count;i > l;i--)
            new(&temp[i]) T(_data[i-1]);
        
        new(&temp[l]) T(ele);
        if(expanded)
            _deallocater(_data, count);
        count++;
        _data = temp;
        return iterator(_data + l);
    }
    iterator insert(iterator pos, size_t n, const T& ele)
    {
        T* temp = _data;
        bool expanded = false;
        long l = pos-begin();
        long i, j;
        if(l < 0 || l > count)
            return end();
        if(buff_size < count + n)
        {
            if(buff_size == 0)
                buff_size = n;
            else
            {
                while(buff_size < count + n)
                    buff_size *= 2;
            }
            temp = _allocateAndCopy(_data, buff_size, 0, l, 0);
            expanded = true;
        }  
        for(i = count + n -1, j=count;i >= l + n;i--,j--)
            new(&temp[i]) T(_data[j-1]);
        for(i = l;i < l+n;i++)
            new(&temp[i]) T(ele);
        if(expanded)
            _deallocater(_data, count);
        count += n;
        _data = temp;
        return iterator(_data + l + n);
    }
    iterator insert(iterator pos, std::initializer_list<T> list)
    {
        T* temp = _data;
        size_t n = list.size();
        bool expanded = false;
        long l = pos-begin();
        long i, j;
        if(l < 0 || l > count)
            return end();
        if(buff_size < count + n)
        {
            if(buff_size == 0)
                buff_size = n;
            else
            {
                while(buff_size < count + n)
                    buff_size *= 2;
            }
            temp = _allocateAndCopy(_data, buff_size, 0, l, 0);
            expanded = true;
        }  
        for(i = count + n -1, j=count;i >= l + n;i--,j--)
            new(&temp[i]) T(_data[j-1]);
        i=l;
        for(auto ele:list)
            new(&temp[i++]) T(ele);
        if(expanded)
            _deallocater(_data, count);
        count += n;
        _data = temp;
        return iterator(_data + l + n);
    }
    template<class InputIterator>
    iterator insert(iterator pos, InputIterator first, InputIterator last)
    {
        T* temp = _data;
        size_t n = last - first;
        bool expanded = false;
        long l = pos-begin();
        long i, j;
        if(l < 0 || l > count)
            return end();
        if(buff_size < count + n)
        {
            if(buff_size == 0)
                buff_size = n;
            else
            {
                while(buff_size < count + n)
                    buff_size *= 2;
            }
            temp = _allocateAndCopy(_data, buff_size, 0, l, 0);
            expanded = true;
        }  
        for(i = count + n -1, j=count;i >= l + n;i--,j--)
            new(&temp[i]) T(_data[j-1]);
        i=l;
        for(auto itr=first;itr != last;itr++)
            new(&temp[i++]) T(*itr);
        if(expanded)
            _deallocater(_data, count);
        count += n;
        _data = temp;
        return iterator(_data + l + n);
    }
    template<class... Args>
    iterator emplace(iterator pos, Args&&... args)
    {
        T* temp = _data;
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
            temp = _allocateAndCopy(_data, buff_size, 0, l, 0);
            expanded = true;
        }  
        for(i = count;i > l;i--)
            new(&temp[i]) T(_data[i-1]);
        
        new(&temp[l]) T(args...);
        if(expanded)
            _deallocater(_data, count);
        count++;
        _data = temp;
        return iterator(_data + l);
    }
    template<class... Args>
    void emplace_back(Args&&... args)
    {
        if(count == buff_size)
            _expandBuffer();
        new(&_data[count++]) T(args...);
    }
    void clear()
    {
        _clear(_data, count);
        count=0;
    }
    T* data(){return _data;}
    void swap(HVector &other)
    {
        std::swap(count,other.count);
        std::swap(buff_size,other.buff_size);
        std::swap(_data,other._data);
    }
    iterator erase(iterator pos)
    {
        long l = pos-begin();
        size_t i;
        if(l < 0 || l >= count)
            return end();
        _data[l].~T();
        for(i=(size_t)l+1;i<count;i++)
            _data[i-1] = _data[i];
        count--;
        return iterator(_data + l);
    }
    iterator erase(iterator first, iterator second)
    {
        long s = first - begin();
        long e = second - begin();
        long st = s;
        size_t i;
        if(s < 0 || s >= count || e < s)
            return end();
        for(i = (size_t)s;i < (size_t)e;i++)
        {
            _data[i].~T();
        }
        for(i=(size_t)e;i<count;i++)
        {
            _data[s++] = _data[i];
        }
        count = count - (e - st);
        return iterator(_data + st);
    }
    void assign(size_t n, const T& val)
    {
        if(n > count)
        {
            _deallocater(_data, count);
            _data = _allocate(n);
            buff_size = n;
        }
        else
            _clear(_data, count);
            
        for(size_t i=0;i < n;i++)
            new(&_data[i]) T(val);
        count = n;
    }
    
    void assign(std::initializer_list<T> list)
    {
        if(list.size() > count)
        {
            _deallocater(_data, count);
            _data = _allocate(list.size());
            buff_size = list.size();
        }
        else
            _clear(_data, count);
    
        count = list.size();
        int i=0;
        for(auto ele:list)
            new(&_data[i++]) T(ele);
    }
    template<class InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        if(last - first > count)
        {
            _deallocater(_data, last - first);
            _data = _allocate(last - first);
            buff_size = last - first;
        }
        else
            _clear(_data, count);
    
        count = last - first;
        int i=0;
        for(auto itr = first; itr != last; itr++)
            new(&_data[i++]) T(*itr);
    }
};
