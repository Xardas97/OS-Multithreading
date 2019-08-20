#include"KrnEvent.h"
#include"PCB.h"

KernelEv::KernelEv(IVTNo ivtNo){
	owner = (PCB*)running;
	myEntry = IVTEntry::IVTEntries[ivtNo];
	myEntry->connect(this);
	val = 0;
	blocked = 0;
}

void KernelEv::wait  (){
	if(owner == running){
		if(val==0){
			blocked = 1;
			owner->block();
		}
		else val = 0;
	}
}

extern unsigned lockFlag;
extern unsigned short contextFlag;
void KernelEv::signal(){
	if(blocked) {
		blocked = 0;
		owner->start();
		if(lockFlag) dispatch();
		else contextFlag = 1;
	}
	else val = 1;
}

KernelEv::~KernelEv(){
	myEntry->disconnect(this);
}
