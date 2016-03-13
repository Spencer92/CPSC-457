#include "world/MyFS.h"
#include <cstring>

map<string,OurRamBlock> ourKernelFS;
/*static MyFS::char* startingAddress = &reservedMemory[0];
static MyFS::char* endingAddress = &reservedMemory[RAM_SPACE];
*/

ssize_t MyFS::pread(void *buf, size_t nbyte, off_t o) {

  
  
  /*
  if(fileCheck >= getEndingAddress())
    {
      return 0;
    }
  if(!fileCheck->used)
    {
      

    }
  */
  /*
    int start;
    int fileSize;
    if(fileSize > blockSize)
       fileSize -= blockSize;
    for(
   */
  
  /*  if (o + nbyte > orf.size)
    {
      nbyte = orf.size - o;
    }
  memcpy( buffer, (bufptr_t)(orf.virtualMemoryAddress + o), nbyte );
  return nbyte;
  return 0;
}

  ssize_t read(void *buf, size_t nbyte) {
  ssize_t len = pread(buffer, nbyte, offset);
  if (len >= 0)
    {
      offset += len;
    }
    return len;*/
  return 0;
}

ssize_t MyFS::read(void *buf, size_t nbyte)
{
  return 0;
}

ssize_t MyFS::write(const void *buf, size_t nbyte)
{
  
  

  
}

OurRamBlock* checkForSpace()
{
  OurRamBlock* freeBlock;
  freeBlock->startingAddress = MyFS::getStartingAddress();
  for(int i = 0; i < RAM_SPACE; i += FILE_SPACE)
    {
      if(freeBlock != NULL && freeBlock->used)
	{
	  freeBlock += FILE_SPACE;
	  
	}
      else if(freeBlock == NULL)
	{
	  return NULL;
	}
      else
	{
	  freeBlock->startingAddress = MyFS::getReservedMemory(i);
	  return freeBlock;
	}
    }
}













