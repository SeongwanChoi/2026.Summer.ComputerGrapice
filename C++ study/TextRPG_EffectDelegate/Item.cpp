#include "Item.h"
#include "Player.h"
#include <fstream>
#include <sstream>

using namespace std;

// ==========================================
// CItem 구현부
// ==========================================
CItem::CItem(int id, string name, EITEMTYPE type, int price)
	: m_nID(id), m_strName(name), m_eType(type), m_nPrice(price)
{
}

CItem::~CItem()
{
	m_vecEffects.clear();
	m_vecEffectIDs.clear();
}

void CItem::AddEffect(CEffect* pEffect)
{
	if (pEffect != nullptr)
	{
		m_vecEffects.push_back(pEffect);
	}
}

void CItem::AddEffectID(int effectId)
{
	m_vecEffectIDs.push_back(effectId);
}

// 1. 기존 상속 기반 효과 실행
void CItem::Use(CPlayer* pCaster, CPlayer* pTarget)
{
	cout << "\n🧪 [" << m_strName << "] 아이템 사용!" << endl;

	if (m_vecEffects.empty())
	{
		cout << "아무런 효과가 없는 아이템입니다." << endl;
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
void CItem::Use(CPlayer* pCaster, CPlayer* pTarget, IEffectManager* pEffectMgr)
{
	cout << "\n🧪 [델리게이트] [" << m_strName << "] 아이템 사용!" << endl;

	if (m_vecEffectIDs.empty() || pEffectMgr == nullptr)
	{
		cout << "아무런 효과가 없는 아이템입니다." << endl;
		return;
	}

	for (int effectId : m_vecEffectIDs)
	{
		pEffectMgr->ApplyEffect(effectId, pCaster, pTarget);
	}
}

// ==========================================
// ItemManager 구현부
// ==========================================
ItemManager::~ItemManager()
{
	for (CItem* pItem : m_vecItems)
	{
		if (pItem != nullptr)
		{
			delete pItem;
		}
	}
	m_vecItems.clear();
}

// 1. 기존 상속 기반 로드 함수
bool ItemManager::LoadFromCSV(const string& filename, EffectManager& effectManager)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Item CSV 파일을 열 수 없습니다: " << filename << endl;
		return false;
	}

	string line;
	getline(file, line); // 헤더 스킵

	while (getline(file, line))
	{
		stringstream ss(line);
		string idStr, name, typeStr, priceStr, effectIdsStr;

		getline(ss, idStr, ',');
		getline(ss, name, ',');
		getline(ss, typeStr, ',');
		getline(ss, priceStr, ',');
		getline(ss, effectIdsStr, ',');

		if (name.empty()) continue;

		int id = stoi(idStr);
		int price = priceStr.empty() ? 0 : stoi(priceStr);

		CItem* pNewItem = new CItem(id, name, CItem::CONSUMABLE, price);

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
					pNewItem->AddEffect(pEffect);
				}
			}
		}

		AddItem(pNewItem);
	}

	file.close();
	cout << "Item_Table 로드 및 상속 효과 동기화 완료 (" << m_vecItems.size() << "개 등록)" << endl;
	return true;
}

// 2. [신규] 델리게이트/인터페이스 기반 로드 함수
bool ItemManager::LoadFromCSV(const string& filename, IEffectManager& effectManager)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Item CSV 파일을 열 수 없습니다: " << filename << endl;
		return false;
	}

	string line;
	getline(file, line); // 헤더 스킵

	while (getline(file, line))
	{
		stringstream ss(line);
		string idStr, name, typeStr, priceStr, effectIdsStr;

		getline(ss, idStr, ',');
		getline(ss, name, ',');
		getline(ss, typeStr, ',');
		getline(ss, priceStr, ',');
		getline(ss, effectIdsStr, ',');

		if (name.empty()) continue;

		int id = stoi(idStr);
		int price = priceStr.empty() ? 0 : stoi(priceStr);

		CItem* pNewItem = new CItem(id, name, CItem::CONSUMABLE, price);

		stringstream effectSS(effectIdsStr);
		string singleEffectIdStr;

		// 델리게이트 방식은 ID만 등록하여 관리자에 처리를 위임
		while (getline(effectSS, singleEffectIdStr, ';'))
		{
			if (!singleEffectIdStr.empty())
			{
				int effectId = stoi(singleEffectIdStr);
				pNewItem->AddEffectID(effectId);
			}
		}

		AddItem(pNewItem);
	}

	file.close();
	cout << "Item_Table 로드 및 델리게이트 ID 바인딩 완료 (" << m_vecItems.size() << "개 등록)" << endl;
	return true;
}

CItem* ItemManager::GetItem(int idx)
{
	if (idx >= 0 && idx < (int)m_vecItems.size())
	{
		return m_vecItems[idx];
	}
	cout << "존재하지 않는 아이템 번호입니다." << endl;
	return nullptr;
}

void ItemManager::AddItem(CItem* pItem)
{
	if (pItem != nullptr)
	{
		m_vecItems.push_back(pItem);
	}
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
		cout << i << ". " << m_vecItems[i]->m_strName
			<< " (가격: " << m_vecItems[i]->m_nPrice << "G)" << endl;
	}
}