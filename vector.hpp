/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:26:53 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/27 10:41:42 by ael-hadd         ###   ########.fr       */
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
			typedef ft::iterator<value_type>				iterator;
			typedef ft::iterator<const value_type>			const_iterator;
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
			explicit vector (const allocator_type& alloc = allocator_type()) :
				_allocator(alloc),
				_container(nullptr),
				_capacity(0),
				_size(0)	{}
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
				_allocator(alloc),
				_container(nullptr),
				_capacity(0),
				_size(n)	{ this->assign(n, val); }
			template <class InputIterator>
				vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) :
					_allocator(alloc),
					_container(nullptr),
					_capacity(0),
					_size(0)     { this->assign(first, last); }
			vector (const vector& x) : _allocator(x._allocator), _container(nullptr), _capacity(0), _size(0)
				{ this->assign(x.begin(), x.end()); }
			vector& operator= (const vector& x)
				{ this->assign(x.begin(), x.end()); return (*this); }
			~vector()	{ this->clear(); this->deallocate(); }

			// Iretators:
			iterator begin()	{ return (iterator(_container)); }
			const_iterator begin() const	{ return (const_iterator(_container)); }
			iterator end()	{ return (iterator(_container + _size)); }
			const_iterator end() const	{ return (const_iterator(_container + _size)); }
			reverse_iterator rbegin()	{ return (reverse_iterator(_container + _size)); }
			const_reverse_iterator rbegin() const	{ return (const_reverse_iterator(_container + _size)); }
			reverse_iterator rend()	{ return (reverse_iterator(this->begin())); }
			const_reverse_iterator rend() const	{ return (const_reverse_iterator(this->begin())); }

			// Capacity:
			size_type size() const	{ return (_size); }
			size_type max_size() const	{return (_allocator.max_size()); }
			void resize (size_type n, value_type val = value_type())	
			{
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
			size_type capacity() const	{ return (_capacity); }
			bool empty() const 	{ return (!_size); }
			void reserve (size_type n)	{ 
				if (n > max_size())
					throw std::length_error("The requested size is greater than the maximum allowed size");
				else if ( n <= _capacity) return ;
				pointer	_data = _allocator.allocate(n);
				for (size_type i = 0; i < _size; i++)
				{
					_allocator.construct(_data + i, _container[i]);
					_allocator.destroy(&_container[i]);
				}
				this->deallocate();
				_container = _data;
				_capacity = n;
			}
			void shrink_to_fit()	{
				if (_capacity > _size)
				{
					for ( ; _capacity > _size; _capacity--)
						_allocator.destroy(&_container[_capacity]);
				}
			}

			// Element access:
			reference operator[] (size_type n)	{ if (n >= _size){ return (*end());} return (_container[n]); }
			const_reference operator[] (size_type n) const	{ if (n >= _size){ return (*end());} return (_container[n]); }
			reference at (size_type n)	{
				if (n >= _size)
					throw std::out_of_range("The index requested is out of bounds");
				return (_container[n]);
			}
			const_reference at (size_type n) const	{
				if (n >= _size)
					throw std::out_of_range("The index requested is out of bounds");
				return (_container[n]);
			}
			reference front()	{ return (_container[0]); }
			const_reference front() const	{ return (_container[0]); }
			reference back()	{ return (_container[_size - 1]); }
			const_reference back() const 	{ return (_container[_size -1]); }

			// Modifiers:
			template <class InputIterator>
				void assign (InputIterator first, InputIterator last)	{
					this->clear();
					for (InputIterator it = first; it != last; it++)
						_size++;
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
					this->deallocate();
					_capacity = _size;
					_container = _allocator.allocate(_capacity);
				}
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(_container + i, val);
			}
			void push_back (const value_type& val)	{
				this->reserve(_size + 1);
				_allocator.construct(_container + _size, val);
				_size++;
			}
			void pop_back()	{ this->resize(_size - 1); }
			iterator insert (iterator position, const value_type& val)	{
				size_type	i = position - begin();
				this->insert(position, 1, val);
				return (iterator(_container + i));
			}
			void insert (iterator position, size_type n, const value_type& val)	{
				vector<T>	tmp(*this);
				size_type	i = position - begin();
				this->reserve(_size	+ n);
				for (size_type j = i; j < i + n; ++j)
					_allocator.construct(_container + j, val);
				for (size_type j = i + n; j < _size + n; ++j)
					_allocator.construct(_container + j, tmp[j - n]);
			}
			template <class InputIterator>
				void insert (iterator position, InputIterator first, InputIterator last)	{
					vector<T>	tmp(*this);
					size_type	n = last - first;
					size_type	i = position - begin();
					this->reserve(_size + n);
					_size += n;
					for (size_type j = i; j < i + n; ++j)
						_allocator.construct(_container + j, *first++);
					for (size_type j = i + n; j < _size; ++j)
						_allocator.construct(_container + j, tmp[j -n]);
					}
			iterator erase (iterator position)	{
				size_type	i = position - begin();
				for (size_type j = i; j < _size; ++j)
				{
					_allocator.destroy(&_container[j]);
					if (j + 1 < _size)
						_allocator.construct(_container + j, _container[j + 1]);
				}
				_size--;
				return (position);
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
			void swap (vector& x)	{
				ft::swap(_container, x._container);
				ft:swap(_capacity, x._capacity);
				ft::swap(_size, x._size);
			}
			void clear()	{
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(&_container[i]);
				_size = 0;
				
			}

			// Allocator:
			allocator_type get_allocator() const	{ return (_allocator); }
			private:
				void deallocate() { if (_capacity) _allocator.deallocate(_container, _capacity); }
	};
	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
		{
			x.swap(y);
		}
}
