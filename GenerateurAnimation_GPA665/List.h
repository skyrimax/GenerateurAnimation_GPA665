#pragma once

template<class T>
class list
{
public:
	list();
	~list();

	bool empty();
	size_t size();

	// Accessing first element
	T& front();
	const T& front() const;

	// Accessing last element
	T& back();
	const T& back() const;

	// Insert element at the front of the list
	void push_front(const T& val);
	void push_front(T&& val);

	// Remove first element
	void pop_front();

	// Insert element at the back of the list
	void push_back(const T& val);
	void push_back(T&& val);

	// Remove last element
	void pop_back();

	// Insert element after specified position
	void insert_after(size_t position, const T& val);
	void insert_after(size_t position, T&& val);

	// Delete element after specified position
	void erase_after(size_t position);

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
		iterator& operator--();
		iterator operator--(int);

		T& operator*() const;
		T* operator->() const;

	private:
		Node* m_node;
	};

	class backward_iterator
	{
	public:
		backward_iterator();
		backward_iterator(const backward_iterator& it);
		~backward_iterator();

		backward_iterator& operator=(const backward_iterator& it);

		bool operator==(const backward_iterator& it) const;
		bool operator!=(const backward_iterator& it) const;

		backward_iterator& operator++();
		backward_iterator operator++(int);
		backward_iterator& operator--();
		backward_iterator operator--(int);

		T& operator*() const;
		T* operator->() const;

	private:
		Node* m_node;
	};

	// Iterator methods
	iterator begin();
	iterator end();
	backward_iterator rbegin();
	backward_iterator rend();

private:
	struct Node
	{
		Node* next;
		Node* previous;
		T data;
	};

	iterator m_begin;
	iterator m_end;

	backward_iterator m_rbegin;
	backward_iterator m_rend;

	Node* m_head;
	Node* m_tail;
};

#include"List.tpp"

