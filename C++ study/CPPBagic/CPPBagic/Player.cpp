#include <string>
#include <iostream>

using namespace std;

// °æÇèÄ¡ È¹µæ ¼ö´Ü
// ¸ó½ºÅÍ Ã³Ä¡
// È¹µæ·® : 
class CPlayer
{
	string m_strName;
	string m_strLocation;
	int m_nHP;
	int m_nMaxHP;
	int m_nAtk;

	int m_nLv;
	int m_nExp;
public:
	CPlayer(string name, int hp, int atk, int exp)
	{
		m_strName = name;
		m_nHP = hp;
		m_nMaxHP = hp;
		m_nAtk = atk;
		m_nLv = 1;
		m_nExp = exp;
	}

	void LvUp()
	{
		if (m_nExp >= 100)
		{
			m_nExp -= 100;
			m_nLv++;
			m_nAtk += 5;
			m_nHP += 10;
		}
	}

	void stealExp(int exp)
	{
		m_nExp += exp;
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
		cout << "Lv:" << m_nLv << endl;
		cout << "Exp:" << m_nExp << endl;
	}

	void setName(string name) { m_strName = name; }
};

void PlayerClassMain()
{
	CPlayer cPlayer("Player", 100, 10, 0);
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

void PlayerBattleMain(CPlayer& cPlayer, int Stage)
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
		{
			cout << "Monster is Dead!" << endl;
			cPlayer.stealExp(cMonster.getExp());
		}
			
	}

	cout << "Game Over !!!" << endl;
}

void PlayerGameMain(int stage)
{
	CPlayer cPlayer("Player", 100, 10);
	cPlayer.Display();

	PlayerBattleMain(cPlayer, stage);
}