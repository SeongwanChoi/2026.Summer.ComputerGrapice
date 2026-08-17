#include <iostream>
#include <thread>
#include <mutex>
#include "Commander.h"

using namespace std;

Commander::Commander(int re, int ndm, int edm, int vdm, int ar, int sar, int bar, int cp)
{
		nResources = re;
		n_Normal_Damage = ndm;
		n_Explosion_Damage = edm;
		n_Vibration_Damage = vdm;
		n_Armor = ar;
		n_Small_Armor = sar;
		n_Big_Armor = bar;

		m_bAutoMining = true;
		srand(static_cast<unsigned int>(time(nullptr)));

		// 백그라운드 미네랄 채취 스레드 시작 
		m_MiningThread = thread(&Commander::AutoMiningWorker, this);

		cout << "반갑습니다 사령관님, 숫자를 눌러 명령을 내려주세요" << endl;
		Display();
}

Commander::~Commander()
{
	// 프로그램 종료 시 스레드 안전하게 종료 대기
	m_bAutoMining = false;
	if (m_MiningThread.joinable())
	{
		m_MiningThread.join();
	}
}

// 백그라운드에서 주기적으로 자원을 캐는 스레드 함수
void Commander::AutoMiningWorker()
{
	while (m_bAutoMining)
	{
		this_thread::sleep_for(chrono::seconds(1)); // 1초마다 미네랄 증가

		// 여러 스레드가 동시에 자원 변수에 접근하는 것을 방지 (Thread-safe)
		lock_guard<mutex> lock(m_ResourceMutex);
		nResources += n_UP_Resources;
		// cout << "\n[시스템] 미네랄이 " << n_UP_Resources << "만큼 채취되었습니다. (현재 자원: " << nResources << ")" << endl;
	}
}

void Commander::Command()
{
	cout << "========================" << endl;
	cout << "1. 자원 확인		";
	cout << "2. 업그레이드		";
	cout << "3. 병력증원" << endl;
	cout << "4. 전장으로		";
	cout << "5. 전술판" << endl;
	cout << "========================" << endl;
}

void Commander::Paming()
{
	cout << "========================" << endl;
	cout << endl;
	cout << "현재 자원 : " << nResources << endl;
	cout << endl;
	cout << "========================" << endl;
}

void Commander::Upgrade()
{
	int Upgrade = 0;
	bool g_bUpgrade = 1;

	while (g_bUpgrade)
	{
		cout << "1. 획득 미네랄 + 1 " << endl;
		cout << "2. 폭발 공격 강화" << endl;
		cout << "3. 진동 공격 강화" << endl;
		cout << "4. 장갑 강화" << endl;
		cout << "5. 소형 장갑 강화" << endl;
		cout << "6. 대형 장갑 강화" << endl;
		cout << "7. 나가기" << endl;
		cin >> Upgrade;

		switch (Upgrade)
		{
			case 1:
				n_UP_Resources++;
				break;
			case 2:
				n_Normal_Damage += 10;
				n_Explosion_Damage += 10;
				break;
			case 3:
				n_Normal_Damage += 10;
				n_Vibration_Damage += 10;
				break;
			case 4:
				n_Armor += 10;
				break;
			case 5:
				n_Small_Armor += 10;
				break;
			case 6:
				n_Big_Armor += 10;
				break;
			case 7:
				g_bUpgrade = 0;
				break;
			default:
				cout << "다시 입력해주세요. " << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
		}
	}
	
}

void Commander::PartyFull()
{
	int unitChoice = 0;
	bool g_bTraining = true;

	while (g_bTraining)
	{
		cout << "\n--- 병력 증원 센터 (현재 미네랄: " << nResources << ") ---" << endl;
		cout << "1. 마린 생산 (50원) - HP: 40, ATK: " << n_Normal_Damage << endl;
		cout << "2. 파이어뱃 생산 (80원) - HP: 50, ATK: " << n_Normal_Damage + 5 << endl;
		cout << "3. 나가기" << endl;
		cout << "선택: ";
		cin >> unitChoice;

		switch (unitChoice)
		{
		case 1: // 마린 생산
		{
			lock_guard<mutex> lock(m_ResourceMutex);
			if (nResources >= 50) {
				nResources -= 50;
				m_Army.push_back({ "마린", 40, n_Normal_Damage });
				cout << "마린이 생산되었습니다." << endl;
			}
			else {
				cout << "미네랄이 부족합니다!" << endl;
			}
			break;
		}
		case 2: // 파이어뱃 생산
		{
			lock_guard<mutex> lock(m_ResourceMutex);
			if (nResources >= 80) {
				nResources -= 80;
				m_Army.push_back({ "파이어뱃", 50, n_Normal_Damage + 5 });
				cout << "파이어뱃이 생산되었습니다." << endl;
			}
			else {
				cout << "미네랄이 부족합니다!" << endl;
			}
			break;
		}
		case 3:
			g_bTraining = false;
			break;
		default:
			cout << "잘못된 선택입니다." << endl;
			break;
		}
	}
}

void Commander::Battle()
{

}

void Commander::Display()
{
	cout << "========================" << endl;
	cout << "자원: " << nResources << endl;
	cout << "일반 공격력: " << n_Normal_Damage << endl;
	cout << "폭발 공격력: " << n_Explosion_Damage << endl;
	cout << "진동 공격력: " << n_Vibration_Damage << endl;
	cout << "방어력: " << n_Armor << endl;
	cout << "소형 방어력: " << n_Small_Armor << endl;
	cout << "대형 방어력: " << n_Big_Armor << endl;
	cout << "========================" << endl;
}

