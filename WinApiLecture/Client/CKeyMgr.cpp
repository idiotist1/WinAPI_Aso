#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT, //LEFT
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',

	VK_MENU, // ATL 
	VK_CONTROL, // CTRL
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN, // Enter 
	VK_ESCAPE, //ESC
};

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{
	// 키의 갯수만큼 반복
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::update()
{
	// 윈도우 포커싱 알아내기
	HWND hMainWnd = CCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus(); // 포커스 중인 윈도우 핸들

	// 윈도우 포커싱 중이라면
	if (hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			// 키가 눌려있다면
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				// 이전 프레임에 눌려 있었다면
				if (m_vecKey[i].bPrevPush)
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				// 이전 프레임에 눌려있지 않았다면
				else
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevPush = true;
			}
			// 키가 안눌려있다면
			else
			{
				// 이전 프레임에 눌려 있었다면
				if (m_vecKey[i].bPrevPush)
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				//  이전에도 안눌려 있었다면
				else
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrevPush = false;
			}
		}
	}
	// 포커싱 중이 아니라면
	else
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			m_vecKey[i].bPrevPush = false;

			bool isAway = KEY_STATE::AWAY == m_vecKey[i].eState;
			bool isTap = KEY_STATE::TAP == m_vecKey[i].eState;
			bool isHold = KEY_STATE::HOLD == m_vecKey[i].eState;

			if (isTap || isHold || isAway)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}

