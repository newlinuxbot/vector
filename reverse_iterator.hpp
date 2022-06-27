#ifndef reverse_iterator_HPP
# define reverse_iterator_HPP

#include <iostream>

using namespace std;

namespace ft
{
	template <typename T>
	class reverse_iterator
	{
		public:
			typedef std::random_access_iterator_tag iterator_category;
			typedef int difference_type;
			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;
		public:
			// Constructors
			reverse_iterator(T* ptr) : _ptr(ptr) {};
			reverse_iterator(const reverse_iterator &copy){(void)copy;};
			
			// Destructor
			~reverse_iterator() {};
			
			// Operators
			reverse_iterator & operator=(const reverse_iterator &assign){(void)assign;};

			reference operator*() const { return *_ptr; }
			pointer operator->() { return _ptr; }

			reverse_iterator& operator++() { _ptr--; return *this; }

			reverse_iterator operator++(int) { reverse_iterator tmp = *this; ++(*this); return tmp; }

			reverse_iterator& operator--() { _ptr++; return *this; }

			reverse_iterator operator--(int) { reverse_iterator tmp = *this; --(*this); return tmp; }

            bool operator< (const reverse_iterator<T>& rhs)
            {
                return _ptr < rhs._ptr;
            }
            bool operator> (const reverse_iterator<T>& rhs)
            {
                return _ptr > rhs._ptr;
            }
			bool operator>= (const reverse_iterator<T>& rhs)
            {
                return _ptr >= rhs._ptr;
            }
			bool operator<= (const reverse_iterator<T>& rhs)
            {
                return _ptr <= rhs._ptr;
            }

			friend bool operator== (const reverse_iterator& a, const reverse_iterator& b) { return a._ptr == b._ptr; };
			friend bool operator!= (const reverse_iterator& a, const reverse_iterator& b) { return a._ptr != b._ptr; };
			friend unsigned int operator- (const reverse_iterator& a, const reverse_iterator& b) { return a._ptr - b._ptr; };
			friend unsigned int operator+ (const reverse_iterator& a, const reverse_iterator& b) { return a._ptr + b._ptr; };
			friend unsigned int operator/ (const reverse_iterator& a, const reverse_iterator& b) { return a._ptr / b._ptr; };
			friend unsigned int operator* (const reverse_iterator& a, const reverse_iterator& b) { return a._ptr * b._ptr; };
			
            
		private:
			T* _ptr;
	};
}

#endif