#pragma once

template <class T>
class forward_list
{
public:
	// Basic constructor and destructor
	forward_list();
	~forward_list();

	bool empty();
	size_t size();

	// Accessing first element
	T& front();
	const T& front() const;

	// Insert element at the front of the list
	void push_front(const T& val);
	void push_front(T&& val);

	// Remove first element
	void pop_front();

	// Insert element after specified position
	void insert_after(size_t position, const T& val);
	void insert_after(size_t position, T&& val);

	// Delete element after specified position
	void erase_after(size_t position);

	// Insert element at the end of the list
	void push_back(const T& val);
	void push_back(T&& val);

	// Remove last element
	void pop_back();

	class iterator
	{
	public:
		iterator();
		iterator(const iterator& it);
		~iterator();

		iterator& operator=(const iterator& it);

		bool operator==(const iterator& it) const;
		bool operator!=(const iterator& it) const;

		iterator& operator++();
		iterator operator++(int);

		T& operator*() const;
		T* operator->() const;

	private:
		Node* m_node;
	};

	// Iterator methods
	iterator begin();
	iterator end();

private:
	struct Node
	{
		Node* next;
		T data;
	};

	Node* m_head;
	Node* m_tail;

	iterator m_begin;
	iterator m_end;
};

#include "forward_list.tpp"