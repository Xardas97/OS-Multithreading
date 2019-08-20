#include<dos.h>
#include"KrnThrd.h"
#include"sysCall.h"
#include"idleThr.h"
#include"thrList.h"
#include"SemList.h"
#include"EvList.h"
#include"PCB.h"

extern PCB* runningKernelThread;

KernelThread::KernelThread(){
	runningKernelThread = new PCB(4096, 0, this);
}

void KernelThread::wrapper(KernelThread* runningThread){
	runningThread->run();
}

KernelThread::~KernelThread(){
	delete runningKernelThread;
}

extern IdleThread *idle;
extern ThreadList threadList;
extern SemaphoreList semList;
extern EventList eventList;
extern SystemCallArguments *sysArgs;
extern volatile unsigned short contextFlag;

void interrupt systemReturn(...);

void KernelThread::run(){
	while(1){
		//izvrsenje poziva
		switch(sysArgs->name){
			case ThreadConstructor: sysArgs->arg1 = threadList.put(new PCB(sysArgs->arg1, sysArgs->arg2, sysArgs->arg3)); break;
			case ThreadDestructor: if(threadList.get(sysArgs->arg1) != idle->idlePCB() && threadList.get(sysArgs->arg1)->stanje != Zavrsio)
										threadList.get(sysArgs->arg1)->queue->put((PCB*)running);
									threadList.remove(sysArgs->arg1);
									break;
			case Sleep: ((PCB*)running)->sleep(sysArgs->arg1); break;
			case Dispatch: contextFlag = 1; break;
			case Start: threadList.get(sysArgs->arg1)->start(); break;
			case Wait: if(threadList.get(sysArgs->arg1)->stanje != Zavrsio)
							threadList.get(sysArgs->arg1)->queue->put((PCB*)running);
						break;
			//Semaphores
			case SemConstructor: sysArgs->arg1 = semList.put(new KernelSem(sysArgs->arg1)); break;
			case SemDestructor: semList.remove(sysArgs->arg1); break;
			case SemWait: sysArgs->arg1 = semList.get(sysArgs->arg1)->wait(sysArgs->arg2); break;
			case SemSignal: semList.get(sysArgs->arg1)->signal(); break;
			case SemVal: sysArgs->arg1 = semList.get(sysArgs->arg1)->val(); break;
			//Events
			case EvConstructor: sysArgs->arg1 = eventList.put(new KernelEv(sysArgs->arg1)); break;
			case EvDestructor: eventList.remove(sysArgs->arg1); break;
			case EvWait: eventList.get(sysArgs->arg1)->wait(); break;
			case EvSignal: eventList.get(sysArgs->arg1)->signal(); break;
		}

		systemReturn(); //povratak na korisnicku nit
	}
}
