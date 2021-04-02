/*
 * kernelsem.h
 *
 *  Created on: May 16, 2018
 *      Author: OS1
 */



#ifndef KERNELSM_H_
#define KERNELSM_H_

class Blocked;
class KernelSem {
public:
KernelSem (int init=1);
 ~KernelSem ();
friend class KernelEv;
protected:
	void signalEveryone();
private:
int  wait (int toBlock);
void signal();
int val () const;
int value;

Blocked* blockedQueue;
friend class Semaphore;
};


#endif /* KERNELSE_H_ */
