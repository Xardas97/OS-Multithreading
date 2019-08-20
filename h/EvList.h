#ifndef HEADERS_EVLIST_H_
#define HEADERS_EVLIST_H_

#include"KrnEvent.h"

class EventList{
public:
	EventList();
	int put(KernelEv*);
	KernelEv* get(int ID);
	void remove(int ID);
private:
	KernelEv* evArray[30];
	struct elem{
		KernelEv* event;
		int id;
		elem* sled;
	};
	elem* prvi;
};

#endif
