#include "List.h"

#pragma once
#include <utility>

// Default cunstructor creating empty container
template<class T>
list<T>::list()
	: m_head(nullptr), m_tail(nullptr)
{
}

// Copy constructor
template<class T>
list<T>::list(const list<T>& x)
{
	Node* tempNode=x.m_head;
	Node* newNode;
	Node* previousNode=nullptr;

	// Do untile the end of the container is reached
	while (tempNode != nullptr) {
		// Assign the new node, set next node to nullptr and reference the previous node
		newNode = new Node;
		newNode->next = nullptr;
		newNode->previous = previousNode;

		// If not first element, append new node at the end of the container
		if (previousNode) {
			previousNode->next = newNode;
		}
		// Else the node is appended to the begining
		else {
			m_head = newNode;
		}

		// Copy data from node in original container to the new node
		newNode->data = tempNode->data;

		// Move to the next node
		tempNode = tempNode->next;
		// Remember end of new container
		previousNode = newNode;
	}

	// Set tail of container
	m_tail = newNode;
}

// Move constuctor
template<class T>
list<T>::list(list<T>&& x)
{
	// Transfer ownership of data from previous container to new container
	m_head = x.m_head;
	m_tail = x.m_tail;

	// Remove ownership of data from previous container
	x.m_head = nullptr;
	x.m_tail = nullptr;
}

// Destructor
template<class T>
list<T>::~list()
{
	Node* tempNode;

	// Do until the end of the container is reached
	while (m_head) {
		// Temporary memorisation of first node
		tempNode = m_head;
		// Move first node pointer to next node
		m_head = m_head->next;
		// Delete previous first node
		delete tempNode;
	}
}

// Copy asignement operator
template<class T>
list<T>& list<T>::operator=(const list<T>& x)
{
	Node* tempNode = x.m_head;
	Node* newNode;
	Node* previousNode = nullptr;

	// Empty the current structure
	clear();

	// Do untile the end of the container is reached
	while (tempNode != nullptr) {
		// Assign the new node, set next node to nullptr and reference the previous node
		newNode = new Node;
		newNode->next = nullptr;
		newNode->previous = previousNode;

		// If not first element, append new node at the end of the container
		if (previousNode) {
			previousNode->next = newNode;
		}
		// Else the node is appended to the begining
		else {
			m_head = newNode;
		}

		// Move to the next node
		newNode->data = tempNode->data;
		// Remember end of new container
		previousNode = newNode;
	}

	// Set tail of container
	m_tail = newNode;

	// Return this container
	return *this;
}

// Move assignment operator
template<class T>
list<T>& list<T>::operator=(list<T>&& x)
{
	// Empty the current structure
	clear();

	// Transfert of the other list's internal data to the calling object
	m_head = x.m_head;
	m_tail = x.m_tail;

	// Removing ownership of data from other object
	x.m_head = nullptr;
	x.m_tail = nullptr;

	// Return this container
	return *this;
}

// Return if the structure is empty
template<class T>
bool list<T>::empty()
{
	return m_head == nullptr;
}

// Return the size of the structure
template<class T>
size_t list<T>::size()
{
	size_t i = 0;
	Node* tempNode = m_head;

	// Do until the end of the structure is reached
	while (tempNode)
	{
		// Move to the next node
		tempNode = tempNode->next;

		// Increase the count by one
		i++;
	}

	// Return the count
	return i;
}

// Return first element of the structure
template<class T>
T & list<T>::front()
{
	return *m_head;
}

// Return first element of the structure
template<class T>
const T & list<T>::front() const
{
	return *m_head;
}

// Return last element of the structure
template<class T>
T & list<T>::back()
{
	return *m_end;
}

// Return last element of the structure
template<class T>
const T & list<T>::back() const
{
	return *m_end;
}

// Add an element to the begining of the structure
template<class T>
void list<T>::push_front(const T & val)
{
	// Allocate memory for the new element
	Node* newNode = new Node;

	// Add reference to next node in new node
	newNode->next = m_head;
	newNode->previous = nullptr;

	// If the structure is empty, also add element to the end
	if (!m_tail) {
		m_tail = newNode;
	}
	// If the structure is not empty, add reference to new node in next node
	else {
		m_head->previous = newNode;
	}

	// Add new element to the begining of the structure and place the rest of it after
	m_head = newNode;

	// Copy data over to the new element
	newNode->data = val;
}

