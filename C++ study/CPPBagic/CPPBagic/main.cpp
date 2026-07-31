#include <iostream>//입출력라이브러리
#include <time.h>
#include <vector>

using namespace std;

//F5: 프로그램 실행
//알고리즘: 문제를 푸는 방법. 플레이어가 몬스터를 (공격)했다.
//플레이어가 몬스터를 공격한다.
//플레이어가 몬스터를 공격하면 (몬스터의 체력)이 감소한다.
//플레이어가 몬스터를 공격하면 체력이 공격력만큼 감소한다.
//데이터: 체력 = 100, 공격력 = 10
//알고리즘: 체력-공격력 체력=90
//플레이어가 몬스터를 공격하면 (몬스터의 체력)이 (플레이어의 공격력)감소한다.
//데이터: 몬스터의 체력, 플레이어의 공격력
//알고리즘: 몬스터의 체력 - 플레이어의 공격력
//함수: 어떤기능을 묶어서 재사용 하도록 만드는 것
void PlayerAttackMonsterMain() 
{//구문
	int nMonsterHP = 100; // 몬스터의 체력
	int nPlayerAttack = 10; // 플레이어의 공격력

	cout << "몬스터의 체력: " << nMonsterHP << endl; //문장
	cout << "플레이어의 공격력: " << nPlayerAttack << endl;
	nMonsterHP = nMonsterHP - nPlayerAttack;
	cout << "몬스터의 체력: " << nMonsterHP << endl;
	cout << "플레이어의 공격력: " << nPlayerAttack << endl;
}
//플레이어가 몬스터를 공격하면 (몬스터의 체력)이 (플레이어의 공격력)감소한다.
//데이터: 몬스터의 체력, 플레이어의 공격력
//알고리즘: 몬스터의 체력 - 플레이어의 공격력
//플레이어가 몬스터를 공격하면 크리티컬이 발생하도록 만든다.
//크리티컬: 치명타,약점공격하여 더 큰데미지를 줌.
//약점을 공격이 항상되지않도록 랜덤으로 크리티컬이 발생한다.
//랜덤: 확률: 상자에 있는 공중에 1개를 뽑는 경우 > 램덤
//데이터: 랜덤값, 25%를 구현하기위한 값
//알고리즘: 프로그램이 시작될때 랜덤시드를 지정한다.
//.....  
//크리티컬어택발생전에 랜덤값 25%의 확률로 생성하고, 랜덤값이 1이면 크리티컬확률이 작동한다.
//크리티컬이 터지면 "크리티컬히트"를 출력한다
//.....
void PlayerCritcalAttackMonsterMain()
{
	int nMonsterHP = 100; 
	int nPlayerAttack = 10; 

	cout << "몬스터의 체력: " << nMonsterHP << endl; 
	cout << "플레이어의 공격력: " << nPlayerAttack << endl;

	//크리티컬어택발생
	
	int nRandom = rand() % 4; //0~99까지 랜덤숫자
	cout << "Random:" << nRandom << endl;
	if (nRandom == 1)
	{
		cout << "크리키컬히트!" << endl;
		nMonsterHP = nMonsterHP - (nPlayerAttack*2);
	}
	else
		nMonsterHP = nMonsterHP - nPlayerAttack;

	cout << "몬스터의 체력: " << nMonsterHP << endl;
	cout << "플레이어의 공격력: " << nPlayerAttack << endl;
}
//마을,상점,필드 중 가고 싶은 장소를 입력하면, ??장소에 도착했습니다. 메세지가 뜨는 프로그램을 만듦.
//데이터: 장소명(문자열)
//알고리즘(가고 싶은 장소의 값과 일치한 장소를 선택)하고 선탁한 장소로 간다.
void StageMain()
{
	string strPlace;

	cout << "마을,상점,필드 중 가고 싶은곳을 선택하시오." << endl;
	cin >> strPlace;

	if (strPlace == "마을")
		cout << "마을 입니다" << endl;
	else if (strPlace == "상점")
		cout << "상점 입니다" << endl;
	else if (strPlace == "필드")
		cout << "필드 입니다" << endl;
}
//마을,상점,필드 중 가고 싶은 장소를 입력하면, ??장소에 도착했습니다. 메세지가 뜨는 프로그램을 만듦.
//데이터: 장소명(문자열)
//알고리즘(가고 싶은 장소의 값과 일치한 장소를 선택)하고 선탁한 장소로 간다.
void CPPStageMain()
{
	string strPlace;

	cout << "마을, 상점, 필드 중 가고 싶은 곳을 선택하시오." << endl;
	cin >> strPlace;

	// 이동 가능한 장소들을 벡터에 등록
	vector<string> arrPlace;
	arrPlace.push_back("마을"); // index 0
	arrPlace.push_back("상점"); // index 1
	arrPlace.push_back("필드"); // index 2

	// 1. std::find로 벡터 안에서 입력받은 장소의 위치(이터레이터)를 찾습니다.
	auto iter = find(arrPlace.begin(), arrPlace.end(), strPlace);

	// 기본 인덱스 값은 찾지 못했을 때를 대비해 -1로 설정합니다.
	int nIdx = -1;

	// 2. 장소를 찾았다면(끝까지 가지 않았다면) 시작점과의 거리(오프셋)를 구합니다.
	if (iter != arrPlace.end())
	{
		nIdx = distance(arrPlace.begin(), iter);
	}

	// 3. 구한 인덱스(오프셋)를 switch 문으로 분기 처리합니다.
	switch (nIdx)
	{
	case 0:
		cout << "✨ [마을]에 입장했습니다. 안전한 곳입니다." << endl;
		// 마을 관련 로직 호출 (예: TownMain();)
		break;

	case 1:
		cout << "🛒 [상점]에 입장했습니다. 아이템을 구매할 수 있습니다." << endl;
		// 상점 관련 로직 호출 (예: ShopMain();)
		break;

	case 2:
		cout << "⚔️ [필드]에 입장했습니다. 몬스터와 전투가 시작됩니다!" << endl;
		// 필드/전투 관련 로직 호출 (예: FieldMain();)
		break;

	default:
		cout << "❌ 잘못된 입력입니다. '마을', '상점', '필드' 중 정확히 입력해주세요." << endl;
		break;
	}
}
enum PLACE_TYPE
{
	PLACE_TOWN = 1, // 마을 (1번)
	PLACE_SHOP,     // 상점 (2번)
	PLACE_FIELD,    // 필드 (3번)
	PLACE_MAX       // 최대 개수 체크용
};
void CPPStageMain2()
{
	// 2. 출력용 string 배열 선언 (인덱스 맞추기를 위해 0번은 빈 값 또는 안내용으로 둠)
	// 예: 인덱스 1 = 마을, 2 = 상점, 3 = 필드
	string arrPlaceName[PLACE_MAX] = { "", "마을", "상점", "필드" };

	int nChoice = 0;

	cout << "가고 싶은 곳의 번호를 선택하시오." << endl;
	cout << "1. " << arrPlaceName[PLACE_TOWN] << endl;
	cout << "2. " << arrPlaceName[PLACE_SHOP] << endl;
	cout << "3. " << arrPlaceName[PLACE_FIELD] << endl;
	cout << "입력: ";
	cin >> nChoice;

	// 3. switch 문으로 열거형 값 분기 처리
	switch (nChoice)
	{
	case PLACE_TOWN:
	case PLACE_SHOP:
	case PLACE_FIELD:
		// 배열에서 스트링 값을 가져와서 쉽게 출력
		cout << "✨ [" << arrPlaceName[nChoice] << "]에 입장했습니다!" << endl;
		break;

	default:
		cout << "❌ 잘못된 번호입니다. 1부터 3까지의 숫자를 입력해주세요." << endl;
		break;
	}
}
//죽었다: 전투가 끝났다? 체력이 0 되었다.
//알고리즘을 만들때 잘모르겠으면 무한루프를 돌리고, 조건을 찾아서 브레이크하면쉽게 찾을수있다.
void PlayerAttackMonsterWhileMain()
{//구문
	int nMonsterHP = 100; // 몬스터의 체력
	int nPlayerAttack = 10; // 플레이어의 공격력
	cout << "몬스터의 체력: " << nMonsterHP << endl; //문장
	cout << "플레이어의 공격력: " << nPlayerAttack << endl;

	//while (true)
	while(nMonsterHP != 0)
	{
		nMonsterHP = nMonsterHP - nPlayerAttack;
		cout << "몬스터의 체력: " << nMonsterHP << endl;
		cout << "플레이어의 공격력: " << nPlayerAttack << endl;

		//if (nMonsterHP == 0) break;
	}
}
//몬스터 슬라임,스켈레톤,좀비,드래곤를 리스트에 저장하고, 그리고, 각 인덱스(0,3)에 접근해서 출력하고, 리스트에 있는 모든값을 출력한다.
//데이터: 리스트 -> 배열,동적배열(std::vector) -> string
//알고리즘: 벡터에 0번째 값과, 3번째값을 출력하고, 벡터의 0번부터 크기기 까지 하나씩 출력한다.
void MonsterListMain()
{
	vector<string> listMonster;

	listMonster.push_back("Slime");
	listMonster.push_back("Skeleton");
	listMonster.push_back("Zombile");
	listMonster.push_back("Dragon");

	cout << "listMonster[0]:" << listMonster[0] << endl;
	cout << "listMonster[3]:" << listMonster[3] << endl;

	for (int i = 0; i < listMonster.size(); i++)
	{
		cout << i <<":" <<listMonster[i] << ",";
		//printf("%d:%s,", i, listMonster[i].c_str());
	}
	cout << endl;
}

