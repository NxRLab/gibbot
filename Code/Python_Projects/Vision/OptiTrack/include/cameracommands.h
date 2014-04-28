
//======================================================================================================-----
//== NaturalPoint 2010
//======================================================================================================-----


//== Internal use, not intended for Camera SDK users but are necessary
//== for proper functionality.

#ifndef __CAMERACOMMANDS_H__
#define __CAMERACOMMANDS_H__

//== INCLUDES ===========================================================================================----

#include "cameralibraryglobals.h"
#include "cameratypes.h"
#include "camera.h"

//== GLOBAL DEFINITIONS AND SETTINGS ====================================================================----


namespace CameraLibrary
{

    class CLAPI cCommand_StorageWriteChunk : public cCameraCommand
    {
    public:
        cCommand_StorageWriteChunk(int StartAddress, unsigned char* Buffer, int BufferSize);
        static cCommand_StorageWriteChunk* Factory(int StartAddress, unsigned char* Buffer, int BufferSize);
    protected:
        cCommand_StorageWriteChunk() {}
        void Execute();
    private:
        int  mStartAddress;
        unsigned char  mChunkData[256];
        int  mChunkDataSize;
    };

    class CLAPI cCommand_StorageReadChunk : public cCameraCommand
    {
    public:
        cCommand_StorageReadChunk(int StartAddress, int BufferSize);

        bool IsComplete();
        unsigned char *Buffer();
    protected:
        cCommand_StorageReadChunk() {}
        void Execute();

        bool WaitForCompletion() { return true; }
        int  ExpectedResponsePacketType();
        void CameraResponse(unsigned char *Buffer, long BufferSize);
    private:
        int  mStartAddress;
        unsigned char  mChunkData[256];
        int  mChunkDataSize;
    };
}

#endif
