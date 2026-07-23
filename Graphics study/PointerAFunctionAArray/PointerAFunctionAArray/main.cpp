#include <stdio.h>

// 데이터의 값을 전위연산자와 후위연산자를 이해하기위해 프로그램을 작성하여라

// 전방 선언, 함수의 선언
void OperatortestMain();
void PointerTestMain();
void PointerTestMain2();
void Pointer();
void Swap1(int numA, int numB);
void Swap2(int* pnumA, int* pnumB);
void Swap3(int& numA, int& numB);

int main() 
{
	int numA = 10;
	int numB = 20;
	printf("Origin[%p]%d <-> [%p]%d\n", &numA, numA, &numB, numB);

	// 함수의 호출
	Swap1(numA, numB);
	printf("Swap1[%p]%d <-> [%p]%d\n", &numA, numA, &numB, numB);

	Swap2(&numA, &numB);
	printf("Swap2[%p]%d <-> [%p]%d\n", &numA, numA, &numB, numB);

	Swap3(numA, numB);
	printf("Swap3[%p]%d <-> [%p]%d\n", &numA, numA, &numB, numB);
	return 0;
}

// 함수의 정의

// 전위연산자 : 값이 먼저 증가하고 대입(복사)된다.
// 후위연산자 : 값을 먼저 대입(복사)하고 증가시킨다.
// 전위 연산으로 변수의 값을 저장하고, 후위연산을해서 값을 각 변후(2개가 필요)에 대입하여 연산결과가 어떻게 달라지는지 관찰하고,
// 코드에 보이지않는 순서를 찾아내어 이해한다.
// 데이터(변수) : nDataA, nDataB
// 식별자 : 무언가를 구분하기위해 지은 이름
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
	float fData = 3.14f;

	int* pData = &nData;
	float* pfData = &fData;

	printf("nData[%d, %p]\n", nData, &nData);
	printf("nData[%p, %d]\n", pData, *pData);

	printf("fData[%f, %p]\n", fData, &fData);
	printf("pfData[%p, %f]\n", pfData, *pfData);
}

void PointerTestMain2()
{
	int nData2 = 10;
	int* pData2 = &nData2;

	printf("nData2 = %d, &nData2= %p\n", nData2, &nData2);
	printf("pData2 = %p, *pData2 = %d\n", pData2, *pData2);
}

// 문제 : 정수와 실수의 데이터를 선언하고, 선언된 데이터를 각 실수와 정수의 포인터에 저장하여 모든 변수들에서 연산할 수 있는 모든 결과를 출력하라
// 데이터 : nData3, fData, *nData3, *fData
void Pointer()
{
	int		nData3 = 10;
	float	fData = 3.14f;

	int* pData3 = &nData3;
	float* pfData = &fData;

	printf("nData3 = %d, &nData = %d\n", nData3, &nData3);
	printf("pData3 = %d, *pData3 = %d\n", pData3, *pData3);
	printf("fData = %f, &fData = %f\n", fData, &fData);
	printf("pfData = %f, *pfData = %f\n", pfData, *pfData);
}

// 문제 : 데이터 2개를 저장하고 저장된 데이터를 각각 값/포인터/참조를 이용하여 함수를, 이용하여 두 값을 교환해보고 변수의 값과 주소 값을 출력한다.
// 1. 값에 의한 호출함수
// 2. 포인터에 의한 호출함수
// 3. 참조에 의한 호출함수
// 데이터 : numA, numB
// 알고리즘 : 1. 문제에 필요한각 함수를 작성한다
// 2. 변수를 2개 선언하고, 각 변수에 타입에 적절한 데이터를 저장하고, 주소값과 변수값을 출력한다
// 3. 값에 의한 호출함수에 각 변수를 매개변수로 넣고 각 변수의 데이터와 주소값을 출력한다.

void Swap1(int numA, int numB)
{
	int swap = numA;
	numA = numB;
	numB = swap;
}

void Swap2(int* pnumA, int* pnumB)
{
	int swap = *pnumA;
	*pnumA = *pnumB;
	*pnumB = swap;
}

void Swap3(int& numA, int& numB)
{
	int swap = numA;
	numA = numB;
	numB = swap;
}
