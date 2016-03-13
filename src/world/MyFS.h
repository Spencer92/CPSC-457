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
  char* startingAddress;
  bool used;
  unsigned long size;
  OurRamBlock* nextBlock;
OurRamBlock(char* theStart, bool isUsed,unsigned long blockSize,OurRamBlock* block) : startingAddress(theStart), used(isUsed), size(blockSize),nextBlock(block)
  {
    nextBlock = NULL;
  }
  /*  vaddr virtualMemoryAddress;
  paddr physicalMemoryAddress;
  size_t size;
  OurRamFile* nextRamFile;
  OurRamFile(vaddr v, paddr p, size_t s, OurRamFile* n) : virtualMemoryAddress(v), physicalMemoryAddress(p), size(s), nextRamFile(n=NULL) {}*/
};

extern map<string,OurRamBlock> ourKernelFS;

class MyFS : public Access {
 private:
  static char reservedMemory[RAM_SPACE];
  static constexpr char* startingAddress = &reservedMemory[0];
  static constexpr char* endingAddress = &reservedMemory[RAM_SPACE];
  const OurRamBlock &theFile;
  
  
 public:
 MyFS(const OurRamBlock &theFile) : theFile(theFile) {}

  virtual ssize_t pread(void *buf, size_t nbyte, off_t o);
  virtual ssize_t read(void *buf, size_t nbyte);
  virtual ssize_t write(const void *buf, size_t nbyte);
  static char* getStartingAddress()
  {
    return startingAddress;
  }
  static char* getEndingAddress()
  {
    return endingAddress;
  }
  static char* getReservedMemory(int location)
  {
    return &reservedMemory[location];
  }
};



						    
  













#endif
