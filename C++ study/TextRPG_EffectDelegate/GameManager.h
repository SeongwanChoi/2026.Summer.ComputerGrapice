#pragma once

#include <string>
#include <vector>
#include "Item.h"
#include "Skill.h"
#include "Effect.h"
#include "MonsterManager.h"

class CPlayer;

class CGameManager
{
private:
	enum EPLACE
	{
		PLACE_TOWN = 0,
		PLACE_SHOP,
		PLACE_FIELD,
		PLACE_INVENT,
		PLACE_SKILL_MASTER,
		PLACE_MAX
	};

	enum MONSTER
	{
		SLIME = 0,
		ORC,
		GOBLIN,
		MAX
	};

	std::string arrPlaceName[PLACE_MAX] = {
		"마을", "상점", "사냥터", "인벤토리 열기", "스킬 마스터"
	};

	std::string arrFiledName[MONSTER::MAX] = {
		"초보자 사냥터", "중급자 사냥터", "상급자 사냥터"
	};

	CPlayer* pPlayer = nullptr;
	bool m_isExit = false;

	// 기존 단일 EffectManager 객체 대신 인터페이스 포인터로 변경 (다형성 적용)
	IEffectManager* m_pEffectManager = nullptr;
	ItemManager    itemManager;
	SkillManager   skillManager;
	MonsterManager monsterManager;

public:
	CGameManager();
	~CGameManager();

	// 1. 기존 상속 기반 CEffectManager 초기화 함수
	void Init();

	// 2. [신규] 델리게이트 기반 DelegateEffectManager 초기화 함수
	void InitDelegate();

	void InitTest();
	void Update();
	bool IsExit() const { return m_isExit; }

	bool PlayerBattileMainPtr(CPlayer* pPlayer, CPlayer* pMonster);
};