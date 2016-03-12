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

#define 4096 RAM_SPACE
#define 256 FILE_SPACE


struct  OurRamBlock{
  bool used;
  unsigned long size;
  unsigned short blocksUsed;
  OurRamBlock* nextBlock;
OurRamBlock(bool isUsed,unsigned long blockSize,unsigned short usedBlocks,OurRamBlock* block) : used(isUsed), size(blockSize),nextBlock(block)
  {
    nextBlock = NULL;
    usedBlocks = 0;
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
  static const unsigned long &startingAddress;
  static char reservedMemory[RAM_SPACE];
  static const unsigned long &endingAddress;
  
  
 public:
 MyFS(const OurRamFile &theFile) {} 
  virtual ssize_t pread(void *buffer, size_t nbyte, off_t o);
  virtual ssize_t read(void *buffer, size_t nbyte);
  virtual ssize_t write(const void *buffer, size_t nbyte);
  static unsigned long* getStartingAddress()
  {
    return startingAddress;
  }
  static unsigned long* getEndingAddress()
  {
    return endingAddress;
  }
  













#endif
