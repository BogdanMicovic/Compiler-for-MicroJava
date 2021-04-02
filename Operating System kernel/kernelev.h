/*
 * kernelev.h.h
 *
 *  Created on: May 16, 2018
 *      Author: OS1
 */



#ifndef KERNELEV_H_
#define KERNELEV_H_

typedef unsigned char IVTNo;

class Thread;
class PCB;
class KernelSem;

class KernelEv {
public:
	KernelEv (IVTNo ivtNo);
	~KernelEv ();
	void wait ();
	void signal();
private:

	IVTNo ivtNo;
	Thread* glavna;
	KernelSem *mySem;
	//friend class IVTEntry;
};

#endif /* KERNELEV_H_ */
