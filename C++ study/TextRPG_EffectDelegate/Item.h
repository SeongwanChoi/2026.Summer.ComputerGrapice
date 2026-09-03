#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Effect.h"

using namespace std;

class CPlayer;

// ==========================================
// CItem 클래스 정의
// ==========================================
class CItem
{
public:
	enum EITEMTYPE { CONSUMABLE, EQUIP, ETC };

	int m_nID;
	string m_strName;
	EITEMTYPE m_eType;
	int m_nPrice;

	// 1. 상속 기반 효과 포인터 관리
	vector<CEffect*> m_vecEffects;

	// 2. 델리게이트 기반 효과 ID 관리
	vector<int> m_vecEffectIDs;

	CItem(int id = 0, string name = "", EITEMTYPE type = CONSUMABLE, int price = 0);
	~CItem();

	// 효과 추가 (상속 기반)
	void AddEffect(CEffect* pEffect);

	// 효과 ID 추가 (델리게이트 기반)
	void AddEffectID(int effectId);

	// 아이템 사용 (상속 기반)
	void Use(CPlayer* pCaster, CPlayer* pTarget);

	// 아이템 사용 (델리게이트 기반)
	void Use(CPlayer* pCaster, CPlayer* pTarget, IEffectManager* pEffectMgr);
};

// ==========================================
// ItemManager 클래스 정의
// ==========================================
class ItemManager
{
private:
	vector<CItem*> m_vecItems;

public:
	~ItemManager();

	// 1. 기존 상속 기반 로드 함수
	bool LoadFromCSV(const string& filename, EffectManager& effectManager);

	// 2. [신규] 델리게이트/인터페이스 기반 통합 로드 함수
	bool LoadFromCSV(const string& filename, IEffectManager& effectManager);

	CItem* GetItem(int idx);
	void AddItem(CItem* pItem);
	void DisplayItemList();

	int GetSize() { return (int)m_vecItems.size(); }
};