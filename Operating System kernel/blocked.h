/*
 * queue.h
 *
 *  Created on: May 16, 2018
 *      Author: OS1
 */
#include "pcb.h"


#ifndef BLOCKED_H_
#define BLOCKED_H_

class PCB;
class Blocked{
public:
friend class Thread;
struct Elem{
	 volatile PCB* pcb;
	 Elem* next;

	Elem(volatile PCB* pcbq){
    pcb=pcbq;
    next=0;
  }
};
 Blocked();
 ~Blocked();
 void put(volatile PCB* pcb);
 volatile PCB* get();
 void remove_blocked_threads();
 int size();
 
 //void remove_sleeping_threads();
private:
  int length;
  Elem* head;
  Elem* last;

};



#endif /* BLOCKED_H_ */
