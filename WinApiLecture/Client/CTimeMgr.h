#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llCurCount = {};
	LARGE_INTEGER m_llPrevCount = {};
	LARGE_INTEGER m_llFrequency = {};

	// 프레임 사이의 시간값(deltaTime)
	double m_dDt = 0.f; 
	// 1초 체크를 위한 누적 시간
	double m_dAcc = 0.f;
	// 초당 함수 호출 횟수 체크
	UINT m_iCallCount = 0; 
	// FPS
	UINT m_iFPS = 0;

	

	// 1 프레임당 시간 Delta Time
public:
	//QueryPerformanceCounter 이건 뭐니?
	void Init();
	void update();
public:
	double GetDT() { return m_dDt; }
	float GetfDT() { return (float)m_dDt; }
};

