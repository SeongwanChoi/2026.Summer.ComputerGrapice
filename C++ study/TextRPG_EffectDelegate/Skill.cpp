#include "Skill.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// ==========================================
// CSkill 클래스 구현
// ==========================================
CSkill::CSkill(string name, ESKILLKIND kind, int mpCost)
{
	m_strName = name;
	m_eSkillKind = kind;
	m_nMPCost = mpCost;
}

CSkill::~CSkill()
{
	m_vecEffects.clear();
	m_vecEffectIDs.clear();
}

void CSkill::AddEffect(CEffect* pEffect)
{
	if (pEffect != nullptr)
	{
		m_vecEffects.push_back(pEffect);
	}
}

void CSkill::AddEffectID(int effectId)
{
	m_vecEffectIDs.push_back(effectId);
}

// 1. 기존 상속 기반 효과 실행[cite: 23]
void CSkill::Use(CPlayer* pCaster, CPlayer* pTarget)
{
	cout << "\n✨ [" << m_strName << "] 스킬 시전!" << endl;

	if (m_vecEffects.empty())
	{
		cout << "아무런 효과가 없는 스킬입니다." << endl;
		return;
	}

	for (CEffect* pEffect : m_vecEffects)
	{
		if (pEffect != nullptr)
		{
			pEffect->Apply(pCaster, pTarget);
		}
	}
}

// 2. [신규] 델리게이트/인터페이스 기반 효과 실행
void CSkill::Use(CPlayer* pCaster, CPlayer* pTarget, IEffectManager* pEffectMgr)
{
	cout << "\n✨ [델리게이트] [" << m_strName << "] 스킬 시전!" << endl;

	if (m_vecEffectIDs.empty() || pEffectMgr == nullptr)
	{
		cout << "아무런 효과가 없는 스킬입니다." << endl;
		return;
	}

	// 델리게이트 관리자에 ID를 넘겨 순차 실행
	for (int effectId : m_vecEffectIDs)
	{
		pEffectMgr->ApplyEffect(effectId, pCaster, pTarget);
	}
}

// ==========================================
// SkillManager 클래스 구현
// ==========================================
SkillManager::~SkillManager()
{
	m_vecSkills.clear();
}

// 1. 기존 상속 기반 로드 함수[cite: 23]
bool SkillManager::LoadFromCSV(const string& filename, EffectManager& effectManager)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Skill CSV 파일을 열 수 없습니다: " << filename << endl;
		return false;
	}

	string line;
	getline(file, line); // 헤더 스킵[cite: 23]

	while (getline(file, line))
	{
		stringstream ss(line);
		string idStr, name, mpStr, kindStr, effectIdsStr;

		getline(ss, idStr, ',');
		getline(ss, name, ',');
		getline(ss, mpStr, ',');
		getline(ss, kindStr, ',');
		getline(ss, effectIdsStr, ',');

		if (name.empty()) continue;

		int mpCost = mpStr.empty() ? 0 : stoi(mpStr);
		CSkill newSkill(name, CSkill::ACTIVE, mpCost);

		stringstream effectSS(effectIdsStr);
		string singleEffectIdStr;

		while (getline(effectSS, singleEffectIdStr, ';'))
		{
			if (!singleEffectIdStr.empty())
			{
				int effectId = stoi(singleEffectIdStr);
				CEffect* pEffect = effectManager.GetEffect(effectId);

				if (pEffect != nullptr)
				{
					newSkill.AddEffect(pEffect);
				}
			}
		}

		AddSkill(newSkill);
	}

	file.close();
	cout << "Skill_Table 로드 및 상속 효과 동기화 완료 (" << m_vecSkills.size() << "개 등록)" << endl;
	return true;
}

// 2. [신규] 델리게이트/인터페이스 기반 로드 함수
bool SkillManager::LoadFromCSV(const string& filename, IEffectManager& effectManager)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Skill CSV 파일을 열 수 없습니다: " << filename << endl;
		return false;
	}

	string line;
	getline(file, line); // 헤더 스킵[cite: 23]

	while (getline(file, line))
	{
		stringstream ss(line);
		string idStr, name, mpStr, kindStr, effectIdsStr;

		getline(ss, idStr, ',');
		getline(ss, name, ',');
		getline(ss, mpStr, ',');
		getline(ss, kindStr, ',');
		getline(ss, effectIdsStr, ',');

		if (name.empty()) continue;

		int mpCost = mpStr.empty() ? 0 : stoi(mpStr);
		CSkill newSkill(name, CSkill::ACTIVE, mpCost);

		stringstream effectSS(effectIdsStr);
		string singleEffectIdStr;

		// 델리게이트 방식은 ID만 등록하여 관리자에 처리를 위임
		while (getline(effectSS, singleEffectIdStr, ';'))
		{
			if (!singleEffectIdStr.empty())
			{
				int effectId = stoi(singleEffectIdStr);
				newSkill.AddEffectID(effectId);
			}
		}

		AddSkill(newSkill);
	}

	file.close();
	cout << "Skill_Table 로드 및 델리게이트 ID 바인딩 완료 (" << m_vecSkills.size() << "개 등록)" << endl;
	return true;
}

CSkill* SkillManager::GetSkill(int idx)
{
	if (idx >= 0 && idx < (int)m_vecSkills.size())
	{
		return &m_vecSkills[idx];
	}
	cout << "존재하지 않는 스킬 번호입니다." << endl;
	return nullptr;
}

void SkillManager::AddSkill(CSkill skill)
{
	m_vecSkills.push_back(skill);
}

void SkillManager::DisplaySkillList()
{
	cout << "\n=== [전체 스킬 목록] ===" << endl;
	if (m_vecSkills.empty())
	{
		cout << "등록된 스킬이 없습니다." << endl;
		return;
	}

	for (size_t i = 0; i < m_vecSkills.size(); ++i)
	{
		cout << i << ". " << m_vecSkills[i].m_strName
			<< " (소모 MP: " << m_vecSkills[i].m_nMPCost << ")" << endl;
	}
}