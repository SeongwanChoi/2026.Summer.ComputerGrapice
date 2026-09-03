#pragma once

#include <string>
#include <vector>
#include <functional>
#include "Effect.h"

using namespace std;

class CPlayer;

class CSkill
{
public:
	enum ESKILLKIND { ACTIVE, PASSIVE };

	string m_strName;
	ESKILLKIND m_eSkillKind;
	int m_nMPCost;  // 소모 마나

	// 1. 상속 기반 효과 포인터 관리[cite: 21]
	vector<CEffect*> m_vecEffects;

	// 2. 델리게이트 기반 효과 ID 목록 관리
	vector<int> m_vecEffectIDs;

	CSkill(string name = "none", ESKILLKIND kind = ESKILLKIND::ACTIVE, int mpCost = 0);
	~CSkill();

	// 효과 추가 (상속 포인터 방식)[cite: 21]
	void AddEffect(CEffect* pEffect);

	// 효과 ID 추가 (델리게이트 방식)
	void AddEffectID(int effectId);

	// 스킬 사용 (상속 기반 효과 실행)[cite: 21]
	void Use(CPlayer* pCaster, CPlayer* pTarget);

	// 스킬 사용 (델리게이트 기반 효과 실행)
	void Use(CPlayer* pCaster, CPlayer* pTarget, IEffectManager* pEffectMgr);
};

class SkillManager
{
	vector<CSkill> m_vecSkills;

public:
	~SkillManager();

	// 기존 상속 기반 로드 함수[cite: 21]
	bool LoadFromCSV(const string& filename, EffectManager& effectManager);

	// [신규] 델리게이트/인터페이스 기반 통합 로드 함수
	bool LoadFromCSV(const string& filename, IEffectManager& effectManager);

	CSkill* GetSkill(int idx);
	void AddSkill(CSkill skill);
	void DisplaySkillList();

	int GetSize() { return (int)m_vecSkills.size(); }
};