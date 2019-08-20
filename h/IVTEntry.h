#ifndef HEADERS_IVTENTRY_H_
#define HEADERS_IVTENTRY_H_

typedef void interrupt (*pInterrupt)(...);
class KernelEv;

class IVTEntry{
public:
	IVTEntry(unsigned numEntry, pInterrupt newRoutine);
	~IVTEntry();
	void signal();
	void callOld();
	void connect(KernelEv*);
	void disconnect(KernelEv*);
	static IVTEntry **IVTEntries;
private:
	unsigned num;
	pInterrupt old;
	KernelEv* myEvent;
};

#endif
