#include <Python.h>
#include "cameralibrary.h"

using namespace CameraLibrary;

static PyObject *
pyoptitrack_waitForInitialization(PyObject *self, PyObject *args)
{
	//== For OptiTrack Ethernet cameras, it's important to enable development mode if you
	//== want to stop execution for an extended time while debugging without disconnecting
	//== the Ethernet devices.  Lets do that now:

    CameraLibrary_EnableDevelopment();

	//== Initialize connected cameras ==========----
	
    CameraManager::X().WaitForInitialization();

	return Py_None;
}

static PyObject *
pyoptitrack_shutdown(PyObject *self, PyObject *args)
{
    CameraManager::X().Shutdown();

	return Py_None;
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
	if (!PyArg_ParseTuple(args, "i", &cameraUID)) {
		return NULL;
	}
    Camera *camera = CameraManager::X().GetCamera(cameraUID);
	if (!camera) {
		PyErr_SetString(PyExc_ValueError, "Invalid camera UID");
		return NULL;
	}
	
    camera->SetVideoType(SegmentMode);
    camera->Start();

	return Py_None;
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

	return Py_None;
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
pyoptitrack_getBlobsForCamera(PyObject *self, PyObject *args)
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

	Frame *frame = camera->GetFrame();
	if (frame) {
		int count = frame->ObjectCount();
	
		PyObject *result = PyList_New(count);
		for (int i = 0; i < count; i++) {
			cObject *obj = frame->Object(i);
			PyObject *item = Py_BuildValue("(f,f)", obj->X(), obj->Y());
			PyList_SetItem(result, i, item);
		}

		frame->Release();
		return result;
	}

	return Py_None;
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
	{"startCamera", pyoptitrack_startCamera, METH_VARARGS, "arg: camera UID.  Calls SetVideoType(SegmentMode) and Start()"},
	{"setIntensityForCamera", pyoptitrack_setIntensityForCamera, METH_VARARGS, "args: camera UID, int [0, 16).  Varies active lighting"},
	{"getDimensionsForCamera", pyoptitrack_getDimensionsForCamera, METH_VARARGS, "arg: camera UID.  Returns a tuple (width, height)"},
	{"getBlobsForCamera", pyoptitrack_getBlobsForCamera, METH_VARARGS, "arg: camera UID.  Returns a list of (x, y) tuples"},
	{"foo", pyoptitrack_foo, METH_VARARGS, "just testing"},
	{NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initpyoptitrack(void)
{
	PyObject *m = Py_InitModule("pyoptitrack", PyoptitrackMethods);
}

