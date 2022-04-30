//-----------------------------------------------------------------------------
// File : rsResource.cpp
// Desc : Resource
// Copyright(c) Project Asura. All right resreved.
//-----------------------------------------------------------------------------


namespace rs {

///////////////////////////////////////////////////////////////////////////////
// TextureResource class
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
//      コンストラクタです.
//-----------------------------------------------------------------------------
TextureResource::TextureResource()
: m_RefCount    (0)
, m_Usage       (0)
, m_pTexture    (nullptr)
{ /* DO_NOTHING */ }

//-----------------------------------------------------------------------------
//      デストラクタです.
//-----------------------------------------------------------------------------
TextureResource::~TextureResource()
{ Term(); }

//-----------------------------------------------------------------------------
//      初期化処理です.
//-----------------------------------------------------------------------------
bool TextureResource::Init(a3d::IDevice* pDevice, const PassTextureDesc& desc, uint32_t usage)
{
    if (pDevice == nullptr)
    { return false; }

    a3d::RESOURCE_STATE state = a3d::RESOURCE_STATE_GENERAL;

    if (desc.Format == a3d::RESOURCE_FORMAT_D16_UNORM
     || desc.Format == a3d::RESOURCE_FORMAT_D24_UNORM_S8_UINT
     || desc.Format == a3d::RESOURCE_FORMAT_D32_FLOAT)
    { state = a3d::RESOURCE_STATE_DEPTH_WRITE; }

    a3d::TextureDesc resDesc = {};
    resDesc.Dimension           = a3d::RESOURCE_DIMENSION_TEXTURE2D;
    resDesc.Width               = desc.Width;
    resDesc.Height              = desc.Height;
    resDesc.Format              = desc.Format;
    resDesc.DepthOrArraySize    = 1;
    resDesc.MipLevels           = 1;
    resDesc.SampleCount         = 1;
    resDesc.Layout              = a3d::RESOURCE_LAYOUT_OPTIMAL;
    resDesc.Usage               = usage;
    resDesc.InitState           = state;
    resDesc.HeapType            = a3d::HEAP_TYPE_DEFAULT;

    if (!pDevice->CreateTexture(&resDesc, &m_pTexture))
    { return false; }

    return true;
}

//-----------------------------------------------------------------------------
//      終了処理を行います.
//-----------------------------------------------------------------------------
void TextureResource::Term()
{
    if (m_pTexture != nullptr)
    {
        m_pTexture->Release();
        m_pTexture = nullptr;
    }

    m_State = a3d::RESOURCE_STATE_UNKNOWN;
    m_Usage = 0;
}

//-----------------------------------------------------------------------------
//      参照カウンタを増やします.
//-----------------------------------------------------------------------------
void TextureResource::Increment()
{ m_RefCount++; }

//-----------------------------------------------------------------------------
//      参照カウンタを減らします.
//-----------------------------------------------------------------------------
void TextureResource::Decrement()
{ m_RefCount--; }

//-----------------------------------------------------------------------------
//      参照カウンタを返却します.
//-----------------------------------------------------------------------------
uint32_t TextureResource::GetRefCount() const
{ return m_RefCount; }

//-----------------------------------------------------------------------------
//      リソースステートを取得します.
//-----------------------------------------------------------------------------
a3d::RESOURCE_STATE TextureResource::GetState() const
{ return m_State; }

//-----------------------------------------------------------------------------
//      リソースステートを設定します.
//-----------------------------------------------------------------------------
void TextureResource::SetState(a3d::RESOURCE_STATE state)
{ m_State = state; }

//-----------------------------------------------------------------------------
//      テクスチャを取得します.
//-----------------------------------------------------------------------------
a3d::ITexture* TextureResource::GetTexture() const
{ return m_pTexture; }

//-----------------------------------------------------------------------------
//      テクスチャ構成設定を取得します.
//-----------------------------------------------------------------------------
const PassTextureDesc& TextureResource::GetDesc() const
{ return m_Desc; }

//-----------------------------------------------------------------------------
//      設定が同じかどうかチェックします.
//-----------------------------------------------------------------------------
bool TextureResource::IsEqual(const PassTextureDesc& desc, uint32_t usage) const
{
    return m_Desc.Width  == desc.Width
        && m_Desc.Height == desc.Height
        && m_Desc.Format == desc.Format
        && m_Usage       == usage;
}

} // namespace rs