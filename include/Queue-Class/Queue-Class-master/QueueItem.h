// Alan Derrick
// C++ Fall 2010
// HW2 Queue
// File: QueueItem.h

class Queue;        // forward class description

#ifndef QUEUEITEM_H
#define QUEUEITEM_H

class QueueItem 
{
public:
    QueueItem( char *pData, int id);    // ctor
    void setNext(QueueItem *pItem);
    QueueItem* getNext() const;
    int getId() const;
    const char* getData() const;
private:
    char _data[30];
    const int _itemId;                  // unique id for item in queue
    QueueItem* _pNext;                  // next item in queue
};   // end definition class QueueItem

#endif