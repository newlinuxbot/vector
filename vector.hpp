#ifndef Vector_HPP
# define Vector_HPP

# include <iostream>
# include <string>

#include "iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
    template <typename T, class Alloc = std::allocator<T> >
    class Vector
    {
        private:
            T *arr;
            unsigned int mysize;
            unsigned int mycapacity;
            std::allocator<T> alloc;
            unsigned int maxsize;
        public:
            typedef ft::Iterator<T> iterator;
            typedef ft::Iterator< const T >  const_iterator;
            typedef ft::reverse_iterator<T> reverse_iterator;
            typedef ft::reverse_iterator<const T> const_reverse_iterator;
            typedef unsigned int size_type ;
            explicit Vector ()
            {
                arr = new T[1];
                mysize = 0;
                mycapacity = 1;
                maxsize = 1073741823;
            }
            
            explicit Vector (int n, const T& val = 0)
            {
                arr = new T[n];
                for (int i = 0; i < n; i++)
                    arr[i] = val;
                mysize = n;
                mycapacity = n;
                maxsize = 1073741823;
            }

            Vector(const Vector<T> &copy)
            {
                arr = new T[copy.size()];
                for (int i = 0; i < copy.size() ; i++)
                    arr[i] = copy.getArray()[i];
                mysize = copy.size();
                mycapacity = copy.capacity();
            }

            explicit Vector (iterator first, iterator last)
            {
                arr = new T[1];
                mycapacity = 1;
                mysize = 0;
                for (iterator i = first; i < last; i++)
                {
                    if (mysize == mycapacity)
                    {
                        T *tmp = new T[mycapacity * 2];
                        for (int i = 0; i < mysize; i++)
                            tmp[i] = arr[i];
                        delete[]arr;
                        arr = tmp;
                        mycapacity *= 2;
                    }
                    arr[mysize++] = *i;
                } 
            }

            ~Vector()
            {
               delete[]arr;
            }
            
            Vector & operator=(const Vector &assign)
            {
               delete[]arr;
                arr = new T[assign.size()];
                for (int i = 0; i < assign.size() ; i++)
                    arr[i] = assign.getArray()[i];
                mysize = assign.size();
                mycapacity = assign.capacity();
                return *this;
            }
            
            unsigned int size() const
            {
                return mysize;
            }
            T* getArray() const
            {
                return arr;
            }
            unsigned int max_size()
            {
                return maxsize;
            }
            
            iterator begin() { return iterator(&arr[0]); }
            iterator end()   { return iterator(&arr[mysize]); }

            reverse_iterator rbegin() { return reverse_iterator(&arr[mysize-1]); }
            reverse_iterator rend()   { return reverse_iterator(&arr[-1]); }

            void resize(int s, T v = NULL)
            {
                if (s < mysize)
                    mysize = s;
                if (mysize < s)
                {
                    T* tmp = new T[s];
                    for (int i = 0; i < mysize; i++)
                        tmp[i] = arr[i];
                    for (int i = mysize; i < s; i++)
                        tmp[i] = v;
                   delete[]arr;
                    arr = tmp;
                    mysize = s;
                }
            }

            int capacity() const
            {
                return mycapacity;
            }

            bool empty()
            {
                if (mysize == 0)
                    return true;
                return false;
            }

            void reserve(int n)
            {
                if (n > mycapacity)
                {
                    T* tmp = new T[n];
                    for (int i = 0; i < mysize; i++)
                        tmp[i] = arr[i];
                   delete[]arr;
                    arr = tmp;
                    mycapacity = n;
                }
            }

            struct indexOutOfBound : public std::exception
            {
                const char * what () const throw ()
                {
                    return "Index Out Of Bound !";
                }
            };

            T &at(unsigned int i)
            {
                if (i >= mysize)
                    throw indexOutOfBound();
                return arr[i];
            }

            T &operator[](unsigned int i)
            {
                if (i >= mysize)
                    throw indexOutOfBound();
                return arr[i];
            }

            T &front()
            {
                return arr[0];
            } 

            T &back()
            {
                return arr[mysize-1];
            }

            void push_back (const T& val)
            {
                if (mysize == mycapacity)
                {
                    T *tmp = new T[mycapacity * 2];
                    for (unsigned int i = 0; i < mysize; i++)
                        tmp[i] = arr[i];
                   delete[]arr;
                    arr = tmp;
                    mycapacity *= 2;
                }
                arr[mysize++] = val;
            }


            void pop_back()
            {
                mysize--;
            }

            void assign (int n, const T& val)
            {
                T *tmp = new T[n];
                mysize = 0;
                for (int i = 0; i < n; i++)
                    tmp[mysize++] = val;
               delete[]arr;
                arr = tmp;
            }

            void assign (iterator first, iterator last)
            {
                mycapacity = 1;
                mysize = 0;
                for (; first < last; first++)
                {
                    if (mysize == mycapacity)
                    {
                        T *tmp = new T[mycapacity * 2];
                        for (unsigned int i = 0; i < mysize; i++)
                            tmp[i] = arr[i];
                        delete[]arr;
                        arr = tmp;
                        mycapacity *= 2;
                    }
                    arr[mysize++] = *first;
                }
            }

            iterator insert (iterator position, const T& val)
            {
                
                unsigned int pos = position - arr;
                if (mysize + 1 >= mycapacity)
                {
                    T *tmp = new T[mycapacity * 2];
                    for (unsigned int i = 0; i < mysize; i++)
                        tmp[i] = arr[i];
                   delete[]arr;
                    arr = tmp;
                    mycapacity *= 2;
                }
                T *tmp2 = new T[mycapacity];
                for (unsigned int i = 0, j = 0; i <= mysize;i++)
                {
                    if (i == pos)
                    {
                        tmp2[j] = val;
                        j++;
                    }
                    
                    tmp2[j++] = arr[i];
                }
                delete[]arr;
                arr = tmp2;
                mysize += 1;
                return begin();
            }

            void insert (iterator position, unsigned int n, const T& val)
            {
                unsigned int pos = position - arr;
                if (mysize + n >= mycapacity)
                {
                    T *tmp = new T[mycapacity + n];
                    for (unsigned int i = 0; i < mysize; i++)
                        tmp[i] = arr[i];
                   delete[]arr;
                    arr = tmp;
                    mycapacity += n;
                }
                T *tmp2 = new T[mycapacity];
                for (unsigned int i = 0, j = 0; i <= mysize;i++)
                {
                    if (i == pos)
                    {
                        for(unsigned int x = 0; x < n; x++)
                            tmp2[j++] = val;
                    }
                    tmp2[j++] = arr[i];
                }
               delete[]arr;
                arr = tmp2;
                mysize += n;
            }

            void insert (iterator position, iterator first, iterator last)
            {
                unsigned int pos = position - arr;
                if (mysize + (last-first) >= mycapacity)
                {
                    T *tmp = new T[mycapacity * 2 + (last-first)];
                    for (unsigned int i = 0; i < mysize; i++)
                        tmp[i] = arr[i];
                    delete[]arr;
                    arr = tmp;
                    mycapacity = (mycapacity * 2) + (last-first);
                }
                T *tmp2 = new T[mycapacity];
                for (unsigned int i = 0, j = 0; i <= mysize;i++)
                {
                    if (i == pos)
                    {
                        for (iterator x = first; x < last; x++)
                        {
                            tmp2[j] = *x;
                            j++;
                        }
                    }
                    tmp2[j++] = arr[i];
                }
                delete[]arr;
                arr = tmp2;
                mysize += (last-first);
            }
           
            
            iterator erase (iterator position)
            {
                unsigned int pos = position - arr;
                T *tmp = new T[mycapacity];
                for (unsigned int i = 0, j = 0; i <= mysize;i++)
                {
                    if (i == pos)
                        continue;
                    tmp[j++] = arr[i];
                }
               delete[] arr;
                arr = tmp;
                mysize -= 1;
                return position;
            }
            
            iterator erase (iterator first, iterator last)
            {
                unsigned int firstpos = first - arr;
                unsigned int lastpos = last - arr;
                T *tmp = new T[mycapacity];
                for (unsigned int i = 0,j = 0; i < mysize;i++)
                {
                    if (i == firstpos)
                        i += lastpos - firstpos;
                    tmp[j++] = arr[i];
                }
               delete[]arr;
                arr = tmp;
                mysize -= (lastpos - firstpos);
                return first;
            }

            void swap (Vector& x)
            {
                T* tmpArr = arr;
                int tmpMySize = mysize;
                int tmpMyCapacity = mycapacity;
                arr = x.arr;
                mysize = x.mysize;
                mycapacity = x.mycapacity;
                x.arr = tmpArr;
                x.mysize = tmpMySize;
                x.mycapacity = tmpMyCapacity;
            }

            void clear()
            {
               delete[]arr;
                arr = new T[1];
                mysize = 0;
                mycapacity = 1;
            }

            bool equal ( iterator first1, iterator last1, iterator first2 )
            {
                while (first1!=last1) {
                    if (!(*first1 == *first2)) 
                    return false;
                    ++first1; ++first2;
                }
                return true;
            }

           
            bool equal ( iterator first1, iterator last1, iterator first2, bool (*func)(T,T))
            {
                while (first1!=last1) {
                        if (!func(*first1,*first2))
                        return false;
                        ++first1; ++first2;
                    }
                return true;
            }

            bool lexicographical_compare (iterator first1, iterator last1, iterator first2, iterator last2)
            {
                while (first1!=last1)
                {
                    if (first2==last2 || *first2<*first1) return false;
                    else if (*first1<*first2) return true;
                    ++first1; ++first2;
                }
                return (first2!=last2);
            }

            bool operator== (const Vector<T,Alloc>& rhs)
            {
                if (mysize != rhs.size())
                    return false;
                return equal(begin(), end(), rhs.begin());
            }
            bool operator!= (const Vector<T,Alloc>& rhs)
            {
                if (mysize == rhs.size())
                    return false;
                return !equal(begin(), end(), rhs.begin());
            }
            bool operator< (const Vector<T,Alloc>& rhs)
            {
                return lexicographical_compare(begin(), end(), rhs.begin(), rhs.end());
            }
            bool operator> (const Vector<T,Alloc>& rhs)
            {
                return lexicographical_compare(rhs.begin(), rhs.end(), begin(), end());
            }
            bool operator<= (const Vector<T,Alloc>& rhs)
            {
                return equal(begin(), end(), rhs.begin()) || !lexicographical_compare(begin(), end(), rhs.begin(), rhs.end());
            }
             bool operator>= (const Vector<T,Alloc>& rhs)
            {
                return equal(begin(), end(), rhs.begin()) || !lexicographical_compare(rhs.begin(), rhs.end(), begin(), end());
            }
            std::allocator<T> get_allocator() const 
            { 
                return alloc; 
            }
    };
    template <class T,class Alloc>
    void swap (ft::Vector<T,Alloc>& a, ft::Vector<T,Alloc>& b) {
        a.swap(b);
    }
}

#endif