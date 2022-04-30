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
//      コンストラクタです.
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
//      デストラクタです.
//-----------------------------------------------------------------------------
PassGraph::~PassGraph()
{ Term(); }

//-----------------------------------------------------------------------------
//      初期化処理です.
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
//      終了処理を行います.
//-----------------------------------------------------------------------------
void PassGraph::Term()
{
    for(auto i=0u; i<m_JobCount; ++i)
    {
        // 完了まで待機.
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
//      参照カウンタを増やします.
//-----------------------------------------------------------------------------
void PassGraph::AddRef()
{ m_RefCount++; }

//-----------------------------------------------------------------------------
//      解放処理を行います.
//-----------------------------------------------------------------------------
void PassGraph::Release()
{
    m_RefCount--;
    if (m_RefCount == 0)
    { delete this; }
}

//-----------------------------------------------------------------------------
//      参照カウントを取得します.
//-----------------------------------------------------------------------------
uint32_t PassGraph::GetRefCount() const
{ return m_RefCount; }

//-----------------------------------------------------------------------------
//      パスを追加します.
//-----------------------------------------------------------------------------
bool PassGraph::AddPass(const Tag& tag, PassSetup setup, PassExecute execute)
{
}

//-----------------------------------------------------------------------------
//      コンパイルします.
//-----------------------------------------------------------------------------
void PassGraph::Compile()
{
}

//-----------------------------------------------------------------------------
//      コマンドキューに登録します.
//-----------------------------------------------------------------------------
void PassGraph::Commit()
{
    // コマンドキューに登録します.
    {
    }

    m_FrameIndex = (m_FrameIndex + 1) & 0x1;
    m_FrameHeap[m_FrameIndex].Reset();
}

//-----------------------------------------------------------------------------
//      ジョブ数を取得します.
//-----------------------------------------------------------------------------
uint32_t PassGraph::GetJobCount() const
{ return m_JobCount; }

//-----------------------------------------------------------------------------
//      ジョブを取得します.
//-----------------------------------------------------------------------------
IJob* PassGraph::GetJob(uint32_t index) const
{
    if (index >= m_JobCount)
    { return nullptr; }

    return &m_pJobs[index];
}

//-----------------------------------------------------------------------------
//      リソースを取得または生成します.
//-----------------------------------------------------------------------------
ResourceHandle PassGraph::GetOrCreate(const PassTextureDesc& desc)
{
}

//-----------------------------------------------------------------------------
//      レンダーターゲットビューを取得します.
//-----------------------------------------------------------------------------
a3d::IRenderTargetView* PassGraph::GetRTV(const ResourceHandle& handle) const
{
}

//-----------------------------------------------------------------------------
//      深度ステンシルビューを取得します.
//-----------------------------------------------------------------------------
a3d::IDepthStencilView* PassGraph::GetDSV(const ResourceHandle& handle) const
{
}

//-----------------------------------------------------------------------------
//      アンオーダードアクセスビューを取得します.
//-----------------------------------------------------------------------------
a3d::IUnorderedAccessView* PassGraph::GetUAV(const ResourceHandle& handle) const
{
}

//-----------------------------------------------------------------------------
//      シェーダリソースビューを取得します.
//-----------------------------------------------------------------------------
a3d::IShaderResourceView* PassGraph::GetSRV(const ResourceHandle& handle) const
{
}

//-----------------------------------------------------------------------------
//      生成処理を行います.
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
//      パスグラフを生成します.
//-----------------------------------------------------------------------------
bool CreatePassGraph(const PassGraphDesc& desc, IPassGraph** ppGraph)
{ return PassGraph::Create(desc, ppGraph); }

} // namespace rs