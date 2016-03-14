#ifndef MYFS_H
#define MYFS_H

#include "world/Access.h"
#include "runtime/SynchronizedArray.h"
#include "kernel/Output.h"
#include "devices/Keyboard.h"

#include <map>
#include <string>
#include <cerrno>
#include <unistd.h> // SEEK_SET, SEEK_CUR, SEEK_END

#define RAM_SPACE 4096
#define FILE_SPACE 256


struct  OurRamBlock{
  unsigned long* startingAddress;
  bool used;
  unsigned long size;
  OurRamBlock* nextBlock;
OurRamBlock(unsigned long* theStart, bool isUsed,unsigned long blockSize,OurRamBlock* block) : startingAddress(theStart), used(isUsed), size(blockSize),nextBlock(block)
  {
    nextBlock = NULL;
  }
};

extern map<string,OurRamBlock> ourKernelFS;

class MyFS : public Access {
 private:

  const OurRamBlock &theFile;
  static char reservedMemory[RAM_SPACE];
  static constexpr void* startingAddress = (void*) &reservedMemory[0];
  static constexpr void* endingAddress = &reservedMemory[RAM_SPACE];

  
 public:

 MyFS(const OurRamBlock &theFile) : theFile(theFile)
  {
    for(int i = 0; i < RAM_SPACE; i++)
      {
	reservedMemory[i] = 0;
      }
  }

  virtual ssize_t pread(void *buf, size_t nbyte, off_t o);
  virtual ssize_t read(void *buf, size_t nbyte);
  virtual ssize_t write(const void *buf, size_t nbyte);
  virtual OurRamBlock* checkForSpace();
  static unsigned long getStartingAddress()
  {
    return (unsigned long)&startingAddress;
  }
  static unsigned long getEndingAddress()
  {
    return (unsigned long)&endingAddress;
  }
  static unsigned long* getReservedMemory(int location)
  {
    void* conversion = (void*)&reservedMemory[location];
    return (unsigned long*)conversion;
  }
  static unsigned long* getStartingAddressPointer()
  {
    void* conversion = (void*)&reservedMemory[0];
    return (unsigned long*)conversion;
  }
  static unsigned long* getEndingAddressPointer()
  {
    void* conversion = (void*)&reservedMemory[FILE_SPACE];
    return (unsigned long*)conversion;
  }
};



						    
  













#endif
