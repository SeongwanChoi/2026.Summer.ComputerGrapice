#include "GameManager.h"
#include "Player.h"
#include <iostream>
#include <typeinfo>

using namespace std;

CGameManager::CGameManager()
{
	pPlayer = new CPlayer("Player", 100, 10, 10, 0, 0);
	m_pEffectManager = nullptr;
}

CGameManager::~CGameManager()
{
	if (pPlayer != nullptr)
	{
		delete pPlayer;
		pPlayer = nullptr;
	}

	// 동적 할당된 이펙트 관리자 해제
	if (m_pEffectManager != nullptr)
	{
		delete m_pEffectManager;
		m_pEffectManager = nullptr;
	}
}

// 1. [기존] 상속 기반 EffectManager 초기화
void CGameManager::Init()
{
	if (m_pEffectManager != nullptr) delete m_pEffectManager;

	// 상속 기반 관리자 동적 생성
	m_pEffectManager = new EffectManager();
	m_pEffectManager->LoadFromCSV("TextRPG_Effect.csv");

	// ItemManager 및 SkillManager 로드 (인터페이스/참조 전달)
	// (※ ItemManager::LoadFromCSV가 EffectManager& 참조를 받는다면 IEffectManager& 지원되도록 매개변수 타입을 맞추어 주어야 합니다)
	itemManager.LoadFromCSV("TextRPG_sheet.csv", *static_cast<EffectManager*>(m_pEffectManager));
	itemManager.DisplayItemList();

	skillManager.LoadFromCSV("TextRPG_Skill.csv", *static_cast<EffectManager*>(m_pEffectManager));

	// 3. 몬스터 테이블 로드
	monsterManager.LoadFromCSV("monsters.csv");
}

// 델리게이트 기반 전체 초기화 (Effect, Item, Skill)
void CGameManager::InitDelegate()
{
	if (m_pEffectManager != nullptr) delete m_pEffectManager;

	// 1. 델리게이트 기반 이펙트 관리자 생성 및 로드
	m_pEffectManager = new DelegateEffectManager();
	m_pEffectManager->LoadFromCSV("TextRPG_Effect.csv");

	cout << "💚 [DelegateEffectManager] 델리게이트 기반 이펙트 관리자로 초기화되었습니다." << endl;

	// 2. 델리게이트 방식으로 Item 및 Skill 로드 (IEffectManager& 전달)
	itemManager.LoadFromCSV("TextRPG_sheet.csv", *m_pEffectManager);
	itemManager.DisplayItemList();

	skillManager.LoadFromCSV("TextRPG_Skill.csv", *m_pEffectManager);

	// 3. 몬스터 테이블 로드
	monsterManager.LoadFromCSV("monsters.csv");
}

void CGameManager::InitTest()
{
	pPlayer->SetMoney(999999);

	// 테스트용 아이템 지급
	if (itemManager.GetSize() > 2)
	{
		pPlayer->AddItem(itemManager.GetItem(2));
		pPlayer->AddItem(itemManager.GetItem(2));
		pPlayer->AddItem(itemManager.GetItem(2));
	}

	// 테스트용 스킬 배우기
	for (int i = 0; i < skillManager.GetSize(); ++i)
	{
		pPlayer->LearnSkill(skillManager.GetSkill(i));
	}

	// 몬스터에게 아이템 지급
	if (monsterManager.GetSize() > 0 && itemManager.GetSize() > 1)
		monsterManager.GetMonster(0)->AddItem(itemManager.GetItem(1));
	if (monsterManager.GetSize() > 1 && itemManager.GetSize() > 2)
		monsterManager.GetMonster(1)->AddItem(itemManager.GetItem(2));
	if (monsterManager.GetSize() > 2 && itemManager.GetSize() > 3)
		monsterManager.GetMonster(2)->AddItem(itemManager.GetItem(3));
}

