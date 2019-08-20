#include"SemQ.h"
#include"PCB.h"

void SemaphoreQueue::put(PCB* newPCB){
	elem *novi = new elem();
	novi->sled = 0;
	novi->pcb = newPCB;
	if(posl) { posl->sled = novi; posl = novi; }
	else prvi = posl = novi;
	newPCB->block();
}

void SemaphoreQueue::unblock(){
	if(prvi){
		prvi->pcb->start();
		prvi = prvi->sled;
		if(!prvi) posl=0;
	}
}
