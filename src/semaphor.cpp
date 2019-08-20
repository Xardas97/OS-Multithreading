#include<dos.h>
#include"semaphor.h"
#include"sysCall.h"

Semaphore::Semaphore(int init){
	SystemCallArguments newSysArgs;
	newSysArgs.name = SemConstructor;
	newSysArgs.arg1 = init;
#ifndef BCC_BLOCK_IGNORE
	unsigned scx = FP_SEG(&newSysArgs);
	unsigned sdx = FP_OFF(&newSysArgs);
#endif
	asm{
		mov cx, scx
		mov dx, sdx
		int 61h;
	}
	myImpl = newSysArgs.arg1;
}
Semaphore::~Semaphore(){
	SystemCallArguments newSysArgs;
	newSysArgs.name = SemDestructor;
	newSysArgs.arg1 = myImpl;
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

int Semaphore::wait(int toBlock){
	SystemCallArguments newSysArgs;
	newSysArgs.name = SemWait;
	newSysArgs.arg1 = myImpl;
	newSysArgs.arg2 = toBlock;
#ifndef BCC_BLOCK_IGNORE
	unsigned scx = FP_SEG(&newSysArgs);
	unsigned sdx = FP_OFF(&newSysArgs);
#endif
	asm{
		mov cx, scx
		mov dx, sdx
		int 61h;
	}
	return newSysArgs.arg1;
}

void Semaphore::signal(){
	SystemCallArguments newSysArgs;
	newSysArgs.name = SemSignal;
	newSysArgs.arg1 = myImpl;
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


int Semaphore::val() const{
	SystemCallArguments newSysArgs;
	newSysArgs.name = SemVal;
	newSysArgs.arg1 = myImpl;
#ifndef BCC_BLOCK_IGNORE
	unsigned scx = FP_SEG(&newSysArgs);
	unsigned sdx = FP_OFF(&newSysArgs);
#endif
	asm{
		mov cx, scx
		mov dx, sdx
		int 61h;
	}
	return newSysArgs.arg1;
}
