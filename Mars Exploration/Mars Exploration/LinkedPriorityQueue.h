#pragma once
using namespace std;
#include "Node.h"
#include "Pair.h"
#include"PriorityQueueADT.h"
template <class T, class M>
class LinkedpriorityQueue :public PriorityQueueADT <T , M>
{
private:
	Node<Pair<T, M>>* Head;
public:
	LinkedpriorityQueue();
	bool isEmpty() const;
	bool enqueue(const Pair<T, M>& temp);
	bool dequeue(Pair<T, M>& frntEntry);
	bool peek(Pair<T, M>& frntEntry)  const;
	~LinkedpriorityQueue();
	LinkedpriorityQueue(const LinkedpriorityQueue<T, M>& LQ);
	bool isFull();
};

template<class T, class M>
LinkedpriorityQueue<T, M>::LinkedpriorityQueue()
{
	Head = nullptr;
}

template<class T, class M>
bool LinkedpriorityQueue<T, M>::isEmpty() const
{
	return (Head == nullptr);
}

template<class T, class M>
bool LinkedpriorityQueue<T, M>::enqueue(const Pair<T, M>& temp)
{
	if (!isFull())
	{
		Node <Pair<T, M>>* s = new Node<Pair<T, M>>(temp);
		if (!Head)
		{
			Head = s;
			return true;
		}
		Node<Pair<T, M>>* p2 = Head;
		Node<Pair<T, M>>* p1 = Head->getNext();
		if (Head->getItem().getPriority() == temp.getPriority() && Head->getNext()->getItem().getPriority() != temp.getPriority())
		{
			s->setNext(p1);
			p2->setNext(s);
			s = nullptr;
			return true;
		}
		else if (Head->getItem().getPriority() < temp.getPriority())
		{
			s->setNext(Head);
			Head = s;
			s = nullptr;
			return true;
		}
		else
		{
			while (p1 != nullptr && p1->getItem().getPriority() > temp.getPriority())
			{
				p2 = p1;
				p1 = p1->getNext();
			}
			p2->setNext(s);
			s->setNext(p1);
			s = nullptr;
			return true;
		}
	}
	return false;
}

template<class T, class M>
bool LinkedpriorityQueue<T, M>::dequeue(Pair<T, M>& frntEntry)
{
	if (isEmpty())
		return false;

	Node<Pair<T, M>>* nodeToDeletePtr = Head;
	frntEntry = Head->getItem();
	Head = Head->getNext();
	// Queue is not empty; remove front


	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;

	return true;
}

template<class T, class M>
bool LinkedpriorityQueue<T, M>::peek(Pair<T, M>& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = Head->getItem();
	return true;
}

template<class T, class M>
LinkedpriorityQueue<T, M>::~LinkedpriorityQueue()
{
	Pair<T, M> temp;
	while (dequeue(temp));
}

template<class T, class M>
LinkedpriorityQueue<T, M>::LinkedpriorityQueue(const LinkedpriorityQueue<T, M>& LQ)
{
	Node<Pair<T, M>>* NodePtr = LQ.frontPtr;
	Node<Pair<T, M>>* backPtr = Head;
	if (!NodePtr) //LQ is empty
	{
		Head = nullptr;
		return;
	}

	//insert the first node
	Node<Pair<T, M>>* ptr = new Node<Pair<T, M>>(NodePtr->getItem());
	Head = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node<Pair<T, M>>* ptr = new Node<Pair<T, M>>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}

template<class T, class M>
bool LinkedpriorityQueue<T, M>::isFull()
{
	Node<Pair<T, M>>* t = new Node<Pair<T, M>>();
	if (t)
	{
		return true;
	}
	return false;
}
