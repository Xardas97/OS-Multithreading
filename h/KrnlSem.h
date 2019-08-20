#ifndef HEADERS_KRNLSEM_H_
#define HEADERS_KRNLSEM_H_

#include"SemQ.h"

class KernelSem {
public:
  KernelSem (int init=1);
  int wait (int toBlock);
  void signal();
  int val () const;
private:
  int value;
  SemaphoreQueue semQ;
};

#endif
