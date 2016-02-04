template <typename T>
Heap<T>::Heap()
	: mSize(0)
{
}

//----------------------------------------------------------------------------------------------------

template <typename T>
Heap<T>::~Heap()
{
}

//----------------------------------------------------------------------------------------------------

template <typename T>
void Heap<T>::Insert(T value)
{
	mData[mSize] = value;
	HeapUp(mSize);
	++mSize;
}

//----------------------------------------------------------------------------------------------------

template <typename T>
T Heap<T>::Remove()
{
	T result = mData[0];
	mData[0] = mData[--mSize];
	HeapDown(0);
	return result;
}

//----------------------------------------------------------------------------------------------------

template <typename T>
void Heap<T>::HeapUp(int child)
{
	int parent = (child - 1)/2;
	if (parent < 0)
		return;
	if (mData[child] < mData[parent])
	{
		std::swap(mData[parent], mData[child]);
		HeapUp(parent);
	}
}

//----------------------------------------------------------------------------------------------------

template <typename T>
void Heap<T>::HeapDown(int parent)
{
	int lChild = 2 * parent + 1;
	int rChild = 2 * parent + 2;
	
	// No children
	if (lChild >= mSize)
		return;
	int child = lChild;
	if (rChild < mSize && mData[rChild] < mData[lChild])
		child = rChild;
	if (mData[child] < mData[parent])
	{
		std::swap(mData[parent], mData[child]);
		HeapDown(child);
	}
}