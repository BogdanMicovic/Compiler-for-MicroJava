/*
 * kernelev.cpp
 *
 *  Created on: May 16, 2018
 *      Author: OS1
 */



#include "kernel.h"
#include "kernelev.h"
#include "ivtentry.h"
#include "kernelsm.h"
int syncPrintf(const char *format, ...);
extern Thread *running;

KernelEv::KernelEv (IVTNo ivtNo) {
	if(IVTEntry::IVTTable[ivtNo]) {		
	this->glavna=Kernel::running->myThread;
	this->ivtNo=ivtNo;
	this->mySem = new KernelSem(0);
	IVTEntry::IVTTable[ivtNo]->eventList->put(this);
	}
}
KernelEv::~KernelEv () {
	//syncPrintf(" KernelEv destruktor ");
	IVTEntry::IVTTable[ivtNo]->eventList->remove(this);
	delete mySem;
}
void KernelEv::wait () { 
	if (Kernel::running->myThread!=glavna) return ;
	 mySem->wait(1);

}

void KernelEv::signal() {
	//syncPrintf("Usao u signal");
	if (mySem->val()==1) return;
	mySem->signalEveryone();
	//syncPrintf("Izasao iz signala");
}