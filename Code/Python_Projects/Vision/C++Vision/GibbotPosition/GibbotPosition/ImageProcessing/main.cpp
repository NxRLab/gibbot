
//=================================================================================-----
//== NaturalPoint (c)
//== Camera Library SDK Sample
//==
//== This sample brings up a connected camera and displays it's MJPEG output using a
//== GLSL shader that performs edge detection on the camera's image.
//=================================================================================-----

#include "supportcode.h"       //== Boiler-plate code for application window init ===---
#include "cameralibrary.h"     //== Camera Library header file ======================---
#include <math.h>
//#include "Transform.h"
//#include "Cluster.h"
#include "TransformandCluster.h"


using namespace CameraLibrary;
using namespace std;

int main(int argc, char* argv[])
{
	//== For OptiTrack Ethernet cameras, it's important to enable development mode if you
	//== want to stop execution for an extended time while debugging without disconnecting
	//== the Ethernet devices.  Lets do that now:

    CameraLibrary_EnableDevelopment();

	//== Initialize Camera SDK ==--
	
	CameraLibrary::CameraManager::X();

	//== At this point the Camera SDK is actively looking for all connected cameras and will initialize
	//== them on it's own.

	//== Now, lets pop a dialog that will persist until there is at least one camera that is initialized
	//== or until canceled.

	PopWaitingDialog();

    //== Get a connected camera ================----
	CameraList list;
	const Core::cUID cameraUID = list[0].UID();

    Camera *camera = CameraManager::X().GetCamera(cameraUID);

    //== If no device connected, pop a message box and exit ==--

    if(camera==0)
    {
        MessageBox(0,"Please connect a camera","No Device Connected", MB_OK);
        return 1;
    }

	//== Determine camera resolution to size application window ==----
	
    int cameraWidth  = camera->Width();
    int cameraHeight = camera->Height();

	int dimensions[2] = {cameraHeight, cameraWidth}; // rotate camera 

 	//== Open the application window =============================----
		
    //if (!CreateAppWindow("Camera Library SDK - Sample",cameraWidth,cameraHeight,32,gFullscreen))
	//    return 0;

    //== Create a texture to push the rasterized camera image ====----

    //== We're using textures because it's an easy & cpu light 
    //== way to utilize the 3D hardware to display camera
    //== imagery at high frame rates

    //Surface  Texture(cameraWidth, cameraHeight);
    //Bitmap * framebuffer = new Bitmap(cameraWidth, cameraHeight, Texture.PixelSpan()*4,
    //                           Bitmap::ThirtyTwoBit, Texture.GetBuffer());

    //== For this example, I'm going to create a secondary processing frame buffer
    //== as a scratchpad for my image processing algorithm

    //Bitmap * scratchpad = new Bitmap(cameraWidth, cameraHeight, 0, Bitmap::ThirtyTwoBit);


    //== MJPEG Mode ==--

    //camera->SetVideoType(Core::MJPEGMode);  //== Select MJPEG Video =============---
    camera->SetAEC(true);             //== Enable Automatic Exposure Control ====---
    camera->SetAGC(true);             //== Enable Automatic Gain Control ========---

    //== Start camera output ==--
	camera->SetVideoType(Core::SegmentMode);
	camera->SetIntensity(0);
    camera->Start();

    //== Turn on some overlay text so it's clear things are     ===---
    //== working even if there is nothing in the camera's view. ===---

    camera->SetTextOverlay(true);

    //== Ok, start main loop.  This loop fetches and displays   ===---
    //== camera frames.                                         ===---
	int runTag = 0;

    while(1)
    {
        //== Fetch a new frame from the camera ===---

        Frame *frame = camera->GetLatestFrame();

        if(frame)
        {
            
			
			int objcount = frame->ObjectCount();

			if (objcount == 0){
				MessageBox(0,"No objects found. Terminating","No Objects", MB_OK);
				break;
			}

			cObject **objArray = new (nothrow) cObject* [objcount];
			for (int ii = 0; ii < objcount; ii++){
				objArray[ii] = frame->Object(ii);
			}

			

			//get board corners and camera frame corners to feed to transform function
			float * boardArray = getBoardCorners();
			float * cameraArray = getCamCorners(camera);
			
			//Get transform matrix
			MatrixXf TSolve = getTransformData(cameraArray,boardArray);

			float ** newBlobCoords = new (nothrow) float*[objcount];
			for (int jj = 0; jj < objcount; jj++){
				newBlobCoords[jj] = transformBlob(objArray[jj],TSolve);
			}

			//find corner blobs and change them to float arrays
			cObject **cornerArray = getCornerBlobs(objArray,objcount,camera);
			float ** fourCorners = new (nothrow) float * [4];
			for (int kk = 0; kk < 4; kk++){
				fourCorners[kk] = transformBlob(cornerArray[kk],TSolve);
			}

			

			//filter out float arrays
			if (objcount < 4){
				MessageBox(0,"Not enough corners found. Terminating","Too Few Corners", MB_OK);
				break;
			}
			float ** filteredArray = filterBlobs(newBlobCoords, fourCorners, objcount, 4);
			
			//if (objcount != 10) continue;
			//get cluster center
			float * gibbotPositions = new (nothrow) float [6];
			//gibbotPositions = getClusters(filteredArray, objcount - 4);
			float test1 = gibbotPositions[0];
			float test2 = gibbotPositions[1];
			float test3 = gibbotPositions[2];
			float test4 = gibbotPositions[3];
			float test5 = gibbotPositions[4];
			float test6 = gibbotPositions[5];
            //== Escape key to exit application ==--

            if (keys[VK_ESCAPE])
                break;

            //== Release frame =========--

            frame->Release();
        }

	    Sleep(2);

        //== Service Windows Message System ==--

        if(!PumpMessages())
            break;
    }

    //== Close window ==--

    //CloseWindow();

    //== Release camera ==--

    camera->Release();

    //== Shutdown Camera Library ==--

    CameraManager::X().Shutdown();

    //== Exit the application.  Simple! ==--

	return 1;
}