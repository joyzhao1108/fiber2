#include "Camera_h.h"
#include <windows.h>
//#include "cyapi.h" //USB3.0函数库头文件

int CameraInit ( unsigned int* SerialNumber )
{
	return 0;
}

bool Capture ( unsigned int IntegrationTime )
{
	return true;
}

bool SaveImage ( char* Path, char* Name )
{
	return true;
}

bool LEDOpen ( bool open )
{
	return true;
}
