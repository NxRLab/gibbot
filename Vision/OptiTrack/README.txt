The OptiTrack SDK is written in C++.  The pyoptitrack module has been written to expose parts of that API that are important to the Gibbot.

The enclosed Visual Studio project outputs pyoptitrack.pyd.  Set the configuration to Release.  Go to Build > Rebuild Solution.

Copy optitrack.pyd and cameralibrary.dll to the directory where your Python code will be executed.


import pyoptitrack
pyoptitrack.waitForInitialization()
print pyoptitrack.getCameraList()  # If this list is non-empty, you're good!