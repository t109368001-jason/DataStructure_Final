// Alan Derrick
// C++ Fall 2010
// HW2 Queue
// File: main.cpp

#include "stdafx.h"
#include <iostream>
using std::cout;
using std::endl;

#include "QueueItem.h"
#include "Queue.h"

int main()
{
    Queue myQueue;

    myQueue.removeItem(); 
    myQueue.addItem("red");
    myQueue.addItem("green");
    myQueue.addItem("blue");
    myQueue.addItem("orange");
    cout << "Printing out 4 items: red, green, blue, orange.\n" << endl;
    myQueue.print();            // print contents of queue (item ID and data)
   
    myQueue.removeItem();
    myQueue.removeItem();
    myQueue.addItem("brown");
    myQueue.addItem("tan");
    myQueue.addItem("purple");
    myQueue.addItem("lavendar");
    cout << "Printing: blue/orange/brown/tan/purple/lavendar.\n" << endl;
    myQueue.print(); // print contents of queue 
   
    myQueue.removeItem();
    myQueue.removeItem();
    myQueue.removeItem();
    myQueue.removeItem();
    cout << "Printing: purple & lavendar.\n" << endl;
    myQueue.print();
    
    myQueue.erase();

    myQueue.addItem("Blue-32!");
    myQueue.addItem("Blue-22!");
    myQueue.addItem("Hut-Hut!");
    cout << "Printing out a football hike cadence:\n" << endl;
    myQueue.print();

    myQueue.erase();
    cout << "Printing out the newly erased queue, should be empty:\n" << endl;
    myQueue.print();
    
	return 0;
}

