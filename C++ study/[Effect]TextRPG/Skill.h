#pragma once

#include <string>
#include <vector>
#include "Effect.h" // CEffect 및 EffectManager 포함

using namespace std;

class CPlayer;

class CSkill
{
public:
	enum ESKILLKIND { ACTIVE, PASSIVE };

	string m_strName;
	ESKILLKIND m_eSkillKind;
	int m_nMPCost;  // 소모 마나

	// 다중 효과 포인터 관리
	vector<CEffect*> m_vecEffects;

	CSkill(string name = "none", ESKILLKIND kind = ESKILLKIND::ACTIVE, int mpCost = 0);
	~CSkill();

	// 효과 추가
	void AddEffect(CEffect* pEffect);

	// 스킬 사용 (시전자와 타겟을 전달)
	void Use(CPlayer* pCaster, CPlayer* pTarget);
};

class SkillManager
{
	vector<CSkill> m_vecSkills;

public:
	~SkillManager();

	// EffectManager를 참조받아 스킬-효과 동기화
	bool LoadFromCSV(const string& filename, EffectManager& effectManager);

	CSkill* GetSkill(int idx);
	void AddSkill(CSkill skill);
	void DisplaySkillList();

	int GetSize() { return (int)m_vecSkills.size(); }
};