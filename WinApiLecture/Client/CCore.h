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

	// 더블 버퍼링 용도
	HBITMAP m_hBit = 0;
	HDC m_memDC = 0;

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();
private:
	void update();
	void render();
public:
	HWND GetMainHwnd() { return m_hWnd; }
};