void CGameManager::Update()
{
	int nChoice = 0;
	cout << "\n가고 싶은 곳의 번호를 선택하시오." << endl;
	cout << "0. " << arrPlaceName[PLACE_TOWN] << " (체력 회복)" << endl;
	cout << "1. " << arrPlaceName[PLACE_SHOP] << " (상점)" << endl;
	cout << "2. " << arrPlaceName[PLACE_FIELD] << " (사냥터)" << endl;
	cout << "3. " << arrPlaceName[PLACE_INVENT] << " (인벤토리 열기)" << endl;
	cout << "4. " << arrPlaceName[PLACE_SKILL_MASTER] << " (스킬 습득)" << endl;
	cout << "입력: ";
	cin >> nChoice;

	switch (nChoice)
	{
	case PLACE_TOWN:
		cout << "\n마을에서 휴식을 취해 체력과 마나가 모두 회복되었습니다." << endl;
		pPlayer->Recovery();
		pPlayer->Display();
		break;

	case PLACE_SHOP:
	{
		cout << "\n=== [상점] ===" << endl;
		cout << "현재 소지금: " << pPlayer->GetMoney() << "G" << endl;
		cout << "1. 체력 포션 구매 (가격: 100G)" << endl;
		cout << "2. 나가기" << endl;
		cout << "선택: ";
		int shopChoice;
		cin >> shopChoice;

		if (shopChoice == 1)
		{
			if (pPlayer->UseMoney(100))
			{
				CItem* pPotion = itemManager.GetItem(0);
				if (pPotion != nullptr)
				{
					pPlayer->AddItem(pPotion);
					cout << "포션을 구매하여 인벤토리에 추가했습니다!" << endl;
				}
			}
			else
			{
				cout << "돈이 부족합니다!" << endl;
			}
		}
		break;
	}
	case PLACE_FIELD:
	{
		cout << "\n가고 싶은 사냥터 번호를 선택하시오." << endl;
		for (int i = 0; i < MONSTER::MAX && i < monsterManager.GetSize(); ++i)
		{
			cout << i << ". " << arrFiledName[i] << " : " << monsterManager.GetMonster(i)->GetName() << endl;
		}
		cout << "입력: ";
		cin >> nChoice;

		if (nChoice >= 0 && nChoice < monsterManager.GetSize())
		{
			if (PlayerBattileMainPtr(pPlayer, monsterManager.GetMonsterClone(nChoice)))
			{
				m_isExit = true; // 플레이어 사망 시 종료 플래그 설정
			}
		}
		else
		{
			cout << "잘못된 지역 번호입니다." << endl;
		}
	}
	break;

	case PLACE_INVENT:
	{
		pPlayer->ShowInventory();
		pPlayer->ShowSkillList();
		break;
	}
	case PLACE_SKILL_MASTER:
	{
		cout << "\n[스킬 마스터]: \"새로운 스킬을 배우러 왔는가?\"" << endl;
		skillManager.DisplaySkillList();
		cout << "습득할 스킬 번호를 선택하세요 (-1: 나가기): ";
		int skillChoice;
		cin >> skillChoice;

		if (skillChoice >= 0 && skillChoice < skillManager.GetSize())
		{
			CSkill* pSkill = skillManager.GetSkill(skillChoice);
			if (pSkill != nullptr)
			{
				pPlayer->LearnSkill(pSkill);
			}
		}
		else if (skillChoice != -1)
		{
			cout << "잘못된 스킬 번호입니다." << endl;
		}
		break;
	}
	default:
		cout << "잘못된 입력입니다. 다시 선택해주세요." << endl;
		break;
	}
}

bool CGameManager::PlayerBattileMainPtr(CPlayer* pPlayer, CPlayer* pMonster)
{
	if (pPlayer == nullptr || pMonster == nullptr) return false;

	cout << "\n⚔️ [" << pMonster->GetName() << "]을(를) 조우했습니다!" << endl;

	while (!pPlayer->Dead() && !pMonster->Dead())
	{
		// ------------------ 플레이어 턴 ------------------
		cout << "\n================ [ 전투 메뉴 ] ================" << endl;
		cout << "플레이어 HP: " << pPlayer->GetHp() << " | MP: " << pPlayer->GetMp()
			<< " | 몬스터 HP: " << pMonster->GetHp() << endl;
		cout << "1. 일반 공격" << endl;
		cout << "2. 아이템 사용" << endl;
		cout << "3. 스킬 사용" << endl;
		cout << "행동을 선택하세요: ";

		int nAction = 0;
		cin >> nAction;

		if (nAction == 1)
		{
			pPlayer->Attack(pMonster);
		}
		else if (nAction == 2)
		{
			pPlayer->ShowInventory();

			cout << "사용할 아이템 번호 입력: ";
			int nIdx;
			cin >> nIdx;

			if (!pPlayer->UseItem(nIdx, pMonster)) {
				cout << "아이템 사용에 실패했습니다." << endl;
				continue;
			}
		}
		else if (nAction == 3)
		{
			pPlayer->ShowSkillList();
			cout << "사용할 스킬 번호 입력: ";
			int nIdx;
			cin >> nIdx;

			if (!pPlayer->UseSkill(nIdx, pMonster)) {
				cout << "스킬 사용에 실패했습니다." << endl;
				continue;
			}
		}
		else
		{
			cout << "잘못된 입력입니다. 다시 선택해주세요." << endl;
			continue;
		}

		// 몬스터 사망 체크
		if (pMonster->Dead())
		{
			cout << "\n" << pPlayer->GetName() << " 승리! (" << pMonster->GetName() << " 처치)" << endl;
			pPlayer->StillExp(pMonster);
			pPlayer->StillMoney(pMonster);
			pPlayer->StillItem(pMonster);

			if (pPlayer->LvUp(5))
				cout << pPlayer->GetName() << " Level Up!" << endl;

			pPlayer->Display();
			cout << "Battle End !!!\n" << endl;
			delete pMonster;
			return false;
		}

		// ------------------ 몬스터 턴 ------------------
		cout << "\n[" << pMonster->GetName() << "]의 반격!" << endl;
		pMonster->Attack(pPlayer);

		if (pPlayer->Dead())
		{
			cout << pPlayer->GetName() << " 이(가) 사망했습니다..." << endl;
			cout << "Battle End !!!\n" << endl;
			delete pMonster;
			return true;
		}
	}

	delete pMonster;
	return false;
}