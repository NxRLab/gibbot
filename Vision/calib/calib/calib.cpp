
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

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
#define RECORDED_FRAMES 3
#define NUMBER_OF_POINTS 13
#define X_FRAMES 100

void printMat(const Mat& m)
{
	cout << "[";
	for (int i = 0; i < m.rows; i++) {
		for (int j = 0; j < m.cols; j++) {
			cout << m.at<double>(i,j) << " ";
		}
		cout << "\n ";
	}
	cout << "]\n";
}

static bool runCalibration( vector<vector<Point3f> > objectPoints, vector<vector<Point2f> > imagePoints,
                    Size imageSize, float aspectRatio,
                    int flags, Mat& cameraMatrix, Mat& distCoeffs,
                    vector<Mat>& rvecs, vector<Mat>& tvecs)
{
    cameraMatrix = Mat::eye(3, 3, CV_64F);
    if( flags & CV_CALIB_FIX_ASPECT_RATIO )
        cameraMatrix.at<double>(0,0) = aspectRatio;

    distCoeffs = Mat::zeros(8, 1, CV_64F);

    //objectPoints.resize(imagePoints.size(),objectPoints[0]);

    double rms = calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix,
                    distCoeffs, rvecs, tvecs, flags|CV_CALIB_FIX_K4|CV_CALIB_FIX_K5);
                    ///*|CV_CALIB_FIX_K3*/|CV_CALIB_FIX_K4|CV_CALIB_FIX_K5);
    printf("RMS error reported by calibrateCamera: %g\n", rms);

    bool ok = checkRange(cameraMatrix) && checkRange(distCoeffs);

    
    return ok;
}


int main(int argc, char* argv[])
{
    printf("==============================================================================\n");
    printf("== Frame Synchronization Example                          NaturalPoint 2010 ==\n");
    printf("==============================================================================\n\n");
	
	Mat M(2,2, CV_8UC3, Scalar(0,0,255));
	printMat(M);

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

    //== Create Image Points Vector of Vectors ==-- DBE
	vector<vector<Point2f>> imagePoints (RECORDED_FRAMES);
	for(int i = 0; i < RECORDED_FRAMES; i++)
		imagePoints[i].resize(NUMBER_OF_POINTS);
	
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
						//== Record a point into imagePoints ==-- DBE
						if(frame->ObjectCount() == NUMBER_OF_POINTS)
						{
							imagePoints[TotalFrames][j] = Point2f(object->X(), object->Y());
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
    //== Create Object Points ==-- DBE
	vector<vector<Point3f>> objectPoints (RECORDED_FRAMES);   //Point3f instead of 2f
	for (int i = 0; i < RECORDED_FRAMES; i++)
		objectPoints[i].resize(NUMBER_OF_POINTS);
	int x, y, z;
	for( int i = 0; i < RECORDED_FRAMES; i++)
	{
		x = 0;
		y = 0;
		z = 0;
		for ( int j = 0; j < NUMBER_OF_POINTS; j++)
		{
			objectPoints[i][j] = Point3f(x, y, z);
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
///*
	//== Print Object Points ==-- DBE
	for( int i = 0; i < RECORDED_FRAMES; i++)
	{
		for ( int j = 0; j < NUMBER_OF_POINTS; j++)
		{
			std::cout << objectPoints[i][j];
		}
		cout << endl << endl;
	}
///*
	//== Print Image Points ==-- DBE
	for( int i = 0; i < RECORDED_FRAMES; i++)
	{
		for ( int j = 0; j < NUMBER_OF_POINTS; j++)
		{
			std::cout << imagePoints[i][j];
		}
		cout << endl << endl;
	}
//*/

	//== Define Image Size ==-- DBE
	Size imageSize = Size(1280, 1024);

    //Initialize Camera Matrix
	Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
	cout << "cameaMatrix = ";
	printMat(cameraMatrix);


	// double aspectRatio=1;
	 //Get initial Camera Matrix; doesn't work
	// cameraMatrix=initCameraMatrix2D(objectPoints,imagePoints,imageSize,aspectRatio);


	 
	//Initialize distCoeffs
	Mat distCoeffs;
	distCoeffs = Mat::zeros(8, 1, CV_64F);

	//Create rvecs and tvecs output vectors
	vector<Mat> rvecs, tvecs;
	

	//== Define Flags ==-- DBE
	int flags=0;

	//== Define Criteria ==-- DBE
	TermCriteria criteria=TermCriteria( TermCriteria::COUNT+TermCriteria::EPS, 30, DBL_EPSILON);

	
	cout<<"Frames in objectPoints: "<<objectPoints.size()<<endl;
	cout<<"Frames in imagePoints:  "<<imagePoints.size()<<endl;
	cout<<"Points in a frame of objectPoints: "<<objectPoints[2].size()<<endl;
	cout<<"Points in a frame of imagePoints:  "<<imagePoints[2].size()<<endl;

	cout<<"imageSize="<<imageSize.width<<","<<imageSize.height<<endl;
	cout << "distCoeffs = ";
	printMat(distCoeffs);

	runCalibration( objectPoints, imagePoints,
                    imageSize, 1,
                    flags, cameraMatrix, distCoeffs,
                    rvecs, tvecs);

	//== Perform Calibration ==-- DBE
	//double Re_Projection_Error =  calibrateCamera(objectPoints, imagePoints, imageSize,
		//cameraMatrix, distCoeffs, rvecs, tvecs, flags);
		//criteria);

	

	//== Print Calibration ==-- DBE
	cout << "\nCalibration Results:\n" << endl;
	cout << "Camera Matrix" << cameraMatrix << endl;
	//cout << endl << "Re-projection Error: " << Re_Projection_Error << endl;

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
