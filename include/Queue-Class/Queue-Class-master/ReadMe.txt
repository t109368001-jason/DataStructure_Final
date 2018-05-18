Necessary skills: class construction, class composition, pointers and linked lists, heap memory management with C++ new/delete operators.
Description
Create a Queue class that implements a queue abstraction. A queue is a FIFO list (First In First Out queue). A simple example is waiting in line, where the first person in the line is the first served. New arrivals are added to the back of the line, the next person served is (removed) from the front of the line. 
The Queue class needs to implement the following operations: 
	• adding to the queue at one end (the tail) 
	• removing from the queue at the other end (the head) 
	• printing all items the queue (from head to tail) 
	• erasing all items in the queue (leaving the queue empty).
	• destructor to empty the queue before it's destroyed (to release all memory)
Additions and removals always occur at the opposite ends of the queue. 
You should create the following methods in your Queue class to implement the above operations 
	• addItem
	• removeItem
	• print
	• erase
Your Queue class must implement a linked list. Linked lists are implemented using individual items which contain a pointer to the next item in the list, as well as the information to be stored.
Your Queue implementation uses a companion QueueItem class to represent each element in the list. A QueueItem contains character string as the data value, a unique (among all QueueItems in a Queue) integer item identifier, and a pointer to the next QueueItem in the list. The following is the definition for the QueueItem class. 
