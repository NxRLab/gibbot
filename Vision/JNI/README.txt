How to set up a new project in Visual Studio:

Option 1: The fast way

Load project property files in JNI dir into a new project.
(http://manski.net/2012/01/sharing-project-properties-in-visual-c/)

Option 2: The straightforward way

Assuming the following directory structure

Eigen/ Camera SDK/ VSS/,

where Eigen contains the Eigen library
(http://eigen.tuxfamily.org/index.php?title=Main_Page),
Camera SDK is the Natural Point Optitrack SDK
(http://www.optitrack.com/products/camera-sdk/), and
VSS is your Visual Studio solution folder (i.e., create directory for solution
is checked when making a new project), then open your project's properties page
and make the following edits under Configuration Properties (multiple entries
are appended to the same setting):

C/C++ -> General -> Additional Include Directories = $(SolutionDir)..
C/C++ -> General ->
Additional Include Directories = $(SolutionDir)..\Camera SDK\include
C/C++ -> Preprocessor -> Preprocessor Definitions = CAMERALIBRARY_IMPORTS
C/C++ -> Code Generation -> Runtime Library = Multi-threaded (/MT)

Linker -> General -> Additional Library Directories =
$(SolutionDir)..\Camera SDK\lib

Build Events -> Post Build Event -> Command Line =
XCOPY "$(SolutionDir)..\Camera SDK\lib\CameraLibrary*S.dll" "$(TargetDir)" /D /K /Y
Build Events -> Post Build Event -> Description =
Copy Camera SDK static DLLs into Configuration folder

** 32-bit **
Linker -> Input -> Additional Dependencies = CameraLibrary2010S.lib
** 64-bit **
Linker -> Input -> Additional Dependencies = CameraLibrary2010x64S.lib

** optional **
C/C++ -> Preprocessor -> Preprocessor Definitions = NDEBUG
C/C++ -> Preprocessor -> Preprocessor Definitions = _CONSOLE
C/C++ -> Preprocessor -> Preprocessor Definitions = CORE_IMPORTS

Linker -> Input -> Additional Dependencies = opengl32.lib
Linker -> Input -> Additional Dependencies = glu32.lib
Linker -> Input -> Additional Dependencies = ws2_32.lib
Linker -> Input -> Additional Dependencies = setupapi.lib

** optional 32-bit **
C/C++ -> Preprocessor -> Preprocessor Definitions = WIN32
C/C++ -> Code Generation -> Enable Enhanced Instruction Set =
Streaming SIMD Extensions 2 (/arch:SSE2)

** optional 64-bit **
C/C++ -> Preprocessor -> Preprocessor Definitions = WIN64

The sse2 extensions optimize Eigen's compute time
(http://eigen.tuxfamily.org/index.php?title=Visual_Studio).  The other options
are for the OptiTrack system.  If the assumed directory structure is not used,
then the relative paths with respect to the variable $(SolutionDir) will not
be correct.  Appropriate modifications should be made.  Finally, XCOPY
will copy the static library DLLs into $(TargetDir) if the dlls in the Camera
SDK are newer than $(TargetDir) (/D), without prompting whether the files
should be overwritten (/Y), and with user permission settings preserved (/K).

Each camera name listed in the program corresponds to the serial number located
on the back of the camera in the lower-right corner.  The following link leads to
a discussion about the units of the cameras physical properties:
https://forums.naturalpoint.com/viewtopic.php?f=66&t=8698&p=44539&hilit=imager+width#p44539.


*************** Addendum
In order to compile with Java headers need to include
C/C++ -> General -> Additional Include Directories = $(JAVA_HOME)\include
C/C++ -> General -> Additional Include Directories = $(JAVA_HOME)\include\win32

where $(JAVA_HOME) is assumed to be defined and is where your Java JDK is
locally installed.  For now, JAVA_HOME must be, relative to the JNI project
folder, 

JAVA_HOME = $(SolutionDir)../../jdk/

In other words, the JDK should be installed to a folder called jdk in the gibbot
top-level GitHub directory folder.
