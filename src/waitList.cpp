#include"waitList.h"
#include"PCB.h"

void waitToCompleteQueue::put(PCB* newPCB){
	elem *novi = new elem();
	novi->pcb = newPCB;
	novi->sled = prvi;
	prvi = novi;
	newPCB->block();
}

void waitToCompleteQueue::unblock(){
	elem *stari = prvi;
	while(prvi){
		prvi->pcb->start();
		stari = prvi;
		prvi = prvi->sled;
		delete stari;
	}
}
