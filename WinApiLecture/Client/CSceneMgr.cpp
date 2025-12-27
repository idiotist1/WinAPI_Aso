#include "pch.h"
#include "CSceneMgr.h"
#include "CScene_Start.h"

CSceneMgr::CSceneMgr()
{
}

CSceneMgr::~CSceneMgr()
{
	// 씬 전부 삭제
	for (int i = 0; i < (UINT)SCENE_TYPE::END; i++)
	{
		if (m_arrScene != nullptr)
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneMgr::init()
{
	// 모든 Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start();
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	// 현재 씬 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();
}

void CSceneMgr::update()
{
	m_pCurScene->update();
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}
