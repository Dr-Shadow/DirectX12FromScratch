#include "Window_Win32.h"
#include "DynamicLibrary.h"

extern "C"
{
	DLL_EXPORT IWindow* entry(void)
	{
		return (new Window_Win32());
	}
}