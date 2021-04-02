/*
 * thread.h
 *
 *  Created on: May 14, 2018
 *      Author: OS1
 */
// File: thread.h
#ifndef THREAD_H_
#define THREAD_H_



typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096; // Bilo 4096
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;


class PCB; // Kernel's implementation of a user's thread


class Thread {
public:

void start();
void waitToComplete();
virtual ~Thread();
static void sleep(Time timeToSleep);
friend class PCB;
friend class Kernel;
friend class Unactive;
PCB* myPCB;

protected:


Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
virtual void run() {}

private:


};


void dispatch ();




#endif /* THREAD_H_ */
