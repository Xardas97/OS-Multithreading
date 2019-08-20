#include"SleepQ.h"
#include"idleThr.h"
#include"PCB.h"
#include"schedule.h"

void tick();
extern volatile unsigned short lockFlag;
extern volatile unsigned short contextFlag;
extern volatile int brojac;
extern IdleThread *idle;
extern SleepQueue sleepQueue;

unsigned tsp;
unsigned tss;
unsigned tbp;

void interrupt timer(...){	// prekidna rutina
	brojac--;
	sleepQueue.tick();
	if (brojac<-1000) brojac = -1; //kako ne bi doslo do prekoracenje kod kvnt=0, -10000 da ne bi stalno menjao vrednost brojaca
	if (brojac == 0){
		if(lockFlag){
			asm {
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			}
			running->sp = tsp;
			running->ss = tss;
			running->bp = tbp;

			if(running->stanje==Radi) Scheduler::put((PCB*)running);
			running = Scheduler::get();
			if(running==0) running = idle->idlePCB();
			brojac = running->kvant;

			tbp = running->bp;
			tsp = running->sp;
			tss = running->ss;
			asm {
				mov sp, tsp
				mov ss, tss
				mov bp, tbp
			}
		}
		else contextFlag = 1;
	}
	//poziv stare prekidne rutine
	asm int 60h;
	tick();
}
