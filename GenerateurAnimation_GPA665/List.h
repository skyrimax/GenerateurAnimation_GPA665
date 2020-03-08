#pragma once

template<class T>
class list
{
public:
	list();
	list(const list<T>& x);
	list(list<T>&& x);
	~list();

	list<T>& operator=(const list<T>& x);
	list<T>& operator=(list<T>&& x);

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

	// Method to empty the structure
	void clear();

	class iterator
	{
	public:
		// Basic constructors and destructor
		iterator();
		iterator(const iterator& it);
		~iterator();

		// Assignment operator
		iterator& operator=(const iterator& it);

		// Comparation operators
		bool operator==(const iterator& it) const;
		bool operator!=(const iterator& it) const;

		// Pre and post incrementation and decrement operators
		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);

		// Dereference operators
		T& operator*() const;
		T* operator->() const;

	private:
		typename list<T>::Node* m_node;

		friend class list;
	};

	class backward_iterator
	{
	public:
		// Basic constructors and destructor
		backward_iterator();
		backward_iterator(const backward_iterator& it);
		~backward_iterator();

		// Assignment operator
		backward_iterator& operator=(const backward_iterator& it);

		// Comparation operators
		bool operator==(const backward_iterator& it) const;
		bool operator!=(const backward_iterator& it) const;

		// Pre and post incrementation and decrement operators
		backward_iterator& operator++();
		backward_iterator operator++(int);
		backward_iterator& operator--();
		backward_iterator operator--(int);

		// Dereference operators
		T& operator*() const;
		T* operator->() const;

	private:
		typename list<T>::Node* m_node;

		friend class list;
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

	Node* m_head;
	Node* m_tail;
};

#include"List.tpp"

