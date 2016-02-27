/******************************************************************************
    Copyright © 2012-2015 Martin Karsten

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/
#ifndef _Scheduler_h_
#define _Scheduler_h_ 1

#include "generic/EmbeddedContainers.h"
#include "runtime/Runtime.h"
#include "generic/tree.h"

class Thread;
class ThreadNode;

class Scheduler {
  friend void Runtime::idleLoop(Scheduler*);
  bufptr_t idleStack[minimumStack];

  BasicLock readyLock;
  BasicLock printLock;
  
  volatile mword readyCount; 
  Tree<ThreadNode> *readyTree;
  
  volatile mword preemption;
  volatile mword resumption;

  Scheduler* partner;

  template<typename... Args>
  inline void switchThread(Scheduler* target, Args&... a);

  inline void enqueue(Thread& t);

  Scheduler(const Scheduler&) = delete;                  // no copy
  const Scheduler& operator=(const Scheduler&) = delete; // no assignment


  /*
    minGranularity is the minimum time a task must run before it can be
    pre-empted by some other task.
    
    The Epoch Length is the amount of time that must be fairly divided
    between all of the processes that need to run.
    
    These values are than multiplied by the CPU tick rate, in order
    to give the amount of time given in ticks, represented with 
    schedMinGranulartiyTicks and defaultEpochLengthTicks.
  */
  
  
  
  static mword schedMinGranularity;
  static mword defaultEpochLength;

  static mword schedMinGranularityTicks;
  static mword defaultEpochLengthTicks;

  mword readyTotalPriority;

  
public:
  Scheduler();

  //Get before conversion
  static mword getSchedMinGranularity() {return schedMinGranularity; }
  static mword getEpochLength() {return defaultEpochLength; }

  //Get after conversion
  static mword getSchedMinGranularityTicks() {return schedMinGranularity; }
  static mword getEpochLengthTicks() {return defaultEpochLength; }
  
  //Set before conversion
  static void setSchedMinGranularity(mword schedMin) { schedMinGranularity = schedMin; }
  static void setEpochLength(mword epoch) {defaultEpochLength = epoch; }

  //Set after conversion
  static void setSchedMinGranularityTicks(mword schedMin) { schedMinGranularity = schedMin; }
  static void setEpochLengthTicks(mword epoch) {defaultEpochLength = epoch; }


  bool switchTest(Thread* t);
  void setPartner(Scheduler& s) { partner = &s; }
  static void resume(Thread& t);
  void preempt();
  void suspend(BasicLock& lk);
  void suspend(BasicLock& lk1, BasicLock& lk2);
  void terminate() __noreturn;
};

#endif /* _Scheduler_h_ */
