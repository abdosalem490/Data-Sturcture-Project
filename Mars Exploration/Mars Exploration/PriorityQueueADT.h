#pragma once
template<class T , class M>
class PriorityQueueADT
{
public:
  
    virtual bool isEmpty() const = 0;

  
    virtual bool enqueue(const Pair<T, M>& temp) = 0;


    virtual bool dequeue(Pair<T, M>& FrontEntry) = 0;

    
    virtual bool peek(Pair<T, M>& FrontEntry) const = 0;

    virtual ~PriorityQueueADT() { }
};
