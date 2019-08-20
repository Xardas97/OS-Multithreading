#include"dos.h"
#include"schedule.h"
#include"PCB.h"
#include"SleepQ.h"

extern SleepQueue sleepQueue;

void PCB::sleep(Time timeToSleep){
	sleepQueue.put(this, timeToSleep);
}

void PCB::start(){
	if(stanje!=Radi){
		stanje = Radi;
		Scheduler::put(this);
	}
}

extern unsigned short contextFlag;
void PCB::block(){
	stanje = Blok;
	contextFlag = 1;
}

PCB::PCB(StackSize stackSize, int kvnt, Thread *myThread){
	if(stackSize>65536) stackSize=65536;
	stackSize /= sizeof(unsigned);
	kvant = kvnt;
	stanje = Spreman;
	queue = new waitToCompleteQueue();

	stack = new unsigned[stackSize];

#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-1] = FP_SEG(myThread); //argument funkcije wrapper
	stack[stackSize-2] = FP_OFF(myThread);
#endif
	stack[stackSize-5] =0x200;//setovan I fleg u pocetnom PSW-u za nit
	bp = ss = sp = 0;
#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-6] = FP_SEG(Thread::wrapper);
	stack[stackSize-7] = FP_OFF(Thread::wrapper);

	sp = FP_OFF(stack+stackSize-16);
	ss = FP_SEG(stack+stackSize-16);
	bp = sp;
#endif
}

PCB::PCB(StackSize stackSize, int kvnt, KernelThread *myThread){
	if(stackSize>65536) stackSize=65536;
	stackSize /= sizeof(unsigned);
	kvant = kvnt;
	stanje = Spreman;
	queue = new waitToCompleteQueue();

	stack = new unsigned[stackSize];

#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-1] = FP_SEG(myThread); //argument funkcije wrapper
	stack[stackSize-2] = FP_OFF(myThread);
#endif
	stack[stackSize-5] =0x200;//setovan I fleg u pocetnom PSW-u za nit
	bp = ss = sp = 0;
#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-6] = FP_SEG(KernelThread::wrapper);
	stack[stackSize-7] = FP_OFF(KernelThread::wrapper);

	sp = FP_OFF(stack+stackSize-16);
	ss = FP_SEG(stack+stackSize-16);
	bp = sp;
#endif
}

PCB::~PCB(){
	delete[] stack;
	delete queue;
}
