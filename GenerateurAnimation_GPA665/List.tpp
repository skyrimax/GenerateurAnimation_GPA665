#include "List.h"

#pragma once
#include <utility>

template<class T>
list<T>::list()
	: m_head(nullptr), m_tail(nullptr)
{
}

template<class T>
list<T>::list(const list<T>& x)
{
	Node* tempNode=x.m_head;
	Node* newNode;
	Node* previousNode=nullptr;

	while (tempNode != nullptr) {
		newNode = new Node;
		newNode->next = nullptr;
		newNode->previous = previousNode;

		if (previousNode) {
			previousNode->next = newNode;
		}
		else {
			m_head = newNode;
		}

		newNode->data = tempNode->data;

		tempNode = tempNode->next;
	}

	m_tail = newNode;
}

template<class T>
list<T>::list(list<T>&& x)
{
	m_head = x.m_head;
	m_tail = x.m_tail;

	x.m_head = nullptr;
	x.m_tail = nullptr;
}

template<class T>
list<T>::~list()
{
	Node* tempNode;

	while (m_head) {
		tempNode = m_head;
		m_head = m_head->next;
		delete tempNode;
	}
}

template<class T>
list<T>& list<T>::operator=(const list<T>& x)
{
	clear();

	Node* tempNode = x.m_head;
	Node* newNode;
	Node* previousNode = nullptr;

	while (tempNode != nullptr) {
		newNode = new Node;
		newNode->next = nullptr;
		newNode->previous = previousNode;

		if (previousNode) {
			previousNode->next = newNode;
		}
		else {
			m_head = newNode;
		}

		newNode->data = tempNode->data;
	}

	m_tail = newNode;

	return *this;
}

template<class T>
list<T>& list<T>::operator=(list<T>&& x)
{
	clear();

	m_head = x.m_head;
	m_tail = x.m_tail;

	x.m_head = nullptr;
	x.m_tail = nullptr;

	return *this;
}

template<class T>
bool list<T>::empty()
{
	return m_head == nullptr;
}

template<class T>
size_t list<T>::size()
{
	size_t i = 0;
	Node* tempNode = m_head;

	while (tempNode)
	{
		tempNode = tempNode->next;

		i++;
	}

	return i;
}

template<class T>
T & list<T>::front()
{
	return *m_head;
}

template<class T>
const T & list<T>::front() const
{
	return *m_head;
}

template<class T>
T & list<T>::back()
{
	return *m_end;
}

template<class T>
const T & list<T>::back() const
{
	return *m_end;
}

template<class T>
void list<T>::push_front(const T & val)
{
	Node* newNode = new Node;

	newNode->next = m_head;
	newNode->previous = nullptr;

	m_head->previous = newNode;

	m_head = newNode;

	if (!m_tail) {
		m_tail = newNode;
	}
	else {
		m_head->previous = newNode;
	}

	newNode->data = val;
}

template<class T>
void list<T>::push_front(T && val)
{
	Node* newNode = new Node;

	newNode->next = m_head;
	newNode->previous = nullptr;

	if (!m_head) {
		m_tail = newNode;
	}
	else {
		m_head->previous = newNode;
	}

	m_head = newNode;

	newNode->data = std::move(val);
}

template<class T>
void list<T>::pop_front()
{
	if (m_head) {
		Node* tempNode = m_head;
		m_head = tempNode->next;

		if (!m_head) {
			m_tail = nullptr;
		}
		else {
			m_head->previous = nullptr;
		}

		delete tempNode;
	}
}

template<class T>
void list<T>::push_back(const T & val)
{
	Node* newNode = new Node;

	newNode->next = nullptr;
	newNode->previous = m_tail;

	if (!m_tail) {
		m_head = newNode;
	}
	else {
		m_tail->next = newNode;
	}

	m_tail = newNode;

	newNode->data = val;
}

template<class T>
void list<T>::push_back(T && val)
{
	Node* newNode = new Node;

	newNode->next = nullptr;
	newNode->previous = m_tail;

	if (!m_tail) {
		m_head = newNode;
	}
	else {
		m_tail->next = newNode;
	}

	m_tail = newNode;

	newNode->data = std::move(val);
}

template<class T>
void list<T>::pop_back()
{
	if (m_head) {
		Node* tempNode = m_tail;
		m_tail = tempNode->previous;

		if (!m_tail) {
			m_head = nullptr;
		}
		else {
			m_tail->next = nullptr;
		}

		delete tempNode;
	}
}

template<class T>
void list<T>::insert_after(size_t position, const T & val)
{
	size_t size = size();

	if (position < size - 1) {
		Node* posNode = m_head;
		Node* newNode = new Node;

		for (int i = 0; i < position; i++) {
			posNode = posNode->next;
		}

		newNode->next = posNode->next;
		newNode->previous = posNode;

		posNode->next->previous = newNode;
		posNode->next = newNode;

		newNode->data = val;
	}
	else if (position == size - 1) {
		push_back(val);
	}
}

