#ifndef SOURCE_KRNEVENT_H_
#define SOURCE_KRNEVENT_H_

#include"event.h"
#include"IVTEntry.h"

class PCB;

class KernelEv {
public:
   KernelEv(IVTNo ivtNo);
   ~KernelEv();
   void wait();
   void signal();
protected:
   friend class IVTEntry;
   friend class Event;
private:
   PCB* owner;
   unsigned short blocked;
   unsigned short val;
   IVTEntry *myEntry;
};

#endif
