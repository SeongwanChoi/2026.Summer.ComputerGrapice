#include "Item.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// ==========================================
// CItem 클래스 구현
// ==========================================
CItem::CItem(string name, EITEMKIND kind, int gold)
{
	m_strName = name;
	m_eItemKind = kind;
	m_nGold = gold;
}

CItem::~CItem()
{
	m_vecEffects.clear();
}

void CItem::AddEffect(CEffect* pEffect)
{
	if (pEffect != nullptr)
	{
		m_vecEffects.push_back(pEffect);
	}
}

void CItem::Use(CPlayer* pCaster, CPlayer* pTarget)
{
	cout << "\n[" << m_strName << "] 아이템을 사용합니다!" << endl;

	if (m_vecEffects.empty())
	{
		cout << "아무런 효과가 없는 아이템입니다." << endl;
		return;
	}

	// 아이템에 등록된 모든 효과 순차 적용
	for (CEffect* pEffect : m_vecEffects)
	{
		if (pEffect != nullptr)
		{
			pEffect->Apply(pCaster, pTarget);
		}
	}
}

// ==========================================
// ItemManager 클래스 구현
// ==========================================
ItemManager::~ItemManager()
{
	m_vecItems.clear();
}

bool ItemManager::LoadFromCSV(const string& filename, EffectManager& effectManager)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Item CSV 파일을 열 수 없습니다: " << filename << endl;
		return false;
	}

	string line;
	// 헤더 스킵: Item_ID, Name, Item_Kind, Price, Effect_IDs
	getline(file, line);

	while (getline(file, line))
	{
		stringstream ss(line);
		string idStr, name, kindStr, goldStr, effectIdsStr;

		getline(ss, idStr, ',');
		getline(ss, name, ',');
		getline(ss, kindStr, ',');
		getline(ss, goldStr, ',');
		getline(ss, effectIdsStr, ',');

		if (name.empty()) continue;

		int gold = goldStr.empty() ? 0 : stoi(goldStr);

		CItem newItem(name, CItem::CONSUMABLE, gold);

		// 세미콜론(;)으로 구분된 Effect_ID 파싱 (예: "101;102")
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
					newItem.AddEffect(pEffect);
				}
				else
				{
					cout << "[경고] 아이템 " << name << "에 등록되지 않은 Effect ID(" << effectId << ")가 연결되었습니다." << endl;
				}
			}
		}

		AddItem(newItem);
	}

	file.close();
	cout << "Item_Table 로드 및 효과 동기화 완료 (" << m_vecItems.size() << "개 등록)" << endl;
	return true;
}

CItem* ItemManager::GetItem(int idx)
{
	if (idx >= 0 && idx < (int)m_vecItems.size())
	{
		return &m_vecItems[idx];
	}
	cout << "존재하지 않는 아이템 번호입니다." << endl;
	return nullptr;
}

void ItemManager::AddItem(CItem item)
{
	m_vecItems.push_back(item);
}

void ItemManager::DisplayItemList()
{
	cout << "\n=== [전체 아이템 목록] ===" << endl;
	if (m_vecItems.empty())
	{
		cout << "등록된 아이템이 없습니다." << endl;
		return;
	}

	for (size_t i = 0; i < m_vecItems.size(); ++i)
	{
		cout << i << ". " << m_vecItems[i].m_strName << " (가격: " << m_vecItems[i].m_nGold << "G)" << endl;
	}
}