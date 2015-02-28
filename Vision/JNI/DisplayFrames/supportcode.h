

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <gl\gl.h>   //== OpenGL Headers
#include "bitmap.h"  //== Bitmap Class

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	
BOOL    CreateAppWindow  (const char* title, int width, int height, int bits, bool fullscreenflag);
GLvoid  CloseWindow    (GLvoid);

bool PumpMessages();
bool FullscreenToggle();
bool PopWaitingDialog();

#define BYTESPERPIXEL 4
#define RGBA(x,y,z,a) ((a<<24)|(x<<16)|(y<<8)|z)

extern HDC      hDC;	      // Private GDI Device Context
extern bool	    keys[256];    // Array Used For Scanning Keyboard
extern bool	    gActive;      // Window Active Flag Set To TRUE By Default
extern bool	    gFullscreen;  // Fullscreen Flag Set To Fullscreen Mode By Default

class Surface
{
public:
    Surface (int Width, int Height);
    ~Surface();
    GLuint  GetTexture();
    void    Resize(int Width, int Height);
    int     CalculateSize(int Width);

    int     Width ()        { return mWidth;  }
    int     Height()        { return mHeight; }
    int     SurfaceWidth () { return mSurfaceWidth;  }
    int     SurfaceHeight() { return mSurfaceHeight; }

    void            PutPixel(int X, int Y, PIXEL Color);
    unsigned char * GetBuffer() { return buffer; }
    void            RebindTexture();
    int             PixelSpan() { return mSpan; }
private:
    unsigned char * buffer;
    int             mWidth, mHeight;
    int             mSurfaceWidth, mSurfaceHeight;
    bool            mDirty;
    GLuint          mTexture;
    int             mSpan;
};

int     DrawGLScene     (Surface *surf, int width, int height);
