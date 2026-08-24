#include "MonsterManager.h"
#include <istream>
#include <fstream>
#include <sstream>

MonsterManager::~MonsterManager() {
	// 메모리 해제
	for (size_t i = 0; i < m_vecMonsters.size(); ++i) {
		delete m_vecMonsters[i];
	}
	m_vecMonsters.clear();
}

// MonsterManager 구현부
bool MonsterManager::LoadFromCSV(const string& filename)
{
	ifstream file = ifstream(filename);
	if (!file.is_open())
	{
		cout << "몬스터 CSV 파일을 열 수 없습니다: " << filename << endl;
		return false;
	}

	string line;
	// 첫 번째 줄(헤더) 스킵
	getline(file, line);

	while (getline(file, line))
	{
		stringstream ss(line);
		string idStr, name, hpStr, defStr, atkStr, expStr;

		// 쉼표 단위로 파싱
		getline(ss, idStr, ',');
		getline(ss, name, ',');
		getline(ss, hpStr, ',');
		getline(ss, defStr, ',');
		getline(ss, atkStr, ',');
		getline(ss, expStr, ',');

		if (name.empty()) continue;

		// 문자열을 정수로 변환 후 몬스터 객체 생성 (Heap 메모리에 동적 할당)
		int hp = stoi(hpStr);
		int def = stoi(defStr);
		int atk = stoi(atkStr);
		int exp = stoi(expStr);

		CPlayer* pNewMonster = new CPlayer(name, hp, def, atk, exp);
		AddMonster(pNewMonster);

		cout << "몬스터 등록 완료: " << name << " (HP: " << hp << ")" << endl;
	}

	file.close();
	return true;
}
// 원본 몬스터 추가
void MonsterManager::AddMonster(CPlayer* monster) {
	m_vecMonsters.push_back(monster);
}

// 복사본(Clone)을 생성해서 반환하는 함수 (중요!)
CPlayer* MonsterManager::GetMonsterClone(int idx) {
	if (idx >= 0 && idx < m_vecMonsters.size()) {
		// 원본 객체를 복사(Copy Constructor)하여 새로운 객체를 힙(Heap)에 생성 후 반환
		return new CPlayer(*m_vecMonsters[idx]);
	}
	return nullptr;
}

// 복사본(Clone)을 생성해서 반환하는 함수 (중요!)
CPlayer* MonsterManager::GetMonster(int idx) {
	if (idx >= 0 && idx < m_vecMonsters.size()) {
		// 원본 객체를 복사(Copy Constructor)하여 새로운 객체를 힙(Heap)에 생성 후 반환
		return m_vecMonsters[idx];
	}
	return nullptr;
}