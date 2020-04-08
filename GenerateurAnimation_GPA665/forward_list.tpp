#include "forward_list.h"

#pragma once
#include <utility>

// Default cunstructor creating empty container
template<class T>
forward_list<T>::forward_list()
	: m_head(nullptr), m_tail(nullptr)
{
}

// Copy constructor
template<class T>
forward_list<T>::forward_list(const forward_list<T>& x)
{
	Node* tempNode = x.m_head;
	Node* newNode=nullptr;
	Node* previousNode=nullptr;

	// Do untile the end of the container is reached
	while (tempNode != nullptr) {
		// Assign the new node and set next node to nullptr
		newNode = new Node;
		newNode->next = nullptr;

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
forward_list<T>::forward_list(forward_list<T>&& x)
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
forward_list<T>::~forward_list()
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
forward_list<T>& forward_list<T>::operator=(const forward_list<T>& x)
{
	Node* tempNode = x.m_head;
	Node* newNode=nullptr;
	Node* previousNode = nullptr;

	// Empty the current structure
	clear();

	// Do untile the end of the container is reached
	while (tempNode != nullptr) {
		// Assign the new node and set next node to nullptr
		newNode = new Node;
		newNode->next = nullptr;

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

	// Return this container
	return *this;
}

// Move assignment operator
template<class T>
forward_list<T>& forward_list<T>::operator=(forward_list<T>&& x)
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
bool forward_list<T>::empty()
{
	return m_head==nullptr;
}

// Return the size of the structure
template<class T>
size_t forward_list<T>::size()
{
	size_t i=0;
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
T & forward_list<T>::front()
{
	return *m_head;
}

// Return first element of the structure
template<class T>
const T & forward_list<T>::front() const
{
	return *m_head;
}

// Add an element to the begining of the structure
template<class T>
void forward_list<T>::push_front(const T & val)
{
	// Allocate memory for the new element
	Node* newNode = new Node;

	// Add new element to the begining of the structure and place the rest of it after
	newNode->next = m_head;
	m_head = newNode;

	// If the structure is empty, also add element to the end
	if (!m_tail) {
		m_tail = newNode;
	}

	// Copy data over to the new element
	newNode->data = val;
}

// Add an element to the begining of the structure
template<class T>
void forward_list<T>::push_front(T && val)
{
	// Allocate memory for the new element
	Node* newNode = new Node;

	// Add new element to the begining of the structure and place the rest of it after
	newNode->next = m_head;
	m_head = newNode;

	// If the structure is empty, also add element to the end
	if (!m_tail) {
		m_tail = newNode;
	}

	// Move data over to the new element
	newNode->data = std::move(val);
}

// Remove the first element from the structure
template<class T>
void forward_list<T>::pop_front()
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

		// Delete element
		delete tempNode;
	}
}

// Add an element at position of the structure
template<class T>
void forward_list<T>::insert_after(size_t position, const T & val)
{
	// Get size of structure
	size_t size = size();

	// If insert position does not reach the last element
	if (position < size-1) {
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
void forward_list<T>::insert_after(size_t position, T && val)
{
	// Get size of structure
	size_t size = size();

	// If insert position does not reach the last element
	if (position < size - 1) {
		// Get first element
		Node* posNode = m_head;
		// Allocate new element
		Node* tempNode = new Node;

		// Go to insert position
		for (int i = 0; i < position; i++) {
			posNode = posNode->next;
		}

		// Insert new element
		tempNode->next = posNode->next;
		posNode->next = tempNode;

		// Move data over to the new element
		tempNode->data = std::move(val);
	}
	// If the insert position is the end, use function for that
	else if (position == size - 1) {
		push_back(val);
	}
}

// Remove the element at position from the structure
template<class T>
void forward_list<T>::erase_after(size_t position)
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
		Node* nodeToDelete = posNode->next;
		posNode->next = posNode->next->next;

		// Delete element
		delete nodeToDelete;
	}
	// If the delete position is the end, use function for that
	else if (position == size - 1) {
		pop_back();
	}
}

// Add an element to the end of the structure
template<class T>
void forward_list<T>::push_back(const T & val)
{
	// Allocate memory for the new element
	Node* newNode = new Node;
	// Initialize new element
	newNode->next = nullptr;

	if (m_tail) {
		// Add element at the end
		m_tail->next = newNode;
		m_tail = newNode;
	}
	else {
		// If the structure is empty, also add element to the begining
		m_tail = newNode;
		m_head = newNode;
	}

	// Copy data over to the new element
	newNode->data = val;
}

// Add an element to the end of the structure
template<class T>
void forward_list<T>::push_back(T && val)
{
	// Allocate memory for the new element
	Node* newNode = new Node;
	// Initialize new element
	newNode->next = nullptr;

	if (m_tail) {
		// Add element at the end
		m_tail->next = newNode;
		m_tail = newNode;
	}
	else {
		// If the structure is empty, also add element to the begining
		m_tail = newNode;
		m_head = newNode;
	}

	// Move data over to the new element
	newNode->data = std::move(val);
}

// Remove the first element from the structure
template<class T>
void forward_list<T>::pop_back()
{
	// If the structure is not empty
	if (m_head) {
		// Memorise the element to be deleted
		Node* tempNode = m_tail;

		// If structure is now empty, remove reference from end of the structure
		if (m_head == m_tail) {
			m_head = nullptr;
			m_tail = nullptr;
		}
		// Else remove reference from second to last element
		else {
			// Start at begining of structure
			Node* secondToLast = m_head;

			// Move to second to last element
			while (secondToLast->next != tempNode) {
				secondToLast = secondToLast->next;
			}

			// Remove element from structure
			m_tail = secondToLast;
			secondToLast->next = nullptr;
		}

		// Delete element
		delete tempNode;
	}
}

// Remove all data from structure
template<class T>
void forward_list<T>::clear()
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
typename forward_list<T>::iterator forward_list<T>::begin()
{
	iterator begin;

	// Set iterator to the begining of the structure
	begin.m_node = m_head;
	
	return begin;
}

// Return an iterator past the last element
template<class T>
typename forward_list<T>::iterator forward_list<T>::end()
{
	iterator end;

	// Set iterator past the end
	end.m_node = nullptr;

	return end;
}

// Default constructor for iterators
template<class T>
forward_list<T>::iterator::iterator()
{
	m_node = nullptr;
}

// Copy constructor for iterators
template<class T>
forward_list<T>::iterator::iterator(const iterator & it)
{
	// Set the new iterator to point on the same value as it
	m_node = it.m_node;
}

// Iterator destructor
template<class T>
forward_list<T>::iterator::~iterator()
{
}

// Assigement operator for iterators
template<class T>
typename forward_list<T>::iterator & forward_list<T>::iterator::operator=(const iterator & it)
{
	// Set the this iterator to point on the same value as it
	m_node = it.m_node;

	// Return this iterator
	return *this;
}

// Comparason operator to determine if two iterators are the same
template<class T>
bool forward_list<T>::iterator::operator==(const iterator & it) const
{
	// True is they point on the same element
	return m_node == it.m_node;
}

// Comparason operator to determine if two iterators are different
template<class T>
bool forward_list<T>::iterator::operator!=(const iterator & it) const
{
	// True is they point on different element
	return m_node != it.m_node;
}

// Pre incrementation operator
template<class T>
typename forward_list<T>::iterator & forward_list<T>::iterator::operator++()
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
typename forward_list<T>::iterator forward_list<T>::iterator::operator++(int)
{
	// Create an iterator pointing on the current element that will become the previous element
	iterator* it = new iterator(*this);

	// If the iterator isn't passed the end
	if (m_node) {
		// Move iterator the next element
		m_node = m_node->next;
	}

	// Return an iterator pointing on the previous element
	return *it;
}

// Dereference operator
template<class T>
T & forward_list<T>::iterator::operator*() const
{
	// Return direct reference to the pointed element's data
	return m_node->data;
}

// Dereference operator
template<class T>
T * forward_list<T>::iterator::operator->() const
{
	// Return a pointer to the pointed element's data
	return &m_node->data;
}