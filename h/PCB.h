#ifndef HEADERS_PCB_H_
#define HEADERS_PCB_H_
#include"Thread.h"
#include"KrnThrd.h"
#include"waitList.h"

enum Stanje{Zavrsio, Radi, Blok, Spreman};

class PCB{
public:
	PCB(StackSize, int kvant, Thread*);
	PCB(StackSize, int kvant, KernelThread*);


	unsigned *stack;
	unsigned sp;
	unsigned ss;
	unsigned bp;
	Stanje stanje;
	int kvant;

	waitToCompleteQueue *queue;

	void start();
	void block();
	void sleep(Time);
	~PCB();
};

extern volatile PCB* running;

#endif
