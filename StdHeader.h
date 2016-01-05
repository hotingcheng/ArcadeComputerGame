#ifndef STDHEADER_H
#define STDHEADER_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#pragma warning( disable : 4786 )

// The Window Header
#include <windows.h>
#include <mmsystem.h>




// C RunTime Header Files
#include <stdlib.h>
#include <tchar.h>
#include <assert.h>


// Local Header Files
#include "GameType.h"
//#include "File.h"
#include "GameError.h"
#include "CScreen.h"
#include "CApplicationInfo.h"
#include "InputLayer.h"
#include "GraphicsLayer.h"
#include "Sound.h"

#endif