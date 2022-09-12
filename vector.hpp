/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:26:53 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/09/11 16:50:36 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include	<iostream>
#include	<memory>
#include	"iterators.hpp"
#include	"algorithm.hpp"

namespace	ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T									value_type;
			typedef Alloc								allocator_type;
			typedef T&								reference;
			typedef const T&							const_reference;
			typedef T*								pointer;
			typedef const T*							const_pointer;
			typedef ft::vec_iterator<value_type>				iterator;
			typedef ft::vec_iterator<const value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef size_t								size_type;
		protected:
			size_type	_size;
			size_type	_capacity;
			pointer	_container;
			allocator_type	_allocator;
		public:
			// MEMBER FUNCTIONS
			vector() : _size(0), _capacity(0), _container(nullptr), _allocator(allocator_type()) {}

			explicit vector (const allocator_type& alloc) : 
				 _size(0), _capacity(0), _container(nullptr), _allocator(alloc)	{}

			explicit vector( size_type n, const T& val = T(), const allocator_type& alloc = allocator_type()) :
				_size(0), _capacity(0), _container(nullptr), _allocator(alloc)	{
					this->assign(n, val);
			}

			template <class InputIt>
				vector (InputIt first, InputIt last, const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr) :
						_size(0), _capacity(0), _container(nullptr), _allocator(alloc)	{
							this->assign(first, last);
			}

			vector (const vector& x) : _size(0), _capacity(0), _container(nullptr), _allocator(x.get_allocator())	{
				
			this->assign(x.begin(), x.end());
			}

			vector& operator= (const vector& x)	{
				this->assign(x.begin(), x.end()); return (*this);
			}

			~vector()	{  this->clear(); this->deallocate();}

			// Iretators:
			iterator begin()	{ return (iterator(_container)); }

			const_iterator begin() const	{ return (const_iterator(_container)); }

			iterator end()	{ return (iterator(_container + _size)); }

			const_iterator end() const	{ return (const_iterator(_container + _size)); }

			reverse_iterator rbegin()	{
				iterator iter = this->end();
				return (reverse_iterator(iter));
			}

			const_reverse_iterator rbegin() const	{
				const_iterator iter = this->end();
				return (reverse_iterator(iter));
			}

			reverse_iterator rend()	{
				iterator iter = this->begin();
				return (reverse_iterator(iter));
			}

			const_reverse_iterator rend() const	{
				const_iterator iter = this->begin();
				return (reverse_iterator(iter));
			}


			// Capacity:
			size_type size() const	{ return (_size); }

			size_type max_size() const	{return (_allocator.max_size()); }
		
			size_type capacity() const	{ return (_capacity); }

			bool empty() const 	{ return (!_size); }

			void reserve (size_type n)	{ 
				if (n > max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				else if ( n <= _capacity) return ;
				if (_capacity == 0 || n > _capacity*2)
					_capacity = n;
				else
					_capacity *= 2;
				pointer	_data = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
				{
					_allocator.construct(_data + i, _container[i]);
					_allocator.destroy(&_container[i]);
				}
				this->deallocate();
				_container = _data;
			}


			// Element access:
			reference operator[](size_type n)	{ if (n >= _size || n < 0){ return (*end());} return (_container[n]); }

			const_reference operator[](size_type n) const	{ if (n >= _size){ return (*end());} return (_container[n]); }

			reference at (size_type n)	{
				if (n >= _size)
					throw std::out_of_range("vector");
				return (_container[n]);
			}

			const_reference at (size_type n) const	{
				if (n >= _size)
					throw std::out_of_range("vector");
				return (_container[n]);
			}

			reference front()	{ return (_container[0]); }

			const_reference front() const	{ return (_container[0]); }

			reference back()	{ return (_container[_size - 1]); }

			const_reference back() const 	{ return (_container[_size -1]); }

			// Modifiers:
			template <class InputIt>
				void assign (InputIt first, InputIt last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr)	{
					this->clear();
					_size = last - first;
					if (_size > _capacity)
					{
						this->deallocate();
						_capacity = _size;
						_container = _allocator.allocate(_capacity);
					}
					for (size_type i = 0; first != last; i++, first++)
						_allocator.construct(_container + i , *first);
				}

			void assign (size_type n, const value_type& val)	{
				this->clear();
				_size = n;
				if (_size > _capacity){
					_capacity = n;
					this->deallocate();
					_container = _allocator.allocate(_capacity);
				}
				for (size_type i = 0; i < n; i++)
					_allocator.construct(_container + i, val);
			}

			void push_back (const value_type& val)	{
				this->reserve(_size + 1);
				_allocator.construct(_container + _size, val);
				_size++;
			}

			void pop_back()	{ this->resize(_size - 1); }

			iterator insert (iterator pos, const value_type& val)	{
				size_type	i = pos - begin();
				this->insert(pos, 1, val);
				return (iterator(_container + i));
			}

			void insert (iterator pos, size_type n, const value_type& val)	{
				vector<value_type>	tmp(*this);
				size_type	i = pos - begin();
				this->reserve(_size	+ n);
				_size += n;
				for (size_type j = i; j < i + n; j++)
					_allocator.construct(_container + j, val);
				for (size_type j = i + n; j < _size + n; ++j)
					_allocator.construct(_container + j, tmp[j - n]);
			}

			template <class InputIt>
				void insert (iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr)	{
					vector<value_type>	tmp(*this);
					size_type	n = last - first;
					size_type	i = pos - begin();
					this->reserve(_size + n);
					_size += n;
					for (size_type j = i; j < i + n; ++j)
						_allocator.construct(_container + j, *first++);
					for (size_type j = i + n; j < _size; ++j)
						_allocator.construct(_container + j, tmp[j -n]);
				}

			iterator erase (iterator pos)	{
				size_type	i = pos - begin();
				for (size_type j = i; j < _size; ++j)
				{
					_allocator.destroy(&_container[j]);
					if (j + 1 < _size)
						_allocator.construct(_container + j, _container[j + 1]);
				}
				_size--;
				return (pos);
			}

			iterator erase (iterator first, iterator last)	{
				vector<T>	tmp(*this);

				size_type	i = first - begin();
				size_type	n = last - first;
				for (size_type j = i; j < _size; ++j)
					_allocator.destroy(&_container[j]);
				for (size_type j = i + n; j < _size; ++j)
					_allocator.construct(_container + j - n, tmp[j]);
				_size -= n;
				return (first);
			}

			void resize (size_type n, value_type val = value_type())	{
				if (n <= _size)
				{
					for (size_type i = n; i < _size; i++)
						_allocator.destroy(&_container[i]);
					_size = n;
				}
				this->reserve(n);
				if (n > _size){
					for (size_type i = _size; i < n; i++)
						_allocator.construct(_container + i, val);
					_size = n;
				}
			}
			
			void swap (vector& x)	{
				ft::swap(this->_size, x._size);
				ft::swap(this->_capacity, x._capacity);
				ft::swap(this->_container, x._container);
				ft::swap(this->_allocator, x._allocator);
			}

			void clear()	{
				if (_size)
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy(&_container[i]);
				_size = 0;
				
			}

			// Allocator:
			allocator_type get_allocator() const	{ return (_allocator); }

			private:
				void deallocate() { if (_capacity) _allocator.deallocate(_container, _capacity); }
	};

	template< class T, class Alloc >
		bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )	{
			return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

	template< class T, class Alloc >
		bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )	{
			return !(lhs == rhs);
		}

	template< class T, class Alloc >
		bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )	{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

	template< class T, class Alloc >
		bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )	{
			return !(rhs < lhs);
		}

	template< class T, class Alloc >
		bool operator>( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )	{
			return (rhs < lhs);
		}

	template< class T, class Alloc >
		bool operator>=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )	{
			return !(lhs < rhs);
		}

	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
		{
			x.swap(y);
		}
}
