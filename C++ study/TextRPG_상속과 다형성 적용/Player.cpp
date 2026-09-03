#include "Player.h"
#include "Item.h"
#include "Skill.h"
#include <iostream>
#include <typeinfo>

using namespace std;

// ==========================================
// CPlayer 클래스 구현
// ==========================================
CPlayer::CPlayer(string name, int hp, int def, int atk, int exp, int money)
{
	cout << typeid(*this).name() << ":" << name << endl;
	m_strName = name;
	m_nMaxHP = hp;
	m_nHP = hp;
	m_nMaxMP = 100;
	m_nMP = 100;
	m_sStat = SStat(hp, 100, atk, def);
	m_nExp = exp;
	m_nLv = 1;
	m_nMoney = money;
}

CPlayer::CPlayer(const CPlayer& clone)
{
	cout << "Copy " << typeid(*this).name() << ":" << clone.m_strName << endl;
	*this = clone;
}

CPlayer::~CPlayer()
{
	cout << "~" << typeid(*this).name() << ":" << m_strName << endl;
}

void CPlayer::RecoceryHP(int val)
{
	m_nHP += val;
	if (m_nHP > m_nMaxHP) m_nHP = m_nMaxHP;
}

void CPlayer::RecoceryMP(int val)
{
	m_nMP += val;
	if (m_nMP > m_nMaxMP) m_nMP = m_nMaxMP;
}

void CPlayer::Recovery()
{
	m_nHP = m_nMaxHP;
	m_nMP = m_nMaxMP;
}

bool CPlayer::LvUp(int add)
{
	if (m_nExp >= 100)
	{
		m_nLv++;
		m_sStat += add;
		m_nHP += add;
		m_nMP += add;
		m_nMaxHP += add;
		m_nMaxMP += add;
		m_nExp -= 100;
		return true;
	}

	return false;
}

void CPlayer::TakeDemage(int atk)
{
	m_nHP -= atk;
	if (m_nHP < 0) m_nHP = 0;
}

void CPlayer::StillExp(CPlayer* target)
{
	m_nExp += target->m_nExp;
}

void CPlayer::StillMoney(CPlayer* target)
{
	m_nMoney += target->m_nMoney;
	target->m_nMoney = 0;
}

void CPlayer::StillItem(CPlayer* target)
{
	for (size_t i = 0; i < target->m_vecInventory.size(); ++i)
	{
		this->m_vecInventory.push_back(target->m_vecInventory[i]);
		cout << target->m_vecInventory[i]->m_strName << "을(를) 강탈했습니다." << endl;
	}
	target->m_vecInventory.clear();
}

void CPlayer::EarnMoney(int amount)
{
	if (amount > 0) m_nMoney += amount;
}

bool CPlayer::UseMoney(int amount)
{
	if (amount > 0 && m_nMoney >= amount)
	{
		m_nMoney -= amount;
		return true;
	}
	return false;
}

void CPlayer::Attack(CPlayer* target)
{
	int demage = this->m_sStat.atk - target->m_sStat.def;
	if (demage <= 0) demage = 1;

	target->TakeDemage(demage);
}

bool CPlayer::Dead()
{
	return m_nHP <= 0;
}

void CPlayer::Display()
{
	cout << "----------------------------------" << endl;
	cout << "Name:" << m_strName << endl;
	cout << "HP:" << m_nHP << "/" << m_nMaxHP << endl;
	cout << "MP:" << m_nMP << "/" << m_nMaxMP << endl;
	cout << "Atk:" << m_sStat.atk << endl;
	cout << "Lv/Exp:" << m_nLv << "/" << m_nExp << endl;
	cout << "Money:" << m_nMoney << "G" << endl;
	cout << "----------------------------------" << endl;
}

// 인벤토리 관리 구현
void CPlayer::AddItem(CItem* item)
{
	m_vecInventory.push_back(item);
}

void CPlayer::ShowInventory()
{
	cout << "\n=== [인벤토리 목록] ===" << endl;
	if (m_vecInventory.empty()) {
		cout << "인벤토리가 비어있습니다." << endl;
		return;
	}
	for (size_t i = 0; i < m_vecInventory.size(); ++i) {
		cout << i << ". " << m_vecInventory[i]->m_strName << endl;
	}
}

bool CPlayer::UseItem(int nIdx, CPlayer* pTarget)
{
	if (nIdx < 0 || nIdx >= (int)m_vecInventory.size()) return false;

	CItem* pItem = m_vecInventory[nIdx];
	// 갱신된 CItem::Use(caster, target) 호출
	pItem->Use(this, pTarget);
	m_vecInventory.erase(m_vecInventory.begin() + nIdx);
	return true;
}

// 스킬 관련 구현
void CPlayer::LearnSkill(CSkill* skill)
{
	m_vecSkills.push_back(skill);
	cout << skill->m_strName << " 스킬을 습득했습니다." << endl;
}

void CPlayer::ShowSkillList()
{
	cout << "\n=== [보유 스킬 목록] ===" << endl;
	if (m_vecSkills.empty()) {
		cout << "습득한 스킬이 없습니다." << endl;
		return;
	}
	for (size_t i = 0; i < m_vecSkills.size(); ++i) {
		// m_nPower 필드 참조 제거 및 갱신된 구조에 맞춰 소모 MP만 출력
		cout << i << ". " << m_vecSkills[i]->m_strName
			<< " (소모 MP: " << m_vecSkills[i]->m_nMPCost << ")" << endl;
	}
}

bool CPlayer::UseSkill(int nIdx, CPlayer* pTarget)
{
	if (nIdx < 0 || nIdx >= (int)m_vecSkills.size()) return false;

	CSkill* pSkill = m_vecSkills[nIdx];

	if (m_nMP < pSkill->m_nMPCost) {
		cout << "MP가 부족합니다. (현재 MP: " << m_nMP << ", 필요 MP: " << pSkill->m_nMPCost << ")" << endl;
		return false;
	}

	m_nMP -= pSkill->m_nMPCost;
	pSkill->Use(this, pTarget);
	return true;
}