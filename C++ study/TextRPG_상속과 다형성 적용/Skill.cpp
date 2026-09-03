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
}

void CSkill::AddEffect(CEffect* pEffect)
{
	if (pEffect != nullptr)
	{
		m_vecEffects.push_back(pEffect);
	}
}

void CSkill::Use(CPlayer* pCaster, CPlayer* pTarget)
{
	cout << "\n✨ [" << m_strName << "] 스킬 시전!" << endl;

	if (m_vecEffects.empty())
	{
		cout << "아무런 효과가 없는 스킬입니다." << endl;
		return;
	}

	// 스킬에 등록된 모든 효과를 순차적으로 적용
	for (CEffect* pEffect : m_vecEffects)
	{
		if (pEffect != nullptr)
		{
			pEffect->Apply(pCaster, pTarget);
		}
	}
}

// ==========================================
// SkillManager 클래스 구현
// ==========================================
SkillManager::~SkillManager()
{
	m_vecSkills.clear();
}

bool SkillManager::LoadFromCSV(const string& filename, EffectManager& effectManager)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Skill CSV 파일을 열 수 없습니다: " << filename << endl;
		return false;
	}

	string line;
	// 헤더 스킵 (Skill_ID, Name, MP_Cost, Skill_Kind, Effect_IDs)
	getline(file, line);

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

		// 세미콜론(;) 단위로 파싱하여 EffectManager에서 효과 바인딩
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
				else
				{
					cout << "[경고] 스킬 " << name << "에 등록되지 않은 Effect ID(" << effectId << ")가 연결되었습니다." << endl;
				}
			}
		}

		AddSkill(newSkill);
	}

	file.close();
	cout << "Skill_Table 로드 및 효과 동기화 완료 (" << m_vecSkills.size() << "개 등록)" << endl;
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