template<class T>
void list<T>::insert_after(size_t position, T && val)
{
	size_t size = size();

	if (position < size - 1) {
		Node* posNode = m_head;
		Node* newNode = new Node;

		for (int i = 0; i < position; i++) {
			posNode = posNode->next;
		}

		newNode->next = posNode->next;
		newNode->previous = posNode;

		posNode->next->previous = newNode;
		posNode->next = newNode;

		newNode->data = std::move(val);
	}
	else if (position == size - 1) {
		push_back(val);
	}
}

template<class T>
void list<T>::erase_after(size_t position)
{
	size_t size = size();

	if (position < size - 1) {
		Node* posNode = m_head;

		for (int i = 0; i < position; i++) {
			posNode = posNode->next;
		}

		Node* nodeToDelete=posNode->next;

		posNode->next = nodeToDelete->next;
		nodeToDelete->next->previous = posNode;

		delete nodeToDelete;
	}
	else if (position == size - 1) {
		pop_back();
	}
}

template<class T>
void list<T>::clear()
{
	Node* tempNode;

	while (m_head) {
		tempNode = m_head;
		m_head = m_head->next;
		delete tempNode;
	}

	m_tail = nullptr;
}

template<class T>
typename list<T>::iterator list<T>::begin()
{
	iterator begin;

	begin.m_node = m_head;

	return begin;
}

template<class T>
typename list<T>::iterator list<T>::end()
{
	iterator end;

	end.m_node = nullptr;

	return end;
}

template<class T>
typename list<T>::backward_iterator list<T>::rbegin()
{
	backward_iterator rbegin;

	rbegin.m_node = m_tail;

	return rbegin;
}

template<class T>
typename list<T>::backward_iterator list<T>::rend()
{
	backward_iterator rend;

	rend.m_node = nullptr;
	
	return rend;
}

template<class T>
list<T>::iterator::iterator()
{
	m_node = nullptr;
}

template<class T>
list<T>::iterator::iterator(const iterator& it)
{
	m_node = it.m_node;
}

template<class T>
list<T>::iterator::~iterator()
{
}

template<class T>
typename list<T>::iterator & list<T>::iterator::operator=(const iterator & it)
{
	m_node = it.m_node;

	return *this;
}

template<class T>
bool list<T>::iterator::operator==(const iterator & it) const
{
	return m_node == it.m_node;
}

template<class T>
bool list<T>::iterator::operator!=(const iterator & it) const
{
	return m_node != it.m_node;
}

template<class T>
typename list<T>::iterator & list<T>::iterator::operator++()
{
	if (m_node) {
		m_node = m_node->next;
	}

	return *this
}

template<class T>
typename list<T>::iterator list<T>::iterator::operator++(int)
{
	iterator* it=new iterator(*this);

	if (m_node) {
		m_node = m_node->next;
	}

	return *it;
}

template<class T>
typename list<T>::iterator & list<T>::iterator::operator--()
{
	if (m_node) {
		m_node = m_node->previous;
	}

	return *this
}

template<class T>
typename list<T>::iterator list<T>::iterator::operator--(int)
{
	iterator* it=new iterator(*this);

	if (m_node) {
		m_node = m_node->previous;
	}

	return it;
}

template<class T>
T & list<T>::iterator::operator*() const
{
	return m_node->data;
}

template<class T>
T * list<T>::iterator::operator->() const
{
	return &m_node->data;
}

template<class T>
inline list<T>::backward_iterator::backward_iterator()
{
	m_node = nullptr;
}

template<class T>
list<T>::backward_iterator::backward_iterator(const backward_iterator & it)
{
	m_node = it.m_node;
}

template<class T>
list<T>::backward_iterator::~backward_iterator()
{
}

template<class T>
typename list<T>::backward_iterator & list<T>::backward_iterator::operator=(const backward_iterator & it)
{
	m_node = it.m_node;

	return *this;
}

template<class T>
bool list<T>::backward_iterator::operator==(const backward_iterator & it) const
{
	return m_node == it.m_node;
}

template<class T>
bool list<T>::backward_iterator::operator!=(const backward_iterator & it) const
{
	return m_node != it.m_node;
}

template<class T>
typename list<T>::backward_iterator & list<T>::backward_iterator::operator++()
{
	if (m_node) {
		m_node = m_node.previous;
	}

	return *this;
}

template<class T>
typename list<T>::backward_iterator list<T>::backward_iterator::operator++(int)
{
	backward_iterator* it = new backward_iterator(*this);

	if (m_node) {
		m_node = m_node->previous;
	}

	return *it;
}

template<class T>
typename list<T>::backward_iterator & list<T>::backward_iterator::operator--()
{
	if (m_node) {
		m_node = m_node.next;
	}
}

template<class T>
typename list<T>::backward_iterator list<T>::backward_iterator::operator--(int)
{
	backward_iterator* it = new backward_iterator(*this);

	if (m_node) {
		m_node = m_node.next;
	}

	return *it;
}

template<class T>
T & list<T>::backward_iterator::operator*() const
{
	return m_node->data;
}

template<class T>
T * list<T>::backward_iterator::operator->() const
{
	return &m_node->data;
}