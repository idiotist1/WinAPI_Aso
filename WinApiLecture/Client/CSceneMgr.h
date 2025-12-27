#pragma once

class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	class CScene* m_arrScene[(UINT)SCENE_TYPE::END] = {}; // ¸ðµç ¾À ¸ñ·Ï
	class CScene* m_pCurScene = nullptr; // ÇöÀç ¾À
public:
	void init();
	void update();
	void render(HDC _dc);
};

