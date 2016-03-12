#include "world/MyFS.h"
#include <cstring>

map<string,OurRamFile> ourKernelFS;

ssize_t FileAccess::pread(void *buffer, size_t nbyte, off_t o) {

  static OurRamFile* fileCheck = getStartingAddress() + sizeof(unsigned long);

  if(fileCheck >= getEndingAddress())
    {
      return 0;
    }
  if(!fileCheck->used)
    {
      unsigned long error = &fileCheck;
      if(theFile->
    }

  /*
    int start;
    int fileSize;
    if(fileSize > blockSize)
       fileSize -= blockSize;
    for(
   */
  /*
  if (o + nbyte > orf.size)
    {
      nbyte = orf.size - o;
    }
  memcpy( buffer, (bufptr_t)(orf.virtualMemoryAddress + o), nbyte );
  return nbyte;*/
}

ssize_t FileAccess::read(void *buffer, size_t nbyte) {
  ssize_t len = pread(buffer, nbyte, offset);
  if (len >= 0)
    {
      offset += len;
    }
    return len;
}

ssize_t write(const void *buffer, size_t nbyte)
{
  return 0;
}
