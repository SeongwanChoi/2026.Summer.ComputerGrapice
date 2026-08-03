#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <string>
#include <unordered_map>//hash_map -> unordered_map: vs2019부터 변경
using namespace std;
//벡터: 동적배열
//0.배열은 데이터가 저장될공간이 미리 확보되어있다.
//1.인덱스로 원소접근이 가능하다.
//2.각 자료는 포인터연산(인덱스)을 통한 순차/랜덤접근이 가능하다.
//3.배열의 크기를 런타임중에 변경가능하다.
// container : 화물의 짐을 담는 물건을 뜻하는 말, 컴퓨터에서 담아야할 물건은? 데이터
void VectorMain() // 동적 배열
{
	vector<int> container(1);//컨테이너생성시 크기를 지정가능하다.
	container[0] = 10;
	cout << "Print:";
	for (int i = 0; i < container.size(); i++)
		cout << "[" << i << "]" << container[i] << ",";
	cout << endl;
	container.resize(3); //배열의 크기를 지정한다.
	container[1] = 20;
	container[2] = 30;
	cout << "Print:";
	for (int i = 0; i < container.size(); i++)
		cout << "[" << i << "]" << container[i] << ",";
	cout << endl;
	//1.추가 2.삽입 3.삭제 4.모두삭제
	vector<int>::iterator it;
	container.push_back(40); 
	cout << "PrintPtr:";
	for (it = container.begin(); it != container.end(); it++)
		cout << "[" << &*it << "]" << *it << ",";
	cout << endl;
	container.clear(); //모두삭제
	cout << "Clear:";
	for (it = container.begin(); it != container.end(); it++)
		cout << "[" << &*it << "]" << *it << ",";
	cout << endl;
}
//연결리스트
//1.데이터는 순차접근만 가능하다.(랜덤x)
//2.연결리스트에 추가,삽입,삭제은 O(1)이다.
//3.연결리스트의 종류: 단일, 환형, 이중 stl의 리스트는 어디에 해당되는가?
void ListMain()
{
	list<int> listData = {10, 20};
	listData.push_front(30);
	list<int>::iterator it;
	cout << "PrintList:";
	for (it = listData.begin(); it != listData.end(); it++)
		cout << *it << ",";
	cout << endl;

	it = listData.begin();
	it++;
	listData.insert(it, 40); // insert: 가리키는 위치 앞에 원하는 데이터 삽입
	cout << "insertList:";
	for (it = listData.begin(); it != listData.end(); it++)
		cout << *it << ",";
	cout << endl;

	it = listData.begin();
	it++;
	listData.erase(it); // erase: 가리키는 위치의 데이터를 삭제
	cout << "erasetList:";
	for (it = listData.begin(); it != listData.end(); it++)
		cout << *it << ",";
	cout << endl;

	listData.clear(); // clear: 모든 데이터를 삭제
	cout << "clearList:";
	for (it = listData.begin(); it != listData.end(); it++)
		cout << *it << ",";
	cout << endl;
}
//데크: 앞뒤로 자료를 추가/삭제가능, 랜덤접근가능.
void DequeMain()
{
	deque<int> deqData = { 10, 20 };
	deque<int>::iterator it;
	cout << "PrintDeque:";
	for (it = deqData.begin(); it != deqData.end(); it++)
		cout << *it << ",";
	cout << endl;

	deqData.emplace_front(30); 
	deqData.push_front(40);
	it = deqData.begin();
	it++;
	deqData.insert(it, 50);
	cout << "insertDeque:";
	for (it = deqData.begin(); it != deqData.end(); it++)
		cout << *it << ",";
	cout << endl;

	deqData.pop_front();
	deqData.pop_back();
	it = deqData.begin();
	it++;
	deqData.erase(it); 
	cout << "erasetDeque:";
	for (it = deqData.begin(); it != deqData.end(); it++)
		cout << *it << ",";
	cout << endl;
	
	deqData.clear();
	cout << "clearDeque:";
	for (it = deqData.begin(); it != deqData.end(); it++)
		cout << *it << ",";
	cout << endl;
}
//스택: 뒤에서 추가되고 뒤에서 꺼냄.
//재귀함수에서 이전 함수를 호출할때마다 스택에 쌓임.
//문자열뒤집기 -> 문자배열 -> apple -> elppa
void StackMain()
{
	stack<int> stackData;
	cout << "StackEmpty : " << stackData.empty() << endl;
	stackData.push(10);
	stackData.push(20);
	stackData.push(30);

	cout << "StackSize : " << stackData.size() << endl;
	int stackSize = stackData.size();
	cout << "PrintStack:";
	for (int i = 0; i < stackSize; i++)
	{
		cout << stackData.top() << ",";
		stackData.pop();
	}

}
//큐: 뒤에서 추가하고 앞에서 꺼냄.
//메세지큐: 이벤트가 발생한 순서대로 저장하는 공간.
//입력된 순서대로 명령어 처리하기
void QueueMain()
{
	queue<int> queueData;
	cout << "QueueEmpty : " << queueData.empty() << endl;
	queueData.push(10);
	queueData.push(20);
	queueData.push(30);

	cout << "QueueSize : " << queueData.size() << endl;
	int queueSize = queueData.size();
	cout << "PrintQueue:";
	for (int i = 0; i < queueSize; i++)
	{
		cout << queueData.front() << ",";
		queueData.pop();
	}
}
//우선순위큐: 우선순위가 높은 원소가 먼저나감(힙)
//무작위로 데이터를 넣었을때 어떤 순서대로 데이터가 나오는가? 큰값부터 나온다.
void PriorytyQueueMain()
{
	priority_queue<int> queueData;
	queueData.push(10);
	queueData.push(90);
	queueData.push(5);
	queueData.push(120);
	queueData.push(3);

	

	cout << "QueueSize : " << queueData.size() << endl;

	int queueSize = queueData.size();
	cout << "PrintQueue:";
	for (int i = 0; i < queueSize; i++)
	{
		cout << queueData.top() << ",";
		queueData.pop();
	}
}
//맵: 사전식으로 데이터를 찾을수있다.
//해당영어단어를 넣으면 한국어 결과가 나온다.
void MapMain()
{
	map<string, string> mapDic;

	mapDic["test"] = "시험";
	mapDic["pratice"] = "연습";
	mapDic["try"] = "도전";
	mapDic["note"] = "기록";

	cout << mapDic["try"] << endl;
	cout << mapDic["note"] << endl;
	cout << mapDic.find("try")->second << endl;
}
//셋: 순서없이 데이터를 넣는다. 데이터는 순서와 상관없이 데이터를 찾는다.
void SetMain()
{
	set<int> setData;

	setData.insert(10);
	setData.insert(20);
	setData.insert(30);
	setData.insert(40);

	set<int>::iterator it = setData.find(10);

	if (it != setData.end()) it;
	for (it = setData.begin(); it != setData.end(); it++)
		cout << *it << ",";
	cout << endl;
}
//해시맵: 해시테이블
void HashMapMain()
{
	unordered_map<string, string> mapDic;

	mapDic["test"] = "시험";
	mapDic["pratice"] = "연습";
	mapDic["try"] = "도전";
	mapDic["note"] = "기록";

	cout << mapDic["try"] << endl;
	cout << mapDic["note"] << endl;
	
}
void main()
{
	VectorMain();
	//ListMain();
	//DequeMain();
	//StackMain();
	//QueueMain();
	//PriorytyQueueMain();
	//MapMain();
	//SetMain();
	//HashMapMain();
}