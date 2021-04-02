/*
 * eventlist.cpp
 *
 *  Created on: May 16, 2018
 *      Author: OS1
 */

#include "eventlis.h"
#include "kernelev.h"
extern int syncPrintf(const char *format, ...);
EventList::Elem::~Elem(){delete even;}
EventList::EventList(){head=0;}//syncPrintf("IVTEntry Eventlist Konstruktor");}
EventList::~EventList() {
	Elem* prev,*tek=head;
	while(tek){
		prev=tek;
		tek=tek->next;
		delete prev;
	}
}
void EventList::signal() {
	Elem* tek=head;
	while(tek){
		tek->even->signal();
		tek=tek->next;

	}
}
void EventList::put(KernelEv* event) {
	Elem* novi=new Elem(event,head);
	head=novi;
}
void EventList::remove(KernelEv* event) {
	Elem* prev=0;
	Elem* tek=head;
	while(tek){
		if(tek->even==event) {
			if(prev) prev->next=tek->next;
			else head=tek->next;
			delete tek;
			return;
		}
		prev=tek;
		tek=tek->next;
	}
}




