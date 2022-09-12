/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:26:47 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/09/11 11:45:19 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

#include <iostream>
#include "algorithm.hpp"
#include "iterators.hpp"
#include "red_black.hpp"

namespace	ft
{
	template< class Key, class T, class Compare = ft::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> > > 
	class map
	{
		public:
			typedef Key												key_type;
			typedef T													mapped_type;
			typedef ft::pair<const Key, T>								value_type;
			typedef Compare											key_compare;
			typedef value_type&											reference;
			typedef const value_type&									const_reference;
			typedef typename Allocator::pointer							pointer;
			typedef typename Allocator::const_pointer						const_pointer;
			typedef typename std::size_t									size_type;
			typedef typename std::ptrdiff_t								difference_type;

		public:
			class value_compare : public ft::binary_function<value_type, value_type, bool>
			{
				protected:
					key_compare comp;
				public:
					value_compare() : comp(key_compare()) {}

					value_compare(key_compare c) : comp(c) {}

					bool operator()(const value_type &lhs, const value_type &rhs) const
					{	
						return comp(lhs.first, rhs.first);
					};
			};

		private:
			typedef ft::RBTree<value_type, value_compare>					tree_type;
			typedef std::allocator<tree_type>								allocator_type;
			typedef ft::Node<value_type>	 								node_type;
			typedef ft::Node<value_type>*	 								node_pointer;

		public:
			typedef ft::RBiterator<value_type, const value_type>				iterator;
			typedef ft::RBiterator<const value_type, value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

		public:
			tree_type*		_tree;
			allocator_type		_tree_allocator;
			Allocator			_allocator;
			key_compare		_comp;
			
		public:
			// Constructors and destructors
			map() : _tree(nullptr), _tree_allocator(), _allocator(), _comp() {
				_tree = _tree_allocator.allocate(1); _tree_allocator.construct(_tree);
			}

			explicit map(const Compare &comp, const Allocator &alloc = Allocator()) : _tree(nullptr), _allocator(alloc), _comp(comp) {
				_tree = _tree_allocator.allocate(1);
				_tree_allocator.construct(_tree);
			}

			template< class InputIt >
			map(InputIt first, InputIt last, const Compare &comp = Compare(), const Allocator &alloc = Allocator()) : _allocator(alloc), _comp(comp) {
				_tree = _tree_allocator.allocate(1);
				_tree_allocator.construct(_tree);
				while (first != last)
					insert(*first++);
			}

			map( const map& other ) : _allocator(other.get_allocator()), _comp(other._comp) {
				_tree = _tree_allocator.allocate(1);
				_tree_allocator.construct(_tree);
				*this = other;
			}

			~map()	{
				_tree_allocator.destroy(_tree);
				_tree_allocator.deallocate(_tree, 1);
			}

			map&			operator=(const map& other) {

				this->clear();
				
				// _tree_allocator.destroy(_tree);
				// _tree_allocator.deallocate(_tree, 1);

				// _tree = _tree_allocator.allocate(1);
				// _tree_allocator.construct(_tree);
				insert(other.begin(), other.end());
				return (*this);
			}


			// Element access
			T&	at(const Key &key) {
				value_type pair = ft::make_pair(key, T());
				node_pointer node = _tree->search(pair);
				if (node == _tree->end())
					throw std::out_of_range("map::at:  key not found");
				return node->key.second;
			}

			const T&	at(const Key &key) const {
				value_type pair = ft::make_pair(key, T());
				node_pointer node = _tree->search(pair);
				if (node == _tree->end())
					throw std::out_of_range("map::at:  key not found");
				return node->key.second;
			}
			
			mapped_type&	operator[](const key_type& key)	{
				value_type pair = ft::make_pair(key, T());
				node_pointer node = _tree->search(pair);
				if (node == _tree->end())
					return (insert(pair).first->second);
				return (node->key.second);
			}


			// Iterators
			iterator begin()	{
				return (iterator(_tree->begin())); }

			const_iterator begin() const	{
				return (const_iterator(_tree->begin())); }

			iterator end()	{
				return (iterator(_tree->end())); }

			const_iterator end() const	{
				return (const_iterator(_tree->end())); }

			reverse_iterator rbegin()	{
				iterator iter = this->end();
				return (reverse_iterator(iter)); }

			const_reverse_iterator rbegin() const	{
				const_iterator iter = this->end();
				return (const_reverse_iterator(iter)); }

