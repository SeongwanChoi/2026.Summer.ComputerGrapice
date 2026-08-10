#include <iostream>

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
		n_Combat_Power = cp;
		cout << "반갑습니다 사령관님, 숫자를 눌러 명령을 내려주세요" << endl;
		Display();
}

void Commander::Command()
{
	cout << "========================" << endl;
	cout << "1. 자원채취		";
	cout << "2. 업그레이드		";
	cout << "3. 병력증원" << endl;
	cout << "4. 전장으로		";
	cout << "5. 전술판" << endl;
	cout << "========================" << endl;
}

void Commander::Paming()
{
	cout << "미네랄을 획득했습니다." << endl;
	nResources += 1;
	cout << "현재 자원 : " << nResources << endl;
}

void Commander::Upgrade()
{

}

void Commander::CombatUp()
{

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

void GamePlay()
{
	Commander commander;
	int nChoice;

	while (true) {
		commander.Command();
		cin >> nChoice;

		switch (nChoice)
		{
			case 1:
				commander.Paming();
			break;
			case 2:
				commander.Upgrade();
			break;
			case 3:
				commander.CombatUp();
			break;
			case 4:
				commander.Battle();
			break;
			case 5:
				commander.Display();
			break;
			default:
				cout << "잘못된 입력입니다. 다시 선택해주세요." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}
	
}