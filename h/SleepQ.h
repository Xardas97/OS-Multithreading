#ifndef HEADERS_SLEEPQ_H_
#define HEADERS_SLEEPQ_H_

#include"PCB.h"

class SleepQueue{
public:
	SleepQueue(): prvi(0){}
	void tick();
	void put(PCB*, unsigned);
private:
	class elem{
	public:
		PCB *pcb;
		elem *sled;
		unsigned ticks;
	};
	elem *prvi;
};

#endif