//플레이어가 몬스터를 공격하면 체력이 공격력만큼 감소한다.
//플레이어가 몬스터를 공격하면 (몬스터의 체력)이 (플레이어의 공격력)감소한다.
//플레이어에게 공격을 받으면 몬스터는 (반격:공격을 받으면 몬스터가 플레이어를 공격해 몬스터의 공격력만큼 플레이어의 체력이 감소)한다.
//데이터: 몬스터의 체력, 플레이어의 공격력, 몬스터의 공격력, 플레이어의 체력
//알고리즘: 몬스터의 체력 - 플레이어의 공격력, 플레이이어의 체력 - 몬스터의 공격력
void BattleMain()
{

	int nPlayerAttack = 20; // 플레이어의 공격력
	int nPlayerHP = 40;
	cout << "플레이어의 체력: " << nPlayerAttack << endl; //문장
	cout << "플레이어의 공격력: " << nPlayerAttack << endl;

	
	int nMonsterAttack = 20;
	int nMonsterHP = 40; // 몬스터의 체력
	cout << "몬스터의 체력: " << nMonsterHP << endl; //문장
	cout << "몬스터의 공격력: " << nMonsterAttack << endl;

	//while (true)
	while (nMonsterHP > 0 && nPlayerHP > 0)
	{
		if (nPlayerHP <= 0)
		{
			cout << "플레이어사망!" << endl;
			//break;
		}
		else
		{
			cout << "플레이어의 공격!" << endl;
			nMonsterHP = nMonsterHP - nPlayerAttack;
			cout << "몬스터의 체력: " << nMonsterHP << endl; //문장
			cout << "몬스터의 공격력: " << nMonsterAttack << endl;
		}

		if (nMonsterHP <= 0)
		{
			cout << "몬스터사망!" << endl;
			//break;
		}
		else
		{
			cout << "몬스터의 공격!" << endl;
			nPlayerHP = nPlayerHP - nMonsterAttack;
			cout << "플레이어의 체력: " << nPlayerAttack << endl; //문장
			cout << "플레이어의 공격력: " << nPlayerAttack << endl;
		}	
	}
}

//extern void PlayerClassMain();//함수의 선언
extern void PlayerGameMain();

int main() 
{
	//cout << "Hello, World!" << endl;
	srand(static_cast<unsigned int>(time(NULL)));
	//PlayerAttackMonsterMain();
	//PlayerCritcalAttackMonsterMain();
	//StageMain();
	//CPPStageMain();
	//CPPStageMain2();
	//PlayerAttackMonsterWhileMain();
	//BattleMain();
	//MonsterListMain();

	//PlayerClassMain();
	PlayerGameMain();
	return 0;
}