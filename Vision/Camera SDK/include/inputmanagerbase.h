
//=============================================================================================-----
//== Copyright NaturalPoint, All Rights Reserved
//=============================================================================================-----

#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

//== INCLUDES ==================================================================================----

#include "cameralibraryglobals.h"

//== GLOBAL DEFINITIONS AND SETTINGS ===========================================================----

//== CLASS DEFINITIONS =========================================================================----

class cInputBase;
class cInputListener;
class cInputManagerListener;

namespace CameraLibrary
{
    class Frame;
}

//== Internal use, not intended for Camera SDK users but are necessary
//== for proper functionality.

class cInputObject
{
public:
    enum DeviceTypes
    {
        UnknownCamera = -1, //== Invalid/Unknown Device
        BaseCamera = 0,     //== Camera
        Rev4,               //== CameraRev4
        Rev5,               //== CameraRev5
        Rev6,               //== CameraRev6
        Rev7,               //== CameraRev7
        Rev8,               //== CameraRev8
        Rev9,               //== CameraRev9
        Rev10,              //== CameraRev10
        Rev11,              //== CameraRev11
        Rev12,              //== CameraRev12
        Rev13,              //== CameraRev13
        Rev14,              //== CameraRev14
        Rev15,              //== CameraRev15
        Rev16,              //== CameraRev16
        Rev17,              //== CameraRev17
        Rev18,              //== CameraRev18
        Rev21,              //== CameraRev21
        Rev22,              //== CameraRev22
        Rev23,              //== CameraRev23
        Rev24,              //== CameraRev24
        Rev25,              //== CameraRev25
        Rev26,              //== CameraRev26
        Rev27,              //== CameraRev27
        Rev28,              //== CameraRev28
        Rev29,              //== CameraRev29
        Rev30,              //== CameraRev30
        Rev31,              //== CameraRev31
        Rev32,              //== CameraRev32
        Rev33               //== CameraRev33
    };

    cInputObject();
    ~cInputObject();

    DeviceTypes DeviceType();
    void        SetDeviceType(DeviceTypes Type);

    void        SetSubModel(int subModel);
    int         SubModel();
private:
    DeviceTypes mDeviceType;
    int         mSubModel;
};

//== Internal use, not intended for Camera SDK users but are necessary
//== for proper functionality.

class CLAPI InputManager
{
public:
    InputManager()  { mListener = 0; };
    ~InputManager() {};

    enum ConnectionTypes
    {
        NoConnection = 0,
        USB,
        File,
        Memory,
        Ethernet,
        TestPattern,
        ConnectionTypeCount
    };


protected:
    cInputManagerListener * mListener;
};


//== Internal use, not intended for Camera SDK users but are necessary
//== for proper functionality.

class cVirtualConfigurationData
{
public:
    cVirtualConfigurationData() { CameraID=0; };
    ~cVirtualConfigurationData() {};
    
    char CameraName[CameraLibrary::kCameraNameMaxLen];
    int CameraWidth;
    int CameraHeight;
    int CameraFrameRate;
    int CameraRevision;
    int CameraSerial;
    int CameraID;
};

//== Internal use, not intended for Camera SDK users but are necessary
//== for proper functionality.

class CLAPI cInputListener
{
public:
    cInputListener()  {};
    ~cInputListener() {};

    virtual void IncomingData(unsigned char *Buffer, long BufferSize);
    virtual void IncomingComm(unsigned char *Buffer, long BufferSize);
    virtual void IncomingFrame(CameraLibrary::Frame *);
    virtual void IncomingDebugMsg(const char *Text) {};
    virtual void IncomingDisconnect();
    virtual void SendVirtualConfigurationData(cVirtualConfigurationData *);
    virtual void IncomingXACTError() {};
    virtual void IncomingTelemetryFanSpeed(float FanSpeed) {};
    virtual void IncomingTelemetryCameraTemp(float CameraTemp) {};
    virtual void IncomingTelemetryMasterMAC(const char MAC[6], bool Master) {};
};


//== Internal use, not intended for Camera SDK users but are necessary
//== for proper functionality.

class CLAPI cInputManagerListener
{
public:
    cInputManagerListener()  {};
    ~cInputManagerListener() {};

    virtual void DeviceConnected() {};
    virtual void DeviceRemoved()   {};
};


#endif

