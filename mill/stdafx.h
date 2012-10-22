#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <shellapi.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <atlbase.h>
#include <atlcom.h>
#include <atlwin.h>
#include <wtl/include/atlapp.h>
#include <wtl/include/atlres.h>
#include <wtl/include/atlctrls.h>
#include <wtl/include/atlctrlx.h>
#include <wtl/include/atlframe.h>
#include <wtl/include/atlcrack.h>
#include <tplib/include/service.h>
#include <tplib/include/pinyin.h>
#include <tplib/include/format_shim.h>
#include <bdlog/include/bdlog.h>
#include <bdlog/include/bdlog_util.h>

#include "serviceid.h"
#include "mill.h"

#undef IDC_STATIC