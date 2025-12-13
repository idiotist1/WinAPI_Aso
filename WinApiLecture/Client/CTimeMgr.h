#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llCurCount = {};
	LARGE_INTEGER m_llFrequency = {};
	// FPS
	// 1 프레임당 시간 Delta Time
public:
	//QueryPerformanceCounter 이건 뭐니?
	void Init();
};

