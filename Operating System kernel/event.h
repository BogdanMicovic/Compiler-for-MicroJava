/*
 * event.h
 *
 *  Created on: May 16, 2018
 *      Author: OS1
 */


#ifndef EVENT_H_
#define EVENT_H_
#include "ivtentry.h"

#define PREPAREENTRY(ivtno,old) \
void interrupt routine##ivtno(...); \
IVTEntry ent##ivtno(ivtno,routine##ivtno); \
void interrupt routine##ivtno(...) { \
	if (old) ent##ivtno.callOldInterrupt(); \
	ent##ivtno.signal(); \
}

typedef unsigned char IVTNo;

class KernelEv;
class Event {
public:

Event (IVTNo ivtNo);
~Event ();
void wait ();

protected:

friend class KernelEv;
void signal(); // can call KernelEv
private:
KernelEv* myImpl;
};


#endif /* EVENT_H_ */
