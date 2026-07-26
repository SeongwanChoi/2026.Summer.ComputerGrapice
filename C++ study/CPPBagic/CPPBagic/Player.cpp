#include <string>
#include <iostream>

using namespace std;

class CPlayer
{
	string m_strName;
	string m_strLocation;
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

	void setName(string name) { m_strName = name; }
};

void PlayerClassMain()
{
	CPlayer cPlayer("Player", 100, 10);
	CPlayer cMonster("Monster", 100, 10);

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

	cout << "Game Over !!!" << endl;
}

void PlayerBattileMain(CPlayer cPlayer, int Stage)
{
	cPlayer.Display();
	CPlayer cMonster("", 100, 10);

	switch (Stage)
	{
	case 1:
		cMonster.setName("Slime");
		break;
	case 2:	
		cMonster.setName("Skeleton");
		break;
	case 3:	
		cMonster.setName("Zombie");
		break;
	case 4:
		cMonster.setName("Dragon");
		break;
	default:
		cMonster.setName("Unknown");
		break;
	}

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

	cout << "Game Over !!!" << endl;
}

void PlayerGameMain(int stage)
{
	CPlayer cPlayer("Player", 100, 10);
	cPlayer.Display();
	
	PlayerBattileMain(cPlayer, stage);
}