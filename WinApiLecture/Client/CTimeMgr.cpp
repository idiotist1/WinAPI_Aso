#include "pch.h"
#include "CTimeMgr.h"

CTimeMgr::CTimeMgr()
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Init()
{
	QueryPerformanceCounter(&m_llCurCount);
	QueryPerformanceFrequency(&m_llFrequency);
}
