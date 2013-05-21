
#define WIN32_LEAN_AND_MEAN  	// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>

// optitrack headers
#include <cameralibrary.h>

// opencv headers
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace CameraLibrary;
using namespace cv;
using namespace std;

// Constants
#define RECORDED_FRAMES 15
#define NUMBER_OF_POINTS 13
#define X_FRAMES 100

int main(int argc, char* argv[])
{
    printf("==============================================================================\n");
    printf("== Frame Synchronization Example                          NaturalPoint 2010 ==\n");
    printf("==============================================================================\n\n");

    //== This example attaches a frame synchronizer for all connected cameras.  Once
    //== attached, it receives their synchronized frame data as a FrameGroup vs. the
    //== GetFrame approach used for a single camera.

    //== For OptiTrack Ethernet cameras, it's important to enable development mode if you
    //== want to stop execution for an extended time while debugging without disconnecting
    //== the Ethernet devices.  Lets do that now:

    CameraLibrary_EnableDevelopment();

	//== Next, lets wait until all connected cameras are initialized ==

    printf("Waiting for cameras to spin up...");
    
    //== Initialize Camera Library ==----

    CameraManager::X().WaitForInitialization();
    
    //== Verify all cameras are initialized ==--

    if(CameraManager::X().AreCamerasInitialized())
        printf("complete\n\n");
    else
    {
        printf("failed (return key to exit)");
        getchar();
        return 1;
    }

    //== Connect to all connected cameras ==----

    Camera *camera[kMaxCameras];
    int     cameraCount=0;

    CameraList list;

    printf("Cameras:\n");

    for(int i=0; i<list.Count(); i++)
    {
        printf("Camera %d >> %s\n", i, list[i].Name());

        camera[i] = CameraManager::X().GetCamera(list[i].UID());
        if(camera[i]==0)
            printf("unable to connected to camera...\n");
        else {
            cameraCount++;
			//camera[i]->SetVideoType(PrecisionMode); <-what's this? -NR
			// values derived from visualtest.exe in camera SDK/bin -NR
			camera[i]->SetExposure(50);
			camera[i]->SetThreshold(200);
			camera[i]->SetIntensity(15);
		}
    }
        
    if(cameraCount==0)
    {
        printf("no cameras (return key to exit)");
        getchar();
        return 1;
    }

    printf("\n");

    //== Create and attach frame synchronizer ==--

    cModuleSync * sync = new cModuleSync();

    for(int i=0; i<cameraCount; i++)
        sync->AddCamera(camera[i]);

    //== Start cameras ==--

    printf("Starting cameras... (any key to exit)\n\n");

    for(int i=0; i<cameraCount; i++)
        camera[i]->Start();

    //== Create Object Points Vector of Vectors ==-- DBE
	vector<vector<Point2f>> objectPoints (RECORDED_FRAMES);
	for(int i = 0; i < RECORDED_FRAMES; i++)
		objectPoints[i].resize(NUMBER_OF_POINTS);
	
	//== Initialize Total Recorded Frame Count ==-- DBE
	int TotalFrames = 0;

	//== Pool for frame groups ==--
    while(!_kbhit() && TotalFrames < RECORDED_FRAMES)
    {
        FrameGroup *frameGroup = sync->GetFrameGroup();

        if(frameGroup)
        {
            //== Print something every 100 frames ==--

            static int frameThrottle = X_FRAMES;
            static int frameCount    = 0;
            frameThrottle = (frameThrottle+1)%100;

            frameCount++;

            if(frameThrottle==0)
            {
                //== Ok, lets print something about this frame group ==--

                printf("Received Group Frame #%d (Contains %d frames)   ", frameCount, frameGroup->Count());

                if(sync->LastFrameGroupMode()==FrameGroup::Hardware)
                    printf("Synchronized\n");
                else
                    printf("Unsynchronized\n");

                for(int i=0; i<frameGroup->Count(); i++)
                {
                    Frame * frame = frameGroup->GetFrame(i);

                    printf("  - Camera #%d is reporting %d 2D objects\n", i, frame->ObjectCount());
					
					// print the objects and display -NR
					cv::Mat M;
					M.create(frame->GetCamera()->Height(), frame->GetCamera()->Width(), CV_32F);
					for(int j = 0; j < frame->ObjectCount(); j++) {
						cObject *object = frame->Object(j);
						printf("\tObject #%d: (%4.2f,%4.2f)\n", j, object->X(), object->Y());
						cv::circle(M, cv::Point2f(object->X(), object->Y()), object->Radius(), cv::Scalar(255, 0, 0));
						//== Record a point into objectPoints ==-- DBE
						if(frame->ObjectCount() == NUMBER_OF_POINTS)
						{
							objectPoints[TotalFrames][j] = Point2f(object->X(), object->Y());
						}
					}

					if(frame->ObjectCount() == NUMBER_OF_POINTS)
						TotalFrames++;

					if(frame->ObjectCount()) {
						cv::imshow("objects", M);
						cv::waitKey(2);
					}

                    frame->Release();
                }

                printf("\n");
            }

            frameGroup->Release();
        }

        Sleep(2);
    }
    //== Create Image Points ==-- DBE
	vector<vector<Point2f>> imagePoints (RECORDED_FRAMES);
	for (int i = 0; i < RECORDED_FRAMES; i++)
		imagePoints[i].resize(NUMBER_OF_POINTS);
	int x, y;
	for( int i = 0; i < RECORDED_FRAMES; i++)
	{
		x = 0;
		y = 0;
		for ( int j = 0; j < NUMBER_OF_POINTS; j++)
		{
			imagePoints[i][j] = Point2f(x, y);
			if (y%2 == 0)
			{
				x= x +2;;
				if (x > 4)
				{
					y++;
					x = 1;
				}
			}
			else
			{
				x = x + 2;
				if (x > 4)
				{
					y++;
					x = 0;
				}
			}
		}
	}
/*
	//== Print Object Points ==-- DBE
	for( int i = 0; i < RECORDED_FRAMES; i++)
	{
		for ( int j = 0; j < NUMBER_OF_POINTS; j++)
		{
			std::cout << objectPoints[i][j];
		}
		cout << endl << endl;
	}

	//== Print Image Points ==-- DBE
	for( int i = 0; i < RECORDED_FRAMES; i++)
	{
		for ( int j = 0; j < NUMBER_OF_POINTS; j++)
		{
			std::cout << imagePoints[i][j];
		}
		cout << endl << endl;
	}
*/

    //== Create Output Arrays ==-- DBE
	Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
	vector<float> distCoeffs;
	vector<Mat> rvecs, tvecs;

	//== Define Image Size ==-- DBE
	Size imageSize = Size(1280, 1024);

	//== Define Flags ==-- DBE
	int flags=0;

	//== Define Criteria ==-- DBE
	TermCriteria criteria=TermCriteria( TermCriteria::COUNT+TermCriteria::EPS, 30, DBL_EPSILON);

	//== Perform Calibration ==-- DBE
	double Re_Projection_Error =  calibrateCamera(objectPoints,  imagePoints, imageSize,
		cameraMatrix, distCoeffs, rvecs, tvecs, flags,
		criteria);

	//== Print Calibration ==-- DBE
	cout << "\nCalibration Results:\n" << endl;
	cout << "Camera Matrix" << cameraMatrix << endl;
	cout << endl << "Re-projection Error: " << Re_Projection_Error << endl;

    //== Destroy synchronizer ==--

    sync->RemoveAllCameras();
    delete sync;

    //== Release cameras ==--

    for(int i=0; i<cameraCount; i++)
        camera[i]->Release();

    //== Disconnect devices and shutdown Camera Library ==--

    CameraManager::X().Shutdown();
	return 0;
}
