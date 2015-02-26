
//==================================================================================-----
//== NaturalPoint (C) 2010
//==================================================================================-----

#ifndef __CAMERALIBRARY__CAMERALIBRARY_H__
#define __CAMERALIBRARY__CAMERALIBRARY_H__

#include "cameralibraryglobals.h"
#include "cameramanager.h"
#include "camera.h"
#include "camerarev21.h"
#include "camerarev16.h"
#include "camerarev15.h"
#include "camerarev14.h"
#include "camerarev13.h"
#include "camerarev12.h"
#include "camerarev11.h"
#include "camerarev10.h"
#include "camerarev9.h"
#include "camerarev8.h"
#include "camerarev7.h"
#include "camerarev6.h"
#include "camerarev5.h"
#include "camerarev4.h"
#include "frame.h"
#include "cameracommands.h"
#include "bitmap.h"
#include "modulefileoutput.h"
#include "modulelogger.h"
#include "moduleconsole.h"
#include "modulelinearwand.h"
#include "moduleprojection.h"
#include "modulesync.h"
#include "modulevector.h"
#include "modulevectorprocessing.h"
#include "cameratypes.h"
#include "singleton.h"

//== GLOBAL DEFINITIONS AND SETTINGS ================================================----

//== GLOBAL SETTINGS ================================================================----

class CLAPI cCameraLibrary {
public:
	cCameraLibrary(void);

	//== Any overall camera library globals can go here ==

};

class CLAPI cCameraLibraryStartupSettings : public CameraLibrary::Singleton<cCameraLibraryStartupSettings>
{
public:
    cCameraLibraryStartupSettings();

	void EnableEthernetDevices(bool Enable);
	bool IsEthernetDevicesEnabled();
	void EnableUSBDevices(bool Enable);
	bool IsUSBDevicesEnabled();
	void EnableDevelopment();
	bool IsDevelopmentEnabled();

    void SetEnableFilterSwitch(bool Enable);
    bool IsFilterSwitchEnabled();

};



class GlobalLibraryStartup
{
public:
    GlobalLibraryStartup();
    ~GlobalLibraryStartup();
    bool Alive() { return true; };
};

extern GlobalLibraryStartup gStartupLibrary;

#ifdef _DEBUG
#define CameraLibrary_EnableDevelopment() cCameraLibraryStartupSettings::X().EnableDevelopment()
#else
#define CameraLibrary_EnableDevelopment()
#endif


#endif
