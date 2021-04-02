/*
 * semaphor.cpp
 *
 *  Created on: May 16, 2018
 *      Author: OS1
 */

#include"semaphor.h"
#include"kernelsm.h"
#include"kernel.h"

Semaphore::Semaphore( int init){
	lock();
    myImpl=new KernelSem(init);
	unlock();
}
 
int Semaphore::wait(int toBolock){
  lock();
  int rez=myImpl->wait(toBolock);
  unlock();
  return rez; // Da li ima potrebe za lock unlock ? 
}
 void Semaphore::signal(){
 	lock();
	myImpl->signal();
	unlock();
}

int Semaphore::val()const{
	return myImpl->val();
}

Semaphore::~Semaphore(){
	lock();
	delete myImpl;
	unlock();
}




