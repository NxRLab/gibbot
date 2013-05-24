
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
#define RECORDED_FRAMES 15
#define NUMBER_OF_POINTS 13
#define X_FRAMES 100


 //== Declarations of functions ==--
vector<vector<Point2f>> GetImagePoints(cModuleSync * sync);
vector<vector<Point3f>> MakeObjectPoints();
void printMat(const Mat& m);
static Mat prepareCameraMatrix(Mat& cameraMatrix0, int rtype);
static Mat prepareDistCoeffs(Mat& distCoeffs0, int rtype);
static void collectCalibrationData( InputArrayOfArrays objectPoints,
                                    InputArrayOfArrays imagePoints1,
                                    InputArrayOfArrays imagePoints2,
                                    Mat& objPtMat, Mat& imgPtMat1, Mat* imgPtMat2,
                                    Mat& npoints );
double mycalibrateCamera( InputArrayOfArrays _objectPoints,
                            InputArrayOfArrays _imagePoints,
                            Size imageSize, InputOutputArray _cameraMatrix, InputOutputArray _distCoeffs,
                            OutputArrayOfArrays _rvecs, OutputArrayOfArrays _tvecs, int flags, TermCriteria criteria );
bool runCalibration( Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs, vector<vector<Point3f> >& objectPoints, 
                    vector<vector<Point2f> >& imagePoints, vector<Mat>& rvecs, vector<Mat>& tvecs);

 //== Definitions of functions ==--

