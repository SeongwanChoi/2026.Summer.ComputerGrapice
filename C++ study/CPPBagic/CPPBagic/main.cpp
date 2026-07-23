#include <iostream> // 입출력 라이브러리
#include <vector>
// F5 : 프로그램 실행

using namespace std;

// 알고리즘 : 문제를 푸는 방법

// 플레이어가 몬스터를 공격한다.
// 플레이어가 몬스터를 공격하면 몬스터의 체력이 감소한다.
// 플레이어가 몬스터를 공격하면 (몬스터의 체력)이 (플레이어의 공격력)만큼 감소한다.


// 데이터 : 몬스터의 체력, 플레이어의 공격력
// 알고리즘 : 몬스터의 체력 - 플레이어의 공격력

// 크리티컬 : 약점을 공격하여 큰 데미지를 준다, 약점은 확률로 조정한다
// 확률 : 나타난 경우의 수
// 데이터 : 랜덤값, 25%를 구현하기 위한 값
// 알고리즘 : 프로그램이 시작될 때 랜덤시드를 지정한다.
// 2. 크리티컬 어택 발생 전에 랜덤값을 가져온다.
// 3. 랜덤값이 1이면 크리티컬이 발생한다, 아니라면 정상적인 데미지 증가를 적용한다.

// 종료 : 전투대상의 체력이 0이 되었다.
// 알고리즘을 만들 때 잘 모르겠으면 무한루프를 돌리고, 조건을 찾아서 브레이크하면 쉽게 찾을 수 있다.

// 플레이어에게 공격을 받으면 몬스터는 반격(공격을 받으면 몬스터가 플레이어를 공격한다)한다.
// 데이터 : 몬스터의 공격력, 플레이어의 체력
// 알고리즘 : 플레이어의 체력 - 몬스터의 공격력
void PlayerAttackMonsterMain() {

	int nMonsterHealth = 100;
	int nMonsterAttack = 10;

	int nPlayerHealth = 100;
	int nPlayerAttack = 10;


	cout << "몬스터의 체력 : " << nMonsterHealth << endl;
	cout << "몬스터의 공격력 : " << nMonsterAttack << endl;
	
	cout << "플레이어의 체력 : " << nPlayerHealth << endl;
	cout << "플레이어의 공격력 : " << nPlayerAttack << endl;

	while (nMonsterHealth >= 0 || nPlayerHealth >= 0)
	{
		// 크리티컬 발생
		int nRandom = rand() % 4;
		cout << "Random: " << nRandom << endl;
		if (nRandom == 1)
		{
			cout << "크리티컬!" << endl;
			nMonsterHealth = nMonsterHealth - (nPlayerAttack * 2);
		}
		else
			nMonsterHealth = nMonsterHealth - nPlayerAttack;

		nMonsterHealth = nMonsterHealth - nPlayerAttack;
		nPlayerHealth = nPlayerHealth - nMonsterAttack;

		cout << "몬스터의 체력 : " << nMonsterHealth << endl;
		cout << "플레이어의 체력 : " << nPlayerHealth << endl;
	}
	
}

// 가고싶은 장소를 입력하면 해당 장소에 도착했다는 메시지를 띄운다
// 데이터: 장소명(문자열)
// 알고리즘 : 가고싶은 장소의 값과 일치한 장소를 선택하고 선택한 장소로간다.
void CPPStageMain() 
{
	string strPlace;
	
	cout << "마을, 상점, 필드 중 가고싶은곳을 선택하시오." << endl;
	cin >> strPlace;

	if (strPlace == "마을") {
		cout << "마을 입니다." << endl;
	}
	else if (strPlace == "상점") {
		cout << "상점 입니다." << endl;
	}
	else if (strPlace == "상점") {
		cout << "필드 입니다." << endl;
	}

	
}

int main() {
	srand(static_cast<unsigned int>(time(NULL)));
	PlayerAttackMonsterMain();
	return 0;
}