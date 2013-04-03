
//=============================================================================================-----
//== NaturalPoint 2010
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

namespace 
{
    const int kDevicePathLen = 256;
}

//== Internal use, not intended for Camera SDK users but are necessary
//== for proper functionality.

class cInputObject
{
public:
    enum DeviceTypes
    {
        BaseCamera = 0,     //== Camera
        SNAV3TIR3,          //== CameraRev4
        TIR4,               //== CameraRev5
        C120,               //== CameraRev6
        V100,               //== CameraRev7
        SNAV4,              //== CameraRev8
        TIR5,               //== CameraRev9
        HardwareKey,        //== CameraRev10
        S250E,              //== CameraRev11
        V100R2,             //== CameraRev12
        OptiHub,            //== CameraRev13
        V120Slim,           //== CameraRev14
        V120R2,             //== CameraRev15
        TBAR3,              //== CameraRev16
        TBAR2,              //== CameraRev17
        TIR5V2,             //== CameraRev18
        X150,               //== CameraRev21
        NPInternal2,        //== CameraRev22 (WCB)
        ESYNC,              //== CameraRev23 (eSync)
        IZHub,              //== CameraRev24
        IZ120,              //== CameraRev25
        M360,               //== CameraRev26
        X150SLIM            //== CameraRev27
    };

    cInputObject()  { mDeviceType = cInputObject::BaseCamera; };
    ~cInputObject() {}; 

    DeviceTypes DeviceType() { return mDeviceType; }
    void        SetDeviceType(DeviceTypes Type) { mDeviceType = Type; }

private:
    DeviceTypes mDeviceType;
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

