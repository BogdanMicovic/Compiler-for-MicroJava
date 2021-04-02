/*
 * pcb.h
 *
 *  Created on: May 14, 2018
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#include"thread.h"
#include"queue.h"
#include"blocked.h"






class Thread;
class Queue;


typedef unsigned long LongTime;


class PCB{

public:
	PCB(Thread* myT, StackSize stackSize, LongTime timeSlice);
		~PCB();
	//Stanje u kojem se nalazi nit ovog PCBa
static const int NEW, READY, BLOCKED, OVER;
volatile int state;

Blocked* WaitingForMe;
unsigned int sp, ss;
//Videti da li linija ispod terba da ide u komentar ako red dece niti date niti nije potreban
//Queue MyChilder;
unsigned char* SP;
Thread* myThread;
StackSize stackSize;
ID myID;
//static int idd;
int numberOfChildren; 
//brojacka promenljiva nam govori koliko je vremena proslo
	volatile LongTime timePassedCounter;
	LongTime timeSlice; // Zadato vreme rada niti		
	LongTime timeSleep; // Zadato vreme spavanja niti
	volatile LongTime timePassedSleep; // Vreme provedeno u spavanju

		//red niti koje cekaju na ovu
		//Queue* waitQueue; //Spisak niti koje cekaju na ovu

		//f-ja za obezbedjivanje pocetnog steka niti
		void createStack();
private:

friend Thread;

};



#endif /* PCB_H_ */
