// Alan Derrick
// C++ Fall 2010
// HW2 Queue
// File: Queue1.cpp

#include "stdafx.h"
#include <iostream>
using std::cout;
using std::endl;

#include "Queue.h"
#include "QueueItem.h"

// constructor
Queue::Queue()
{
    QueueItem* _pNext = _pHead = _pTail = 0;
    _itemCounter = 0;
} // end ctor

// destructor
Queue::~Queue()
{
    // in text Fig 9.12 this just does some couts, i think it's automatic
}   // end dtor

// add a new item to the Queue
void Queue::addItem(char *pData)
{
    // dynamically create and init a new QueueItem object
    QueueItem *pItem = new QueueItem(pData, ++_itemCounter);

    if ( 0 == _pHead )          // check for empty queue
        _pHead = _pTail = pItem;
    else
    {
        _pTail->setNext(pItem); // set pTail's item to point at the newest item (link it on the end of the queue)
        _pTail = pItem;         // set pTail to point to the newest item on the end
    }
    QueueItem* _pNext = 0;
}   // end function addItem

// removes the head item from the queue, FIFO
void Queue::removeItem()
{
    if ( _pTail == 0 && _pHead == 0 )
    {
        // empty body
    }
    else
    {
        QueueItem* _pItem = _pHead->getNext();  
        delete _pHead;                                
        _pHead = _pItem;
    }
    
}   // end function removeItem

// Print the entire Queue
void Queue::print()
{
    QueueItem* _pItem = _pHead;
    while ( _pItem != NULL )
    {
    cout << _pItem->getId() << endl;
    cout << _pItem->getData() << endl; 
    _pItem = _pItem->getNext();
    }
}   // end function print

void Queue::erase()
{
    while ( _pHead != NULL )
    {
        QueueItem* _pItem = _pHead->getNext();
        delete _pHead;
        _pHead = _pItem;
    }
}   // end function erase