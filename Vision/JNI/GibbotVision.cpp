#include <jni.h>
#include <iostream>
#include <mutex>
#include <cameralibrary.h>
#include "GibbotVision.h"

using namespace std;
using namespace CameraLibrary;

#define MIN_CAMERAS 2
#define MIN_HUBS 1

class JNIListener : public cModuleSyncListener {
public:
	void FrameGroupAvailable();
	int GetLEDPixelCoordinates(double *&d);
	int GetGibbotPositions(double *&d);
	vector<double> copy;

private:
	vector<double> positions;
};

int nCams;
int nSuccess;
Camera **camera;
cModuleSync *sync;
JNIListener *listener;
mutex mtx;

void JNIListener::FrameGroupAvailable()
{ 
	mtx.lock();
	// clear previous content
	positions.clear();

	// get coordinates from all cameras/frames
	FrameGroup *frameGroup = sync->GetFrameGroup();
	if (frameGroup) {
		for (int i = 0; i < frameGroup->Count(); i++) {
			Frame *frame = frameGroup->GetFrame(i);
			if (frame) {
				positions.push_back(frame->FrameID());
				positions.push_back(frame->TimeStamp());
				for (int j = 0; j < frame->ObjectCount(); j++) {
					cObject *object = frame->Object(j);
					
					positions.push_back(object->X());
					positions.push_back(object->Y());
					//printf("%f: Camera %d - Object %d: (%f, %f)\n", frame->TimeStamp(), i, j, object->X(), object->Y());
				}
				frame->Release();
			}
		}

		frameGroup->Release();
	}

	mtx.unlock();
}

int JNIListener::GetLEDPixelCoordinates(double *&data)
{
	mtx.lock();
	copy = positions;
	mtx.unlock();

	data = copy.data();
	return static_cast<int> (copy.size());
}

int JNIListener::GetGibbotPositions(double *&data)
{
	mtx.lock();
	copy = positions;
	mtx.unlock();

	// insert clustering algorithm here
	// remember data is null; must allocate
	// space, if necessary.

	return 0;
}

JNIEXPORT jdoubleArray JNICALL Java_GibbotVision_getGibbotData(JNIEnv *env, jobject obj)
{
	int n;
	jdouble *d;
	jdoubleArray jPos;

	d = NULL;
	n = listener->GetLEDPixelCoordinates(d);

	jPos = env->NewDoubleArray(n);
	if (jPos == NULL) {
		return NULL;
	}
	
	env->SetDoubleArrayRegion(jPos, 0, n, d);
	return jPos;
}

JNIEXPORT jboolean JNICALL Java_GibbotVision_startCameras(JNIEnv *env, jobject obj)
{
	// startup
	nSuccess = 0;
	CameraManager::X().WaitForInitialization();
	if (!CameraManager::X().AreCamerasInitialized()) {
		cout << 
			"GibbotVisionDLL: Cameras did not initialize properly; exiting..." 
			<< endl;
		return JNI_FALSE;
	}

	// nSuccess = 1 -- cameras init
	nSuccess++;

	// set up
	CameraList cameraList;
	HubList hubList;
	if (cameraList.Count() < MIN_CAMERAS || hubList.Count() < MIN_HUBS) {
		cout << 
			"GibbotVisionDLL: not enough cameras or hubs found.  Need at least "
			<< MIN_CAMERAS << " cameras and " << MIN_HUBS << " hubs." << endl;
		return JNI_FALSE;
	}

	nCams = cameraList.Count();
	camera = new Camera *[nCams];
	listener = new JNIListener();
	sync = cModuleSync::Create();
	sync->AttachListener(listener);

	for (int i = 0; i < nCams; i++) {
		camera[i] = CameraManager::X().GetCamera(cameraList[i].UID());
		if (camera[i] != NULL) {
			cout << "Name: " << camera[i]->Name() << endl;
			sync->AddCamera(camera[i]);

			camera[i]->SetExposure(38);
			camera[i]->SetThreshold(200);
			camera[i]->SetIntensity(15);
			//camera[i]->AttachModule(new cModulePrelabel());
			camera[i]->SetVideoType(Core::ObjectMode);
			camera[i]->SetTextOverlay(true);
			camera[i]->Start();
		}
		else {
			cout << "GibbotVisionDLL: could not get camera " << i << "." << endl;
		}
	}

	// nSuccess = 2 -- min # of cams & hubs
	nSuccess++;

	if (sync->CameraCount() == 0) {
		cout << "GibbotVisionDLL: no cameras could be obtained from manager.";
		return JNI_FALSE;
	}

	// nSucess = 3 -- cameras synced
	nSuccess++;

	return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_GibbotVision_stopCameras(JNIEnv *env, jobject obj)
{
	// clean up
	if (nSuccess >= 3) {
		sync->RemoveAllCameras();
	}
	
	if (nSuccess >= 2) {
		sync->RemoveListener(listener);
		cModuleSync::Destroy(sync);
		for (int i = 0; i < nCams; i++) {
			if (camera[i] != NULL) {
				for (int j = 0; j < camera[i]->ModuleCount(); j++) {
					cCameraModule *module = camera[i]->Module(j);
					camera[i]->RemoveModule(module);
				}
				camera[i]->Release();
			}
		}

		delete listener;
		delete[] camera;
	}

	if (nSuccess >= 1) {
		CameraManager::X().Shutdown();
	}

	return CameraManager::X().AreCamerasShutdown() ? JNI_TRUE : JNI_FALSE;
}