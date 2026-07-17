#include <stdio.h>

// 데이터의 값을 전위연산자와 후위연산자를 이해하기위해 프로그램을 작성하여라

// 전위연산자 : 값이 먼저 증가하고 대입(복사)된다.
// 후위연산자 : 값을 먼저 대입(복사)하고 증가시킨다.
// 전위 연산으로 변수의 값을 저장하고, 후위연산을해서 값을 각 변후(2개가 필요)에 대입하여 연산결과가 어떻게 달라지는지 관찰하고,
// 코드에 보이지않는 순서를 찾아내어 이해한다.
// 데이터(변수) : nDataA, nDataB
// 알고리즘 : nDataA에 값을 넣고 후위연산하여 nDataB에 대입하고, nDataA의 값을 전위연산하고, nDataB에 대입한고, nDataA와 nDataB를 출력한다
// 변수의 값이 변경되고나면 모든 변수의 값을 출력하여, 결과를 확인한다.
void OperatortestMain() 
{
	int nDataA = 1;
	int nDataB = 0;

	nDataB = nDataA++;
	printf("nDataA = %d\n", nDataA);
	printf("nDataB = %d\n", nDataB);

	nDataB = --nDataA;
	printf("nDataA = %d\n", nDataA);
	printf("nDataB = %d\n", nDataB);
}

// 문제 : 정수와 실수의 데이터를 선언하고, 선언된 데이터를 각 실수와 정수의 포인터에 저장하여 모든 변수들에서 연산할 수 있는 모든 결과를 출력하라
// 데이터 : 정수형 변수, 실수형 변수, 정수 포인터, 실수 포인터 
// 포인터 : 변수의 주소값을 저장하는 변수. 예) int* pData = &nData;
// 변수에 할 수 있는 연산 : & - 변수의 주소값을 가져오는 연산자, *: 포이터가 가르키는 변수 값을 가져오는 연산자
// 알고리즘: nData에 값을 넣고, nData의 주소값을 pData에 넣는다
// nData, pData에서 할수있는 연산을 모두 출력하라.
void PointerTestMain()
{
	int nData = 10;
	int* pData = &nData;

	printf("nData[%d, %p]\n", nData, &nData);
	printf("nData[%p, %d]\n", pData, *pData);
}

void PointerTestMain2()
{
	int nData2 = 10;
	int* pData2 = &nData2;

	printf("nData2의 값 = %d, 주소값 = %p\n", nData2, &nData2);
	printf("pData2의 값 = %p, 주소값 = %d\n", pData2, &pData2);
}

int main() 
{
	//OperatortestMain();
	PointerTestMain();
	PointerTestMain2();
	return 0;
}