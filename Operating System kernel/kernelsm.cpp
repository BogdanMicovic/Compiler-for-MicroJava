/*
 * kernelsem.cpp
 *
 *  Created on: May 16, 2018
 *      Author: OS1
 *
*/


#include"kernelsm.h"
#include"kernel.h"
#include "SCHEDULE.h"
int syncPrintf(const char *format, ...);
KernelSem::KernelSem (int init){value=init;blockedQueue=new Blocked();}

KernelSem::~KernelSem(){
	lock();
	//syncPrintf(" KernelSem destruktror ");
	signalEveryone();
	delete blockedQueue;
	unlock();
}
int KernelSem::val () const{
	return value;
}


int syncPrintf(const char * c,...);
int KernelSem::wait (int toBlock){
lock();

if(toBlock!=0){
	//syncPrintf("toBlock!=0  ");
if(value<=0){ 
	//syncPrintf("value<=0  ");
value--;
 Kernel::running->state=PCB::BLOCKED;
 blockedQueue->put(Kernel::running);
 //syncPrintf("wait");
 unlock();
 Kernel::dispatch();
 return 1;
}
else{value--;unlock(); return 0;}

}
else{
    if(value<=0){unlock();return -1;}
	else{value--;unlock();return 0;}
}

}

void KernelSem::signal(){
	//syncPrintf("Usao u signal  ");
lock();
if(value<0){
	PCB* newThread=0;
	newThread=(PCB*)blockedQueue->get();
	if(newThread!=0){
	newThread->state=PCB::READY;
	Scheduler::put(newThread);
	//syncPrintf("Vratio sem  ");
	}
	value++;
}
else{
	//syncPrintf("Ne block  ");
	value++;
}
unlock();
}

void KernelSem::signalEveryone(){
lock();
	PCB *tek;
		while (tek=(PCB*)blockedQueue->get()) {		 //dohvata PCB i brise ga iz reda
			//tek->value=1;
			tek->state=PCB::READY;
			Scheduler::put(tek);
		}
		unlock();
}

