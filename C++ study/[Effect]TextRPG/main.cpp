#include <iostream>//입출력라이브러리
#include <time.h>
#include <vector>
#include <typeinfo> // typeid를 사용하기 위해 추가
#include <fstream>
#include <sstream>
#include "Item.h"
#include "Player.h"
#include "MonsterManager.h"
#include "GameManager.h"

using namespace std;


bool g_isExit = false; // 전역변수

void PlayerAttackMonsterMain()
{
	cout << "PlayerAttackMonsterMainStart" << endl;
	int nMonsterHP = 100; // 몬스터의 체력
	int nPlayerAttack = 10; // 플레이어의 공격력

	cout << "몬스터의 체력: " << nMonsterHP << endl; //문장
	cout << "플레이어의 공격력: " << nPlayerAttack << endl;
	nMonsterHP = nMonsterHP - nPlayerAttack;
	cout << "몬스터의 체력: " << nMonsterHP << endl;
	cout << "플레이어의 공격력: " << nPlayerAttack << endl;
	cout << "PlayerAttackMonsterMainEnd" << endl;
}

void PlayerCritcalAttackMonsterMain()
{
	cout << "PlayerCritcalAttackMonsterMainStart" << endl;
	int nMonsterHP = 100;
	int nPlayerAttack = 10;

	cout << "몬스터의 체력: " << nMonsterHP << endl;
	cout << "플레이어의 공격력: " << nPlayerAttack << endl;

	int nRandom = rand() % 4; //0~99까지 랜덤숫자
	cout << "Random:" << nRandom << endl;
	if (nRandom == 1)
	{
		cout << "크리키컬히트!" << endl;
		nMonsterHP = nMonsterHP - (nPlayerAttack * 2);
	}
	else
		nMonsterHP = nMonsterHP - nPlayerAttack;

	cout << "몬스터의 체력: " << nMonsterHP << endl;
	cout << "플레이어의 공격력: " << nPlayerAttack << endl;
	cout << "PlayerCritcalAttackMonsterMainEnd" << endl;
}

void StageMain()
{
	cout << "StageMainStart" << endl;
	string strPlace;

	// typeid를 이용한 객체 이름과 주소값 출력 예시
	cout << "[TypeID Info] 객체 타입: " << typeid(strPlace).name()
		<< ", 주소값: " << &strPlace << endl;

	cout << "마을,상점,필드 중 가고 싶은곳을 선택하시오." << endl;
	cin >> strPlace;

	if (strPlace == "마을")
		cout << "마을 입니다" << endl;
	else if (strPlace == "상점")
		cout << "상점 입니다" << endl;
	else if (strPlace == "필드")
		cout << "필드 입니다" << endl;
	cout << "StageMainEnd" << endl;
}

void CPPStageMain()
{
	cout << "CPPStageMainStart" << endl;
	string strPlace;
	vector<string> arrPlace;

	cout << "[TypeID Info] strPlace 타입: " << typeid(strPlace).name() << ", 주소값: " << &strPlace << endl;
	cout << "[TypeID Info] arrPlace 타입: " << typeid(arrPlace).name() << ", 주소값: " << &arrPlace << endl;

	cout << "마을, 상점, 필드 중 가고 싶은 곳을 선택하시오." << endl;
	cin >> strPlace;

	arrPlace.push_back("마을"); // index 0
	arrPlace.push_back("상점"); // index 1
	arrPlace.push_back("필드"); // index 2

	auto iter = find(arrPlace.begin(), arrPlace.end(), strPlace);

	int nIdx = -1;

	if (iter != arrPlace.end())
	{
		nIdx = distance(arrPlace.begin(), iter);
	}

	switch (nIdx)
	{
	case 0:
		cout << "✨ [마을]에 입장했습니다. 안전한 곳입니다." << endl;
		break;

	case 1:
		cout << "🛒 [상점]에 입장했습니다. 아이템을 구매할 수 있습니다." << endl;
		break;

	case 2:
		cout << "⚔️ [필드]에 입장했습니다. 몬스터와 전투가 시작됩니다!" << endl;
		break;

	default:
		cout << "❌ 잘못된 입력입니다. '마을', '상점', '필드' 중 정확히 입력해주세요." << endl;
		break;
	}
	cout << "CPPStageMainEnd" << endl;
}

