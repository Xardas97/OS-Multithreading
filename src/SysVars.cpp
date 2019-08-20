#include"sysCall.h"
#include"EvList.h"
#include"IVTEntry.h"
#include"PCB.h"
#include"SemList.h"
#include"SleepQ.h"
#include"ThrList.h"

//context variables
volatile int brojac = 0;
volatile PCB* running;

//context change variables
volatile unsigned short lockFlag = 0;
volatile unsigned short contextFlag = 0;
SystemCallArguments *sysArgs;

//Kernel object lists
EventList eventList = EventList();
ThreadList threadList = ThreadList();
SemaphoreList semList = SemaphoreList();

//Kernel thread variables
PCB* runningKernelThread;
KernelThread kernelThread;


IVTEntry **IVTEntry::IVTEntries = new IVTEntry*[256];
SleepQueue sleepQueue = SleepQueue();
IdleThread *idle;
