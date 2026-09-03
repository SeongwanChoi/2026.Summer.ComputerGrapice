#pragma once

#include <string>
#include <vector>
#include "Effect.h" // Effect 헤더 포함

using namespace std;

class CPlayer;

class CItem
{
public:
	enum EITEMKIND { CONSUMABLE, EQUIPMENT, ETC };

	string m_strName;
	EITEMKIND m_eItemKind;
	int m_nGold;

	// 하나 이상의 효과 포인터를 관리하는 벡터
	vector<CEffect*> m_vecEffects;

	CItem(string name = "none", EITEMKIND kind = EITEMKIND::CONSUMABLE, int gold = 0);
	~CItem();

	// 효과 추가 함수
	void AddEffect(CEffect* pEffect);

	// 아이템 사용 시 포함된 모든 효과 실행
	void Use(CPlayer* pCaster, CPlayer* pTarget);
};

class ItemManager
{
	vector<CItem> m_vecItems;

public:
	~ItemManager();

	// EffectManager 참조를 넘겨받아 효과 ID들을 동기화
	bool LoadFromCSV(const string& filename, EffectManager& effectManager);

	CItem* GetItem(int idx);
	void AddItem(CItem item);
	void DisplayItemList();

	// 안전한 인덱스 접근 및 반복 조회를 위한 요소 개수 반환 함수 (보완 추가)
	int GetSize() const { return static_cast<int>(m_vecItems.size()); }
};