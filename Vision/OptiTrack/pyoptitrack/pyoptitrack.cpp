#include <Python.h>
#include "cameralibrary.h"
#include <vector>

using namespace CameraLibrary;

class CameraListener : public cCameraListener
{
	Camera *camera;
	PyObject *callback;

public:

	CameraListener(Camera *camera, PyObject *callback)
		: camera(camera), callback(callback)
	{
		Py_INCREF(callback);
	}

	~CameraListener()
	{
		camera->RemoveListener(this);
		camera->Release();
		Py_DECREF(callback);
	}

	// executed on background thread!
    virtual void FrameAvailable()
	{
		Frame *frame = camera->GetFrame();
		if (frame) {
			int count = frame->ObjectCount();
			
			// Synchronize with the Python interpreter
			PyGILState_STATE gstate = PyGILState_Ensure();

			PyObject *blobs = PyList_New(count);
			for (int i = 0; i < count; i++) {
				cObject *obj = frame->Object(i);
				PyObject *item = Py_BuildValue("(f,f)", obj->X(), obj->Y());
				PyList_SetItem(blobs, i, item);
			}

			PyObject *arglist = Py_BuildValue("(i,O)", camera->UID(), blobs);
			PyEval_CallObject(callback, arglist);
			Py_DECREF(arglist);

			// End synchronize
			PyGILState_Release(gstate);

			frame->Release();
		}
	}

    virtual void FrameOverflow()
	{
		// ignore (assume FrameAvailable is doing its job)
	}
    virtual void ButtonPressed()
	{
		// ignore (we don't have buttons)
	}
};

static std::vector<CameraListener *> listeners;

static PyObject *
pyoptitrack_waitForInitialization(PyObject *self, PyObject *args)
{
	//== For OptiTrack Ethernet cameras, it's important to enable development mode if you
	//== want to stop execution for an extended time while debugging without disconnecting
	//== the Ethernet devices.  Lets do that now:

    CameraLibrary_EnableDevelopment();

	//== Initialize connected cameras ==========----
	
    CameraManager::X().WaitForInitialization();

	Py_RETURN_NONE;
}

static PyObject *
pyoptitrack_shutdown(PyObject *self, PyObject *args)
{
	for (size_t i = 0; i < listeners.size(); i++) {
		delete listeners[i];
	}
	listeners.clear();

    CameraManager::X().Shutdown();

	Py_RETURN_NONE;
}

static PyObject *
pyoptitrack_getCameraList(PyObject *self, PyObject *args)
{
	CameraList list;
	int count = list.Count();

	PyObject *result = PyList_New(count);
	for (int i = 0; i < count; i++) {
		PyObject *item = PyInt_FromLong(list[i].UID());
		PyList_SetItem(result, i, item);
	}

	return result;
}

static PyObject *
pyoptitrack_startCamera(PyObject *self, PyObject *args)
{
	int cameraUID;
	int numericLabel;
	PyObject *callback;
	if (!PyArg_ParseTuple(args, "iiO", &cameraUID, &numericLabel, &callback)) {
		return NULL;
	}
	if (!PyCallable_Check(callback)) {
        PyErr_SetString(PyExc_TypeError, "callback parameter must be callable");
        return NULL;
    }
    Camera *camera = CameraManager::X().GetCamera(cameraUID);
	if (!camera) {
		PyErr_SetString(PyExc_ValueError, "Invalid camera UID");
		return NULL;
	}

	CameraListener *listener = new CameraListener(camera, callback);
	listeners.push_back(listener);
	
    camera->SetVideoType(SegmentMode);
	camera->AttachListener(listener);
	camera->SetNumeric(true, numericLabel);
    camera->Start();

	Py_RETURN_NONE;
}

static PyObject *
pyoptitrack_setIntensityForCamera(PyObject *self, PyObject *args)
{
	int cameraUID;
	int intensity;
	if (!PyArg_ParseTuple(args, "ii", &cameraUID, &intensity)) {
		return NULL;
	}
    Camera *camera = CameraManager::X().GetCamera(cameraUID);
	if (!camera) {
		PyErr_SetString(PyExc_ValueError, "Invalid camera UID");
		return NULL;
	}
	if (intensity < 0 || intensity >= 16) {
		PyErr_SetString(PyExc_ValueError, "Intensity value out of range");
		return NULL;
	}

	camera->SetIntensity(intensity);

	Py_RETURN_NONE;
}

static PyObject *
pyoptitrack_getDimensionsForCamera(PyObject *self, PyObject *args)
{
	int cameraUID;
	if (!PyArg_ParseTuple(args, "i", &cameraUID)) {
		return NULL;
	}
    Camera *camera = CameraManager::X().GetCamera(cameraUID);
	if (!camera) {
		PyErr_SetString(PyExc_ValueError, "Invalid camera UID");
		return NULL;
	}
	
	int width = camera->Width();
	int height = camera->Height();

	return Py_BuildValue("(i,i)", width, height);
}

static PyObject *
pyoptitrack_foo(PyObject *self, PyObject *args)
{
	return Py_BuildValue("i", 1337);
}

static PyMethodDef PyoptitrackMethods[] =
{
	{"waitForInitialization", pyoptitrack_waitForInitialization, METH_VARARGS, "no args.  Wait for CameraManager to initialize"},
	{"shutdown", pyoptitrack_shutdown, METH_VARARGS, "no args.  Shut down CameraManager"},
	{"getCameraList", pyoptitrack_getCameraList, METH_VARARGS, "arg: camera UID.  Returns a list of connected camera UIDs"},
	{"startCamera", pyoptitrack_startCamera, METH_VARARGS, "args: cameraUID, numericLabel, callback(cameraUID, blobs).  Displays numeric label on the camera and begins passing lists of (x, y) tuples to callback"},
	{"setIntensityForCamera", pyoptitrack_setIntensityForCamera, METH_VARARGS, "args: camera UID, int [0, 16).  Varies active lighting"},
	{"getDimensionsForCamera", pyoptitrack_getDimensionsForCamera, METH_VARARGS, "arg: camera UID.  Returns a tuple (width, height)"},
	{"foo", pyoptitrack_foo, METH_VARARGS, "just testing"},
	{NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initpyoptitrack(void)
{
	PyObject *m = Py_InitModule("pyoptitrack", PyoptitrackMethods);
}

