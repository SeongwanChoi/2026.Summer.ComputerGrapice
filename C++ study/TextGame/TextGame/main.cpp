#include <iostream>
#include <thread>   // std::this_thread::sleep_for를 쓰기 위해 필요
#include <chrono>   // 시간 단위를 쓰기 위해 필요 (seconds, milliseconds 등)

using namespace std;
int main() {
	
	cout << "Hello, World!" << endl;
	cout << "Hello, World!" << endl;
	cout << "Hello, World!" << endl;

	this_thread::sleep_for(chrono::seconds(10));

	cout << "Hello, World!" << endl;
	cout << "Hello, World!" << endl;

	return 0;
}