template<class T>
void list<T>::push_front(T && val)
{
	// Allocate memory for the new element
	Node* newNode = new Node;

	// Add reference to next node in new node
	newNode->next = m_head;
	newNode->previous = nullptr;

	// If the structure is empty, also add element to the end
	if (!m_head) {
		m_tail = newNode;
	}
	// If the structure is not empty, add reference to new node in next node
	else {
		m_head->previous = newNode;
	}

	// Add new element to the begining of the structure and place the rest of it after
	m_head = newNode;

	// Move data over to the new element
	newNode->data = std::move(val);
}

// Remove the first element from the structure
template<class T>
void list<T>::pop_front()
{
	// If the structure is not empty
	if (m_head) {
		// Memorise the element to be deleted
		Node* tempNode = m_head;
		// Remove element from structure
		m_head = tempNode->next;

		// If structure is now empty, remove reference from end of the structure
		if (!m_head) {
			m_tail = nullptr;
		}
		// If the structure is still not empty, remove reference to removed node in next node
		else {
			m_head->previous = nullptr;
		}

		// Delete element
		delete tempNode;
	}
}

// Add an element to the end of the structure
template<class T>
void list<T>::push_back(const T & val)
{
	// Allocate memory for the new element
	Node* newNode = new Node;

	// Initialize new element
	newNode->next = nullptr;
	newNode->previous = m_tail;

	if (!m_tail) {
		// If empty, add element to the begining
		m_head = newNode;
	}
	else {
		// Else, add element at the end of the list
		m_tail->next = newNode;
	}

	// Set end of structure on new element
	m_tail = newNode;

	// Copy data over to the new element
	newNode->data = val;
}

// Add an element to the end of the structure
template<class T>
void list<T>::push_back(T && val)
{
	// Allocate memory for the new element
	Node* newNode = new Node;

	// Initialize new element
	newNode->next = nullptr;
	newNode->previous = m_tail;

	if (!m_tail) {
		// If empty, add element to the begining
		m_head = newNode;
	}
	else {
		// Else, add element at the end of the list
		m_tail->next = newNode;
	}

	// Set end of structure on new element
	m_tail = newNode;

	// Move data over to the new element
	newNode->data = std::move(val);
}

// Remove the first element from the structure
template<class T>
void list<T>::pop_back()
{
	// If the structure is not empty
	if (m_head) {
		// Memorise the element to be deleted
		Node* tempNode = m_tail;
		// Remove reference to element from end of structure
		m_tail = tempNode->previous;

		// If structure is now empty, remove reference from end of the structure
		if (!m_tail) {
			m_head = nullptr;
		}
		// If the structure is still not empty, remove reference to removed node in previous node
		else {
			m_tail->next = nullptr;
		}

		// Delete element
		delete tempNode;
	}
}

// Add an element at position of the structure
template<class T>
void list<T>::insert_after(size_t position, const T & val)
{
	// Get size of structure
	size_t size = size();

	// If insert position does not reach the last element
	if (position < size - 1) {
		// Get first element
		Node* posNode = m_head;
		// Allocate new element
		Node* newNode = new Node;

		// Go to insert position
		for (int i = 0; i < position; i++) {
			posNode = posNode->next;
		}

		// Insert new element
		newNode->next = posNode->next;
		newNode->previous = posNode;

		posNode->next->previous = newNode;
		posNode->next = newNode;

		// Copy data over to the new element
		newNode->data = val;
	}
	// If the insert position is the end, use function for that
	else if (position == size - 1) {
		push_back(val);
	}
}

