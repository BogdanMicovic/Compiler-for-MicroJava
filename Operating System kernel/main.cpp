/*
 * main.cpp
 *
 *  Created on: May 14, 2018
 *      Author: OS1
 */

#include<stdio.h>
#include"kernel.h"
#include"semaphor.h"

extern int userMain(int ,char*[]);
/*class Thread;
static int brojac1=0,brojac2=0,brojac3=0,brojac4=0,brojac5=0,brojac6=0,brojac7=0,brojac8=0,brojac9=0,brojac10=0;
static Semaphore* s1=new Seamaphore();
static long globalni_brojac=0;
class Thread1:public Thread{
	public:
	Thread1 (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice):Thread(defaultStackSize,defaultStackSize){}
	virtual void run();
};
 void Thread1::run(){
	lock();
		printf("Prva nit pocetak\n");
		unlock();
		//sleep(300);
		s1->wait(2);
		for(;brojac1<20000;brojac1++){
			for(;brojac2<20000;brojac2++)
				globalni_brojac++;
			brojac2=0;
		}
		lock();
		printf("prva nit kraj %ld \n",globalni_brojac);
		unlock();
		s1->signal();
}

class Thread2:public Thread{
	public:
	Thread2(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice):Thread(defaultStackSize,defaultStackSize){}
	virtual void run();
};

 void Thread2::run(){
	lock();
		printf("Druga nit pocetak\n");
		unlock();
		//sleep(300);
		s1->wait(2);
		for(;brojac3<20000;brojac3++){
			for(;brojac4<20000;brojac4++)
				globalni_brojac++;
			    brojac4=0;
              }
			
		lock();
		printf("Druga nit kraj %ld \n",globalni_brojac);
		unlock();
		s1->signal();
}

class Thread3:public Thread{
	public:
	Thread3(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice):Thread(defaultStackSize,defaultStackSize){}
	virtual void run();
};

void Thread3::run(){
	lock();
		printf("Treca nit pocetak\n");
		unlock();
		sleep(500);
		for(;brojac7<20000;brojac7++)
			for(;brojac8<20000;brojac8++);
		lock();
		printf("Treca nit kraj\n");
		unlock();
}

class Thread4:public Thread{
	public:
	Thread4(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice):Thread(defaultStackSize,defaultStackSize){}
	virtual void run();
};

void Thread4::run(){
	lock();
		printf("Cetvrta nit pocetak\n");
		unlock();
		sleep(300);
		for(;brojac9<20000;brojac9++)
			for(;brojac10<20000;brojac10++);
		lock();
		printf("Cetvrta nit kraj\n");
		unlock();
}*/
int main(int argc, char* argv[]){
  

//lock();
Kernel::load();


//Thread* t1=new Thread1();
//Thread* t2=new Thread2();
//Thread* t3=new Thread3();
//Thread* t4=new Thread4();

//t1->start();
//t2->start();
//t3->start();
//t4->start();

 int rez=userMain(argc,argv);

//unlock();
//Kernel::dispatch();

//Thread::sleep(200);

//lock();
//printf("main posle sleepa");
//unlock();

/*while(1){
	lock();
	printf("%s","while" );
    unlock();
    for(brojac5=0;brojac5<20000;brojac5++)
    	for(brojac6=0;brojac6<20000;brojac6++);
	//if(t1->myPCB->state==PCB::OVER && t2->myPCB->state==PCB::OVER && t3->myPCB->state==PCB::OVER && t4->myPCB->state==PCB::OVER)
		//break;
	for(brojac5=0;brojac5<20000;brojac5++)
    	for(brojac6=0;brojac6<20000;brojac6++);
}
*/



 //t1->waitToComplete();
 //t2->waitToComplete();
 //t3->waitToComplete();
 //t4->waitToComplete();
 
//lock();
//printf("Kraj Maina");
 //unlock();
Kernel::close();
  return rez;
}



