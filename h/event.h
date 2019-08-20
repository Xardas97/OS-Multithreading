#ifndef _event_h_
#define _event_h_

#include"IVTEntry.h"

#define PREPAREENTRY(num, old)\
		void interrupt isr##num(...);\
		IVTEntry entry##num = IVTEntry(num, isr##num);\
		void interrupt isr##num(...){\
			entry##num.signal();\
			if(old==1) entry##num.callOld();\
		}

typedef unsigned char IVTNo;
typedef int ID;
class KernelEv;

class Event {
public:
   Event (IVTNo ivtNo);
  ~Event ();
   void wait  ();
protected:
   friend class KernelEv;
   void signal(); // can call KernelEv
private:
   ID myImpl;
};



#endif
