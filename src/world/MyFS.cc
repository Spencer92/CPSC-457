#include "world/MyFS.h"
#include <cstring>

map<string,OurRamBlock> ourKernelFS;
/*static MyFS::char* startingAddress = &reservedMemory[0];
static MyFS::char* endingAddress = &reservedMemory[RAM_SPACE];
*/




/***************************************************************************
   Function Name:   pread
  
   Purpose:         To take files that are already established and break them
                    up into fixed-length blocks as specified by FILE_SIZE in
                    MyFS.h


   Input Arguments: buf  : The buffer being written to
                    nbyte: the current size of the buffer
                    o    : the offset from the file

   Output Arguments: The length of the file, otherwise an error if
                     there is no more room inside the allocated RAM
   
   Method notes: The file is checked to see if it is larger than FILE_SIZE,
                 if so, the max amount of space that can be used for a
                 particular block is assigned to that part of the file, and
                 another block is assigned to handle the rest of the file.
                 this repeats until the file size is either the length or
                 less than the length of the block. If a block is already used 
                 when trying to assign values to it, the block will be
                 skipped and the block after will be checked until a 
                 block that is not used is found. If no unused blocks are 
                 found an error is thrown



***************************************************************************/



ssize_t MyFS::pread(void *buf, size_t nbyte, off_t o)
{
  OurRamBlock* freeBlock = new OurRamBlock(NULL,false,0,NULL);

  while(nbyte > FILE_SPACE - sizeof(OurRamBlock))
    {
      freeBlock = MyFS::checkForSpace();
      if(freeBlock != NULL)
	{
	  memcpy(buf,(bufptr_t)theFile.startingAddress+o, FILE_SPACE - sizeof(OurRamBlock));
	}
      else
	{
	  return -1; //Out of space error
	}
      nbyte -= FILE_SPACE;
      o += FILE_SPACE;
    }

  if(nbyte > 0)
    {
      freeBlock = MyFS::checkForSpace();
      if(freeBlock != NULL)
	{
	  memcpy(buf,(bufptr_t)theFile.startingAddress+o, nbyte);
	}
      else
	{
	  return -1; //Out of space error
	}
    }



  return 0;
}


/***************************************************************************
   Function Name:   read
  
   Purpose:         To read the files

   Input Arguments: buf  : The file that's being used
                    nbyte: The current size of the buffer


   Output Arguments: Greater than 0 if there is still data left inside
                     of the file, 0 if there isn't
   
   Method notes: it reads each block within the file struture for use elsewhere
                 If the block it's reading ends, it will see if there is another
                 block allocated to the file and continue to read the rest
                 of the file until there is nothing left to read. If there
                 is nothing left to read the function returns 0



***************************************************************************/




ssize_t MyFS::read(void *buf, size_t nbyte)
{
  off_t offset = 0;
  ssize_t length = pread(buf,nbyte,offset);
  if(length >= 0)
    {
      offset += length;
    }

  return length;
  
}


/***************************************************************************
   Function Name:   write
  
   Purpose:         To write to the files

   Input Arguments: buf  : The file that's being used
                    nbyte: The current size of the buffer


   Output Arguments: the new size of the file, or an error if
                     there is no space left


   Method notes: This modifies an already created file. The new file size
                 is checked, and if the file is now larger than it was
                 before and now goes over the current block size, then
                 a new block is allocated to the file, if it is available.
                 if the file is now small enough that it can fit into less
                 blocks than it was originally allocated, then the blocks
                 are freed in order for them to be used elsewhere.

                 If the file tries to get another block when there is none
                 available, an error is thrown


***************************************************************************/





ssize_t MyFS::write(const void *buf, size_t nbyte)
{
 

  
}



/***************************************************************************
   Function Name:   checkForSpace
  
   Purpose:         To check to see if a block is already used

   Output Arguments: a block of RAM that isn't assigned



   Method notes: A structure is used in order for the blocks of RAM to be
                 checked to see if they are used. If a block is used, it
                 will keep going through blocks until it finds a block.

                 If a block is not found, then it returns NULL, signifying
                 an error.


***************************************************************************/





OurRamBlock* MyFS::checkForSpace()
{
  OurRamBlock* freeBlock = new OurRamBlock(NULL,false,0,NULL);
  freeBlock->startingAddress = MyFS::getStartingAddressPointer();
  for(int i = 0; i < RAM_SPACE; i += FILE_SPACE)
    {
      if(freeBlock != NULL && freeBlock->used)
	{
	  freeBlock += FILE_SPACE;
	  if(freeBlock->startingAddress >= MyFS::getEndingAddressPointer())
	    {
	      freeBlock = NULL;
	    }
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
  return freeBlock;
}













