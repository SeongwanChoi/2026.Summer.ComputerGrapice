#pragma once
#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

class CPlayer;

class MonsterManager
{
	vector<CPlayer*> m_vecMonsters; // 몬스터 원본 포인터 리스트

public:
	~MonsterManager();

	// MonsterManager 구현부
	bool LoadFromCSV(const string& filename);

	// 원본 몬스터 추가
	void AddMonster(CPlayer* monster);

	// 복사본(Clone)을 생성해서 반환하는 함수 (중요!)
	CPlayer* GetMonsterClone(int idx);

	// 복사본(Clone)을 생성해서 반환하는 함수 (중요!)
	CPlayer* GetMonster(int idx);

	int GetSize() { return m_vecMonsters.size(); }
};