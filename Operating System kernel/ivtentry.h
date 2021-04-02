/*
 * ivtentry.h
 *
 *  Created on: May 16, 2018
 *      Author: OS1
 */

#ifndef _IVTENTRY_H_
#define _IVTENTRY_H_

#include "eventlis.h"

typedef void interrupt (*InterruptRoutine)(...);

class IVTEntry {
	friend class KernelEv;
private:
	static IVTEntry* IVTTable[];
	
	unsigned ivtNo;
	EventList* eventList;
	InterruptRoutine oldIR;

public:
	IVTEntry(int,InterruptRoutine);
   ~IVTEntry();
	void signal();
	void callOldInterrupt();
};




#endif