// Add an element at position of the structure
template<class T>
void list<T>::insert_after(size_t position, T && val)
{
	// Get size of structure
	size_t size = size();

	// If insert position does not reach the last element
	if (position < size - 1) {
		// Get first element
		Node* posNode = m_head;
		// Allocate new element
		Node* newNode = new Node;

		// Go to insert position
		for (int i = 0; i < position; i++) {
			posNode = posNode->next;
		}

		// Insert new element
		newNode->next = posNode->next;
		newNode->previous = posNode;

		posNode->next->previous = newNode;
		posNode->next = newNode;

		// Move data over to the new element
		newNode->data = std::move(val);
	}
	// If the insert position is the end, use function for that
	else if (position == size - 1) {
		push_back(val);
	}
}

// Remove the element at position from the structure
template<class T>
void list<T>::erase_after(size_t position)
{
	// Get size of structure
	size_t size = size();

	// If delete position does not reach the last element
	if (position < size - 1) {
		// Get first element
		Node* posNode = m_head;

		// Go to delete position
		for (int i = 0; i < position; i++) {
			posNode = posNode->next;
		}

		// Remove element from structure
		Node* nodeToDelete=posNode->next;

		posNode->next = nodeToDelete->next;
		nodeToDelete->next->previous = posNode;

		// Delete element
		delete nodeToDelete;
	}
	// If the delete position is the end, use function for that
	else if (position == size - 1) {
		pop_back();
	}
}

// Remove all data from structure
template<class T>
void list<T>::clear()
{
	Node* tempNode;

	// Do until the end is reached
	while (m_head) {
		// Memorize the element to be deleted
		tempNode = m_head;
		// Move to the next element
		m_head = m_head->next;
		// Delete element
		delete tempNode;
	}

	// Empty end of structure
	m_tail = nullptr;
}

// Return an iterator to the begining of the list
template<class T>
typename list<T>::iterator list<T>::begin()
{
	iterator begin;

	// Set iterator to the begining of the structure
	begin.m_node = m_head;

	return begin;
}

// Return an iterator past the last element
template<class T>
typename list<T>::iterator list<T>::end()
{
	iterator end;

	// Set iterator past the end
	end.m_node = nullptr;

	return end;
}

// Return a backward iterator to the reverse begining of the list
template<class T>
typename list<T>::backward_iterator list<T>::rbegin()
{
	backward_iterator rbegin;

	// Set backward iterator to the reverse begining of the structure
	rbegin.m_node = m_tail;

	return rbegin;
}

// Return a backward iterator past the reverse last element
template<class T>
typename list<T>::backward_iterator list<T>::rend()
{
	backward_iterator rend;

	// Set backward iterator past the reverse end
	rend.m_node = nullptr;
	
	return rend;
}

// Default constructor for iterators
template<class T>
list<T>::iterator::iterator()
{
	m_node = nullptr;
}

// Copy constructor for iterators
template<class T>
list<T>::iterator::iterator(const iterator& it)
{
	// Set the new iterator to point on the same value as it
	m_node = it.m_node;
}

// Iterator destructor
template<class T>
list<T>::iterator::~iterator()
{
}

// Assigement operator for iterators
template<class T>
typename list<T>::iterator & list<T>::iterator::operator=(const iterator & it)
{
	// Set the this iterator to point on the same value as it
	m_node = it.m_node;

	// Return this iterator
	return *this;
}

// Comparason operator to determine if two iterators are the same
template<class T>
bool list<T>::iterator::operator==(const iterator & it) const
{
	// True is they point on the same element
	return m_node == it.m_node;
}

// Comparason operator to determine if two iterators are different
template<class T>
bool list<T>::iterator::operator!=(const iterator & it) const
{
	// True is they point on different element
	return m_node != it.m_node;
}

// Pre incrementation operator
template<class T>
typename list<T>::iterator & list<T>::iterator::operator++()
{
	// If the iterator isn't passed the end
	if (m_node) {
		// Move iterator the next element
		m_node = m_node->next;
	}

	return *this;
}

// Post incrementation operator
template<class T>
typename list<T>::iterator list<T>::iterator::operator++(int)
{
	// Create an iterator pointing on the current element that will become the previous element
	iterator* it=new iterator(*this);

	// If the iterator isn't passed the end
	if (m_node) {
		// Move iterator the next element
		m_node = m_node->next;
	}

	// Return an iterator pointing on the previous element
	return *it;
}

