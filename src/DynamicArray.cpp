#include <cstdlib>
#include <cassert>
#include "DynamicArray.h"

int kLARGE;
int kINCL;

#define kLARGE 10000
#define kINCL 5000

DynamicArray::DynamicArray(int size, int inc)
{
     assert((size > 1) && (size < kLARGE));
	 assert((inc > 1) && (inc < kINCL));
	 fNum = 0;
	 fCSize = fSize = size;
	 fInc = inc;
	 fItems = new void* [size];
}

int DynamicArray::Position(void *item) const
{
 	for(int i = 0; i< fNum; ++i)
	if(fItems[i] == item) return i+1;
	return 0;
}

void *DynamicArray::Nth(int n) const
{
 	 if((n < 1) || (n > fNum))
	 return 0;
	 --n;
	 return fItems[n];
}

void DynamicArray::Append(void *item)
{
 	 if(fNum == fCSize)
	 Grow(fInc);
	 fItems[fNum] = item;
	 ++fNum;
}

void DynamicArray::Grow(int delta)
{
 	 int newsize = fCSize + delta;
	 void **temp = new void* [newsize];
	 fCSize = newsize;
	 for(int i=0;i < fNum; ++i)
	   temp[i] = fItems[i];
	 delete [] fItems;
	 fItems = temp;
}

void *DynamicArray::Remove(void *item)
{
 	 int where = Position(item);
	 return Remove(where);
}

void *DynamicArray::Remove(int itempos)
{
 	 if((itempos < 1) || (itempos > fNum))
	 return 0;
	 --itempos;
	 void *tmp = fItems[itempos];
	 for(int i = itempos + 1; i < fNum; ++i)
	 fItems[i-1] = fItems[i];
	 --fNum;
	 if((fNum > fSize) && (fNum < (fCSize / 2)))
	 Grow(-fInc);
     return tmp;
}

DynamicArray::~DynamicArray()
{
}
