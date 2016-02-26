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
//void insertTreeTesting(Tree<int>* testTree, int value_1, int value_2, int value_3, short testCase);
void insertTreeTesting(Tree<int>* testTree, int values[], int values_start, int values_end);
void deleteTreeTesting(Tree<int>* testTree, int value_to_delete);

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
    beforeConversionValues = machineValues - '0';

    KOUT::outl("BeforeConversionValues: ",beforeConversionValues);
    beforeConversionValues *= 10;
    KOUT::outl("BeforeConversionValues: ",beforeConversionValues);

    do
      {
    f.read(&machineValues, 1);
    KOUT::outl("Machine values is: ",machineValues);
      }while(machineValues < '0' && machineValues > '9');
    

    beforeConversionValues += machineValues-'0';

    KOUT::outl("BeforeConversionValues: ",beforeConversionValues);
    
    Scheduler::setEpochLength(beforeConversionValues);

    f.read(&machineValues, 1);
    KOUT::outl("Machine values is: ",machineValues);
    f.read(&machineValues, 1);
    KOUT::outl("Machine values is: ",machineValues);
    machineValues -= '0';
    beforeConversionValues = machineValues;

    Clock::wait(3000);
    
    
    Scheduler::setSchedMinGranularity(machineValues);

    KOUT::outl("Epoch length: ",Scheduler::getEpochLength());
    KOUT::outl("SchedMin: ",Scheduler::getSchedMinGranularity());
    
    KOUT::outl();
    KOUT::outl("About to set miliseconds to ticks...");

    Scheduler::setSchedMinGranularityTicks(Scheduler::getSchedMinGranularity() * Machine::getCPUticks());
    Scheduler::setEpochLengthTicks(Scheduler::getEpochLength() * Machine::getCPUticks());


    KOUT::outl("SchedMinGranularity in ticks: ",Scheduler::getSchedMinGranularityTicks());
    KOUT::outl("Epoch Length in ticks:",Scheduler::getEpochLength());

    
    
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

  KOUT::outl("InOrder Traversal Should Give \'8 9 10\' as the result, with 9 as the starting \n node");
  testTree->printTreeInOrder(testTree->root);
  KOUT::outl("\nRoot is ",testTree->root->item);
  while(testTree->root != NULL)
    {
      testTree->erase(testTree->root);
    }
  //delete[] testTree;

  Clock::wait(3000);
  
  KOUT::outl("Starting Tree");
  //  testTree = new Tree<int>();

  KOUT::outl("Starting Right Left Insertion test case, with \'8\' as starting node, \n so no rotation occurred");
  KOUT::outl("Inserting 8...");
  testTree->insert(values[8]);
  KOUT::outl("Inserting 9...");
  testTree->insert(values[9]);
  KOUT::outl("Inserting 7...");
  testTree->insert(values[7]);

  KOUT::outl("InOrder Traversal Should Give \'7 8 9\' as the result, with 8 as the starting \n node, so no rotation occured");
  testTree->printTreeInOrder(testTree->root);
  KOUT::outl("\nRoot is ",testTree->root->item);
  while(testTree->root != NULL)
    {
      testTree->erase(testTree->root);
    }
  //delete[] testTree;

  Clock::wait(3000);
  
  KOUT::outl("Starting Tree");
  //testTree = new Tree<int>();

  KOUT::outl("Starting Left Right Insertion test case, with \'8\' as starting node");
  KOUT::outl("Inserting 8...");
  testTree->insert(values[8]);
  KOUT::outl("Inserting 7...");
  testTree->insert(values[7]);
  KOUT::outl("Inserting 9...");
  testTree->insert(values[9]);

  KOUT::outl("InOrder Traversal Should Give \'7 8 9\' as the result, with 8 as the root");

  testTree->printTreeInOrder(testTree->root);
  KOUT::outl("\nRoot is ",testTree->root->item);
  
  while(testTree->root != NULL)
    {
      testTree->erase(testTree->root);
    }
  //delete[] testTree;

  Clock::wait(3000);

  KOUT::outl("Starting Tree");
  //testTree = new Tree<int>();

  KOUT::outl("Starting Left Left Insertion test case, with \'8\' as starting node");
  KOUT::outl("Inserting 8...");
  testTree->insert(values[8]);
  KOUT::outl("Inserting 7...");
  testTree->insert(values[7]);
  KOUT::outl("Inserting 6...");
  testTree->insert(values[6]);

  KOUT::outl("InOrder Traversal Should Give \'6 7 8\' as the result, with 7 as the root");
  testTree->printTreeInOrder(testTree->root);
  KOUT::outl("\nRoot is ",testTree->root->item);
  while(testTree->root != NULL)
    {
      testTree->erase(testTree->root);
    }
  //delete[] testTree;

  testTree = new Tree<int>();
  insertTreeTesting(testTree,values,values[3],values[11]);

  KOUT::outl("Starting Right Right Deletion test case, with \'",testTree->root->item,"\' as root node");
  KOUT::outl("Need to delete ",values[8],", then ",values[10],", for Right Right deletion");
  deleteTreeTesting(testTree, values[8]);
  deleteTreeTesting(testTree, values[10]);
  KOUT::outl("Inorder Traversal should give 3 4 5 6 7 9 11, with 6 as the root");
  testTree->printTreeInOrder(testTree->root);
  KOUT::outl("\nRoot is: ",testTree->root->item);
  Clock::wait(3000);

    while(testTree->root != NULL)
    {
      testTree->erase(testTree->root);
    }


  insertTreeTesting(testTree,values,values[6],values[12]);
  
    KOUT::outl("Starting Right Left Deletion test case, with \'",testTree->root->item,"\' as root node");
  KOUT::outl("Need to delete ",values[12],", then ",values[7],", for Right Left deletion");
  deleteTreeTesting(testTree, values[12]);
  deleteTreeTesting(testTree, values[7]);
  KOUT::outl("Inorder Traversal should give 6 8 9 10 12, with 9 as root");
  testTree->printTreeInOrder(testTree->root);
  KOUT::outl("\nRoot is: ",testTree->root->item);
  Clock::wait(3000);

    while(testTree->root != NULL)
    {
      testTree->erase(testTree->root);
    }


    insertTreeTesting(testTree,values,values[5],values[12]);

  KOUT::outl("Starting Left Right Deletion test case, with \'",testTree->root->item,"\' as root node");
  KOUT::outl("Need to delete ",values[6],", then ",values[10],", for Left Right deletion");
  deleteTreeTesting(testTree, values[6]);
  deleteTreeTesting(testTree, values[10]);
  KOUT::outl("Inorder Traversal should give 5 7 8 9 11 12, with 8 as the root");
  testTree->printTreeInOrder(testTree->root);
  KOUT::outl("\nRoot is: ",testTree->root->item);
  Clock::wait(3000);

  while(testTree->root != NULL)
    {
      testTree->erase(testTree->root);
    }

  
    insertTreeTesting(testTree,values,values[6],values[11]);

  KOUT::outl("Starting Left Left Deletion test case, with \'",testTree->root->item,"\' as root node");
  KOUT::outl("Need to delete ",values[7],", then ",values[6],", for Left Left deletion");
  deleteTreeTesting(testTree, values[7]);
  deleteTreeTesting(testTree, values[6]);
  KOUT::outl("Inorder Traversal should give 8 9 10 11, with 9 as the root");
  testTree->printTreeInOrder(testTree->root);
  KOUT::outl("\nRoot is: ",testTree->root->item);
  Clock::wait(3000);

    while(testTree->root != NULL)
    {
      testTree->erase(testTree->root);
    }
    /*
    insertTreeTesting(testTree,values,values[6],values[12]);
    
  KOUT::outl("Starting Left Right Deletion test case, with\n no rotation and \'",testTree->root->item,"\' as root node");
  KOUT::outl("Need to delete ",values[7],", then ",values[11],", for Left Left deletion");
  deleteTreeTesting(testTree, values[7]);
  deleteTreeTesting(testTree, values[11]);
  KOUT::outl("Inorder Traversal should give 6 8 9 10 12, with 9 as the root");
  testTree->printTreeInOrder(testTree->root);
  KOUT::outl("\nRoot is: ",testTree->root->item);
  Clock::wait(3000);

    while(testTree->root != NULL)
    {
      testTree->erase(testTree->root);
    }
    */
    
  
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

    void insertTreeTesting(Tree<int>* testTree, int values[], int values_start, int values_end)
{
  KOUT::outl("Deleting Tree");


  /*  if(testCase == 0)
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
      }*/


  for(int i = values_start; i <= values_end; i++)
    {
      KOUT::outl("Inserting ",values[i],"...");
      testTree->insert(values[i]);
    }
  /*  KOUT::outl("Inserting ",value_2,"...");
  testTree->insert(value_2);
  KOUT::outl("Inserting ",value_3,"...");
  testTree->insert(value_3);*/

  
  /*  KOUT::outl("InOrder Traversal Should Give \'8 9\' as the result");
  testTree->printTreeInOrder(testTree->root);
  while(testTree->root != NULL)
    {
      testTree->erase(testTree->root);
    }
  delete testTree;
  */

}

  void deleteTreeTesting(Tree<int>* testTree, int value_to_delete)
{
  /*
  if(testCase == 0 && testTree->root != NULL)
    {
      KOUT::outl("Starting Right Right Deletion test case, with \'",value_1,"\' as starting node");
    }
  else if(testCase == 1 && testTree->root != NULL)
    {
      KOUT::outl("Starting Right Left Deletion test case, with \'",value_1,"\' as starting node");
    }
  else if(testCase == 2 && testTree->root != NULL)
    {
      KOUT::outl("Starting Left Right Deletion test case, with \'",value_1,"\' as starting node");
    }
  else if(testCase == 3 && testTree->root != NULL)
    {
      KOUT::outl("Starting Left Left Deletion test case, with \'",value_1,"\' as starting node");
    }
  */

  KOUT::outl("Deleting ",value_to_delete,"...");
  testTree->deleteNode(value_to_delete);
  /*  KOUT::outl("Deleting ",value_2,"...");
  testTree->deleteNode(value_2);
  KOUT::outl("Deleting ",value_3,"...");
  testTree->deleteNode(value_3);*/

  
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
