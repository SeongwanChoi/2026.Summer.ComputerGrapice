#include <string>
#include <iostream>
#include <vector>

using namespace std;

bool g_isExit = false; // 전역변수

class CPlayer
{
	string m_strName;
	int m_nHP = 0;
	int m_nMaxHP;
	int m_nAtk = 0;

	int m_nLv = 1;
	int m_nExp = 0;
	int m_nMoney = 0;

public:
	string GetName() { return m_strName; }
	int GetMoney() { return m_nMoney; }

	CPlayer(string name, int hp, int atk, int exp, int money = 0)
	{
		m_strName = name;
		m_nHP = hp;
		m_nMaxHP = hp;
		m_nAtk = atk;
		m_nExp = exp;
		m_nLv = 1;
		m_nMoney = money;
	}

	void Recovery()
	{
		m_nHP = m_nMaxHP;
	}

	bool LvUp(int add)
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

	void StillExp(CPlayer& target)
	{
		m_nExp += target.m_nExp;
	}

	// 상대방의 돈을 빼앗는 기능
	void StillMoney(CPlayer& target)
	{
		m_nMoney += target.m_nMoney;
		target.m_nMoney = 0;
	}

	void EarnMoney(int amount)
	{
		if (amount > 0) m_nMoney += amount;
	}

	bool UseMoney(int amount)
	{
		if (amount > 0 && m_nMoney >= amount)
		{
			m_nMoney -= amount;
			return true;
		}
		return false;
	}

	void Attack(CPlayer& target)
	{
		target.m_nHP -= this->m_nAtk;
	}

	bool Dead()
	{
		return m_nHP <= 0;
	}

	void Display()
	{
		cout << "----------------------------------" << endl;
		cout << "Name:" << m_strName << endl;
		cout << "HP:" << m_nHP << "/" << m_nMaxHP << endl;
		cout << "Atk:" << m_nAtk << endl;
		cout << "Lv/Exp:" << m_nLv << "/" << m_nExp << endl;
		cout << "Money:" << m_nMoney << "G" << endl;
		cout << "----------------------------------" << endl;
	}
};

// [수정] 전투 함수: 플레이어가 죽으면 게임 종료(true 반환)하도록 수정
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
			cout << cMonster.GetName() << " 승리! (Monster Dead)" << endl;

			// [해결 1] 몬스터 사망 시 경험치와 돈 획득 로직 추가
			cPlayer.StillExp(cMonster);
			cPlayer.StillMoney(cMonster); // 몬스터의 돈을 빼앗음 (또는 EarnMoney 활용 가능)

			if (cPlayer.LvUp(5))
				cout << cPlayer.GetName() << " Level Up!" << endl;

			cPlayer.Display();
			cMonster.Recovery(); // 다음전을 위해 몬스터 체력 회복
			cout << "Battle End !!!\n" << endl;
			return false; // 전투 종료 (게임은 계속 진행)
		}

		// 몬스터 공격
		cMonster.Attack(cPlayer);
		if (cPlayer.Dead())
		{
			cout << cPlayer.GetName() << " 이(가) 사망했습니다..." << endl;
			cout << "Battle End !!!\n" << endl;
			return true; // 플레이어 사망 시 게임 오버 트리거 반환
		}
	}

	return false;
}

enum MONSTER { FIELD, DUNGEON, GRAVE, VELLY, MAX };
enum PLACE_TYPE
{
	PLACE_TOWN, // 마을 (0번)
	PLACE_SHOP, // 상점 (1번)
	PLACE_FIELD,// 필드 (2번)
	PLACE_MAX
};

void PlayerGameMain()
{
	string arrFiledName[MONSTER::MAX] = { "필드", "던전", "무덤", "계곡" };
	string arrPlaceName[PLACE_TYPE::PLACE_MAX] = { "마을", "상점", "필드" };

	// 시작 시 기본 돈 500G 지급 예시
	CPlayer cPlayer("Player", 100, 10, 0, 500);

	// 몬스터 생성 시 각각의 보상(경험치, 돈) 설정
	CPlayer cSlime("Slime", 20, 5, 50, 100);
	CPlayer cSkeleton("Skeleton", 100, 10, 80, 250);
	CPlayer cZombie("Zombie", 120, 15, 120, 400);
	CPlayer cDragon("Dragon", 200, 20, 200, 1000);

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
			// [해결 3] 상점 기능 구현 예시
			cout << "\n=== [상점] ===" << endl;
			cout << "현재 소지금: " << cPlayer.GetMoney() << "G" << endl;
			cout << "1. 체력 포션 구매 (가격: 100G, 효과: 최대 HP 및 현재 HP 50 증가)" << endl;
			cout << "2. 나가기" << endl;
			cout << "선택: ";
			int shopChoice;
			cin >> shopChoice;

			if (shopChoice == 1)
			{
				if (cPlayer.UseMoney(100))
				{
					cout << "포션을 구매했습니다! (기능 확장 가능)" << endl;
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

			// 유효하지 않은 번호 입력 방지 예외 처리
			if (nChoice >= 0 && nChoice < MONSTER::MAX)
			{
				// PlayerBattileMain이 true를 리턴하면 플레이어가 죽은 것이므로 게임 종료
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
		default:
			cout << "잘못된 입력입니다. 다시 선택해주세요." << endl;
			break;
		}
	}

	cout << "\nGAME OVER!!!" << endl;
}