void PlayerAttackMonsterWhileMain()
{
	cout << "PlayerAttackMonsterWhileMainStart" << endl;
	int nMonsterHP = 100; // 몬스터의 체력
	int nPlayerAttack = 10; // 플레이어의 공격력
	cout << "몬스터의 체력: " << nMonsterHP << endl; //문장
	cout << "플레이어의 공격력: " << nPlayerAttack << endl;

	while (nMonsterHP != 0)
	{
		nMonsterHP = nMonsterHP - nPlayerAttack;
		cout << "몬스터의 체력: " << nMonsterHP << endl;
		cout << "플레이어의 공격력: " << nPlayerAttack << endl;
	}
	cout << "PlayerAttackMonsterWhileMainEnd" << endl;
}

void MonsterListMain()
{
	cout << "MonsterListMainStart" << endl;
	vector<string> listMonster;

	cout << "[TypeID Info] listMonster 타입: " << typeid(listMonster).name() << ", 주소값: " << &listMonster << endl;

	listMonster.push_back("Slime");
	listMonster.push_back("Skeleton");
	listMonster.push_back("Zombile");
	listMonster.push_back("Dragon");

	cout << "listMonster[0]:" << listMonster[0] << endl;
	cout << "listMonster[3]:" << listMonster[3] << endl;

	for (int i = 0; i < listMonster.size(); i++)
	{
		cout << i << ":" << listMonster[i] << ",";
	}
	cout << endl;
	cout << "MonsterListMainEnd" << endl;
}

void BattleMain()
{
	cout << "BattleMainStart" << endl;
	int nPlayerAttack = 20; // 플레이어의 공격력
	int nPlayerHP = 40;
	cout << "플레이어의 체력: " << nPlayerAttack << endl; //문장
	cout << "플레이어의 공격력: " << nPlayerAttack << endl;

	int nMonsterAttack = 20;
	int nMonsterHP = 40; // 몬스터의 체력
	cout << "몬스터의 체력: " << nMonsterHP << endl; //문장
	cout << "몬스터의 공격력: " << nMonsterAttack << endl;

	while (nMonsterHP > 0 && nPlayerHP > 0)
	{
		if (nPlayerHP <= 0)
		{
			cout << "플레이어사망!" << endl;
		}
		else
		{
			cout << "플레이어의 공격!" << endl;
			nMonsterHP = nMonsterHP - nPlayerAttack;
			cout << "몬스터의 체력: " << nMonsterHP << endl; //문장
			cout << "몬스터의 공격력: " << nMonsterAttack << endl;
		}

		if (nMonsterHP <= 0)
		{
			cout << "몬스터사망!" << endl;
		}
		else
		{
			cout << "몬스터의 공격!" << endl;
			nPlayerHP = nPlayerHP - nMonsterAttack;
			cout << "플레이어의 체력: " << nPlayerAttack << endl; //문장
			cout << "플레이어의 공격력: " << nPlayerAttack << endl;
		}
	}
	cout << "BattleMainEnd" << endl;
}

bool PlayerBattileMain(CPlayer& cPlayer, CPlayer cMonster)
{
	cout << "PlayerBattileMainStart" << endl;
	cout << "[TypeID Info] cPlayer 타입: " << typeid(cPlayer).name() << ", 주소값: " << &cPlayer << endl;
	cout << "[TypeID Info] cMonster 타입: " << typeid(cMonster).name() << ", 주소값: " << &cMonster << endl;

	while (!cPlayer.Dead() && !cMonster.Dead())
	{
		cPlayer.Attack(&cMonster);
		if (cMonster.Dead())
		{
			cout << cPlayer.GetName() << " 승리! (Monster Dead)" << endl;

			cPlayer.StillExp(&cMonster);
			cPlayer.StillMoney(&cMonster);
			cPlayer.StillItem(&cMonster);

			if (cPlayer.LvUp(5))
				cout << cPlayer.GetName() << " Level Up!" << endl;

			cPlayer.Display();
			cMonster.Recovery();
			cout << "Battle End !!!\n" << endl;
			cout << "PlayerBattileMainEnd" << endl;
			return false;
		}
		else
			cMonster.Display();

		cMonster.Attack(&cPlayer);
		if (cPlayer.Dead())
		{
			cout << cPlayer.GetName() << " 이(가) 사망했습니다..." << endl;
			cout << "Battle End !!!\n" << endl;
			cout << "PlayerBattileMainEnd" << endl;
			return true;
		}
		else
			cPlayer.Display();
	}

	cout << "PlayerBattileMainEnd" << endl;
	return false;
}


