/*
Consult README.txt on how to set up project in Visual Studio.
*/

#include <iostream>
#include <cameralibrary.h>

#define MIN_CAMERAS 2
#define MIN_HUBS 1

using namespace std;
using namespace CameraLibrary;

void info(Core::cUID);

int main()
{
	CameraManager::X().WaitForInitialization();
	if (!CameraManager::X().AreCamerasInitialized()) {
		cout << "VisionMain: Cameras did not initialize properly; exiting...";
		cin.get();
		return -1;
	}
	
	// list optitrack hubs and cameras
	HubList hubs;
	CameraList cams;

	if (cams.Count() < MIN_CAMERAS || hubs.Count() < MIN_HUBS) {
		cout << "VisionMain Error: Less than " << MIN_CAMERAS << " cameras and " 
			<< MIN_HUBS << " hub(s) detected; exiting..." << endl;
		CameraManager::X().Shutdown();
		cin.get();
		return -1;
	}

	for (int i = 0; i < cams.Count(); i++) {
		cout << "Camera: " << i << " " << cams[i].Name() << endl;
	}

	for (int i = 0; i < hubs.Count(); i++) {
		cout << "Hub: " << i << " " << hubs[i].Name() << endl;
	}
	cout << endl;

	// list individual camera properties
	for (int i = 0; i < cams.Count(); i++) {
		info(cams[i].UID());
	}

	// list individual hub properties
	for (int i = 0; i < hubs.Count(); i++) {
		info(hubs[i].UID());
	}

	cout << " ======================================== " << endl;
	

	CameraManager::X().Shutdown();
	cin.get();

	return 0;
}

void info(Core::cUID UID)
{
	Camera *camera = CameraManager::X().GetCamera(UID);
	Core::DistortionModel dm;
	if (camera) {
		cout << " ======================================== " << endl;
		cout << "Name: " << camera->Name() << endl;
		cout << "Imager Width (mm): " << camera->ImagerWidth() << endl;
		cout << "Imager Height (mm): " << camera->ImagerHeight() << endl;
		cout << "Focal Length (mm): " << camera->FocalLength() << endl;
		cout << "Hardware Frame Rate (fps): " << camera->HardwareFrameRate() << endl;
		cout << "Physical Pixel Width (px): " << camera->PhysicalPixelWidth() << endl;
		cout << "Physical Pixel Height (px): " << camera->PhysicalPixelHeight() << endl;

		camera->GetDistortionModel(dm);
		cout << "Distortion Model (see Camera SDK/include/camerarevisions.h):" << endl;
		cout << "Distortion (??): " << dm.Distort << endl;
		cout << "Horizontal Focal Length (??): " << dm.HorizontalFocalLength << endl;
		cout << "Vertical Focal Length (??): " << dm.VerticalFocalLength << endl;
		cout << "KC1 (??): " << dm.KC1 << endl;
		cout << "KC2 (??): " << dm.KC2 << endl;
		cout << "KC3 (??): " << dm.KC3 << endl;
		cout << "Lens Center X (??): " << dm.LensCenterX << endl;
		cout << "Lens Center Y (??): " << dm.LensCenterY << endl;
		cout << "Tangential 0 (??): " << dm.Tangential0 << endl;
		cout << "Tangential 1 (??): " << dm.Tangential1 << endl;

		camera->Release();
	}
}