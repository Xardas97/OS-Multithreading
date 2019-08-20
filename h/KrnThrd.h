#ifndef HEADERS_KRNTHRD_H_
#define HEADERS_KRNTHRD_H_

class PCB;

class KernelThread {
public:
  KernelThread();
  ~KernelThread();
protected:
  friend class PCB;
private:
  void run();
  static void wrapper(KernelThread* running);
};

#endif