bool PlayerBattileMainPtr(CPlayer * pPlayer, CPlayer * pMonster)
{
	cout << "PlayerBattileMainStart" << endl;
	cout << "[TypeID Info] pPlayer 타입: " << typeid(pPlayer).name() << ", 주소값: " << &pPlayer << endl;
	cout << "[TypeID Info] pMonster 타입: " << typeid(pMonster).name() << ", 주소값: " << &pMonster << endl;

	cout << "\n⚔️ [" << pMonster->GetName() << "]을(를) 조우했습니다!" << endl;

	while (!pPlayer->Dead() && !pMonster->Dead())
	{
		// ------------------ 플레이어 턴 ------------------
		cout << "\n================ [ 전투 메뉴 ] ================" << endl;
		cout << "플레이어 HP: " << pPlayer->GetHp() << " | 몬스터 HP: " << pMonster->GetHp() << endl;
		cout << "1. 일반 공격" << endl;
		cout << "2. 아이템 사용" << endl;
		cout << "행동을 선택하세요: ";

		int nAction = 0;
		cin >> nAction;

		if (nAction == 1)
		{
			pPlayer->Attack(pMonster);
		}
		else if (nAction == 2)
		{
			// 1. 메인에서 출력 함수 호출
			pPlayer->ShowInventory();

			// 2. 메인에서 입력 처리
			cout << "사용할 아이템 번호 입력: ";
			int nIdx;
			cin >> nIdx;

			// 3. 메인에서 로직 함수 호출
			if (!pPlayer->UseItem(nIdx, pMonster)) {
				cout << "사용 실패!" << endl;
			}
			// 아이템 사용 성공 시 여기서 턴 종료(바로 아래 몬스터 턴으로 이동)
		}
		else
		{
			cout << "잘못된 입력입니다. 다시 선택해주세요." << endl;
			continue;
		}

		// 몬스터 사망 체크 (플레이어 공격/아이템 사용 직후)
		if (pMonster->Dead())
		{
			cout << "\n" << pPlayer->GetName() << " 승리! (" << pMonster->GetName() << " 처치)" << endl;
			pPlayer->StillExp(pMonster);
			pPlayer->StillMoney(pMonster);
			pPlayer->StillItem(pMonster);

			if (pPlayer->LvUp(5))
				cout << pPlayer->GetName() << " Level Up!" << endl;

			pPlayer->Display();
			pMonster->Recovery();
			cout << "Battle End !!!\n" << endl;
			if (pMonster) delete pMonster;
			return false;
		}
		else
		{
			pMonster->Display();
		}

		// ------------------ 몬스터 턴 ------------------
		cout << "\n[" << pMonster->GetName() << "]의 반격!" << endl;
		pMonster->Attack(pPlayer);

		if (pPlayer->Dead())
		{
			cout << pPlayer->GetName() << " 이(가) 사망했습니다..." << endl;
			cout << "Battle End !!!\n" << endl;
			if (pMonster) delete pMonster;
			return true;
		}
		else
		{
			pPlayer->Display();
		}
	}

	if (pMonster) delete pMonster;
	return false;
}

void PlayerGameMain()
{
	cout << "PlayerGameMainStart" << endl;
	CGameManager gameManager;

	gameManager.Init();
	gameManager.InitTest();

	int nChoice = 0;

	while (!g_isExit)
	{
		gameManager.Update();
	}

	cout << "\nGAME OVER!!!" << endl;
	cout << "PlayerGameMainEnd" << endl;
}



int main()
{
	cout << "mainStart" << endl;
	srand(static_cast<unsigned int>(time(NULL)));
	PlayerGameMain();
	cout << "mainEnd" << endl;
	return 0;
}