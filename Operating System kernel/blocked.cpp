/*
 * queue.cpp
 *
 *  Created on: May 16, 2018
 *      Author: OS1
 */
#include <stdlib.h>
#include "blocked.h"
#include"kernel.h"
#include"SCHEDULE.h"





Blocked::Blocked(){
	lock();
	head=0;
	length=0;
	last=0;
	unlock();

}
Blocked::~Blocked(){
	lock();
	Elem* stari;
	while(head){
		stari=head;
		head=head->next;
		delete stari;
	}
	unlock();
}


extern int syncPrintf(const char* c,...);

void Blocked::put(volatile PCB* pcb){
	lock();
	
	if(!head)
		head=last=new Elem(pcb);
	else{  
        last->next=new Elem(pcb);
        last=last->next;
	}
		
	
		 
	     

unlock();
}

volatile PCB* Blocked::get(){
	lock();
	Elem* tek;
	if(head==0){unlock();return 0;}
     tek=head;
     head=head->next;
     if(head==0)
     	last=0;
     volatile PCB* rez=tek->pcb;

     unlock();
     return rez;

}



 int Blocked::size(){return length;}


void Blocked::remove_blocked_threads(){   
 lock();
//syncPrintf("Brise iz reda");
 Elem* tek=head;
 while(tek){

 	
 	//for(long k=0;k<1000000;k++);
 	tek->pcb->state=PCB::READY;
 	Scheduler::put((PCB*)tek->pcb);
 	tek=tek->next;
 }
 head=last=0;
 length=0;

 //head=last=0;
 //length=0;
 
  // syncPrintf(" remove ");
	//for(long m=0;m<500000;m++);
 /*Elem* tek=head;
 Elem* pred=0;
 Elem* stari;
 while(tek){
tek->pcb->numberOfChildren--;
if(tek->pcb->numberOfChildren!=0){
	pred=tek;
	tek=tek->next;
}
else{

	stari=tek;
	tek=tek->next;
	if(!pred)
		head=tek;
	else pred->next=tek;
	stari->pcb->state=PCB::READY;
	Scheduler::put((PCB*)stari->pcb);
	//dodata linija
	//stari=0;
}

 }
 	*/
 /*if(head==0){unlock();return;} 

 while(head!=0){
 	head->pcb->numberOfChildren--;
 	if(head->pcb->numberOfChildren==0) {
 head->pcb->state=PCB::READY;
Scheduler::put((PCB*)head->pcb);
}
  head=head->next;
 }*/
unlock();
}


/*void Blocked::remove_sleeping_threads(){
lock();

 Elem* tek=head;
 Elem* pred=0;
 Elem* stari;
 while(tek){
tek->pcb->timePassedSleep++;//povecavamo vreme spavanja
if(curr->pcb->timePassedSleep<curr->pcb->timeSleep){
	pred=tek;
	tek=tek->next;
}
else{
	stari=tek;
	tek=tek->next;
	if(!pred)
		head=tek;
	else pred->next=tek;
	stari->pcb->state=PCB::READY;
	stari->pcb->timePassedSleep=0;
	curr->pcb->timeSleep=0;
  Scheduler::put((PCB*)stari->pcb);
	
	//dodata linija
	stari=0;
}
 }
 unlock();

}
*/