// Pre decrementation operator
template<class T>
typename list<T>::iterator & list<T>::iterator::operator--()
{
	// If the iterator isn't passed the end
	if (m_node) {
		// Move iterator the previous element
		m_node = m_node->previous;
	}
	// Else, set to last element
	else {
		m_node = m_tail;
	}

	return *this
}

// Post decrementation operator
template<class T>
typename list<T>::iterator list<T>::iterator::operator--(int)
{
	// Create an iterator pointing on the current element that will become the next element
	iterator* it=new iterator(*this);

	// If the iterator isn't passed the end
	if (m_node) {
		// Move iterator the previous element
		m_node = m_node->previous;
	}
	// Else, set to last element
	else {
		m_node = m_tail;
	}

	// Return an iterator pointing on the next element
	return it;
}

// Dereference operator
template<class T>
T & list<T>::iterator::operator*() const
{
	// Return direct reference to the pointed element's data
	return m_node->data;
}

// Dereference operator
template<class T>
T * list<T>::iterator::operator->() const
{
	// Return a pointer to the pointed element's data
	return &m_node->data;
}

// Default constructor for backward iterators
template<class T>
inline list<T>::backward_iterator::backward_iterator()
{
	m_node = nullptr;
}

// Copy constructor for backward iterators
template<class T>
list<T>::backward_iterator::backward_iterator(const backward_iterator & it)
{
	m_node = it.m_node;
}

// Backward iterator destructor
template<class T>
list<T>::backward_iterator::~backward_iterator()
{
}

// Assigement operator for backward iterators
template<class T>
typename list<T>::backward_iterator & list<T>::backward_iterator::operator=(const backward_iterator & it)
{
	// Set the this backward iterator to point on the same value as it
	m_node = it.m_node;

	// Return this iterator
	return *this;
}

// Comparason operator to determine if two iterators are the same
template<class T>
bool list<T>::backward_iterator::operator==(const backward_iterator & it) const
{
	// True is they point on the same element
	return m_node == it.m_node;
}

// Comparason operator to determine if two backward iterators are different
template<class T>
bool list<T>::backward_iterator::operator!=(const backward_iterator & it) const
{
	return m_node != it.m_node;
}

// Pre incrementation operator
template<class T>
typename list<T>::backward_iterator & list<T>::backward_iterator::operator++()
{
	// If the iterator isn't passed the reverse end
	if (m_node) {
		// Move iterator the previous element
		m_node = m_node->previous;
	}

	return *this;
}

// Post incrementation operator
template<class T>
typename list<T>::backward_iterator list<T>::backward_iterator::operator++(int)
{
	// Create a backward iterator pointing on the current element that will become the next element
	backward_iterator* it = new backward_iterator(*this);

	// If the iterator isn't passed the reverse end
	if (m_node) {
		// Move iterator the previous element
		m_node = m_node->previous;
	}

	// Return an backward iterator pointing on the next element
	return *it;
}

// Pre decrementation operator
template<class T>
typename list<T>::backward_iterator & list<T>::backward_iterator::operator--()
{
	// If the iterator isn't passed the reverse end
	if (m_node) {
		// Move iterator the next element
		m_node = m_node.next;
	}
	// Else, set to reverse last element
	else {
		m_node = m_head;
	}

	return *this;
}

// Post decrementation operator
template<class T>
typename list<T>::backward_iterator list<T>::backward_iterator::operator--(int)
{
	// Create a backward iterator pointing on the current element that will become the previous element
	backward_iterator* it = new backward_iterator(*this);

	// If the iterator isn't passed the reverse end
	if (m_node) {
		// Move iterator the next element
		m_node = m_node.next;
	}
	// Else, set to reverse last element
	else {
		m_node = m_head;
	}

	// Return an backward iterator pointing on the previous element
	return *it;
}

// Dereference operator
template<class T>
T & list<T>::backward_iterator::operator*() const
{
	// Return direct reference to the pointed element's data
	return m_node->data;
}

// Dereference operator
template<class T>
T * list<T>::backward_iterator::operator->() const
{
	// Return a pointer to the pointed element's data
	return &m_node->data;
}