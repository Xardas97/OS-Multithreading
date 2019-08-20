#include<dos.h>
#include"Thread.h"
#include"sysCall.h"
#include"PCB.h"
#include"ThrList.h"

Thread::Thread (StackSize stackSize, Time timeSlice){
	SystemCallArguments newSysArgs;
	newSysArgs.name = ThreadConstructor;
	newSysArgs.arg1 = stackSize;
	newSysArgs.arg2 = timeSlice;
	newSysArgs.arg3 = this;
#ifndef BCC_BLOCK_IGNORE
	unsigned scx = FP_SEG(&newSysArgs);
	unsigned sdx = FP_OFF(&newSysArgs);
#endif
	asm{
		mov cx, scx
		mov dx, sdx
		int 61h
	}
	myPCB = newSysArgs.arg1;
}

void Thread::sleep(Time timeToSleep){
	SystemCallArguments newSysArgs;
	newSysArgs.name = Sleep;
	newSysArgs.arg1 = timeToSleep;
#ifndef BCC_BLOCK_IGNORE
	unsigned scx = FP_SEG(&newSysArgs);
	unsigned sdx = FP_OFF(&newSysArgs);
#endif
	asm{
		mov cx, scx
		mov dx, sdx
		int 61h;
	}
}

extern ThreadList threadList;
extern volatile unsigned short lockFlag;
void Thread::wrapper(Thread* runningThread){
  runningThread->run();
  lockFlag = 0;
  threadList.get(runningThread->myPCB)->stanje = Zavrsio;
  threadList.get(runningThread->myPCB)->queue->unblock();
  lockFlag = 1;
  dispatch();
}


void Thread::start(){
	SystemCallArguments newSysArgs;
	newSysArgs.name = Start;
	newSysArgs.arg1 = myPCB;
#ifndef BCC_BLOCK_IGNORE
	unsigned scx = FP_SEG(&newSysArgs);
	unsigned sdx = FP_OFF(&newSysArgs);
#endif
	asm{
		mov cx, scx
		mov dx, sdx
		int 61h;
	}
}

Thread::~Thread(){
	SystemCallArguments newSysArgs;
	newSysArgs.name = ThreadDestructor;
	newSysArgs.arg1 = myPCB;
#ifndef BCC_BLOCK_IGNORE
	unsigned scx = FP_SEG(&newSysArgs);
	unsigned sdx = FP_OFF(&newSysArgs);
#endif
	asm{
		mov cx, scx
		mov dx, sdx
		int 61h;
	}
}

void dispatch(){ // sinhrona promena konteksta
	SystemCallArguments newSysArgs;
	newSysArgs.name = Dispatch;
#ifndef BCC_BLOCK_IGNORE
	unsigned scx = FP_SEG(&newSysArgs);
	unsigned sdx = FP_OFF(&newSysArgs);
#endif
	asm{
		mov cx, scx
		mov dx, sdx
		int 61h;
	}
}

void Thread::waitToComplete(){
	SystemCallArguments newSysArgs;
	newSysArgs.name = Wait;
	newSysArgs.arg1 = myPCB;
#ifndef BCC_BLOCK_IGNORE
	unsigned scx = FP_SEG(&newSysArgs);
	unsigned sdx = FP_OFF(&newSysArgs);
#endif
	asm{
		mov cx, scx
		mov dx, sdx
		int 61h;
	}
}
