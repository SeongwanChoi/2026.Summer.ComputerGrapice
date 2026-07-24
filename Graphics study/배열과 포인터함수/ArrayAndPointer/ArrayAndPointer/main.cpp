#include <stdio.h>
#include <memory.h>

// 문제 : 배열의 크기를 상수 변수로 지정, 배열의 크기와 메모리 크기를 계산하여 저장하고,
//		배열을 생성 후 각 변수의 값을 초기화 후, 배열의 이름 및 각 원소에 주소값을 순서대로 출력한다.

// 배열의 이름에 인덱스를 더하는 포인터연산을 이용하여 각 원소의 주소값과 인덱스, 데이터를 출력한다.
// 배열의 이름을 포인터변수에 저장하고, 포인터연산을 배열의 크기만큼 수행하여, 각 포인터의 참조와 주소값을 출력한다.
// 새로운 같은 크기의 배열을 만들고, 새로운배열에 기존배열을 복사한다.

// 데이터 : 배열의 크기를 저장하는 상수, 배열의 메모리 크기, 배열크기, 복사배열
// 알고리즘 : 1. 배열의 크기를 상수를 지정하고, 배열 생성
// 2. 배열의 크기를 구하는 함수를 이용하여 계산
// 3. 배열에 반복문을 이용하여 원소 초기화
// 4. 배열을 출력하며 배열의 이름, 배열의 원소, 주소값과 인덱스, 데이터값을 출력한다.
// 5. 배열의 시작원소에 포인터연산을 하고, 각 결과의 주소값과 인덱스, 데이터값을 출력한다.
// 6. 배열이름값을 포인터에 저장하고, 포인터가 참조하는 값과 포인터가 가진 주소를 출력하고 배열의 크기만큼 반복한다.
// 7. 같은 크기의 새로운 배열을 만들고, 만들어진 배열에 값을 복사하여 출력한다.
// const(상수) : 변경할 수 없는 값
// 배열 : 연속으로 변수를 할당하여 주소값을 통해 바로 인덱스로 접근 가능하도록 할당된다.
// 포인터 연산 : 포인터의 값을 증가시키는 연산. 변수의 크기만큼 주소값이 증가한다. +n을하면 변수의크기 * n개가 된다.


// 배열 복사하기 (직접복사, memcpy활용)
// 컴파일 : 코드를 빌드해서 실행 가능한 형태로 만드는것.
// 정적 : 프로그램이 컴파일되어 변경될 수 없는 상태
// 런타임(동적) : 컴파일을 통해 만들어진 프로그램이 실행됨.
// memcpy : 정적으로 메모리가 할당된 배열을 대상으로 같은 크기만큼의 메모리를 할당하여 배열을 만들고 각 index의 값을 복사하여 할당한다.
void ArrayAndPointer()
{
	const int size = 3;
	int arr[size];
	for (int i = 0; i < size; i++)
		arr[i] = 100 - (i * 10);
	printf("arr : ");
	for (size_t i = 0; i < size; i++)
		printf("[%d / %p] %d, ", i, &arr[i], arr[i]);
	printf("\n");
	int* parr = arr;
	printf("parr + i : ");
	for (size_t i = 0; i < size; i++)
		printf("[%d / %p] %d, ", i, parr + i, *(parr + i));
	printf("\n");
	printf("pData++ : ");
	for (size_t i = 0; i < size; i++)
	{
		printf("[%d / %p] %d, ", i, parr, *parr);
		parr++;
	}
	printf("\n\n");
	int arrCopy[size];
	/*printf("arrCopy : ");
	for (size_t i = 0; i < size; i++)
		printf("[%d / %p] %d, ", i, &arrCopy[i], arrCopy[i]);
	printf("\n");*/

	int nArrMemorySize = sizeof(arr);
	printf("%d",nArrMemorySize);
	memcpy(arrCopy, arr, nArrMemorySize);
	printf("arrCopy : ");
	for (size_t i = 0; i < size; i++)
		printf("[%d / %p] %d, ", i, &arrCopy[i], arrCopy[i]);
	printf("\n");
}

int main()
{
	ArrayAndPointer();
	return 0;
}