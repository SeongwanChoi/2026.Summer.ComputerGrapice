#pragma once
#include <thread>
#include <mutex>
#include <vector>
#include <list>

using namespace std;

enum class AttackType { Normal, Explosion, Vibration };
enum class ArmorType { Small, Medium, Large }; 

struct Unit {
	string name;
	int hp;
	int damage;
	ArmorType armorType;
};

class Commander
{ 
	int nResources;	//	자원
	int n_UP_Resources = 1; // 자원 증가량
	
	int n_Damage;
	int n_Armor;

	vector<Unit> m_Army; // 병력을 담을 연결리스트

	bool m_bAutoMining; // 자동 자원 채취 트리거
	thread m_MiningThread;
	mutex m_ResourceMutex; // 자원 동기화용 뮤텍스

	void AutoMiningWorker();

public:

	Commander(int re = 0, int ndm = 0, int ar = 0);
	~Commander();

	void Display();
	void Command();
	void Paming();
	void Upgrade();
	void PartyFull();
	void Battle();

};