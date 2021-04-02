/*
 * eventlis.h
 *
 *  Created on: May 16, 2018
 *      Author: OS1
 */



#ifndef EVENTLIS_H_
#define EVENTLIS_H_

class EventList{
	friend class KernelEv;
	struct Elem{
		KernelEv*  even;
		Elem* next;
		Elem(KernelEv* event,Elem* sled=0){
			even=event;
			next=sled;
		}
		~Elem();
	};
	Elem *head;
	int no;

	EventList (const EventList& EvQ) {}//zabrana kopiranja
	
public:
	EventList();
	~EventList(); 

	void put(KernelEv* e);
	void remove(KernelEv* e);
	void signal();
};


#endif
