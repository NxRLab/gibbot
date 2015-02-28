/*
Consult README.txt on how to set up project in Visual Studio.
*/

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <iostream>
#include <Eigen/Dense>
#include <cameralibrary.h>

// optional
#include "supportcode.h"

#define MIN_CAMERAS 2
#define MIN_HUBS 1

using namespace std;
using namespace Eigen;
using namespace CameraLibrary;

int show_image();

int main()
{
	MatrixXf A = MatrixXf::Random(3, 2);
	cout << "Here is the matrix A:\n" << A << endl;
	VectorXf b = VectorXf::Random(3);
	cout << "Here is the right hand side b:\n" << b << endl;
	cout << "The least-squares solutions is:\n";
	cout << A.jacobiSvd(ComputeThinU | ComputeThinV).solve(b) << endl;


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
	cout << endl << endl;

	show_image();

	// list individual camera properties
	for (int i = 0; i < cams.Count(); i++) {
		Camera *camera = CameraManager::X().GetCamera(cams[i].UID());
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
			cout << "Distortion Model (Radial 3rd Order Distortion Model):" << endl;
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
	cout << endl << endl;
	

	CameraManager::X().Shutdown();
	cin.get();

	return 0;
}

int show_image()
{
	//== Get a connected camera ================----

	Camera *camera = CameraManager::X().GetCamera();

	//== If no device connected, pop a message box and exit ==--

	if (camera == 0)
	{
		MessageBox(0, "Please connect a camera", "No Device Connected", MB_OK);
		return 1;
	}

	//== Determine camera resolution to size application window ==----

	int cameraWidth = camera->Width();
	int cameraHeight = camera->Height();

	//== Open the application window =============================----

	if (!CreateAppWindow("Camera Library SDK - Sample", cameraWidth, cameraHeight, 32, gFullscreen))
		return 0;

	//== Create a texture to push the rasterized camera image ====----

	//== We're using textures because it's an easy & cpu light 
	//== way to utilize the 3D hardware to display camera
	//== imagery at high frame rates

	Surface  Texture(cameraWidth, cameraHeight);
	Bitmap * framebuffer = new Bitmap(cameraWidth, cameraHeight, Texture.PixelSpan() * 4,
		Bitmap::ThirtyTwoBit, Texture.GetBuffer());

	//== MJPEG Mode ==--

	camera->SetVideoType(Core::ObjectMode);  //== Select MJPEG Video ===================---
	camera->SetAEC(true);             //== Enable Automatic Exposure Control ====---
	camera->SetAGC(true);             //== Enable Automatic Gain Control ========---

	//== Start camera output ==--

	camera->Start();

	//== Turn on some overlay text so it's clear things are     ===---
	//== working even if there is nothing in the camera's view. ===---

	camera->SetTextOverlay(true);

	//== Ok, start main loop.  This loop fetches and displays   ===---
	//== camera frames.                                         ===---

	while (1)
	{
		//== Fetch a new frame from the camera ===---

		Frame *frame = camera->GetFrame();

		if (frame)
		{
			//== Ok, we've received a new frame, lets do something
			//== with it.

			//== Lets have the Camera Library raster the camera's
			//== image into our texture.

			frame->Rasterize(framebuffer);

			//== Display Camera Image ============--

			if (!DrawGLScene(&Texture, frame->Width(), frame->Height()))
				break;

			//== Escape key to exit application ==--

			if (keys[VK_ESCAPE])
				break;

			//== Release frame =========--

			frame->Release();
		}

		Sleep(2);

		//== Service Windows Message System ==--

		if (!PumpMessages())
			break;
	}

	//== Close window ==--

	CloseWindow();

	//== Release camera ==--

	camera->Release();

	return 0;
}

// camerarev13.h is optihub