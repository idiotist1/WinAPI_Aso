#pragma once
#include "define.h"

// * 키매니저 역할
//1. 프레임 동기화
// - 동일 프레임 내에 같은 키에 대해 동일한 이벤트를 가진다.
//2. 키 입력 이벤트 처리
// - tap, hold, away

enum class KEY_STATE
{
	TAP, // 막 누른 시점
	HOLD, // 누르고 있는
	AWAY, // 막 뗀 시점
	NONE, // 눌리지 않고, 이전에도 눌리지 않은 상태
};

enum class KEY
{
	LEFT, 
	RIGHT,
	UP,
	DOWN,
	Q,
	W, 
	E, 
	R, 
	T,
	Y,
	U, 
	O, 
	P,
	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,
	Z,
	X,
	C,
	V,
	B,
	N,
	M,

	ALT, CTRL, LSHIFT, SPACE, ENTER, ESC,

	LAST, // 열거형의 끝
};

struct tKeyInfo
{
	KEY_STATE eState; // 키의 상태값
	bool bPrevPush; // 이전 프레임에서 눌렸는지 여부
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<tKeyInfo> m_vecKey;
public:
	void init();
	void update();
public:
	KEY_STATE GetKeyState(KEY _eKey)
	{
		return m_vecKey[(int)_eKey].eState;
	}
};