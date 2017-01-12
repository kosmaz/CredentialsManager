#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

class DynamicArray
{
    public:
	 		DynamicArray(int size = 10, int inc = 5);
	 		virtual ~DynamicArray();
			virtual int Length(void)const;
			virtual int Position(void *item)const;
			virtual void *Nth(int n) const;
			virtual void Append(void *item);
			virtual void *Remove(void *item);
			virtual void *Remove(int itempos);

	private:
            virtual void Grow(int amount);

			 int fNum;
			 int fSize;
			 int fCSize;
			 int fInc;
			 void **fItems;
};

inline int DynamicArray::Length() const { return fNum; }

#endif	 //DYNAMICARRAY_H





