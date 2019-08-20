#ifndef HEADERS_SEMQ_H_
#define HEADERS_SEMQ_H_

class PCB;

class SemaphoreQueue{
public:
	SemaphoreQueue(): prvi(0), posl(0){}
	void unblock();
	void put(PCB*);
private:
	class elem{
	public:
		PCB *pcb;
		elem *sled;
	};
	elem *prvi, *posl;
};


#endif
