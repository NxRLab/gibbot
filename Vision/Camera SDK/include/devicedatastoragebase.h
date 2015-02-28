
//======================================================================================================-----
//== Copyright NaturalPoint
//======================================================================================================-----

#ifndef __DEVICE_DATA_STORAGE_BASE_H__
#define __DEVICE_DATA_STORAGE_BASE_H__

//== INCLUDES ===========================================================================================----

#include "cameralibraryglobals.h"


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


	virtual int  MaximumSize();
protected:

    //== Helper Functions ===============================================================================----

    unsigned char *mData;		       //== Data block ==================================================----
	CameraLibrary::Camera *mDevice;    //== This is a pointer to the device =============================----

    int            mDataMaxSize;       //== This is the maximum space available for storage =============----
    int            mDataSize;		   //== This is the camera's frame buffer pixel height ==============----
};

#endif

