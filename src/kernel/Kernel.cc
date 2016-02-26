/******************************************************************************
    Copyright � 2012-2015 Martin Karsten

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
#include "runtime/Thread.h"
#include "kernel/AddressSpace.h"
#include "kernel/Clock.h"
#include "kernel/Output.h"
#include "world/Access.h"
#include "machine/Machine.h"
#include "devices/Keyboard.h"

#include "main/UserMain.h"
#include "runtime/Scheduler.h"
#include "generic/tree.h"
void insertTreeTesting(Tree<int>* testTree, int value_1, int value_2, int value_3, short testCase);

AddressSpace kernelSpace(true); // AddressSpace.h
volatile mword Clock::tick;     // Clock.h

extern Keyboard keyboard;

#if TESTING_KEYCODE_LOOP
static void keybLoop() {
  for (;;) {
    Keyboard::KeyCode c = keyboard.read();
    StdErr.print(' ', FmtHex(c));
  }
}
#endif

  


void kosMain() {
  KOUT::outl("Welcome to KOS!", kendl);
  auto iter = kernelFS.find("schedparam");
  Tree<int>* testTree;
  if (iter == kernelFS.end()) {
    KOUT::outl("schedparam information not found");

  } else {
    mword machineValues;
    mword beforeConversionValues;
    FileAccess f(iter->second);

    do
      {
    f.read(&machineValues, 1);
    KOUT::outl("Machine values is: ",machineValues);
      }while(machineValues < '0' || machineValues > '9');
    /*    f.read(&machineValues, 1);
    KOUT::outl("Machine values is: ",machineValues);
    f.read(&machineValues, 1);
    KOUT::outl("Machine values is: ",machineValues);*/
    beforeConversionValues = machineValues - '0';
    //    beforeConversionValues &= 0x00000000000000FF;
    KOUT::outl("BeforeConversionValues: ",beforeConversionValues);
    beforeConversionValues *= 10;
    KOUT::outl("BeforeConversionValues: ",beforeConversionValues);

    do
      {
    f.read(&machineValues, 1);
    KOUT::outl("Machine values is: ",machineValues);
      }while(machineValues < '0' && machineValues > '9');
    
    //f.read(&machineValues, 1);
    beforeConversionValues += machineValues-'0';
    // beforeConversionValues &= 0x000000000000000000FF;
    KOUT::outl("BeforeConversionValues: ",beforeConversionValues);
    
    Scheduler::setEpochLength(beforeConversionValues);
    //    Machine::defaultEpochLength = machineValues;
    f.read(&machineValues, 1);
    KOUT::outl("Machine values is: ",machineValues);
    f.read(&machineValues, 1);
    KOUT::outl("Machine values is: ",machineValues);
    machineValues -= '0';
    beforeConversionValues = machineValues;
    //    beforeConversionValues &= 0x000000000000000000FF;
    Clock::wait(3000);
    
    
    Scheduler::setSchedMinGranularity(machineValues);
    //Machine::schedMinGranularity = machineValues;
    KOUT::outl("Epoch length: ",Scheduler::getEpochLength());
    KOUT::outl("SchedMin: ",Scheduler::getSchedMinGranularity());
    
    KOUT::outl();
    KOUT::outl("About to set miliseconds to ticks...");

    Scheduler::setSchedMinGranularityTicks(Scheduler::getSchedMinGranularity() * Machine::getCPUticks());
    Scheduler::setEpochLengthTicks(Scheduler::getEpochLength() * Machine::getCPUticks());


    KOUT::outl("SchedMinGranularity in ticks: ",Scheduler::getSchedMinGranularityTicks());
    KOUT::outl("Epoch Length in ticks:",Scheduler::getEpochLength());

    
    
    /*    mword before;
    mword after;
    mword total;

    for(int i = 0; i < 10; i++)
    {
      before = CPU::readTSC();
      Clock::wait(1000);
      after = CPU::readTSC();
      total = after - before;
      KOUT::outl("readTSCBefore = ",before);
      KOUT::outl("readTSCAfter = ",after);
      KOUT::outl("readTSCTotal = ",total,"\n");
      KOUT::outl("Epoch length: ",Scheduler::getEpochLength());
      KOUT::outl("SchedMin: ",Scheduler::getSchedMinGranularity());

      }*/
    /*  
#if TESTING_TIMER_TEST
  StdErr.print(" timer test, 3 secs...");
  for (int i = 0; i < 3; i++) {
    Timeout::sleep(Clock::now() + 1000);
    StdErr.print(' ', i+1);
  }
  StdErr.print(" done.", kendl);
#endif

#if TESTING_KEYCODE_LOOP
  Thread* t = Thread::create()->setPriority(topPriority);
  Machine::setAffinity(*t, 0);
  t->start((ptr_t)keybLoop);
#endif
  Thread::create()->start((ptr_t)UserMain);
#if TESTING_PING_LOOP
  for (;;) {
    Timeout::sleep(Clock::now() + 1000);
    KOUT::outl("...ping...");
  }
#endif
    */
  }
  int values[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
  

  KOUT::outl("Starting Tree");
  testTree = new Tree<int>();

  KOUT::outl("Starting Right Right Insertion test case, with \'8\' as starting node");
  KOUT::outl("Inserting 8...");
  testTree->insert(values[8]);
  KOUT::outl("Inserting 9...");
  testTree->insert(values[9]);
  KOUT::outl("Inserting 10...");
  testTree->insert(values[10]);

  KOUT::outl("InOrder Traversal Should Give \'8 9 10\' as the result");
  testTree->printTreeInOrder(testTree->root);
  while(testTree->root != NULL)
    {
      testTree->erase(testTree->root);
    }
  delete testTree;

  KOUT::outl("Starting Tree");
  testTree = new Tree<int>();

  KOUT::outl("Starting Right Left Insertion test case, with \'8\' as starting node");
  KOUT::outl("Inserting 8...");
  testTree->insert(values[8]);
  KOUT::outl("Inserting 9...");
  testTree->insert(values[9]);
  KOUT::outl("Inserting 7...");
  testTree->insert(values[7]);

  KOUT::outl("InOrder Traversal Should Give \'7 8 9\' as the result");
  testTree->printTreeInOrder(testTree->root);
  while(testTree->root != NULL)
    {
      testTree->erase(testTree->root);
    }
  delete testTree;

  KOUT::outl("Starting Tree");
  testTree = new Tree<int>();

  KOUT::outl("Starting Left Right Insertion test case, with \'8\' as starting node");
  KOUT::outl("Inserting 8...");
  testTree->insert(values[8]);
  KOUT::outl("Inserting 7...");
  testTree->insert(values[7]);
  KOUT::outl("Inserting 9...");
  testTree->insert(values[9]);

  KOUT::outl("InOrder Traversal Should Give \'7 8 9\' as the result");
  testTree->printTreeInOrder(testTree->root);
  while(testTree->root != NULL)
    {
      testTree->erase(testTree->root);
    }
  delete testTree;


  
    /*    KOUT::outl("InOrder Traversal Should Give \'8 9\' as the result");
  testTree->printTreeInOrder(testTree->root);
  while(testTree->root != NULL)
    {
      testTree->erase(testTree->root);
    }
    delete testTree;*/
  
  // insertTreeTesting(testTree, values[8],values[9],values[10],0);
  //KOUT::outl("InOrder Traversal Should Give '8,9,10' as the result");
  //testTree->printTreeInOrder(testTree->root);
  //while(testTree->root != NULL)
  //  {
  //    testTree->erase(testTree->root);
  //  }
  // delete testTree;
  

    
  
}

