/*
 * pcb.cpp
 *
 *  Created on: May 15, 2018
 *      Author: OS1
 */

#include"pcb.h"
#include <stdlib.h>
#include <dos.h>
#include "kernel.h"
#include"blocked.h"

int syncPrintf(const char *format, ...);

//konstante stanja niti
const int PCB::NEW = 0;
const int PCB::READY = 1;
const int PCB::BLOCKED = 2;
const int PCB::OVER = 3;
//int PCB::idd=0;

PCB::PCB(Thread* myT, StackSize stackSize, LongTime timeSlice){
lock();
myThread=myT;
this->timeSleep=0;
this->stackSize=stackSize;
this->timeSlice=timeSlice;
state=NEW;
SP=0;
timePassedCounter=0;
timePassedSleep=0;
WaitingForMe= new Blocked();
numberOfChildren=0;
//myID=++idd;
//waitQueue = new Queue();
unlock();
}
PCB::~PCB(){
	lock();
     //syncPrintf("DESTRUKTOR");
		delete WaitingForMe;
		delete SP;
		unlock();
}
void PCB::createStack(){
lock();
this->SP=new unsigned char [stackSize];
static volatile unsigned int tsp,tss,tip,tcs,oldss, oldsp;
//*** Proveriti da li ovde mogu da se inicijalizuju ss i sp ili mora drugacije
this->sp=FP_OFF(this->SP+stackSize);//**BILO je stacksize-1 !!!
this->ss=FP_SEG(this->SP+stackSize);
tip=FP_OFF(&(Kernel::wrapper));
tcs=FP_SEG(&(Kernel::wrapper));
tsp=this->sp;
tss=this->ss;


asm{// Prelazimo na stek koji smo napravili a cuvamo stek tekuce niti koja poziva ovu f-ju
	mov oldsp,sp
	mov oldss,ss
	mov sp,tsp
	mov ss,tss
	// stavlja se PSW na stek
	pushf
	pop ax
    or ax, 0000001000000000b
    push ax	// 9. bit PSWa- I bit
    // Stavlja se PC na stek
	mov ax, tcs
	push ax
	mov ax, tip
	push ax
	// Stavljaju se svi ostali registi
	mov ax,0
	push ax
	push bx
	push cx
	push dx
	push es
	push ds
	push si
	push di
	push bp
  // vracamo tsp od niti tj offset adrese jer se promenio tokom push insturkcija
  mov tsp, sp
// Vracamo se na stek niti koja je pozvala datu f-ju
	mov sp, oldsp
//stek segment je ostao isti
	mov ss, oldss
}
this->sp = tsp;
unlock();

}




