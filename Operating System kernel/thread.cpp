/*
 * thread.cpp
 *
 *  Created on: May 15, 2018
 *      Author: OS1
 */

#include"thread.h"
#include<stdlib.h>
#include<dos.h>
#include"kernel.h"
#include"pcb.h"
#include"SCHEDULE.h"

int syncPrintf(const char *format, ...);
 Thread::Thread (StackSize stackSize , Time timeSlice){
	lock();
	this->myPCB=new PCB(this,  stackSize, (LongTime) timeSlice);
    
	//*** Videti da li mora da se castuje defautTimeSlice u LongTime u konstruktoru ovde
	unlock();
}

Thread::~Thread(){
	lock();
        this->waitToComplete();
		delete myPCB;
		unlock();
}

void Thread::start(){
	lock();
    this->myPCB->myID=++Kernel::idd;
	this->myPCB->state=PCB::READY;
	this->myPCB->createStack();

	Scheduler::put(this->myPCB);

	unlock();

}

void Thread::sleep(Time timeToSleep){
lock();
Kernel::running->timeSleep=(LongTime)timeToSleep;
Kernel::running->state=PCB::BLOCKED;
Kernel::blockedQueue->put(Kernel::running);
Kernel::dispatch();
unlock();

}

void Thread::waitToComplete(){
lock();
        // for(long p=0;p<500000;p++);
         //syncPrintf("Blokira se");
   
	if (myPCB->state == PCB::OVER || myPCB->state==PCB::NEW) { unlock(); return; } //ne sme da se ceka  nit koja se zavrsila
		if (myPCB == (PCB*)Kernel::running) { unlock(); return; } //ne moze da ceka na samu sebe
		if (this == Kernel::starting) { unlock(); return; } //ne moze da se ceka starting nit
		if (this == Kernel::unactive) { unlock(); return; } //ne moze da se ceka unactive nit jer se ona beskonacno dugo izvrsava
	// Mozda treba izbaciti ovu liniju jer se sve moze raditi sa this->myPCB PCB* newPCB=this->myPCB;
	//Kernel::running->numberOfChildren++;
   
   
	Kernel::running->state=PCB::BLOCKED;
	this->myPCB->WaitingForMe->put((PCB*)Kernel::running);

     //Isto uraditi i ovde direktno sa myPCB newPCB->state=PCB::READY;
	unlock();
    Kernel::dispatch();
}

void dispatch(){

	Kernel::dispatch();
}
