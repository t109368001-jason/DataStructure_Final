// Alan Derrick
// C++ Fall 2010
// HW2 Queue
// File: QueueItem.cpp

#include "stdafx.h"
#include <iostream>
using std::cout;
using std::endl;

#include "QueueItem.h"

#include <cstring>
using std::strncpy;
using std::strlen;

QueueItem::QueueItem( char *pData, int id)
    : _itemId(id)
{
    strncpy( _data, pData, strlen( pData ) +1 );
    _pNext = NULL;
}   // end QueItem constructor

void QueueItem::setNext( QueueItem *pItem )
{
    _pNext = pItem; // assign param to _pNext member
}   // end function setNext

QueueItem* QueueItem::getNext() const
{
    return _pNext;
}   // end function getNext

int QueueItem::getId() const
{
    return _itemId;
}   // end function getId

const char* QueueItem::getData() const
{
    return _data;
}   // end function getData()