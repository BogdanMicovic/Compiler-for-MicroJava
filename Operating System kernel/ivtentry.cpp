/*
 * ivtentry.cpp
 *
 *  Created on: May 16, 2018
 *      Author: OS1
 */
#include <dos.h>
#include "IVTEntry.h"
#include "kernel.h"


IVTEntry* IVTEntry::IVTTable[256];
extern int syncPrintf(const char *format, ...);
IVTEntry::IVTEntry(int ivtNo,InterruptRoutine newIR) {
   //syncPrintf("IVTEntry Konstruktor pocetak");
	eventList = new EventList();
	//unsigned newSEG = FP_SEG(newIR), newOFF = FP_OFF(newIR), oldSEG, oldOFF;
	//unsigned entry=4*ivtNo;
	this->ivtNo=ivtNo;
	IVTTable[ivtNo]=this;
	lock();
		oldIR = getvect(ivtNo);
		setvect(ivtNo, newIR);
		/*asm {
			push bx
			push ax
			push es

			mov ax, 0
			mov es, ax
			mov bx, word ptr entry		
			
			cli

			mov ax, word ptr es:bx
			mov word ptr oldOFF, ax		// cuva ofset stare prekidne rutine
			mov ax, word ptr es:bx+2
			mov word ptr oldSEG, ax		// cuva segment stare prekidne rutine

			mov ax, word ptr newOFF
			mov word ptr es:bx, ax
			mov ax, word ptr newSEG
			mov word ptr es:bx+2, ax

			sti;

			pop es
			pop ax
			pop bx
		}*/
		//syncPrintf("IVTEntry Konstruktor kraj");
	unlock();

	//oldIR=(InterruptRoutine)MK_FP(oldSEG,oldOFF);
}
IVTEntry::~IVTEntry() {
	//unsigned oldSEG = FP_SEG(oldIR), oldOFF = FP_OFF(oldIR);
	//unsigned entry=4*ivtNo;
	lock();
	//oldIR();
	setvect(ivtNo, oldIR);
		/*asm {
			push bx
			push ax
			push es

			mov ax, 0
			mov es, ax
			mov bx, word ptr entry;	
			
			cli;

			mov ax, word ptr oldOFF
			mov word ptr es:bx, ax
			mov ax, word ptr oldSEG
			mov word ptr es:bx+2, ax
			
			sti;

			pop es
			pop ax
			pop bx
		}*/
	unlock();
}
void IVTEntry::signal() {
	eventList->signal();
}
void IVTEntry::callOldInterrupt() {
	oldIR();
}



