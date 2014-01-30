
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----

#ifndef __DEVICE_DATA_STORAGE_BASE_H__
#define __DEVICE_DATA_STORAGE_BASE_H__

//== INCLUDES ===========================================================================================----

#include "cameralibraryglobals.h"
#include "serializer.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----

//== CLASS DEFINITIONS ==================================================================================----

namespace CameraLibrary
{
	class Camera;
}

class CLAPI cDeviceDataStorageBase
{
public:
	cDeviceDataStorageBase (CameraLibrary::Camera *Device=0);
    ~cDeviceDataStorageBase();

	virtual void ReadData(Core::cSerializer &Serial);
	virtual void WriteData(Core::cSerializer &Serial);

	virtual int  MaximumSize();
protected:

    //== Helper Functions ===============================================================================----

    unsigned char *mData;		       //== Data block ==================================================----
	CameraLibrary::Camera *mDevice;    //== This is a pointer to the device =============================----

    int            mDataMaxSize;       //== This is the maximum space available for storage =============----
    int            mDataSize;		   //== This is the camera's frame buffer pixel height ==============----
};

#endif

