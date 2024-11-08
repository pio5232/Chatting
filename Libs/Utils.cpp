#include "LibsPch.h"
#include "Utils.h"

namespace C_Utility
{
	template<typename T>
	ManagerPool<T>::~ManagerPool()
	{
		for (T* elementPtr : _elementArr)
		{
			delete elementPtr;
		}
		_elementArr.clear();
	}
}