﻿//-----------------------------------------------------------------------------
// File : rsPass.h
// Desc : Render Pass
// Copyright(c) Project Asura. All right reserved.
//-----------------------------------------------------------------------------
#pragma once


namespace rs {

//-----------------------------------------------------------------------------
// Forward Declarations.
//-----------------------------------------------------------------------------
class PassGraph;


///////////////////////////////////////////////////////////////////////////////
// PassBarrier structure
///////////////////////////////////////////////////////////////////////////////
struct PassBarrier
{
    ResourceHandle          Handle;
    a3d::RESOURCE_STATE     Before;
    a3d::RESOURCE_STATE     After;
};

///////////////////////////////////////////////////////////////////////////////
// Pass class
///////////////////////////////////////////////////////////////////////////////
class Pass : public List<Pass>::Node
{
    //=========================================================================
    // list of friend classes and methods.
    //=========================================================================
    /* NOTHING */

public:
    //=========================================================================
    // public variables.
    //=========================================================================
    Tag             m_Tag           = {};
    uint8_t         m_SyncFlags     = 0;
    bool            m_AsyncCompute  = false;
    PassSetup       m_Setup         = {};
    PassExecute     m_Execute       = {};
    uint32_t        m_BarrierCount  = 0;
    PassBarrier*    m_pBarriers     = nullptr;

    //=========================================================================
    // public methods.
    //=========================================================================

    //-------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //-------------------------------------------------------------------------
    Pass() = default;

    //-------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //-------------------------------------------------------------------------
    Pass(PassGraph* graph)
    : m_pGraph(graph)
    { /* DO_NOTHING */ }

    //-------------------------------------------------------------------------
    //! @brief      参照カウンタを増やします.
    //-------------------------------------------------------------------------
    void Increment()
    { m_RefCount++; }

    //-------------------------------------------------------------------------
    //! @brief      参照カウンタを減らします.
    //-------------------------------------------------------------------------
    void Decrement()
    { m_RefCount--; }

    //-------------------------------------------------------------------------
    //! @brief      参照カウンタを取得します.
    //-------------------------------------------------------------------------
    int32_t GetRefCount() const
    { return m_RefCount; }

    //-------------------------------------------------------------------------
    //! @brief      パスグラフを取得します.
    //-------------------------------------------------------------------------
    PassGraph* GetGraph() const
    { return m_pGraph; }

private:
    //=========================================================================
    // private variables.
    //=========================================================================
    PassGraph*      m_pGraph    = nullptr;
    int32_t         m_RefCount  = 0;

    //=========================================================================
    // private methods.
    //=========================================================================
    /* NOTHING */
};

} // namespace rs