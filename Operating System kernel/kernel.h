/*
 * kernel.h
 *
 *  Created on: May 14, 2018
 *      Author: OS1
 */

#ifndef KERNEL_H_
#define KERNEL_H_
#include "pcb.h"
#include "thread.h"
#include "unactive.h"
#define lock() {asm{pushf; cli;}}
#define unlock() {asm{popf}}

class PCB;
class Thread;
class Unactive;
class Queue;
class Scheduler;
class KernelSem;

typedef void interrupt (*pInterrupt)(...);

//Definisanje makroa za pravilno izvrsavanje sledecih funkcija u slucaju ungezdavanja prekida


class Kernel{
public:
friend KernelEv;
static void load();
static void close();
static void dispatch();
static void wrapper();
static int  idd;
private:
static void interrupt timerInterrupt(...);
static volatile unsigned context_switch_on_demand;
friend class Thread;
friend class PCB;
friend KernelSem;
static Thread* starting;
static Unactive* unactive;
static volatile PCB* running;
static Queue* blockedQueue;
static pInterrupt oldISR;
static pInterrupt newRoutine;
//static int rasporedjivac[10];
};



#endif /* KERNEL_H_ */
