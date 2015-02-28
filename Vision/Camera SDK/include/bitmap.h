
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----

#ifndef __CAMERALIBRARY_BITMAP_H__
#define __CAMERALIBRARY_BITMAP_H__

#include "cameralibraryglobals.h"

#define PIXEL int

#define PIXELCOLOR(r,g,b) ((PIXEL)(((unsigned char)(r)|((int)((unsigned char)(g))<<8))|(((int)(unsigned char)(b))<<16)))
#define PIXELCOLORA(r,g,b,a) ((PIXEL)(((unsigned char)(r)|((int)((unsigned char)(g))<<8))|(((int)(unsigned char)(b))<<16))|(((int)(unsigned char)(a))<<24))

#define GetRedCol(rgb)      (rgb&255)
#define GetGreenCol(rgb)    ((rgb>>8)&255)
#define GetBlueCol(rgb)     ((rgb>>16)&255)
#define GetAlphaCol(rgb)    ((rgb>>24)&255)

#define ABGR(a,b,g,r) (((a)<<24)|((b)<<16)|((g)<<8)|(r))

namespace CameraLibrary
{
    PIXEL Color(int r,int g,int b);

    class CLAPI Bitmap
    {
    public:
        enum ColorDepth 
        { 
            EightBit      = 8, 
            SixteenBit    = 16, 
            TwentyFourBit = 24, 
            ThirtyTwoBit  = 32 
        };

        Bitmap( int pixelWidth, int pixelHeight, int byteSpan, ColorDepth cd, const unsigned char *bits = 0 );

        int PixelWidth();
        int PixelHeight();
        int ByteSpan();

        void Initialize( int pixelWidth, int pixelHeight, int byteSpan, ColorDepth cd, const unsigned char *bits = 0, bool IsDIB = false );

        void HorizontalLine(int x, int y, int x2, PIXEL color);
        void HorizontalLineFrom8BitSource(int x, int y, int x2, unsigned char *buffer);
        void PutPixel(int X, int Y, PIXEL color);
        void PutPixelAlpha(int X, int Y, PIXEL color);
        void Circle(int X, int Y, int Radius, PIXEL Color = PIXELCOLOR(255,255,255));
        void FillCircle(int X, int Y, int Radius, PIXEL Color = PIXELCOLOR(255,255,255));
        void Line(int X1, int Y1, int X2, int Y2, PIXEL Color = PIXELCOLOR(255,255,255));
        void Rectangle(int X1, int Y1, int X2, int Y2, PIXEL Color = PIXELCOLOR(255,255,255));
        void SolidRectangle(int X1, int Y1, int X2, int Y2, PIXEL Color = PIXELCOLOR(255,255,255));

        void Clear(unsigned char Intensity = 0);
        void Print(int x, int y, const char *string, PIXEL foreColor = PIXELCOLOR(255,255,255));
        void PrintLarge(int x, int y, const char *string, PIXEL foreColor = PIXELCOLOR(255,255,255));
        void PrintMedium(int x, int y, const char *string, PIXEL foreColor = PIXELCOLOR(255,255,255));

        PIXEL GetPixel(int X, int Y);

        // GUI uses this to draw.
        unsigned char *GetBits();
        
        int  BufferSize();

        // Reset data to zero.
        void ClearBits();

        void Resize(Bitmap* source);

        // There are 8 bits / byte and the bytes / pixel is determined by the color depth.
        int GetBitsPerPixel();
        int GetBytesPerPixel();


        // -----------------------------------------------------------------------
        // Public Destructor
        // -----------------------------------------------------------------------

        virtual ~Bitmap();

    private:

        // -----------------------------------------------------------------------
        // Private Instance Variables
        // -----------------------------------------------------------------------
        ColorDepth     mColorDepth;
        int            mBytesPerPixel;
        int            mWidth;
        int            mHeight;
        int            mSpan;
        unsigned char *mFrameBuffer;
        int            mBitArrayLength;
        bool           mFreeBits;
    };
}

#endif



