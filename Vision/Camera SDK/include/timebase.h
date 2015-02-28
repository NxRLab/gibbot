
//==================================================================================-----
//== NaturalPoint 2012
//==================================================================================-----

#ifndef __TIMEBASE_H__
#define __TIMEBASE_H__

#include "cameracommonglobals.h"

#ifdef __PLATFORM__LINUX__
class CLAPI cPrecisionTimeBase
{
public:
    cPrecisionTimeBase();
    ~cPrecisionTimeBase();

    void  CatchUp(void);       // reset elapsed time
    float Elapsed(void);       // returns the elapsed time in seconds

private:
    long  GetRawTime(void);
    long  start;
};
#endif

#ifdef WIN32
class CLAPI cPrecisionTimeBase
{
public:
	cPrecisionTimeBase();
	~cPrecisionTimeBase() {};
	
	void    CatchUp();              //== Reset the timer =============================----
	double  Elapsed();              //== Return Elapsed Milliseconds =============--------
private:
    double  Ticks();
	__int64	mStart;
	__int64	mFrequency;
};
#endif

#endif

