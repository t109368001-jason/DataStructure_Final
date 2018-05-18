// Alan Derrick
// C++ Fall 2010
// HW2 Queue
// File: Queue1.h

class QueueItem;    // forward class description

#ifndef QUEUE_H
#define QUEUE_H

class Queue 
{
public:
    Queue();                    // ctor inits a new empty Queue
    ~Queue();                   // dtor erases any remaining QueueItems
    void addItem(char *pData);
    void removeItem();
    void print();
    void erase();
private:
    QueueItem *_pHead;      // always points to first QueueItem in the list
    QueueItem *_pTail;      // always points to last QueueItem in the list
    int _itemCounter;       // always increasing for a unique id to assign to each new QueueItem
};   // end definition class Queue

#endif