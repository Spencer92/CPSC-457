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


struct  OurRamFile{
  vaddr virtualMemoryAddress;
  paddr physicalMemoryAddress;
  size_t size;
  OurRamFile* nextRamFile;
OurRamFile(vaddr v, paddr p, size_t s, OurRamFile* n) : virtualMemoryAddress(v), physicalMemoryAddress(p), size(s), nextRamFile(n=NULL) {}
};

extern map<string,OurRamFile> ourKernelFS;

class MyFS : public Access {
 private:
  const OurRamFile &orf;
  
  
 public:
 MyFS(const OurRamFile &orf) : orf(orf) {} 
  virtual ssize_t pread(void *buffer, size_t nbyte, off_t o);
  virtual ssize_t read(void *buffer, size_t nbyte);
  virtual ssize_t write(const void *buffer, size_t nbyte);
  

};














#endif
