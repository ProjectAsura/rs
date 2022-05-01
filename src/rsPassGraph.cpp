//-----------------------------------------------------------------------------
// File : rsPassGraph.cpp
// Desc : Pass Graph.
// Copyright(c) Project Asura. All right reserved.
//-----------------------------------------------------------------------------


namespace rs {

///////////////////////////////////////////////////////////////////////////////
// PassGraph class
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
//      �R���X�g���N�^�ł�.
//-----------------------------------------------------------------------------
PassGraph::PassGraph()
: m_RefCount        (1)
, m_pDevice         (nullptr)
, m_pGraphicQueue   (nullptr)
, m_pComputeQueue   (nullptr)
, m_JobCount        (0)
, m_pJobs           (nullptr)
, m_FrameIndex      (0)
{
}

//-----------------------------------------------------------------------------
//      �f�X�g���N�^�ł�.
//-----------------------------------------------------------------------------
PassGraph::~PassGraph()
{ Term(); }

//-----------------------------------------------------------------------------
//      �����������ł�.
//-----------------------------------------------------------------------------
bool PassGraph::Init(const PassGraphDesc& desc)
{
    if (desc.MaxJobCount    == 0 
     || desc.pDevice        == nullptr 
     || desc.pGraphicsQueue == nullptr)
    { return false; }

    m_pJobs = new Job[desc.MaxJobCount];

    m_pDevice = desc.pDevice;
    m_pDevice->AddRef();

    m_pGraphicQueue = desc.pGraphicsQueue;
    m_pGraphicQueue->AddRef();

    m_pComputeQueue = desc.pComputeQueue;
    if (m_pComputeQueue != nullptr)
    { m_pComputeQueue->AddRef(); }

    return false;
}

//-----------------------------------------------------------------------------
//      �I���������s���܂�.
//-----------------------------------------------------------------------------
void PassGraph::Term()
{
    for(auto i=0u; i<m_JobCount; ++i)
    {
        // �����܂őҋ@.
        while(!m_pJobs[i].IsFinished())
        { _mm_pause(); }
    }

    if (m_pJobs != nullptr)
    {
        delete[] m_pJobs;
        m_pJobs = nullptr;
    }

    m_JobCount = 0;
    m_Passes.Clear();

    for(auto i=0; i<2; ++i)
    { m_FrameHeap[i].Term(); }

    if (m_pGraphicQueue != nullptr)
    {
        m_pGraphicQueue->Release();
        m_pGraphicQueue = nullptr;
    }

    if (m_pComputeQueue != nullptr)
    {
        m_pComputeQueue->Release();
        m_pComputeQueue = nullptr;
    }

    if (m_pDevice != nullptr)
    {
        m_pDevice->Release();
        m_pDevice = nullptr;
    }
}

//-----------------------------------------------------------------------------
//      �Q�ƃJ�E���^�𑝂₵�܂�.
//-----------------------------------------------------------------------------
void PassGraph::AddRef()
{ m_RefCount++; }

//-----------------------------------------------------------------------------
//      ����������s���܂�.
//-----------------------------------------------------------------------------
void PassGraph::Release()
{
    m_RefCount--;
    if (m_RefCount == 0)
    { delete this; }
}

//-----------------------------------------------------------------------------
//      �Q�ƃJ�E���g���擾���܂�.
//-----------------------------------------------------------------------------
uint32_t PassGraph::GetRefCount() const
{ return m_RefCount; }

//-----------------------------------------------------------------------------
//      �p�X��ǉ����܂�.
//-----------------------------------------------------------------------------
bool PassGraph::AddPass(const Tag& tag, PassSetup setup, PassExecute execute)
{
}

//-----------------------------------------------------------------------------
//      �R���p�C�����܂�.
//-----------------------------------------------------------------------------
void PassGraph::Compile()
{
}

//-----------------------------------------------------------------------------
//      �R�}���h�L���[�ɓo�^���܂�.
//-----------------------------------------------------------------------------
void PassGraph::Commit()
{
    // �R�}���h�L���[�ɓo�^���܂�.
    {
    }

    m_FrameIndex = (m_FrameIndex + 1) & 0x1;
    m_FrameHeap[m_FrameIndex].Reset();
}

//-----------------------------------------------------------------------------
//      �W���u�����擾���܂�.
//-----------------------------------------------------------------------------
uint32_t PassGraph::GetJobCount() const
{ return m_JobCount; }

//-----------------------------------------------------------------------------
//      �W���u���擾���܂�.
//-----------------------------------------------------------------------------
IJob* PassGraph::GetJob(uint32_t index) const
{
    if (index >= m_JobCount)
    { return nullptr; }

    return &m_pJobs[index];
}

//-----------------------------------------------------------------------------
//      ���\�[�X���擾�܂��͐������܂�.
//-----------------------------------------------------------------------------
ResourceHandle PassGraph::GetOrCreate(const PassTextureDesc& desc)
{
}

//-----------------------------------------------------------------------------
//      �����_�[�^�[�Q�b�g�r���[���擾���܂�.
//-----------------------------------------------------------------------------
a3d::IRenderTargetView* PassGraph::GetRTV(const ResourceHandle& handle) const
{
}

//-----------------------------------------------------------------------------
//      �[�x�X�e���V���r���[���擾���܂�.
//-----------------------------------------------------------------------------
a3d::IDepthStencilView* PassGraph::GetDSV(const ResourceHandle& handle) const
{
}

//-----------------------------------------------------------------------------
//      �A���I�[�_�[�h�A�N�Z�X�r���[���擾���܂�.
//-----------------------------------------------------------------------------
a3d::IUnorderedAccessView* PassGraph::GetUAV(const ResourceHandle& handle) const
{
}

//-----------------------------------------------------------------------------
//      �V�F�[�_���\�[�X�r���[���擾���܂�.
//-----------------------------------------------------------------------------
a3d::IShaderResourceView* PassGraph::GetSRV(const ResourceHandle& handle) const
{
}

//-----------------------------------------------------------------------------
//      �����������s���܂�.
//-----------------------------------------------------------------------------
bool PassGraph::Create(const PassGraphDesc& desc, IPassGraph** ppGraph)
{
    auto instance = new PassGraph();
    if (instance == nullptr)
    { return false; }

    if (!instance->Init(desc))
    {
        delete instance;
        return false;
    }

    *ppGraph = instance;
    return true;
}

//-----------------------------------------------------------------------------
//      �p�X�O���t�𐶐����܂�.
//-----------------------------------------------------------------------------
bool CreatePassGraph(const PassGraphDesc& desc, IPassGraph** ppGraph)
{ return PassGraph::Create(desc, ppGraph); }

} // namespace rs