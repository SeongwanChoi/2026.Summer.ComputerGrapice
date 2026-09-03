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

	EffectManager  effectManager;
	ItemManager    itemManager;
	SkillManager   skillManager;
	MonsterManager monsterManager;

public:
	CGameManager();
	~CGameManager();

	void Init();
	void InitTest();
	void Update();
	bool IsExit() const { return m_isExit; }

	bool PlayerBattileMainPtr(CPlayer* pPlayer, CPlayer* pMonster);
};