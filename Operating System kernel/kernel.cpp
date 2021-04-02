/*
 * kernel.cpp
 *
 *  Created on: May 15, 2018
 *      Author: OS1
 */
#include"kernel.h"
#include "SCHEDULE.h"
#include <dos.h>
#include <stdlib.h>
#include<stdio.h>
int syncPrintf(const char *format, ...);
//int Kernel::rasporedjivac[10]={0,0,0,0,0,0,0,0,0,0};
void tick();
volatile unsigned  Kernel::context_switch_on_demand=0;
volatile PCB* Kernel:: running;
Thread* Kernel::starting=0;
int Kernel::idd=0;
Unactive* Kernel::unactive=0;
Queue* Kernel::blockedQueue=new Queue();

pInterrupt Kernel::oldISR=0;
pInterrupt Kernel::newRoutine=Kernel::timerInterrupt;
void Kernel::load(){
	lock();
	oldISR = getvect(0x08);
	setvect(0x60,oldISR);
	setvect(0x08,timerInterrupt);
    starting=new Thread();
    starting->myPCB->state=PCB::READY;
    running = (volatile PCB*)starting->myPCB;
    unactive=new Unactive();
    unactive->start();
   unlock();
}

void Kernel::close(){
	lock();
	oldISR=getvect(0x60);
	setvect(0x08,oldISR);
	delete starting;
	delete unactive;
	unlock();
}

void Kernel::dispatch(){

		lock();
		Kernel::context_switch_on_demand = 1;
		Kernel::timerInterrupt();
		Kernel::context_switch_on_demand=0;
		unlock();


}

void interrupt Kernel::timerInterrupt(...){
	static volatile unsigned tsp,tss;
	//static volatile PCB *newThread;
	//syncPrintf("context= %d  ",context_switch_on_demand);

	if (!context_switch_on_demand && Kernel::running->timeSlice != 0) Kernel::running->timePassedCounter+=(LongTime)1;
	//syncPrintf("demand=%d",context_switch_on_demand);
	if(!context_switch_on_demand){ Kernel::blockedQueue->remove_sleeping_threads();}
	if(!Kernel::context_switch_on_demand){ asm int 60h;tick();}
	
	//*** DA LI SME DA SE KORISTI SLEDECA LINIJA KODA JER AKO NAM DODJE PREKID OD TAJMERA DOK JE AKTIVNA UNACTIVE NIT NIKADA SE NECE PRECI NA IZVRSAVANJE
	//*** DRUGE NITI CAK IAKO NISU SVE NITI BLOKIRANE I U REDU SPREMNIH NITI POSTOJI NIT KOJA BI MOGLA DA SE IZVRSAVA
	//if (!Kernel::context_switch_on_demand && (running->timePassedCounter < running->timeSlice ) ) {context_switch_on_demand=0;return;}
	if (!context_switch_on_demand && (running->timePassedCounter < running->timeSlice || running->timeSlice == 0) ) {//context_switch_on_demand=0;
	return;}
	if ( Kernel::running->timePassedCounter>Kernel::running->timeSlice || context_switch_on_demand) {
     //***Izbacen uslov u for petlji iznad za ||Kernel::running->timeSlice==0
	//	syncPrintf(" Ulazi");
		  //Kernel::context_switch_on_demand=0;
		if(context_switch_on_demand)
			context_switch_on_demand=0;
		asm {
	// cuva sp
	mov tsp, sp
	mov tss, ss
	}
	Kernel::running->sp = tsp;
	Kernel::running->ss = tss;
	if( running->state == PCB::READY && running != unactive->myPCB ){
				Scheduler::put((PCB*)running);
                //rasporedjivac[Kernel::running->myID]=Kernel::running->myID;
               // for(int i=0;i<10;i++)
                	//if(rasporedjivac[i]!=0)
                		//syncPrintf("PUT");

			}

            Kernel::running=Scheduler::get();
			//newThread = Scheduler::get();
			if (Kernel::running == 0) Kernel::running = unactive->myPCB; //ako je prazan Scheduler koristimo unactive(idle) nit
			//*** DA LI JE POTREBNA SLEDECA LINIJA KODA JER SMO U GORE VODILI RACUNA AD SAMO SPREMNE NITI KOJE NISU UNACTIVE STAVLJAMO U RED CEKANJA SPREMNIH NITI
			//if (newThread->state != PCB::READY) continue;


	/*asm {
	// cuva sp
	mov tsp, sp
	mov tss, ss
	}

	Kernel::running->sp = tsp;
	Kernel::running->ss = tss;
   if( running->state == PCB::READY && running != unactive->myPCB )
				Scheduler::put((PCB*)running);
	
	running = newThread;
*/

	tsp = running->sp;
	tss = running->ss;



	asm {
	// restaurira sp
	mov sp, tsp
	mov ss, tss
	}

	Kernel::running->timePassedCounter = 0;
		
	}
// Poziv stare prekidne rutine u slucaju da je stvarno doslo do prekida
	//if(!Kernel::context_switch_on_demand){ asm int 60h;tick();}

		Kernel::context_switch_on_demand = 0;
      //syncPrintf("*** Zavrsio tajmer  ***  ");

}

void Kernel::wrapper(){

	running->myThread->run();
    lock();
    running->state=PCB::OVER;
    running->WaitingForMe->remove_blocked_threads();
    dispatch();
    unlock();


}


