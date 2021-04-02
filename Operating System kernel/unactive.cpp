/*
 * unactive.cpp
 *
 *  Created on: May 20, 2018
 *      Author: OS1
 */
#include"unactive.h"
#include"pcb.h"
#include"kernel.h"
int syncPrintf(const char* c,...);
Unactive::Unactive(): Thread(512,1) {}

 void Unactive::run(){
	while(1){
		
//	syncPrintf("idle");
	//for(int i=0;i<30000;i++)
		//for(int j=0;j<30000;j++);
	}
}

void Unactive::start(){
	    lock(); 
	    myPCB->myID=++Kernel::idd;
		myPCB->state=PCB::READY;
		myPCB->createStack();

		unlock();
}
