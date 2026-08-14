#pragma once
#include <thread>
#include <mutex>

using namespace std;

class Commander;

class Commander
{ 
	int nResources;	//	자원
	int n_UP_Resources = 1; // 자원 증가량
	
	int n_Normal_Damage;	//  기본 공격 데미지
	int n_Explosion_Damage;	//	폭발 공격 데미지
	int n_Vibration_Damage;	//	진동 공격 데미지

	int n_Armor;		//	방어력
	int n_Small_Armor;	//  소형 방어력
	int n_Big_Armor;	//	대형 방어력

	
	bool m_bAutoMining; // 자동 자원 채취 트리거
	thread m_MiningThread;
	mutex m_ResourceMutex; // 자원 동기화용 뮤텍스

	void AutoMiningWorker();

public:

	Commander(int re = 0, int ndm = 0, int edm = 0, int vdm = 0, int ar = 0, int sar = 0, int bar = 0, int cp = 0);
	~Commander();

	void Display();
	void Command();
	void Paming();
	void Upgrade();
	void PartyFull();
	void Battle();

};