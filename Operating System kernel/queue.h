/*
 * queue.h
 *
 *  Created on: May 16, 2018
 *      Author: OS1
 */
#include "pcb.h"


#ifndef QUEUE_H_
#define QUEUE_H_
class PCB;
class Queue{
public:
friend class Thread;
struct Elem{
	volatile PCB* pcb;
    Elem* next;
	 //*** MOZDA SE KONSTRUKTOR OVE STRUTURE MORA DEFINISATI U CPP FAJLU JER SE MOZE DOGODITI PREKID TOKOM NJEGOVOG IZVRSAVANJA MADA SU SANSE VRLO MALE
	Elem(volatile PCB* pcbq){pcb=pcbq;next=0;}
  
};
Queue();
~Queue();

 void put(volatile PCB* pcb);
 volatile PCB* get();
 void remove_sleeping_threads();
  int size();
 
private:
  int length;
  Elem* head;
  Elem* last;
};



#endif /* QUEUE_H_ */
