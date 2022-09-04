/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:26:47 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/09/04 14:53:45 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

#include <iostream>
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
			typedef ft::RBiterator<value_type>								iterator;
			typedef ft::RBiterator<const value_type>						const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

		private:
			tree_type			_tree;
			allocator_type		_tree_allocator;
			Allocator			_allocator;
			key_compare		_comp;
			
		public:
			// Constructors and destructors
			map() : _comp(), _allocator() { _tree = _tree_allocator.allocate(1); _tree_allocator.construct(_tree); }
			explicit map(const Compare &comp, const Allocator &alloc = Allocator()) : _comp(comp), _allocator(alloc)  {
				_tree = _tree_allocator.allocate(1);
				_tree_allocator.construct(_tree);
			}
			template< class InputIt >
			map(InputIt first, InputIt last, const Compare &comp = Compare(), const Allocator &alloc = Allocator()) : _comp(comp), _allocator(alloc) {
				_tree = _tree_allocator.allocate(1);
				_tree_allocator.construct(_tree);
				while (first != last)
					insert(*first++);
			}
			map( const map& other ) : _comp(other.key_comp), _allocator(other.get_allocator()) {
				_tree = _tree_allocator.allocate(1);
				_tree_allocator.construct(_tree);
				const_iterator it = other.begin();
				while (it != other.end())
					insert(*it++);
			}
			~map()	{
				clear();
			}
			map&			operator=(const map& other) {
				_tree_allocator.destroy(_tree);
				_tree_allocator.deallocate(_tree, 1);

				_tree = _tree_allocator.allocate(1);
				_tree_allocator.construct(_tree);
				insert(other.begin(), other.end());
				return (*this);
			}

			// Element access
			T&	at(const Key &key) {
				node_pointer node = _tree->searchNode(key);
				if (node == nullptr || node == _tree.NIL) return (nullptr);
				return node->data.second;
			}

			const T&	at(const Key &key) const {
				node_pointer node = _tree->searchNode(key);
				if (node == nullptr || node == _tree.NIL) return (nullptr);
				return node->data.second;
			}
			
			mapped_type&	operator[](const key_type& key)	{
				value_type pair = ft::make_pair(key, T());
				node_pointer node = _tree->searchNode(pair);
				if (node == nullptr || node == _tree.NIL)
					return (insert(pair).first->second);
				return (node->key.second);
			}

			// Iterators
			iterator begin()	{
				return (iterator(_tree.begin())); }
			const_iterator begin() const	{
				return (iterator(_tree.begin())); }
			iterator end()	{
				return (iterator(_tree.end())); }
			const_iterator end() const	{
				return (iterator(_tree.end())); }
			reverse_iterator rbegin()	{
				return (reverse_iterator(end())); }
			const_reverse_iterator rbegin() const	{
				return (const_reverse_iterator(end())); }
			reverse_iterator rend()	{
				return (reverse_iterator(begin())); }
			const_reverse_iterator rend() const	{
				return (const_reverse_iterator(begin())); }

			// Capacity
			bool		empty() const { return (_tree.isEmpty()); }
			size_type	size() const	{ return (_tree.size()); }
			size_type	max_size() const	{return (_tree.max_size()); }

			// Modifiers
			void					clear()	{ _tree.clear(); }
			ft::pair<iterator,bool>	insert(const value_type& val)	{
				node_pointer node = _tree.searchNode(val);
				if (node != _tree.NIL)
					return (ft::make_pair(iterator(node,false)));
				node = _tree->insert(val);
				return (ft::make_pair(iterator(node,true)));
			}
			iterator				insert(iterator hint, const value_type& val)	{
				(void) hint;
				return (insert(val).first);
			}
			template<typename InputIt>
				void				insert(InputIt first, InputIt last)	{
					while (first != last)
						insert(*first++);
				}
			void					erase(iterator pos)	{
				_tree->remove(pos.base());
			}
			size_type				erase(const key_type& key)	{
				node_pointer node = _tree.searchNode(key);
				if (node != _tree.NIL)	{
					_tree.remove(node);
					return (1);
				}
				return (0);
			}
			void					erase(iterator first, iterator last);
			void					swap(map& other);

			// Lookup
			iterator								find(const key_type& key);
			const_iterator							find(const key_type& key) const;
			size_type								count(const key_type& key) const;
			iterator								lower_bound(const key_type& key);
			const_iterator							lower_bound(const key_type& key) const;
			iterator								upper_bound(const key_type& key);
			const_iterator							upper_bound(const key_type& key) const;
			ft::pair<iterator,iterator>				equal_range(const key_type& key);
			ft::pair<const_iterator,const_iterator>		equal_range(const key_type& key) const;

			// Observers
			key_compare		key_comp() const;
			value_compare		value_comp() const;

			// Allocator
			Allocator	get_allocator() const	{
				return (_allocator);
			}
			

	};
}