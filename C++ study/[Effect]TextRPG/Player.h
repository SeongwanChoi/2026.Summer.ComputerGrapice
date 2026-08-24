#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

// 전방 선언
class CItem;
class CSkill;

// 플레이어 및 몬스터 능력치 구조체
struct SStat {
	int hp;
	int mp;
	int atk;
	int def;

	SStat(int _hp = 0, int _mp = 100, int _atk = 0, int _def = 0)
		: hp(_hp), mp(_mp), atk(_atk), def(_def) {
	}

	// + 연산자 오버로딩
	SStat operator+(const SStat& other) const {
		return SStat(hp + other.hp, mp + other.mp, atk + other.atk, def + other.def);
	}

	// += 연산자 오버로딩 (구조체)
	SStat& operator+=(const SStat& other) {
		hp += other.hp;
		mp += other.mp;
		atk += other.atk;
		def += other.def;
		return *this;
	}

	// += 연산자 오버로딩 (정수 정사)
	SStat& operator+=(const int& value) {
		hp += value;
		mp += value;
		atk += value;
		def += value;
		return *this;
	}

	// - 연산자 오버로딩
	SStat operator-(const SStat& other) const {
		return SStat(hp - other.hp, mp - other.mp, atk - other.atk, def - other.def);
	}

	// -= 연산자 오버로딩
	SStat& operator-=(const SStat& other) {
		hp -= other.hp;
		mp -= other.mp;
		atk -= other.atk;
		def -= other.def;
		return *this;
	}
};

class CPlayer
{
private:
	string m_strName;
	SStat  m_sStat;

	int m_nHP = 0;
	int m_nMP = 0;
	int m_nMaxHP = 0;
	int m_nMaxMP = 0;

	int m_nLv = 1;
	int m_nExp = 0;
	int m_nMoney = 0;

public:
	// Getter & Setter
	string GetName() const { return m_strName; }
	int GetMoney() const { return m_nMoney; }
	int GetHp() const { return m_nHP; }
	int GetMp() const { return m_nMP; }
	void SetMoney(int money) { m_nMoney = money; }

	// 생성자 및 파괴자
	CPlayer(string name, int hp, int def, int atk, int exp, int money = 0);
	CPlayer(const CPlayer& clone);
	~CPlayer();

	// 전투 및 상태 관련
	void RecoceryHP(int val);
	void RecoceryMP(int val);
	void Recovery();
	bool LvUp(int add);
	void TakeDemage(int atk);
	void StillExp(CPlayer* target);

	void StillItem(CPlayer* target);
	void StillMoney(CPlayer* target);
	void EarnMoney(int amount);
	bool UseMoney(int amount);
	void Attack(CPlayer* target);
	bool Dead();
	void Display();

public:
	vector<CItem*> m_vecInventory; // 인벤토리
	vector<CSkill*> m_vecSkills;   // 보유 스킬 목록

	// 아이템 관련
	void AddItem(CItem* item);
	void ShowInventory();
	bool UseItem(int nIdx, CPlayer* pTarget);

	// 스킬 관련
	void LearnSkill(CSkill* skill);
	void ShowSkillList();
	bool UseSkill(int nIdx, CPlayer* pTarget);
};