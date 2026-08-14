#include <iostream>
#include <thread>   // std::this_thread::sleep_for를 쓰기 위해 필요
#include <chrono>   // 시간 단위를 쓰기 위해 필요 (seconds, milliseconds 등)
#include "Commander.h"

using namespace std;

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
			commander.PartyFull();
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

int main() {

	GamePlay();
	return 0;
}