#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <iostream>

using namespace std;

namespace ft
{
	template <typename T>
	class Iterator
	{
		public:
			typedef std::random_access_iterator_tag iterator_category;
			typedef int difference_type;
			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;
		public:
			// Constructors
			Iterator();
			Iterator(T* ptr) : _ptr(ptr) {};
			Iterator(const Iterator &copy){(void)copy;};
			
			// Destructor
			~Iterator() {};
			
			// Operators
	
			Iterator & operator=(const Iterator &assign){
				_ptr = assign._ptr;
				return *this;
			}

			reference operator*() const { return *_ptr; }
			pointer operator->() { return _ptr; }

			Iterator& operator++() { _ptr++; return *this; }

			Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

			Iterator& operator--() { _ptr--; return *this; }

			Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }

            bool operator< (const Iterator& rhs)
            {
                return _ptr < rhs._ptr;
            }
            bool operator> (const Iterator<T>& rhs)
            {
                return _ptr > rhs._ptr;
            }
			bool operator>= (const Iterator<T>& rhs)
            {
                return _ptr >= rhs._ptr;
            }
			bool operator<= (const Iterator<T>& rhs)
            {
                return _ptr <= rhs._ptr;
            }

			friend bool operator== (const Iterator& a, const Iterator& b) { return a._ptr == b._ptr; };
			friend bool operator- (const Iterator& a, const Iterator& b) { return a._ptr - b._ptr; };
			friend bool operator+ (const Iterator& a, const Iterator& b) { return a._ptr + b._ptr; };
			friend bool operator/ (const Iterator& a, const Iterator& b) { return a._ptr / b._ptr; };
			friend bool operator* (const Iterator& a, const Iterator& b) { return a._ptr * b._ptr; };
			friend bool operator!= (const Iterator& a, const Iterator& b) { return a._ptr != b._ptr; };
			
			
		public:
			T* _ptr;
	};

		
}

#endif