#include "exception.h"

/////////////////////////////////////////////////////////////////////////////
/// @file list.hpp
/// @author Doug Kelly - CS153 Sec. B
/// @brief Templated linked-list class
/////////////////////////////////////////////////////////////////////////////

template <class generic> List<generic>::List()
{
	m_size=0;
	m_front=NULL;
	m_back=NULL;
}

template <class generic> List<generic>::~List()
{
	clear();
}

template <class generic> void List<generic>::push_front(generic x)
{
	// Store the current front of list in a temporary pointer,
	// create a new Node for the new front, and link to the
	// rest of the list.
	Node<generic> *tmp = m_front;
	m_front = new Node<generic>;
	m_front->data = x;
	m_front->forward = tmp;
	if(m_back == NULL)
	{
		// No other items in list; back is front.
		m_back = m_front;
	}
	m_front->backward = NULL;
	if(tmp != NULL)
	{
		// Re-link the old front with the new front.
		tmp->backward = m_front;
	}
	m_size++;
	return;
}

template <class generic> void List<generic>::push_back(generic x)
{
	// Store the current end of list in a temporary pointer,
	// create a new Node for the new end, and link to the
	// rest of the list.
	Node<generic> *tmp = m_back;
	m_back = new Node<generic>;
	m_back->data = x;
	m_back->backward = tmp;
	if(m_front == NULL)
	{
		// No other items in list; back is front.
		m_front = m_back;
	}
	m_back->forward = NULL;
	if(tmp != NULL)
	{
		// Re-link new back with old back.
		tmp->forward = m_back;
	}
	m_size++;
	return;
}

template <class generic> void List<generic>::pop_front()
{
	if(m_front == NULL)
	{
		// List is empty; throw an exception.
		throw(Exception(1, "No element in list; unable to pop."));
	}

	// Store the pointer of the second element in the list in
	// a temporary pointer, delete the first element, and make
	// the second element the new front of the list.
	Node<generic> *tmp = m_front->forward;
	delete m_front;
	m_front = tmp;
	if(m_front != NULL)
	{
		// Set m_front->backward so we don't walk off the end.
		m_front->backward = NULL;
	}
	else
	{
		// No other elements in the list; back is NULL, too
		m_back = NULL;
	}
	m_size--;
	return;
}

template <class generic> void List<generic>::pop_back()
{
	if(m_back == NULL)
	{
		// List is empty; throw an exception.
		throw(Exception(1, "No element in list; unable to pop."));
	}

	// Store the pointer of the next to last element in the list in
	// a temporary pointer, delete the last element, and make
	// the next to last element the new back of the list.
	Node<generic> *tmp = m_back->backward;
	delete m_back;
	m_back = tmp;
	if(m_back != NULL)
	{
		// Reset m_back->forward to NULL, so we don't walk off the end.
		m_back->forward = NULL;
	}
	else
	{
		// No other items in list; reset m_front.
		m_front = NULL;
	}
	m_size--;
	return;
}

template <class generic> void List<generic>::remove(generic x)
{
	Node<generic> *ptr = m_front;
	if(ptr == NULL)
	{
		// Empty linked-list, throw an exception.
		throw(Exception(2, "Attempt to remove from an empty list."));
	}

	if(ptr->data == x)
	{
		// Element is first in list.
		// Special case, since this is dealing with m_front
		Node<generic> *tmp = m_front->forward;
		delete m_front;
		m_front = tmp;
		if(m_front != NULL)
		{
			m_front->backward = NULL;
		}
		m_size--;
		return;
	}

	while(ptr->forward != NULL)
	{
		// Stepping through every element in list
		if(ptr->forward->data == x)
		{
			// Delete this specific element, and reattach the rest
			// of the list.
			Node<generic> *tmp = ptr->forward->forward;
			delete ptr->forward;
			ptr->forward = tmp;
			if(tmp != NULL)
			{
				tmp->backward = ptr;
			}
			m_size--;
			return;
		}
		ptr = ptr->forward;
	}

	return;
}

template <class generic> generic &List<generic>::front()
{
	if(m_front == NULL)
	{
		// No such element exists, throw an exception
		throw(Exception(3, "Attempt to access front of empty list."));
	}

	return m_front->data;
}

template <class generic> generic &List<generic>::back()
{
	if(m_back == NULL)
	{
		// No such element exists, throw an exception
		throw(Exception(4, "Attempt to access back of empty list."));
	}

	return m_back->data;
}

template <class generic> void List<generic>::clear()
{
	while(m_front != NULL)
	{
		// Continuously pop from the front of the list until the
		// list is empty.
		pop_front();
	}
	return;
}

template <class generic> unsigned int List<generic>::size()
{
	return m_size;
}

template <class generic> bool List<generic>::empty()
{
	// Self explanatory.
	if(m_front == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
