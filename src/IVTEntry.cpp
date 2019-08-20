#include<dos.h>
#include"IVTEntry.h"
#include"KrnEvent.h"

IVTEntry::IVTEntry(unsigned numEntry, pInterrupt newRoutine){
	myEvent = 0;
	num = numEntry;
	old = 0;
	asm cli;
#ifndef BCC_BLOCK_IGNORE
	old = getvect(num);
	setvect(num, newRoutine);
#endif
	asm sti;
	IVTEntries[num] = this;
}

IVTEntry::~IVTEntry(){
	asm cli
#ifndef BCC_BLOCK_IGNORE
	setvect(num, old);
#endif
	asm sti
}

void IVTEntry::signal(){
	if(myEvent) myEvent->signal();
}

void IVTEntry::callOld(){
	asm cli;
	old();
	asm sti;
}

void IVTEntry::connect(KernelEv *my){
	myEvent = my;
}

void IVTEntry::disconnect(KernelEv *req){
	if(myEvent == req) myEvent = 0;
}
