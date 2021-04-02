/*
 * queue.cpp
 *
 *  Created on: May 16, 2018
 *      Author: OS1
 */
#include <stdlib.h>
#include "queue.h"
#include"kernel.h"
#include"SCHEDULE.h"

int syncPrintf(const char *format, ...);


Queue::Queue(){
	lock();
	head=0;
	last=0;
	length=0;
	unlock();

}
Queue::~Queue(){
	lock();
	Elem* stari;
	while(head){
		stari=head;
		head=head->next;
		delete stari;
	}
	unlock();
}


void Queue::put(volatile PCB* pcb){
	//syncPrintf("PUT ZA SLEEP");
	lock();
	
	if(!head)
		last=head=new Elem(pcb);
	else{
		last->next=new Elem(pcb);
		last=last->next;
	     }

unlock();

}

volatile PCB* Queue::get(){// Nije dobro napisana metoda 
	
 lock();
	Elem* tek=0;
	if(head==0){unlock();return 0;}
     tek=head;
     head=head->next;
     if(head==0)
     	last=0;
     unlock();
     return tek->pcb;	
}

void Queue::remove_sleeping_threads(){

//syncPrintf("remove_sleeping_threads");


lock();

 Elem* tek=head;
 Elem* pred=0;
 Elem* stari;
 while(tek){
tek->pcb->timePassedSleep++;//povecavamo vreme spavanja
if((tek->pcb->timePassedSleep)<(tek->pcb->timeSleep)){
	pred=tek;
	tek=tek->next;
}
else{ 
	//syncPrintf("Usao u else");
	stari=tek;
	tek=tek->next;
	if(!pred)head=tek;
	else pred->next=tek;
	stari->pcb->state=PCB::READY;
	stari->pcb->timePassedSleep=0;
	stari->pcb->timeSleep=0;
  Scheduler::put((PCB*)stari->pcb);
	
	//dodata linija
	//stari=0;
}
 }
 unlock();



	/*Elem* curr=head;
    Elem* prev=0;
 if(curr==0) return ;
while(curr!=0){
	curr->pcb->timePassedSleep++;//povecavamo vreme spavanja
	if(curr->pcb->timePassedSleep>=curr->pcb->timeSleep){
      curr->pcb->state=PCB::READY;
	curr->pcb->timePassedSleep=0;
	curr->pcb->timeSleep=0;
  Scheduler::put((PCB*)curr->pcb);		
 
		if(prev!=0){
			if(curr->next!=0){
				prev->next=curr->next;
				curr->next->prev=prev;
				curr=curr->next;//dodata
			}
			else{
				prev->next=0;
				curr=0;//dodata
				last=prev;
			}
		}
		else{
			if(curr->next!=0)
				curr=head=curr->next;//dodata(izmenjena) bila je: head=curr->next

			else
				curr=head=last=0;//dodato curr bilo je head=last=0
		}
		//** Videti da li je mozda potrebno dodati pomocne promenljive i val kao sto je vec radjeno jer Scheduler mozda izmeni curr 
	/*curr->pcb->state=PCB::READY;
	curr->pcb->timePassedSleep=0;
	curr->pcb->timeSleep=0;
  Scheduler::put((PCB*)curr->pcb); 
	}
	else{
		prev=curr;
		curr=curr->next;
	}
	//prev=curr;
	//curr=curr->next;
  
  
}
*/
}


 int Queue::size(){return length;}








