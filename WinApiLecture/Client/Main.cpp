#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "CCore.h"


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND g_hWnd; // 메인 윈도우 핸들
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

#include <vector>
using std::vector;

struct tObjectInfo
{
	POINT g_ptObjPos;
	POINT g_ptObjScale;
};

vector<tObjectInfo> g_vecInfo;

// 좌 상단
POINT g_ptRB;

// 우 하단
POINT g_ptLT;

bool bLbtnDown = false;

// 메인함수에 사용되는 함수 선언
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// * SAL 주석(특수한 주석)
//- _In_, _In_opt_ 같은 것들
//- 변수의 용도를 키워드로 작성, 잘 안쓰임, 몰라도 됨(WinAPI에만 사용)
//- _In_ : 데이터는 호출된 함수에 전달되고 읽기전용으로 처리
//- _In_opt_ : _In_과 유사하지만 매개변수가 선택사항 일 경우

// 메인 함수(진입점)
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // 실행된 프로그램 포인터
	_In_opt_ HINSTANCE hPrevInstance, // 이전 인스턴스 포인터(현재 사용되지 않는다) 무조건 null이다.
	_In_ LPWSTR    lpCmdLine, // 프로그램 시작시 전달되는 정보
	_In_ int       nCmdShow) // 창을 만들때 표시하는 방법
{
	// 매개변수가 있지만 사용되지 않는 것을 의미(경고 무시용)
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	// TODO: 여기에 코드를 입력합니다.

	// szTitle, szWindowClass에 문자열을 넣어줌(Resource뷰 -> StringTable, Resource.h를 봐야한다.)
	// 103에 해당하는 StringTable에 있는 문자열을 szTitle에 넣어줌
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	// 109에 해당하는 StringTable에 있는 문자열을 szWindowClass에 넣어줌
	LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);

	// 윈도우 등록
	MyRegisterClass(hInstance);

	// 윈도우 생성
	if (!InitInstance(hInstance, nCmdShow))
	{
		// 실패했다면 main함수 종료
		return FALSE;
	}

	// Core 초기화
	if (FAILED(CCore::GetInst()->init(g_hWnd, POINT{ 1280, 720 })))
	{
		// 메세지박스 띄움
		MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);
		return FALSE;
	}


	// 단축키 정보 불러오기(리소스뷰 -> Accelerator)
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

	MSG msg; // 메세지를 받기위한 객체

	// GetMessage
	//- 프로그램 내부의 MessageQueue에 쌓여있는 메세지들을 꺼내본다. 
	//- hwnd, lParam, message, pt, time, wParam 이런 정보들이 들어온다.
	//- 메시지 큐에서 메세지가 없다면 무한정 대기(★)
	//- msg.message == WM_QUIT 인 경우 false를 반환 -> 프로그램 종료

	// * PeekMessage
	//- PeekMessage는 메세지가 없어도 반환한다. PM_REMOVE를 넣으면 읽은 메세지를 제거한다.
	//- 메세지 큐에 메세지가 있다면 true
	//- 메세지 큐에 메세지가 없다면 false

	// GetTickCount : 윈도우가 부팅된 이후 시간
	// 이전 카운트

	while (true)
	{
		// 메세지가 있다면
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// 종료 메세지라면
			if (WM_QUIT == msg.message)
				break;

			// 단축키 확인 함수
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				// 전달된 메세지가 WM_KEYDOWN인지와 눌려진 키가 문자키인지 검사하고 
				// 조건이 맞다면 WM_CHAR메시지를 만들어서 메시지큐에 덧붙임
				TranslateMessage(&msg);
				// 메시지를 윈도우 프로시저(WndProc 함수)로 보냄
				DispatchMessage(&msg);
			}
		}
		// 메세지가 발생하지 않는 대부분의 시간
		else
		{
			// Game 코드 수행
			// 디자인 패턴
			CCore::GetInst()->progress();
		}
	}


	return (int)msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	// 구조체에 정보를 넣어줌
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CLIENT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex); // 윈도우 클래스를 운영체제에 등록
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	// 윈도우 생성
	// HWND(Handle Window) : 윈도우 아이디
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	// 윈도우 생성에 실패했다면
	if (!hWnd)
	{
		return FALSE;
	}
	g_hWnd = hWnd;
	// 생성한 윈도우를 보여줌
	ShowWindow(hWnd, nCmdShow);
	// 윈도우 Update
	UpdateWindow(hWnd);

	return TRUE;
}

// 콜백 함수이며 메시지가 입력되면 윈도우에 의해 호출되어 메시지를 처리
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// 메뉴 항목을 선택했을때 (리소스 뷰 -> Menu -> IDC_CLIENT)
	case WM_COMMAND:
	{
		// 선택한 메뉴의 ID값을 받아온다.
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			// 다이얼로그 표시
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			// 창 종료
			DestroyWindow(hWnd);
			break;
		default:
			// WndProc에서 처리하지 않은 나머지 메시지 처리
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	// 그리는 작업, 무효화 영역(Invalidate Rect)이 발생한 경우
	// 무효화 영역 : 다른 창으로 가려진 영역(옛날엔 그랬다), 지금은 창을 최소화 했다 올려야 한다.
	case WM_PAINT:
	{
		PAINTSTRUCT ps;

		// HDC(Handle Device Context) 객체를 만든다.-> 그리기 객체 
		HDC hdc = BeginPaint(hWnd, &ps);


		// 그리기 종료
		EndPaint(hWnd, &ps);
	}
	break;
	//키가 눌렸을때
	case WM_KEYDOWN:
	{

	}
	break;
	// 키를 땟을때
	case WM_KEYUP:
		break;
		// 마우스 왼쪽버튼 눌렀을때
	case WM_LBUTTONDOWN:

		break;
	case WM_MOUSEMOVE:
		break;

		// 마우스 오른쪽 버튼 땟을 떄
	case WM_LBUTTONUP:
		break;

	case WM_DESTROY:
		// 메세지큐에 WM_QUIT를 보내는 함수
		PostQuitMessage(0);
		break;
	default:
		// WndProc에서 처리하지 않은 나머지 메시지 처리
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 사용하지 않는 매개변수
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		// OK나 취소버튼을 눌렀따면
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			// Dialog창 닫음
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
