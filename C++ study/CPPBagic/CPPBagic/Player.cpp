#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "Player.h" // 헤더 파일 분리 시 포함할 헤더

using namespace std;

bool g_isExit = false; // 전역변수

// ==========================================
// CItem 클래스 함수 정의
// ==========================================
CItem::CItem(string name, EITEMKIND kind, int value)
{
	m_strName = name;
	m_eItemKind = kind;
	m_nValue = value;
}

void CItem::Use(CPlayer& player)
{
	switch (m_eItemKind)
	{
	case CItem::HP_RECOVER:
		player.RecoceryHP(m_nValue);
		break;
	case CItem::MP_RECOVER:
		player.RecoceryMP(m_nValue);
		break;
	case CItem::TARGET_DEAGE:
		player.TakeDemage(m_nValue);
		break;
	case CItem::TEAM_DEAGE:
		player.RecoceryHP(m_nValue);
		break;
	default:
		break;
	}
}


// ==========================================
// CPlayer 클래스 함수 정의
// ==========================================
CPlayer::CPlayer(string name, int hp, int def, int atk, int exp, int money)
{
	m_strName = name;
	m_nHP = hp;
	m_nMaxHP = hp;
	m_nMP = 100;
	m_nMaxMP = m_nHP;
	m_nDef = def;
	m_nAtk = atk;
	m_nExp = exp;
	m_nLv = 1;
	m_nMoney = money;
}

void CPlayer::RecoceryHP(int val)
{
	m_nHP += val;
}

void CPlayer::RecoceryMP(int val)
{
	m_nMP += val;
}

void CPlayer::Recovery()
{
	m_nHP = m_nMaxHP;
}

bool CPlayer::LvUp(int add)
{
	if (m_nExp >= 100)
	{
		m_nLv++;
		m_nAtk += add;
		m_nHP += add;
		m_nMaxHP += add;
		m_nExp -= 100;
		return true;
	}

	return false;
}

void CPlayer::TakeDemage(int atk)
{
	m_nHP -= atk;
}

void CPlayer::StillExp(CPlayer& target)
{
	m_nExp += target.m_nExp;
}

// 상대방의 돈을 빼앗는 기능
void CPlayer::StillMoney(CPlayer& target)
{
	m_nMoney += target.m_nMoney;
	target.m_nMoney = 0;
}

void CPlayer::StillItem(CPlayer& target)
{
	for (size_t i = 0; i < target.m_vecInventory.size(); ++i)
	{
		this->m_vecInventory.push_back(target.m_vecInventory[i]);
		cout << target.m_vecInventory[i].m_strName << "을(를) 획득했습니다!" << endl;
	}
	target.m_vecInventory.clear();
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

void CPlayer::Attack(CPlayer& target)
{
	target.m_nHP -= (m_nDef - this->m_nAtk);
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
	cout << "Atk:" << m_nAtk << endl;
	cout << "Lv/Exp:" << m_nLv << "/" << m_nExp << endl;
	cout << "Money:" << m_nMoney << "G" << endl;
	cout << "----------------------------------" << endl;
}

// 인벤토리에 아이템을 추가하는 함수
void CPlayer::AddItem(CItem item)
{
	m_vecInventory.push_back(item);
}

// 인벤토리 목록을 출력하고 사용하는 함수
void CPlayer::ShowInventory()
{
	cout << "\n=== [인벤토리] ===" << endl;
	if (m_vecInventory.empty())
	{
		cout << "인벤토리가 비어 있습니다." << endl;
		return;
	}

	for (size_t i = 0; i < m_vecInventory.size(); ++i)
	{
		cout << i << ". " << m_vecInventory[i].m_strName << endl;
	}

	cout << "사용할 아이템 번호를 입력하세요 (취소는 -1): ";
	int choice;
	cin >> choice;

	if (choice >= 0 && choice < m_vecInventory.size())
	{
		// 아이템 사용 함수 호출
		m_vecInventory[choice].Use(*this);
		cout << m_vecInventory[choice].m_strName << "을(를) 사용했습니다!" << endl;

		// 사용한 아이템을 인벤토리에서 제거
		m_vecInventory.erase(m_vecInventory.begin() + choice);
	}
}

bool ItemManager::LoadFromCSV(const string& filename)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "CSV 파일을 열 수 없습니다: " << filename << endl;
		return false;
	}

	string line;
	// 첫 번째 줄(헤더: id, 이름, 기능, 값) 스킵
	getline(file, line);

	while (getline(file, line))
	{
		stringstream ss(line);
		string idStr, name, func, valueStr;

		// 쉼표 단위로 데이터 파싱
		getline(ss, idStr, ',');
		getline(ss, name, ',');
		getline(ss, func, ',');
		getline(ss, valueStr, ',');

		if (name.empty() || valueStr.empty()) continue;

		int value = stoi(valueStr);

		// 기능(func) 문자열에 따라 EITEMKIND 결정
		CItem::EITEMKIND kind = CItem::HP_RECOVER; // 기본값
		if (func.find("hp") != string::npos || func.find("힐링") != string::npos)
		{
			kind = CItem::HP_RECOVER;
		}
		else if (func.find("mp") != string::npos)
		{
			kind = CItem::MP_RECOVER;
		}
		else if (func.find("데미지") != string::npos)
		{
			kind = CItem::TARGET_DEAGE;
		}

		// CItem 생성 후 추가
		CItem newItem(name, kind, value);
		AddItem(newItem);
	}

	file.close();
	return true;
}

