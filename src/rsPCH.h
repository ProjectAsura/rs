//-----------------------------------------------------------------------------
// File : rsPCH.h
// Desc : Pre-Compile Header.
// Copyright(c) Project Asura. All right reserved.
//-----------------------------------------------------------------------------
#pragma once


#include <new>
#include <cstdint>
#include <cassert>
#include <atomic>

#ifndef RS_ASSERT
    #if defined(DEBUG) || defined(_DEBUG)
        #define     RS_ASSERT(expression)  assert(expression)
    #else
        #define     RS_ASSERT(expression)
    #endif
#endif

#include "rsBaseAllocator.h"
#include "rsFrameHeap.h"
#include "rsList.h"
#include "rsStack.h"

#include <rs.h>
#include "rsPass.h"
#include "rsJob.h"

#include "rsResource.h"
#include "rsResourceMgr.h"
#include "rsPassBuilder.h"
#include "rsPassContext.h"
#include "rsPassGraph.h"
