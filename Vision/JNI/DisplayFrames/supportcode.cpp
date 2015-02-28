
//============================================================================================-----
//== This is boiler-plate code for bringing up the application's window and
//== initializing OpenGL, and an OpenGL surface class for rendering the camera
//== image as a quad using the 3D hardware.
//============================================================================================-----

#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "cameralibrary.h"
#include "cameramanager.h"
#include "math.h"
#include "stdio.h"
#include "supportcode.h"

int         gWindowWidth ;
int         gWindowHeight;
extern bool gFullscreen;
extern bool gActive;
extern bool	keys[256];	

HDC			hDC=NULL;		            // Private GDI Device Context
bool	    keys[256];		            // Array Used For Scanning Keyboard
bool	    gActive           = TRUE;   // Window Active Flag Set To TRUE By Default
bool	    gFullscreen       = FALSE;  // Fullscreen Flag Set To Fullscreen Mode By Default
GLuint	    texture[1];			        // Storage For One Texture ( NEW )
int         gSoftwareDecimate = 0;


extern HDC  hDC;		    // Private GDI Device Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application
HGLRC		hRC=NULL;		// Permanent Rendering Context

int LoadGLTextures()									// Load Bitmaps And Convert To Textures
{
	return 0;										// Return The Status
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

    gWindowWidth = width;
    gWindowHeight = height;

    glOrtho(0,gWindowWidth,gWindowHeight,0,100,-100);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	return TRUE;										// Initialization Went OK
}

int DrawGLScene(Surface *surf, int width, int height)
{
    if(surf==NULL)
        return true;

    static bool frameThrottler = true;
    frameThrottler=!frameThrottler;

    if(frameThrottler)  //== Only display every other frame in case VSYNC is enabled.  Otherwise
        return true;    //== application would get behind

    int pixelWidth = width; 
    int pixelHeight= height;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The View

    static GLuint ff = 0;

    int tex = surf->GetTexture();
    if(tex==0)
        tex=ff;
    else
        ff=tex;
    if(tex==0)
        return true;

    glBindTexture(GL_TEXTURE_2D, tex);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0,    0, 0);
        glTexCoord2f((GLfloat)pixelWidth/(GLfloat)surf->SurfaceWidth(), 0.0f); glVertex3f( (GLfloat)gWindowWidth,  0, 0);
		glTexCoord2f((GLfloat)pixelWidth/(GLfloat)surf->SurfaceWidth(), (GLfloat)pixelHeight/(GLfloat)surf->SurfaceHeight()); glVertex3f( (GLfloat)gWindowWidth,(GLfloat)gWindowHeight, 0);
		glTexCoord2f(0.0f, (GLfloat)pixelHeight/(GLfloat)surf->SurfaceHeight()); glVertex3f( 0, (GLfloat) gWindowHeight, 0);
	glEnd();

    SwapBuffers(hDC);					// Swap Buffers (Double Buffering)

	return true;										// Keep Going
}


LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				gActive=TRUE;						// Program Is Active
			}
			else
			{
				gActive=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

        case WM_POWERBROADCAST:
            if(wParam == PBT_APMSUSPEND)
            {
                CameraLibrary::CameraManager::X().PrepareForSuspend();
            }
            if(wParam == PBT_APMRESUMEAUTOMATIC)
            {
                CameraLibrary::CameraManager::X().ResumeFromSuspend();
            }
            break;

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}
        case WM_MOVE:
			return 0;								// Jump Back
        case WM_PAINT:
            return 0;
		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