// 특정 인덱스의 아이템 정보를 가져오거나 처리하는 함수
CItem ItemManager::GetItem(int idx)
{
	if (idx >= 0 && idx < m_vecItems.size())
	{
		cout << "아이템 이름: " << m_vecItems[idx].m_strName << endl;
		cout << "효과 수치: " << m_vecItems[idx].m_nValue << endl;
		return m_vecItems[idx];
	}
	else
	{
		cout << "존재하지 않는 아이템 번호입니다." << endl;
		return CItem();
	}
}

// 아이템 관리 목록에 새로운 아이템을 추가하는 함수
void ItemManager::AddItem(CItem item)
{
	m_vecItems.push_back(item);
	cout << item.m_strName << "이(가) 아이템 목록에 추가되었습니다." << endl;
}

// 등록된 모든 아이템 목록을 출력하는 함수
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
		cout << i << ". " << m_vecItems[i].m_strName << " (효과 값: " << m_vecItems[i].m_nValue << ")" << endl;
	}
}

// ==========================================
// 전투 및 게임 메인 로직
// ==========================================
bool PlayerBattileMain(CPlayer& cPlayer, CPlayer& cMonster)
{
	cPlayer.Display();
	cMonster.Display();

	while (!cPlayer.Dead() && !cMonster.Dead())
	{
		// 플레이어 공격
		cPlayer.Attack(cMonster);
		if (cMonster.Dead())
		{
			cout << cPlayer.GetName() << " 승리! (Monster Dead)" << endl;

			cPlayer.StillExp(cMonster);
			cPlayer.StillMoney(cMonster);
			cPlayer.StillItem(cMonster); // 몬스터가 가진 아이템 획득

			if (cPlayer.LvUp(5))
				cout << cPlayer.GetName() << " Level Up!" << endl;

			cPlayer.Display();
			cMonster.Recovery();
			cout << "Battle End !!!\n" << endl;
			return false;
		}

		// 몬스터 공격
		cMonster.Attack(cPlayer);
		if (cPlayer.Dead())
		{
			cout << cPlayer.GetName() << " 이(가) 사망했습니다..." << endl;
			cout << "Battle End !!!\n" << endl;
			return true;
		}
	}

	return false;
}

enum MONSTER { FIELD, DUNGEON, GRAVE, VELLY, MAX };
enum PLACE_TYPE
{
	PLACE_TOWN,
	PLACE_SHOP,
	PLACE_FIELD,
	PLACE_INVENT,
	PLACE_MAX
};

