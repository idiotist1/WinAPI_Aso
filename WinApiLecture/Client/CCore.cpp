#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CObject g_obj;

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

	// Manager 초기화
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();

	g_obj.SetPos(Vec2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2)));
	g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}

void CCore::progress()
{
	static int callCount = 0;
	++callCount;
	static int iPrevCount = GetTickCount();

	int iCurCount = GetTickCount();
	if (GetTickCount() - iPrevCount > 1000)
	{
		iPrevCount = iCurCount;
		callCount = 0;
	}

	update();
	render();
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	// 비동기 키 입력 체크 함수
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vPos.x -= 1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 1;
	}

	g_obj.SetPos(vPos);
}

void CCore::render()
{
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	// 그리기
	Rectangle(m_hDC, 
		int(vPos.x - vScale.x / 2.f),
		int(vPos.y - vScale.y / 2.f),
		int(vPos.x + vScale.x / 2.f), 
		int(vPos.y + vScale.y / 2.f));
}

CCore::CCore()
{
}

CCore::~CCore()
{
	//DC는 해제해야 한다.
	ReleaseDC(m_hWnd, m_hDC);
}
