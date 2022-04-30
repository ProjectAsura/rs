//-----------------------------------------------------------------------------
// File : rsJob.cpp
// Desc : Job.
// Copyright(c) Project Asura. All right reserved.
//-----------------------------------------------------------------------------


namespace rs {

///////////////////////////////////////////////////////////////////////////////
// Job class
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
//      引数付きコンストラクタです.
//-----------------------------------------------------------------------------
Job::Job(PassGraph* pGraph, Pass* begin, Pass* end, a3d::ICommandList* pCommandList)
: m_pBegin  (begin)
, m_pEnd    (end)
{ /* DO_NOTHING */ }

//-----------------------------------------------------------------------------
//      処理を実行します.
//-----------------------------------------------------------------------------
void Job::Execute()
{
    m_IsFinished = false;
    PassContext context(m_pGraph, m_pCommandList);

    auto itr = m_pBegin;
    while(itr != nullptr && itr != m_pEnd)
    {
        itr->m_Execute(&context);
        itr = itr->GetNext();
    }

    m_IsFinished = true;
}

} // namespace rs
