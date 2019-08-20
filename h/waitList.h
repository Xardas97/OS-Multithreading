#ifndef HEADERS_WAITLIST_H_
#define HEADERS_WAITLIST_H_

class PCB;

class waitToCompleteQueue {
public:
	waitToCompleteQueue(): prvi(0){}
	void put(PCB*);
	void unblock();
private:
	class elem{
	public:
		PCB *pcb;
		elem *sled;
	};
	elem *prvi;
};



#endif
