#include "List.h"

#pragma once
#include <utility>

template<class T>
list<T>::list()
	: m_head(nullptr), m_tail(nullptr)
{
	m_begin.m_node = nullptr;
	m_end.m_node = nullptr;

	m_rbegin.m_node = nullptr;
	m_rend.m_node = nullptr;
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
list<T>::iterator list<T>::begin()
{
	return iterator(m_begin);
}

template<class T>
list<T>::iterator list<T>::end()
{
	return iterator(m_end);
}

template<class T>
list<T>::backward_iterator list<T>::rbegin()
{
	return backward_iterator(m_rbegin);
}

template<class T>
list<T>::backward_iterator list<T>::rend()
{
	return backward_iterator(m_rend);
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
list<T>::iterator & list<T>::iterator::operator=(const iterator & it)
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
list<T>::iterator & list<T>::iterator::operator++()
{
	if (m_node) {
		m_node = m_node->next;
	}

	return *this
}

template<class T>
list<T>::iterator list<T>::iterator::operator++(int)
{
	iterator* it=new iterator(*this);

	if (m_node) {
		m_node = m_node->next;
	}

	return *it;
}

template<class T>
list<T>::iterator & list<T>::iterator::operator--()
{
	if (m_node) {
		m_node = m_node->previous;
	}

	return *this
}

template<class T>
list<T>::iterator list<T>::iterator::operator--(int)
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
	return *m_node
}

template<class T>
T * list<T>::iterator::operator->() const
{
	return m_node;
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
list<T>::backward_iterator & list<T>::backward_iterator::operator=(const backward_iterator & it)
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
list<T>::backward_iterator & list<T>::backward_iterator::operator++()
{
	if (m_node) {
		m_node = m_node.previous;
	}

	return *this;
}

template<class T>
list<T>::backward_iterator list<T>::backward_iterator::operator++(int)
{
	backward_iterator* it = new backward_iterator(*this);

	if (m_node) {
		m_node = m_node.previous;
	}

	return *it;
}

template<class T>
list<T>::backward_iterator & list<T>::backward_iterator::operator--()
{
	if (m_node) {
		m_node = m_node.next;
	}
}

template<class T>
list<T>::backward_iterator list<T>::backward_iterator::operator--(int)
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
	return *m_node;
}

template<class T>
T * list<T>::backward_iterator::operator->() const
{
	return m_node;
}