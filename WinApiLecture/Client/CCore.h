#pragma once

// * 싱글톤 패턴
//- 객체의 생성을 1개로 제한
//- 어디서든 접근 가능

class CCore
{
	SINGLE(CCore);
private:
	HWND m_hWnd = 0; // 메인 윈도우 핸들
	POINT m_ptResolution = {}; // 메인 윈도우 해상도
	HDC m_hDC = 0; //메인 윈도우에 Draw 할 DC
public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();
private:
	void update();
	void render();
};

// * 싱글톤 만드는 방법1
//class CCore
//{
//private:
//	static CCore* g_pInst;
//public:
//	static CCore* GetInstance()
//	{
//		
//		// 최초 호출된 경우
//		if (g_pInst == nullptr)
//		{
//			g_pInst = new CCore();
//		}
//		return g_pInst;
//	}
//
//	static void Release()
//	{
//		if (nullptr != g_pInst)
//		{
//			delete g_pInst;
//			g_pInst = nullptr;
//		}
//	}
//
//private:
//	CCore();
//	~CCore();
//};

