//-----------------------------------------------------------------------------
// File : rsPassContext.cpp
// Desc : Pass Context.
// Copyright(c) Project Asura. All right resreved.
//-----------------------------------------------------------------------------


namespace rs {

///////////////////////////////////////////////////////////////////////////////
// PassContext class
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
//      引数付きコンストラクタです.
//-----------------------------------------------------------------------------
PassContext::PassContext(PassGraph* pGraph, a3d::ICommandList* pCommandList)
: m_pGraph          (pGraph)
, m_pCommandList    (pCommandList)
{
    RS_ASSERT(m_pGraph != nullptr);
    RS_ASSERT(m_pCommandList != nullptr);
}

//-----------------------------------------------------------------------------
//      レンダーターゲットビューを取得します.
//-----------------------------------------------------------------------------
a3d::IRenderTargetView* PassContext::GetRTV(const ResourceHandle& handle) const
{ return m_pGraph->GetRTV(handle); }

//-----------------------------------------------------------------------------
//      深度ステンシルビューを取得します.
//-----------------------------------------------------------------------------
a3d::IDepthStencilView* PassContext::GetDSV(const ResourceHandle& handle) const
{ return m_pGraph->GetDSV(handle); }

//-----------------------------------------------------------------------------
//      アンオーダードアクセスビューを取得します.
//-----------------------------------------------------------------------------
a3d::IUnorderedAccessView* PassContext::GetUAV(const ResourceHandle& handle) const
{ return m_pGraph->GetUAV(handle); }

//-----------------------------------------------------------------------------
//      シェーダリソースビューを取得します.
//-----------------------------------------------------------------------------
a3d::IShaderResourceView* PassContext::GetSRV(const ResourceHandle& handle) const
{ return m_pGraph->GetSRV(handle); }

//-----------------------------------------------------------------------------
//      コマンドリストを取得します.
//-----------------------------------------------------------------------------
a3d::ICommandList* PassContext::GetCommandList() const
{ return m_pCommandList; }

} // namespace rs
