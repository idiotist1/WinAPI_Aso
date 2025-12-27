#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// * 해상도에 맞게 윈도우 크기 조정
	// 윈도우 버전마다 클라이언트 크기가 다르다.(테투리나 메뉴영역) 
	// 그 크기를 제외한 클라이언트 영역 크기를 받아옴
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	// 언어온 사각형 정보로 윈도우 사이즈 세팅
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	// DC(Device Context)를 얻어온다.
	// DC : 출력에 필요한 모든 정보를 갖고 있는 데이터 구조체
	// GDI가 출력장치를 제어 및 DC를 관리
	// DC는 펜, 브러쉬, 폰트 등 화면에 출력하는 GDI Object를 갖고있다.
	// 이를 활용하여 다양한 요소를 화면에 출력
	m_hDC = GetDC(m_hWnd);

	// 더블 버퍼링 용도의 비트맵과 DC를 만든다.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	// WinAPI가 기본 의미없는 1px Bitmap을 들고 있다.
	// 그게 나온다.
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	// 의미없기 때문에 지워버린다.
	DeleteObject(hOldBit);


	// Manager 초기화
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();


	return S_OK;
}

void CCore::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CSceneMgr::GetInst()->update();

	// Rendering


	// 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC);

	// m_memDC에 있는 내용을 m_hDC의 0, 0에서부터 끝까지 다 복사(SRCCOPY) 한다.
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);
}

void CCore::update()
{
	// 비동기 키 입력 체크 함수
	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
	{
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
	{
	}

}

void CCore::render()
{

}

CCore::CCore()
{

}

CCore::~CCore()
{
	// DC는 해제해야 한다. (기본 DC는 ReleaseDC로 지워야 한다.) -> MicroSoft에서 그렇게 만듬
	ReleaseDC(m_hWnd, m_hDC);

	// 더블 버퍼링 HDC와 BITMAP 해제
	// 개발자가 생성한 DC는 DeleteDC로 지워야 한다. -> MicroSoft에서 그렇게 만듬
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}