void insertTreeTesting(Tree<int>* testTree, int value_1, int value_2, int value_3, short testCase)
{
  KOUT::outl("Starting Tree");
  testTree = new Tree<int>();

  if(testCase == 0)
    {
      KOUT::outl("Starting Right Right Insertion test case, with \'",value_1,"\' as starting node");
    }
  else if(testCase == 1)
    {
      KOUT::outl("Starting Right Left Insertion test case, with \'",value_1,"\' as starting node");
    }
  else if(testCase == 2)
    {
      KOUT::outl("Starting Left Right Insertion test case, with \'",value_1,"\' as starting node");
    }
  else
    {
      KOUT::outl("Starting Left Left Insertion test case, with \'",value_1,"\' as starting node");
    }

  KOUT::outl("Inserting ",value_1,"...");
  testTree->insert(value_1);
  KOUT::outl("Inserting ",value_2,"...");
  testTree->insert(value_2);
  KOUT::outl("Inserting ",value_3,"...");
  testTree->insert(value_3);

  
  /*  KOUT::outl("InOrder Traversal Should Give \'8 9\' as the result");
  testTree->printTreeInOrder(testTree->root);
  while(testTree->root != NULL)
    {
      testTree->erase(testTree->root);
    }
  delete testTree;
  */

}




extern "C" void kmain(mword magic, mword addr, mword idx)         __section(".boot.text");
extern "C" void kmain(mword magic, mword addr, mword idx) {
  if (magic == 0 && addr == 0xE85250D6) {
    // low-level machine-dependent initialization on AP
    Machine::initAP(idx);
  } else {
    // low-level machine-dependent initialization on BSP -> starts kosMain
    Machine::initBSP(magic, addr, idx);
  }
}
