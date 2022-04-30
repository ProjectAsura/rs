//-----------------------------------------------------------------------------
// File : rsBaseAllocator.h
// Desc : Base Allocator
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//! @brief      メモリ確保を行います.
//! 
//! @param[in]      size        確保サイズです.
//! @param[in]      alignment   メモリアライメントです.
//! @return     確保したメモリを返却します.
//-----------------------------------------------------------------------------
void* rs_alloc(size_t size, size_t alignment);

//-----------------------------------------------------------------------------
//! @brief      メモリを解放します.
//! 
//! @param[in]      ptr         解放するメモリ.
//-----------------------------------------------------------------------------
void  rs_free(void* ptr);


namespace rs {

//-----------------------------------------------------------------------------
// Constant Value.
//-----------------------------------------------------------------------------
constexpr size_t kDefaultAlignment = 4;     //!< デフォルトアライメント.

///////////////////////////////////////////////////////////////////////////////
// BaseAllocator
///////////////////////////////////////////////////////////////////////////////
class BaseAllocator
{
public:
    static void* operator new (size_t size) noexcept
    { return rs_alloc(size, kDefaultAlignment); }

    static void* operator new[] (size_t size) noexcept
    { return rs_alloc(size, kDefaultAlignment); }

    static void* operator new (size_t, void* memory) noexcept
    { return memory; }

    static void* operator new[] (size_t, void* memory) noexcept
    { return memory; }

    static void operator delete (void* ptr) noexcept
    { rs_free(ptr); }

    static void operator delete[] (void* ptr) noexcept
    { rs_free(ptr); }

    static void operator delete (void*, void*) noexcept
    { /* DO_NOTHING */ }

    static void operator delete[] (void*, void*) noexcept
    { /* DO_NOTHING */ }
};

} // namespace rs

