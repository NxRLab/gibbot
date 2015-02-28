/*
Consult README.txt on how to set up project in Visual Studio.

DisplayFrames.cpp also requires opengl32.lib, glu32.lib, ws2_32.lib, and 
setupapi.lib to be listed in the additional libraries field to compile and run.
*/

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <iostream>
#include <cameralibrary.h>
#include <moduleprelabel.h>

// optional
#include "supportcode.h"

#define MIN_CAMERAS 2
#define MIN_HUBS 1

using namespace std;
using namespace CameraLibrary;

int show_image(cModuleSync *);

int main()
{
	// startup
	CameraManager::X().WaitForInitialization();
	if (!CameraManager::X().AreCamerasInitialized()) {
		cout << "DisplayFrames: Cameras did not initialize properly; exiting...";
		return -1;
	}

	// set up
	CameraList cameraList;
	HubList hubList;
	if (cameraList.Count() < MIN_CAMERAS || hubList.Count() < MIN_HUBS) {
		cout << "DisplayFrames: not enough cameras or hubs found.  Need at least " 
			<< MIN_CAMERAS << " cameras and " << MIN_HUBS << " hubs.";
		return -1;
	}

	Camera **camera = new Camera *[cameraList.Count()];
	cModuleSync *sync = cModuleSync::Create();
	for (int i = 0; i < cameraList.Count(); i++) {
		camera[i] = CameraManager::X().GetCamera(cameraList[i].UID());
		if (camera[i] != NULL) {
			cout << "Name: " << camera[i]->Name() << endl;
			sync->AddCamera(camera[i]);

			camera[i]->SetExposure(55);
			camera[i]->SetThreshold(200);
			camera[i]->SetIntensity(15);
			camera[i]->AttachModule(new cModulePrelabel());
			camera[i]->Start();
			camera[i]->SetVideoType(Core::ObjectMode);
			camera[i]->SetTextOverlay(true);
			camera[i]->SetMarkerOverlay(true);
		}
		else {
			cout << "DisplayFrames: could not get camera " << i << "." << endl;
		}
	}

	if (sync->CameraCount() == 0) {
		cout << "DisplayFrames: no cameras could be obtained from manager.";
		return -1;
	}

	// code taken from Camera SDK example code.
	cout << "number of cameras: " << sync->CameraCount() << endl;
	show_image(sync);

	// clean up
	sync->RemoveAllCameras();
	cModuleSync::Destroy(sync);
	for (int i = 0; i < cameraList.Count(); i++) {
		if (camera[i] != NULL) {
			camera[i]->Release();
		}
	}
	delete[] camera;

	// shutdown
	CameraManager::X().Shutdown();
	return 0;
}

int show_image(cModuleSync *sync)
{
	int n = sync->CameraCount();

	if (n == 0) {
		cout << "DisplayFrames: no cameras are available to sync.";
		return -1;
	}

	//== Determine camera resolution to size application window ==----
	int maxWidth = 0;
	int maxHeight = 0;
	for (int i = 0; i < n; i++) {
		maxWidth = max(maxWidth, sync->GetCamera(i)->Width());
		maxHeight = max(maxHeight, sync->GetCamera(i)->Height());
	}

	//== Open the application window =============================----
	if (!CreateAppWindow("Display Frames", maxWidth, 
		maxHeight, Bitmap::ThirtyTwoBit, gFullscreen)) {
		cout << "DisplayFrames: could not open app window." << endl;
		return -1;
	}

	//== Create a texture to push the rasterized camera image ====----

	Surface Texture(maxWidth, maxHeight);
	Bitmap *framebuffer = new Bitmap(maxWidth, maxHeight, Texture.PixelSpan() * 4,
		Bitmap::ThirtyTwoBit, Texture.GetBuffer());

	//== lets calculate the FPS of the camera ==---

	double startTime = 0;
	int    loopCount = 0;
	double lps = 0;
	cPrecisionTimeBase timer;

	//== Pool for frame groups ==--

	int i = 0;
	int frameWidth = 0;
	int frameHeight = 0;
	while(true) {
		FrameGroup *frameGroup = sync->GetFrameGroup();

		if(frameGroup) {
			// print info on all frames
			printf("Received %d frames ", frameGroup->Count());

			if (sync->LastFrameGroupMode() == FrameGroup::Hardware) {
				printf("Synchronized\n");
			}
			else {
				printf("Unsynchronized\n");
			}

			for (int j = 0; j < frameGroup->Count(); j++) {
				Frame *frame = frameGroup->GetFrame(j);
				if (frame) {
					printf("  - Camera #%d is reporting %d 2D objects @ %f s\n", j, frame->ObjectCount(), frame->TimeStamp());
					frame->Release();
				}
			}

			// show a frame
			if (i < n-1 && keys[VK_UP]) {
				i++;
			}
			else if (i > 0 && keys[VK_DOWN]) {
				i--;
			}

			Frame *frame = frameGroup->GetFrame(i);
			if (frame) {				
				// resize Surface and Bitmap to fit current frame
				frameWidth = frame->Width();
				frameHeight = frame->Height();
				Texture.Resize(frameWidth, frameHeight);
				framebuffer->Initialize(frameWidth, frameHeight, Texture.PixelSpan() * 4,
					Bitmap::ThirtyTwoBit, Texture.GetBuffer());
				frame->Rasterize(framebuffer);

				// display loops per second
				char st[80];
				sprintf_s(st, 80, "Frame LPS: %.1f", lps);
				framebuffer->PrintLarge((frameWidth - ((int)strlen(st) * 12)) / 2, frameHeight / 2, st);
				
				// display current frame
				DrawGLScene(&Texture, frameWidth, frameHeight);
				frame->Release();
			}
			
			frameGroup->Release();
		}

		if (keys[VK_ESCAPE]) {
			break;
		}

		Sleep(2);

		//== Service Windows Message System ==--

		if (!PumpMessages())
			break;

		//== Every second update the FPS reported ==--
		loopCount++;

		double currentTime = timer.Elapsed();

		if (currentTime - startTime > 1.0) {
			double latestLPS = loopCount / (currentTime - startTime);

			startTime = currentTime;
			loopCount = 0;

			if (lps == 0)
				lps = latestLPS;
			else
				lps = (0.5*lps) + (0.5*latestLPS);
		}
	}

	//== Close window ==--

	CloseWindow();

	return 0;
}