GLvoid CloseWindow(GLvoid)								// Properly Kill The Window
{
	if (gFullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
int windowWidth;
int windowHeight;
const char *windowName;

BOOL CreateAppWindow(const char* title, int width, int height, int bits, bool fullscreenflag)
{
    windowWidth  = width;
    windowHeight = height;
    windowName   = title;

	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	gFullscreen=fullscreenflag;			// Set The Global Fullscreen Flag
    
    HICON hIcon = (HICON)LoadImage(0,IDI_WINLOGO,IMAGE_ICON,0,0,LR_SHARED);

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= 0;
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (gFullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				gFullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (gFullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		CloseWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		CloseWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		CloseWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		CloseWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		CloseWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		CloseWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		CloseWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

//==============================

Surface::Surface(int Width, int Height) : buffer(0), mDirty(true)
{
    //== Use power of 2 texture sizes ==

    mSurfaceWidth = CalculateSize(Width);
    mSurfaceHeight = CalculateSize(Height);

    mSpan = mSurfaceWidth;

    mWidth = Width;
    mHeight = Height;

    buffer = (unsigned char*) malloc(mSurfaceWidth * mSurfaceHeight * BYTESPERPIXEL);

    memset(buffer, 0, mSurfaceWidth * mSurfaceHeight * BYTESPERPIXEL);

    if(buffer==0)
        throw("Unable to allocate surface buffer");

    glGenTextures(1, &mTexture);
    if(mTexture==0)
        throw("Unable to gen OpenGL texture");


    glBindTexture(GL_TEXTURE_2D, mTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mSurfaceWidth, mSurfaceHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}

Surface::~Surface()
{

}

void Surface::RebindTexture()
{
    glGenTextures(1, &mTexture);
    if(mTexture==0)
        throw("Unable to gen OpenGL texture");


    glBindTexture(GL_TEXTURE_2D, mTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mSurfaceWidth, mSurfaceHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}


void Surface::Resize(int Width, int Height)
{
    if(Width==mWidth && Height==mHeight)
        return;

    if(Width<1 || Height<1)
        return;

    int newSize = CalculateSize(Width);

    if(newSize>mSurfaceWidth || newSize>mSurfaceHeight)
    {
        if(buffer!=0)
            free(buffer);

        mSurfaceWidth = newSize;
        mSurfaceHeight = newSize;
        mSpan = mSurfaceWidth;
        mWidth = Width;
        mHeight = Height;
        buffer = (unsigned char*) malloc(mSurfaceWidth * mSurfaceHeight * BYTESPERPIXEL);
        if(buffer==0)
            throw("Unable to allocate surface buffer");

        mDirty = true;
    }
}

int  Surface::CalculateSize(int Width)
{
    int mSize = 1;

    while(mSize<Width)
        mSize*=2;

    return mSize;
}

GLuint Surface::GetTexture()
{
    //if(mDirty==true)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mSurfaceWidth, mSurfaceHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
        mDirty = false;
    }
    return mTexture; 
}

void Surface::PutPixel(int X, int Y, PIXEL Color)
{
    if(X>=0 && Y>=0 && X<mWidth && Y<mHeight)
    {
        unsigned int *point = (unsigned int*)buffer + (Y*mSpan)+X;
        *point = Color;
        mDirty = true;
    }
}

//======= Entry Point ======--

extern int main(int argc, char* argv[]);

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
                   HINSTANCE	hPrevInstance,		// Previous Instance
                   LPSTR		lpCmdLine,			// Command Line Parameters
                   int			nCmdShow)			// Window Show State
{
    return main(0,0);
}

bool FullscreenToggle()
{
    keys[VK_F1]=FALSE;					// If So Make Key FALSE
    CloseWindow();						// Kill Our Current Window
    gFullscreen=!gFullscreen;			// Toggle Fullscreen / Windowed Mode

    if (!CreateAppWindow(windowName,windowWidth,windowHeight,32,gFullscreen))
    {
        MessageBox(0,"Unable to toggle to full screen","Error", MB_OK);
        return 1;
    }

    return true;
}

bool PumpMessages()
{
    MSG msg;

    if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
    {
        if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
            return false;
        else									// If Not, Deal With Window Messages
        {
            TranslateMessage(&msg);				// Translate The Message
            DispatchMessage(&msg);				// Dispatch The Message
        }
    }

    return true;
}


//== Code to pop a simple dialog for 'waiting for cameras' using a message box and
//== no resources required for this sample application.

HHOOK hHook = NULL;

LRESULT CALLBACK CBTHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
		return CallNextHookEx(hHook, nCode, wParam, lParam);

	if (nCode == HCBT_ACTIVATE)
	{
		HWND hWnd = reinterpret_cast<HWND>(wParam);
		SetWindowText(GetDlgItem(hWnd, IDOK), TEXT("Cancel"));
		return 0;
	}

	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	CameraLibrary::CameraList list;

	bool found = false;

	for( int i=0; i<list.Count(); i++ )
	{
		if( list[i].State()==CameraLibrary::Initialized )
		{
			found = true;
		}
	}

	if(found==true)
	{
		HWND hWndActive = GetActiveWindow();

		if( hWndActive!=0 )
		{
			SendMessage(hWndActive, WM_COMMAND, IDCANCEL, 0);
		}
	}
}

bool PopWaitingDialog()
{
	//== hook in so we can create a message box that has only a 'Cancel' button ==--

	hHook = SetWindowsHookEx(WH_CBT, reinterpret_cast<HOOKPROC>(&CBTHookProc), NULL, GetCurrentThreadId());

	UINT_PTR nTimer = SetTimer(0, 100, 3000, TimerProc);
	int iResult = MessageBox( 0, "waiting for connected cameras...", "Camera Initialization", MB_OK );

	if( iResult == IDOK )
	{
		//== user has clicked the cancel button ==--
		UnhookWindowsHookEx(hHook);
		return false;
	}

	KillTimer(0, nTimer);

	return true;
}
