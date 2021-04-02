/*
 * unactive.h
 *
 *  Created on: May 20, 2018
 *      Author: OS1
 */

#ifndef UNACTIVE_H_
#define UNACTIVE_H_
#include "thread.h"
class Thread;


class Unactive:public Thread{
public:
Unactive();
virtual  void run();
void start();

};




#endif /* UNACTIVE_H_ */
