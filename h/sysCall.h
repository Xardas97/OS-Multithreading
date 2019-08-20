#ifndef HEADERS_SYSCALL_H_
#define HEADERS_SYSCALL_H_

enum SystemCallName{ ThreadConstructor, ThreadDestructor, Start, Wait, Sleep, Dispatch,
	SemConstructor, SemDestructor, SemWait, SemSignal, SemVal,
	EvConstructor, EvDestructor, EvWait, EvSignal
};

class Thread;
struct SystemCallArguments{
	SystemCallName name;
	unsigned arg1;
	unsigned arg2;
	Thread* arg3;
};

#endif
