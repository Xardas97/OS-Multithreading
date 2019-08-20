#ifndef HEADERS_SEMLIST_H_
#define HEADERS_SEMLIST_H_

#include"KrnlSem.h"

class SemaphoreList{
public:
	SemaphoreList();
	int put(KernelSem*);
	KernelSem* get(int ID);
	void remove(int ID);
private:
	KernelSem* semArray[30];
	struct elem{
		KernelSem* sem;
		int id;
		elem* sled;
	};
	elem* prvi;
};

#endif
