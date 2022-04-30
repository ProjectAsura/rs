﻿//-----------------------------------------------------------------------------
// File : rsBaseAllocator.cpp
// Desc : Base Allocator.
// Copyright(c) Project Asura. All right reserved.
//-----------------------------------------------------------------------------

namespace {

//-----------------------------------------------------------------------------
// Global Variables.
//-----------------------------------------------------------------------------
static rs::IHeap*   g_pHeap = nullptr;

}// namespace

//-----------------------------------------------------------------------------
//      メモリを確保します.
//-----------------------------------------------------------------------------
void* rs_alloc(size_t size, size_t alignment)
{
    RS_ASSERT(g_pHeap != nullptr);
    return g_pHeap->Alloc(size, alignment);
}

//-----------------------------------------------------------------------------
//      メモリを解放します.
//-----------------------------------------------------------------------------
void rs_free(void* ptr)
{
    RS_ASSERT(g_pHeap != nullptr);
    if (ptr != nullptr)
    { g_pHeap->Free(ptr); }
}

namespace rs {

//-----------------------------------------------------------------------------
//      システムの初期化処理です.
//-----------------------------------------------------------------------------
bool InitSystem(IHeap* pHeap)
{
    if (g_pHeap != nullptr)
    { return false; }

    g_pHeap = pHeap;
    return true;
}

//-----------------------------------------------------------------------------
//      システムの終了処理です.
//-----------------------------------------------------------------------------
void TermSystem()
{
    if (g_pHeap != nullptr)
    { g_pHeap = nullptr; }
}

//-----------------------------------------------------------------------------
//      システムが初期化済みかどうかチェックします.
//-----------------------------------------------------------------------------
bool IsInitSystem()
{ return (g_pHeap != nullptr); }

} // namespace rs