int main(int argc, char* argv[])
{
    printf("==============================================================================\n");
    printf("== Camera Calibration                       NaturalPoint 2010 ==\n");
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


	//== Define Image Size ==-- DBE
	Size imageSize = Size(1280, 1024);

	//== Get Image Points and Object Points==--
	vector<vector<Point2f>> imagePoints = GetImagePoints(sync);
	vector<vector<Point3f>> objectPoints = MakeObjectPoints();   //Only Works for our board (Alternating rows of 3 and 2 dots placed two inches apart horizontally and 1 inch vertically on a plane [z = 0])
	
	//Initialize Camera Matrix and distortion coefficient matrix
	Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
	Mat distCoeffs = Mat::zeros(8, 1, CV_64F);

	//Create rvecs and tvecs output vectors
	vector<Mat> rvecs, tvecs;


	//== Perform Calibration ==-- 
	runCalibration(imageSize, cameraMatrix, distCoeffs, objectPoints, imagePoints, rvecs, tvecs);	

	//== Print Calibration ==-- DBE
	cout << "\nCalibration Results:\n" << endl << "distCoeffs = " << endl;
	printMat(distCoeffs);
	cout << "Camera Matrix" << endl;
	printMat(cameraMatrix);

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




vector<vector<Point2f>> GetImagePoints(cModuleSync * sync)
{
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
	return imagePoints;
}

vector<vector<Point3f>> MakeObjectPoints()
{
	vector<vector<Point3f>> objectPoints (RECORDED_FRAMES);
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
	return objectPoints;
}

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


static Mat prepareCameraMatrix(Mat& cameraMatrix0, int rtype)
{
    Mat cameraMatrix = Mat::eye(3, 3, rtype);
    if( cameraMatrix0.size() == cameraMatrix.size() )
        cameraMatrix0.convertTo(cameraMatrix, rtype);
    return cameraMatrix;
}

static Mat prepareDistCoeffs(Mat& distCoeffs0, int rtype)
{
    Mat distCoeffs = Mat::zeros(distCoeffs0.cols == 1 ? Size(1, 8) : Size(8, 1), rtype);
    if( distCoeffs0.size() == Size(1, 4) ||
       distCoeffs0.size() == Size(1, 5) ||
       distCoeffs0.size() == Size(1, 8) ||
       distCoeffs0.size() == Size(4, 1) ||
       distCoeffs0.size() == Size(5, 1) ||
       distCoeffs0.size() == Size(8, 1) )
    {
        Mat dstCoeffs(distCoeffs, Rect(0, 0, distCoeffs0.cols, distCoeffs0.rows));
        distCoeffs0.convertTo(dstCoeffs, rtype);
    }
    return distCoeffs;
}


static void collectCalibrationData( InputArrayOfArrays objectPoints,
                                    InputArrayOfArrays imagePoints1,
                                    InputArrayOfArrays imagePoints2,
                                    Mat& objPtMat, Mat& imgPtMat1, Mat* imgPtMat2,
                                    Mat& npoints )
{
    int nimages = (int)objectPoints.total();
    int i, j = 0, ni = 0, total = 0;
    CV_Assert(nimages > 0 && nimages == (int)imagePoints1.total() &&
        (!imgPtMat2 || nimages == (int)imagePoints2.total()));

	cout << " nimages:  " << nimages << endl;
    for( i = 0; i < nimages; i++ )
    {
		printMat(objectPoints.getMat(i));
        ni = objectPoints.getMat(i).checkVector(3, CV_32F);
        CV_Assert( ni >= 0 );
        total += ni;
    }

    npoints.create(1, (int)nimages, CV_32S);
    objPtMat.create(1, (int)total, CV_32FC3);
    imgPtMat1.create(1, (int)total, CV_32FC2);
    Point2f* imgPtData2 = 0;

    if( imgPtMat2 )
    {
        imgPtMat2->create(1, (int)total, CV_32FC2);
        imgPtData2 = imgPtMat2->ptr<Point2f>();
    }

    Point3f* objPtData = objPtMat.ptr<Point3f>();
    Point2f* imgPtData1 = imgPtMat1.ptr<Point2f>();

    for( i = 0; i < nimages; i++, j += ni )
    {
        Mat objpt = objectPoints.getMat(i);
        Mat imgpt1 = imagePoints1.getMat(i);
        ni = objpt.checkVector(3, CV_32F);
        int ni1 = imgpt1.checkVector(2, CV_32F);
        CV_Assert( ni > 0 && ni == ni1 );
        npoints.at<int>(i) = ni;
        memcpy( objPtData + j, objpt.data, ni*sizeof(objPtData[0]) );
        memcpy( imgPtData1 + j, imgpt1.data, ni*sizeof(imgPtData1[0]) );

        if( imgPtData2 )
        {
            Mat imgpt2 = imagePoints2.getMat(i);
            int ni2 = imgpt2.checkVector(2, CV_32F);
            CV_Assert( ni == ni2 );
            memcpy( imgPtData2 + j, imgpt2.data, ni*sizeof(imgPtData2[0]) );
        }
    }
}

double mycalibrateCamera( InputArrayOfArrays _objectPoints,
                            InputArrayOfArrays _imagePoints,
                            Size imageSize, InputOutputArray _cameraMatrix, InputOutputArray _distCoeffs,
                            OutputArrayOfArrays _rvecs, OutputArrayOfArrays _tvecs, int flags, TermCriteria criteria )
{
    int rtype = CV_64F;
    Mat cameraMatrix = _cameraMatrix.getMat();
    cameraMatrix = prepareCameraMatrix(cameraMatrix, rtype);
    Mat distCoeffs = _distCoeffs.getMat();
    distCoeffs = prepareDistCoeffs(distCoeffs, rtype);
    if( !(flags & CALIB_RATIONAL_MODEL) )
        distCoeffs = distCoeffs.rows == 1 ? distCoeffs.colRange(0, 5) : distCoeffs.rowRange(0, 5);

    int i;
    size_t nimages = _objectPoints.total();
    CV_Assert( nimages > 0 );
    Mat objPt, imgPt, npoints, rvecM((int)nimages, 3, CV_64FC1), tvecM((int)nimages, 3, CV_64FC1);
    collectCalibrationData( _objectPoints, _imagePoints, noArray(),
                            objPt, imgPt, 0, npoints );
    CvMat c_objPt = objPt, c_imgPt = imgPt, c_npoints = npoints;
    CvMat c_cameraMatrix = cameraMatrix, c_distCoeffs = distCoeffs;
    CvMat c_rvecM = rvecM, c_tvecM = tvecM;

    double reprojErr = cvCalibrateCamera2(&c_objPt, &c_imgPt, &c_npoints, imageSize,
                                          &c_cameraMatrix, &c_distCoeffs, &c_rvecM,
                                          &c_tvecM, flags, criteria );

    bool rvecs_needed = _rvecs.needed(), tvecs_needed = _tvecs.needed();

    if( rvecs_needed )
        _rvecs.create((int)nimages, 1, CV_64FC3);
    if( tvecs_needed )
        _tvecs.create((int)nimages, 1, CV_64FC3);

    for( i = 0; i < (int)nimages; i++ )
    {
        if( rvecs_needed )
        {
            _rvecs.create(3, 1, CV_64F, i, true);
            Mat rv = _rvecs.getMat(i);
            memcpy(rv.data, rvecM.ptr<double>(i), 3*sizeof(double));
        }
        if( tvecs_needed )
        {
            _tvecs.create(3, 1, CV_64F, i, true);
            Mat tv = _tvecs.getMat(i);
            memcpy(tv.data, tvecM.ptr<double>(i), 3*sizeof(double));
        }
    }
    cameraMatrix.copyTo(_cameraMatrix);
    distCoeffs.copyTo(_distCoeffs);

    return reprojErr;
}

bool runCalibration( Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs, vector<vector<Point3f> >& objectPoints, 
                    vector<vector<Point2f> >& imagePoints, vector<Mat>& rvecs, vector<Mat>& tvecs)
{
	TermCriteria criteria=TermCriteria( TermCriteria::COUNT+TermCriteria::EPS, 30, DBL_EPSILON);
    //Find intrinsic and extrinsic camera parameters

	vector<Mat> objpnts (RECORDED_FRAMES);
	vector<Mat> imgpnts (RECORDED_FRAMES);
	for(int i = 0; i < RECORDED_FRAMES; i++)
	{
		imgpnts[i] = Mat(imagePoints[i], true);
		objpnts[i] = Mat(objectPoints[i], true);
	}


	double rms = mycalibrateCamera(objpnts, imgpnts, imageSize, cameraMatrix,
                                 distCoeffs, rvecs, tvecs, 0, criteria);
    
	imgpnts.clear();
	objpnts.clear();

	std::cout << "Re-projection error reported by calibrateCamera: "<< rms << endl;

    bool ok = checkRange(cameraMatrix) && checkRange(distCoeffs);

    return ok;
}