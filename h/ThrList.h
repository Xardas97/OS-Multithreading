#ifndef HEADERS_THRLIST_H_
#define HEADERS_THRLIST_H_

#include"PCB.h"

class ThreadList{
public:
	ThreadList();
	int put(PCB*);
	PCB* get(int ID);
	void remove(int ID);
private:
	PCB* pcbArray[30];
	struct elem{
		PCB* pcb;
		int id;
		elem* sled;
	};
	elem* prvi;
};



#endif
