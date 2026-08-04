#pragma once
#include <list>
using namespace std;

class Commander;

class Commander
{ 
	int nResources;	//	자원
	
	int n_Normal_Damage;	//  일반 공격 데미지
	int n_Explosion_Damage;	//	폭발 공격 데미지
	int n_Vibration_Damage;	//	진동 공격 데미지

	int n_Armor;		//	방어력
	int n_Small_Armor;	//  소형 방어력
	int n_Big_Armor;	//	대형 방어력

	int n_Combat_Power;	//	전투력
	
public:

	Commander(int re = 0, int ndm = 0, int edm = 0, int vdm = 0, int ar = 0, int sar = 0, int bar = 0, int cp = 0);
	void Display();
	void Command();
	void Paming();
	void Upgrade();
	void CombatUp();
	void Battle();
};