#include"SleepQ.h"

void SleepQueue::tick(){
	if(prvi) {
		prvi->ticks--;
		elem *tek = prvi;
		while(tek && tek->ticks==0){
			prvi = prvi->sled;
			tek->pcb->start();
			delete tek;
			tek = prvi;
		}
	}
}

void SleepQueue::put(PCB* newPCB, unsigned ticks){
	if(ticks==0) return;
	elem *novi = new elem();
	novi->pcb = newPCB;
	novi->sled = 0;

	if(prvi==0) prvi = novi;
	else{
		elem *tek = prvi, *pret = 0;
		while(tek){
			if(ticks < tek->ticks){
				if(pret) pret->sled = novi;
				else prvi = novi;
				novi->sled = tek;
				tek->ticks -= ticks;
				break;
			}
			ticks-=tek->ticks;
			pret = tek;
			tek = tek->sled;
		}
		if(!tek) pret->sled = novi;
	}

	novi->ticks = ticks;

	newPCB->block();
}