void PlayerGameMain()
{
	string arrFiledName[MONSTER::MAX] = { "필드", "던전", "무덤", "계곡" };
	string arrPlaceName[PLACE_TYPE::PLACE_MAX] = { "마을", "상점", "필드", "인벤토리" };

	ItemManager itemMgr;

	// 1. ItemManager에 게임 내에서 사용할 아이템들을 미리 추가합니다.
	// CSV 데이터 기반 아이템 등록
	itemMgr.AddItem(CItem("힐링포션", CItem::HP_RECOVER, 50));   // id 1
	itemMgr.AddItem(CItem("마나포션", CItem::MP_RECOVER, 50));   // id 2
	itemMgr.AddItem(CItem("짱돌", CItem::TARGET_DEAGE, 20));     // id 3
	itemMgr.AddItem(CItem("폭탄", CItem::TEAM_DEAGE, 10));     // id 4

	// 2. 몬스터 생성 후 ItemManager로부터 아이템을 가져와서(GetItem 혹은 내부 벡터 접근) 분배합니다.
	CPlayer cSlime("Slime", 20, 5, 50, 100);
	cSlime.AddItem(itemMgr.GetItem(0)); // 하급 체력 포션 분배

	CPlayer cSkeleton("Skeleton", 100, 10, 80, 250);
	cSkeleton.AddItem(itemMgr.GetItem(1)); // 중급 체력 포션 분배

	CPlayer cZombie("Zombie", 120, 15, 120, 400);
	cZombie.AddItem(itemMgr.GetItem(2)); // 상급 체력 포션 분배

	CPlayer cDragon("Dragon", 200, 20, 200, 1000);
	cDragon.AddItem(itemMgr.GetItem(3)); // 드래곤의 심장 분배

	CPlayer cPlayer("Player", 100, 0, 10, 500);

	vector<CPlayer> listMonster;
	int nChoice = 0;

	listMonster.push_back(cSlime);
	listMonster.push_back(cSkeleton);
	listMonster.push_back(cZombie);
	listMonster.push_back(cDragon);

	while (!g_isExit)
	{
		cout << "\n가고 싶은 곳의 번호를 선택하시오." << endl;
		cout << "0. " << arrPlaceName[PLACE_TOWN] << " (체력 회복)" << endl;
		cout << "1. " << arrPlaceName[PLACE_SHOP] << " (상점)" << endl;
		cout << "2. " << arrPlaceName[PLACE_FIELD] << " (사냥터)" << endl;
		cout << "3. " << arrPlaceName[PLACE_INVENT] << " (인벤토리 열기)" << endl;
		cout << "입력: ";
		cin >> nChoice;

		switch (nChoice)
		{
		case PLACE_TOWN:
			cout << "\n마을에서 휴식을 취해 체력이 모두 회복되었습니다." << endl;
			cPlayer.Recovery();
			cPlayer.Display();
			break;

		case PLACE_SHOP:
		{
			cout << "\n=== [상점] ===" << endl;
			cout << "현재 소지금: " << cPlayer.GetMoney() << "G" << endl;
			cout << "1. 체력 포션 구매 (가격: 100G, 효과: HP 50 회복)" << endl;
			cout << "2. 나가기" << endl;
			cout << "선택: ";
			int shopChoice;
			cin >> shopChoice;

			if (shopChoice == 1)
			{
				if (cPlayer.UseMoney(100))
				{
					cPlayer.AddItem(CItem("상점표 체력 포션", CItem::HP_RECOVER, 50));
					cout << "포션을 구매하여 인벤토리에 추가했습니다!" << endl;
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
			cout << "\n가고 싶은 곳의 번호를 선택하시오." << endl;
			for (int i = 0; i < MONSTER::MAX; ++i)
			{
				cout << i << ". " << arrFiledName[i] << " : " << listMonster[i].GetName() << endl;
			}
			cout << "입력: ";
			cin >> nChoice;

			if (nChoice >= 0 && nChoice < MONSTER::MAX)
			{
				if (PlayerBattileMain(cPlayer, listMonster[nChoice]))
				{
					g_isExit = true;
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
			cPlayer.ShowInventory();
			break;
		}
		default:
			cout << "잘못된 입력입니다. 다시 선택해주세요." << endl;
			break;
		}
	}

	cout << "\nGAME OVER!!!" << endl;
}