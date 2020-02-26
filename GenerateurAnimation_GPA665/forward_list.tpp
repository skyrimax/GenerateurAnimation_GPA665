#include "forward_list.h"

#pragma once
#include <utility>

template<class T>
forward_list<T>::forward_list()
	: m_head(nullptr), m_tail(nullptr)
{
	m_begin.m_node = m_head;
	m_begin.m_node = nullptr;
}

template<class T>
forward_list<T>::~forward_list()
{
	Node* tempNode;

	while (m_head)	{
		tempNode = m_head;
		m_head = m_head->next;
		delete tempNode;
	}
}

template<class T>
bool forward_list<T>::empty()
{
	return m_head==nullptr;
}

template<class T>
size_t forward_list<T>::size()
{
	size_t i=0;
	Node* tempNode = m_head;

	while (tempNode)
	{
		tempNode = tempNode->next;

		i++;
	}

	return i;
}

template<class T>
T & forward_list<T>::front()
{
	return *m_head;
}

template<class T>
const T & forward_list<T>::front() const
{
	return *m_head;
}

template<class T>
void forward_list<T>::push_front(const T & val)
{
	Node* newNode = new Node;

	newNode->next = m_head;
	m_head = newNode;

	if (!m_tail) {
		m_tail = newNode;
	}

	newNode->data = val;
}

template<class T>
void forward_list<T>::push_front(T && val)
{
	Node* newNode = new Node;

	newNode->next = m_head;
	m_head = newNode;

	if (!m_tail) {
		m_tail = newNode;
	}

	newNode->data = std::move(val);
}

template<class T>
void forward_list<T>::pop_front()
{
	if (m_head) {
		Node* tempNode = m_head;
		m_head = tempNode->next;

		if (!m_head) {
			m_tail = nullptr;
		}

		delete tempNode;
	}
}

template<class T>
void forward_list<T>::insert_after(size_t position, const T & val)
{
	size_t size = size();

	if (position < size-1) {
		Node* posNode = m_head;
		Node* newNode = new Node;

		for (int i = 0; i < position; i++) {
			posNode = posNode->next;
		}

		newNode->next = posNode->next;
		posNode->next = newNode;

		newNode->data = val;
	}
	else if (position == size - 1) {
		push_back(val);
	}
}

template<class T>
void forward_list<T>::insert_after(size_t position, T && val)
{
	size_t size = size();

	if (position < size - 1) {
		Node* posNode = m_head;
		Node* tempNode = new Node;

		for (int i = 0; i < position; i++) {
			posNode = posNode->next;
		}

		tempNode->next = posNode->next;
		posNode->next = tempNode;

		tempNode->data = std::move(val);
	}
	else if (position == size - 1) {
		push_back(val);
	}
}

template<class T>
void forward_list<T>::erase_after(size_t position)
{
	size_t size = size();

	if (position < size - 1) {
		Node* posNode = m_head;

		for (int i = 0; i < position; i++) {
			posNode = posNode->next;
		}

		Node* nodeToDelete = posNode->next;

		posNode->next = posNode->next->next;

		delete nodeToDelete;
	}
	else if (position == size - 1) {
		pop_back();
	}
}

template<class T>
void forward_list<T>::push_back(const T & val)
{
	Node* newNode = new Node;

	newNode->next = nullptr;

	if (m_tail) {
		m_tail->next = newNode;
		m_tail = newNode;
	}
	else {
		m_tail = newNode;
		m_head = newNode;
	}

	newNode->data = val;
}

template<class T>
void forward_list<T>::push_back(T && val)
{
	Node* newNode = new Node;

	newNode->next = nullptr;

	if (m_tail) {
		m_tail->next = newNode;
		m_tail = newNode;
	}
	else {
		m_tail = newNode;
		m_head = newNode;
	}

	newNode->data = std::move(val);
}

template<class T>
void forward_list<T>::pop_back()
{
	if (m_head) {
		Node* tempNode = m_tail;

		if (m_head == m_tail) {
			m_head = nullptr;
			m_tail = nullptr;
		}
		else {
			Node* secondToLast = m_head;

			while (secondToLast->next != tempNode) {
				secondToLast = secondToLast->next;
			}

			m_tail = secondToLast;
			secondToLast->next = nullptr;
		}

		delete tempNode;
	}
}

template<class T>
void forward_list<T>::clear()
{
	Node* tempNode;

	while (m_head) {
		tempNode = m_head;
		m_head = m_head->next;
		delete tempNode;
	}
}

template<class T>
typename forward_list<T>::iterator forward_list<T>::begin()
{
	iterator* begin = new iterator;

	begin->m_node = m_head;
	
	return *begin;
}

template<class T>
typename forward_list<T>::iterator forward_list<T>::end()
{
	iterator* end = new iterator();

	end->m_node = nullptr;

	return *end;
}

template<class T>
forward_list<T>::iterator::iterator()
{
	m_node = nullptr;
}

template<class T>
forward_list<T>::iterator::iterator(const iterator & it)
{
	m_node = it.m_node;
}

template<class T>
forward_list<T>::iterator::~iterator()
{
}

template<class T>
typename forward_list<T>::iterator & forward_list<T>::iterator::operator=(const iterator & it)
{
	m_node = it.m_node;

	return *this;
}

template<class T>
bool forward_list<T>::iterator::operator==(const iterator & it) const
{
	return m_node == it.m_node;
}

template<class T>
bool forward_list<T>::iterator::operator!=(const iterator & it) const
{
	return m_node != it.m_node;
}

template<class T>
typename forward_list<T>::iterator & forward_list<T>::iterator::operator++()
{
	if (m_node) {
		m_node = m_node->next;
	}

	return *this;
}

template<class T>
typename forward_list<T>::iterator forward_list<T>::iterator::operator++(int)
{
	iterator* it = new iterator(*this);

	if (m_node) {
		m_node = m_node->next;
	}

	return *it;
}

template<class T>
T & forward_list<T>::iterator::operator*() const
{
	return m_node->data;
}

template<class T>
T * forward_list<T>::iterator::operator->() const
{
	return &m_node->data;
}