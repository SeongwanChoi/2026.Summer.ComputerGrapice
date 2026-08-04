#include <iostream>
#include <thread>   // std::this_thread::sleep_for를 쓰기 위해 필요
#include <chrono>   // 시간 단위를 쓰기 위해 필요 (seconds, milliseconds 등)

using namespace std;

extern void GamePlay();

int main() {

	GamePlay();
	return 0;
}