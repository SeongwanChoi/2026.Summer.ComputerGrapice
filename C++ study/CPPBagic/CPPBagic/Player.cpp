#include <string>
#include <iostream>

using namespace std;

class CPlayer
{
	string m_strName;
	int m_nHP;
	int m_nAtk;
public:
	CPlayer(string name, int hp, int atk)
	{
		m_strName = name;
		m_nHP = hp;
		m_nAtk = atk;
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
		cout << "Name:" << m_strName << endl;
		cout << "HP:" << m_nHP << endl;
		cout << "Atk:" << m_nAtk << endl;
	}
};

void PlayerClassMain()
{
	CPlayer cPlayer("플레이어", 100, 10);
	CPlayer cMonster("몬스터", 100, 10);

	while (!cPlayer.Dead() && !cMonster.Dead())
	{
		if (!cPlayer.Dead())
		{
			cPlayer.Attack(cMonster);
			cMonster.Display();
		}
		else
			cout << "Player is Dead!" << endl;

		if (!cMonster.Dead())
		{
			cMonster.Attack(cPlayer);
			cPlayer.Display();
		}
		else
			cout << "Monster is Dead!" << endl;
	}
}

void PlayerBattlesMain(CPlayer cPlayer, CPlayer cMonster)
{
	cPlayer.Display();
	cMonster.Display();

	while (!cPlayer.Dead() && !cMonster.Dead())
	{
		if (!cPlayer.Dead())
		{
			cPlayer.Attack(cMonster);
			cMonster.Display();
		}
		else
			cout << "Player is Dead!" << endl;

		if (!cMonster.Dead())
		{
			cMonster.Attack(cPlayer);
			cPlayer.Display();
		}
		else
			cout << "Monster is Dead!" << endl;
	}
}