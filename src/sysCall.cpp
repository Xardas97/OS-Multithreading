#include<dos.h>
#include"sysCall.h"
#include"PCB.h"
#include"schedule.h"
#include"idleThr.h"

extern PCB* runningKernelThread;
extern SystemCallArguments *sysArgs;

extern volatile unsigned short contextFlag;
extern volatile unsigned short lockFlag;
extern volatile int brojac;
extern IdleThread *idle;

unsigned ssp;
unsigned sss;
unsigned sbp;

void interrupt system(...){
	lockFlag = 0;
	asm sti;

	//dohvatanje argumenata
	asm{
		mov ssp, cx
		mov sss, dx
	}
	sysArgs = (SystemCallArguments*) MK_FP(ssp, sss);

	//cuvamo kontekst
	asm {
		mov ssp, sp
		mov sss, ss
		mov sbp, bp
	}
	running->sp = ssp;
	running->ss = sss;
	running->bp = sbp;

	//prelazimo na kernel nit
	ssp = runningKernelThread->sp;
	sss = runningKernelThread->ss;
	sbp = runningKernelThread->bp;
	asm {
		mov sp, ssp
		mov ss, sss
		mov bp, sbp
	}
}

void interrupt systemReturn(...){
	//cuvanje kernel steka
	asm {
		mov ssp, sp
		mov sss, ss
		mov sbp, bp
	}
	runningKernelThread->sp = ssp;
	runningKernelThread->ss = sss;
	runningKernelThread->bp = sbp;

	//promena konteksta ako je potrebno
	if(contextFlag){
		contextFlag = 0;

		if(running->stanje==Radi) Scheduler::put((PCB*)running);
		running = Scheduler::get();
		if(running==0) running = idle->idlePCB();
		brojac = running->kvant;
	}

	//povratak na koristicku nit
	ssp = running->sp;
	sss = running->ss;
	sbp = running->bp;
	asm {
		mov sp, ssp
		mov ss, sss
		mov bp, sbp
	}

	lockFlag = 1;
}
