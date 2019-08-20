#include<dos.h>
#include"event.h"
#include"sysCall.h"

Event::Event(IVTNo ivtNo){
	SystemCallArguments newSysArgs;
	newSysArgs.name = EvConstructor;
	newSysArgs.arg1 = ivtNo;
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

Event::~Event () {
	SystemCallArguments newSysArgs;
	newSysArgs.name = EvDestructor;
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

void Event::wait  (){
	SystemCallArguments newSysArgs;
	newSysArgs.name = EvWait;
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


void Event::signal(){
	SystemCallArguments newSysArgs;
	newSysArgs.name = EvSignal;
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
