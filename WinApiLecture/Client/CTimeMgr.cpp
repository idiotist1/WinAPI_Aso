#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"

CTimeMgr::CTimeMgr()
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Init()
{
	// 현재 카운트
	QueryPerformanceCounter(&m_llPrevCount);
	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	// 현재 카운트
	QueryPerformanceCounter(&m_llCurCount);

	// 이전 프레임의 카운팅과, 현재 프레임 카운팅 값의 차이를 구한다.
	m_dDt = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;
	// 이전 카운트 값을 현재값으로 갱신(다음번에 계산을 위해서)
	m_llPrevCount = m_llCurCount;

	++m_iCallCount;
	m_dAcc += m_dDt; // DT 누적(흐르는 시간)

	if (m_dAcc >= 1.f)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.f;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDt);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
