#include<dos.h>
#include"Thread.h"
#include"PCB.h"
#include"IVTEntry.h"
#include"schedule.h"
#include"idleThr.h"
#include"sysCall.h"

typedef void interrupt (*pInterrupt)(...);
pInterrupt oldRoutine;
void interrupt timer(...);
void interrupt system(...);

// postavlja novu prekidnu rutinu
void inic(){
	asm cli;
#ifndef BCC_BLOCK_IGNORE
	oldRoutine = getvect(8);
	setvect(8, timer);
	setvect(0x60, oldRoutine);
	setvect(0x61, system);
#endif
	asm sti;
}

// vraca staru prekidnu rutinu
void restore(){
	asm cli;
#ifndef BCC_BLOCK_IGNORE
	setvect(8, oldRoutine);
#endif
	asm sti;
}

extern SystemCallArguments *sysArgs;
extern volatile unsigned short lockFlag;
extern IdleThread *idle;
int userMain(int argc, char* argv[]);

int main(int argc, char* argv[]){
	inic();
	idle = new IdleThread();

	PCB *novi = new PCB(128, defaultTimeSlice, (Thread*)0);
	running = novi;
	novi->stanje = Radi;
	lockFlag = 1;

	int ret = userMain(argc, argv);

	delete sysArgs;
	delete idle;
	delete novi;
	delete[] IVTEntry::IVTEntries;

	restore();

	return ret;
}

