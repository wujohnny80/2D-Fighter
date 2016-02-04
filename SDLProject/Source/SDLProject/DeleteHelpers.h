//====================================================================================================
// Filename:	DeleteHelpers.h
// Description:	A collection of helper functions for freeing memory and other structures
//====================================================================================================
#ifndef _DELETEHELPERS_H_
#define _DELETEHELPERS_H_

template <typename T>
inline void SafeDelete(T*& p)
{
	if (p != nullptr)
	{
		delete p;
		p = nullptr;
	}
}

//----------------------------------------------------------------------------------------------------

template <typename T>
inline void SafeDeleteArray(T*& p)
{
	if (p != nullptr)
	{
		delete[] p;
		p = nullptr;
	}
}

//----------------------------------------------------------------------------------------------------

template <typename T>
inline void SafeDeleteVector(T& vec)
{
	T::iterator it = vec.begin();
	while (it != vec.end())
	{
		if (*it != nullptr)
		{
			SafeDelete(*it);
		}
		++it;
	}
	vec.clear();
}

//----------------------------------------------------------------------------------------------------

template <typename T>
inline void SafeOnLostDevice(T& p)
{
	if (p)
		p->onLostDevice(); 
}

//----------------------------------------------------------------------------------------------------

template <typename T>
inline void SafeOnResetDevice(T& p)
{
	if (p)
		p->onResetDevice(); 
}

//----------------------------------------------------------------------------------------------------

template <typename T>
inline void SafeRelease(T*& p)
{
	if (p != nullptr)
	{
		p->Release();
		p = nullptr;
	}
}

#endif // #ifndef _DELETEHELPERS_H_