#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class CPlayer;//클래스의 선언
class CItem;

class CItem //클래스의 정의
{
public:
	enum EITEMKIND { NONE, HP_RECOVER, MP_RECOVER, TARGET_DEAGE, TEAM_DEAGE };

	string m_strName;
	EITEMKIND m_eItemKind;
	int m_nValue;

	// 아이템 생성자 추가
	CItem(string name = "none", EITEMKIND kind = EITEMKIND::NONE, int value = 0);
	void Use(CPlayer& player);
};

class CPlayer
{
	string m_strName;
	int m_nHP = 0;
	int m_nMP;
	int m_nMaxHP;
	int m_nMaxMP;
	int m_nAtk = 0;
	int m_nDef = 0;

	int m_nLv = 1;
	int m_nExp = 0;
	int m_nMoney = 0;

public:
	string GetName() { return m_strName; }
	int GetMoney() { return m_nMoney; }

	CPlayer(string name, int hp, int def, int atk, int exp, int money = 0);

	void RecoceryHP(int val);
	void RecoceryMP(int val);
	void Recovery();
	bool LvUp(int add);
	void TakeDemage(int atk);
	void StillExp(CPlayer& target);

	// 상대방의 돈을 빼앗는 기능
	void StillItem(CPlayer& target);
	void StillMoney(CPlayer& target);
	void EarnMoney(int amount);
	bool UseMoney(int amount);
	void Attack(CPlayer& target);
	bool Dead();
	void Display();

public:
	vector<CItem> m_vecInventory; // 인벤토리 (아이템 목록) 추가

	// 인벤토리에 아이템을 추가하는 함수
	void AddItem(CItem item);

	// 인벤토리 목록을 출력하고 사용하는 함수
	void ShowInventory();
};

class ItemManager
{
	vector<CItem> m_vecItems;

public:
	// CSV 파일을 읽어 아이템들을 초기화하는 함수
	bool LoadFromCSV(const string& filename);

	CItem GetItem(int idx);
	void AddItem(CItem item);

	void DisplayItemList();
};