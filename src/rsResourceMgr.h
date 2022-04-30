//-----------------------------------------------------------------------------
// File : rsResourceMgr.h
// Desc : Resource Manager.
// Copyright(c) Project Asura. All right reserved.
//-----------------------------------------------------------------------------
#pragma once


namespace rs {

///////////////////////////////////////////////////////////////////////////////
// ResourceMgr class
///////////////////////////////////////////////////////////////////////////////
class ResourceMgr
{
public:
    ResourceHandle GetOrCreate(a3d::IDevice* pDevice, const PassTextureDesc& desc, uint32_t usage);

    TextureResource& GetResource(const ResourceHandle& handle) const;

private:
    uint32_t            m_ResourceCount;
    TextureResource*    m_pResources;
};

} // namespace rs
