#ifndef HEADERS_IDLETHR_H_
#define HEADERS_IDLETHR_H_

#include"Thread.h"
#include"ThrList.h"

extern ThreadList threadList;

class IdleThread:public Thread{
public:
	IdleThread(): Thread(defaultStackSize, 1){}
	void run(){
		while(1);
	}

	PCB* idlePCB(){
		return threadList.get(myPCB);
	}
};

#endif
