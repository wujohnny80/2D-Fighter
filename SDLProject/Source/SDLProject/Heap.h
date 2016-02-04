#ifndef _HEAP_H_
#define _HEAP_H_

#include <algorithm>
#include <limits>

template <typename T>
class Heap
{
public:
	Heap();
	~Heap();

	void Insert(T);
	T Remove();

	int Size() const	{ return mSize; }

private:
	void HeapUp(int child);
	void HeapDown(int parent);
	void Swap(T& lhs, T& rhs);

	int mSize;
	T mData[256];
};

#include "Heap.inl"
#endif // _HEAP_H_