			reverse_iterator rend()	{
				iterator iter = this->begin();
				return (reverse_iterator(iter)); }

			const_reverse_iterator rend() const	{
				const_iterator iter = this->begin();
				return (const_reverse_iterator(iter)); }


			// Capacity
			bool		empty() const { return (_tree->isEmpty()); }

			size_type	size() const	{ return (_tree->size()); }

			size_type	max_size() const	{return (_tree->max_size()); }


			// Modifiers
			void					clear()	{
				_tree->clear();
			}

			ft::pair<iterator,bool>	insert(const value_type& val)	{
				node_pointer node = _tree->search(val);
				if (node != _tree->end())
					return (ft::make_pair(iterator(node),false));
				node = _tree->insert(val);
				return (ft::make_pair(iterator(node),true));
			}

			iterator				insert(iterator hint, const value_type& val)	{

				(void) hint;
				return (insert(val).first);
			}

			template<typename InputIt>
			void					insert(InputIt first, InputIt last)	{
				while (first != last)
				{
					insert(*first++);
				}
			}

			void					erase(iterator pos)	{
				_tree->remove(*pos);
			}

			size_type				erase(const key_type& key)	{
				value_type pair = ft::make_pair(key , T());
					return (_tree->remove(pair));
			}

			void					erase(iterator first, iterator last)	{
				while(first != last)
					erase(first++);
			}

			void					swap(map& other)	{
				ft::swap(this->_tree, other._tree);
				ft::swap(this->_tree_allocator, other._tree_allocator);
				ft::swap(this->_allocator, other._allocator);
				ft::swap(this->_comp, other._comp);
			}


			// Lookup
			iterator								find(const key_type& key)	{
				node_pointer node = _tree->search(ft::make_pair(key, T()));
				if (node != _tree->end())
					return (iterator(node));
				return (iterator(end()));
			}

			const_iterator							find(const key_type& key) const	{
				node_pointer node = _tree->search(ft::make_pair(key, T()));
				if (node != _tree->end())
					return (const_iterator(node));
				return (const_iterator(end()));
			}

			size_type								count(const key_type& key) const	{
				node_pointer node = _tree->search(ft::make_pair(key, T()));
				if (node != _tree->end())
					return (1);
				return (0);
			}

			iterator								lower_bound(const key_type& key)	{
				iterator it;
				for (it = begin(); it != end() && _comp((*it).first, key); ++it)
					;
				return (it);
			}

			const_iterator							lower_bound(const key_type& key) const	{
				const_iterator it;
				for (it = begin(); it != end() && _comp((*it).first, key); ++it)
					;
				return (it);
			}

			iterator								upper_bound(const key_type& key)	{
				iterator it;
				for (it = begin(); it != end() && !_comp(key, (*it).first); ++it)
					;
				return (it);
			}

			const_iterator							upper_bound(const key_type& key) const	{
				const_iterator it;
				for (it = begin(); it != end() && _comp(key, (*it).first); ++it)
					;
				return (it);
			}

			ft::pair<iterator,iterator>				equal_range(const key_type& key)	{
				return (ft::make_pair(iterator(lower_bound(key)), iterator(upper_bound(key))));
			}

			ft::pair<const_iterator,const_iterator>		equal_range(const key_type& key) const	{
				return (ft::make_pair(const_iterator(lower_bound(key)), const_iterator(upper_bound(key))));
			}


			// Observers
			key_compare		key_comp() const	{ return(Compare()); }

			value_compare		value_comp() const	{ return (value_compare()); }


			// Allocator
			Allocator	get_allocator() const	{
				return (_allocator);
			}

	};

	template< class Key, class T, class Compare, class Alloc >
		bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )	{
			return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		};

	template< class Key, class T, class Compare, class Alloc >
		bool operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )	{
			return !(lhs == rhs);
		};

	template< class Key, class T, class Compare, class Alloc >
		bool operator<( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )	{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		};

	template< class Key, class T, class Compare, class Alloc >
		bool operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )	{
			return !(rhs < lhs);
		};

	template< class Key, class T, class Compare, class Alloc >
		bool operator>( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )	{
			return (rhs < lhs);
		};

	template< class Key, class T, class Compare, class Alloc >
		bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )	{
			return !(lhs < rhs);
		};

	template< class Key, class T, class Compare, class Alloc >
		void swap( map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs )	{
			lhs.swap(rhs);
		};
}