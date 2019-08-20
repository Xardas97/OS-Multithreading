#include"KrnlSem.h"

extern volatile PCB* running;

int KernelSem::wait(int toBlock){
	int ret = 0;
	if(toBlock){
		if(--value<0){
			semQ.put((PCB*)running);
			ret = 1;
		}
	}
	else{
		if(value<=0) ret= -1;
		else value--;
	}
	return ret;
}


void KernelSem::signal(){
	if(value++<0)
		semQ.unblock();
}

int KernelSem::val () const{
	return value;
}

KernelSem::KernelSem(int i){
	value = i;
	semQ = SemaphoreQueue();
}
