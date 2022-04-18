#pragma once
#define MAX_SIZE 10002  // 메인 함수에서 입력받은 size로 바꿔줄 것

void exchangeSort(int *arr, int size);

void merge(int* arr, int low, int mid, int high);
void mergeSort(int* arr, int low, int high);

int partition(int* arr, int left, int right);
void quickSort(int* arr, int left, int right);

typedef struct {
	int data[MAX_SIZE];	// 힙은 완전 이진트리이기 때문에 배열로 구현해도 된다.
	int size;	// 유효원소 수 : MAX_SIZE - 1 : 배열의 0인덱스는 미사용
} heapType;

void insertHeap(heapType* h, int item); // 원소 추가 후 MaxHeap 형태로
int getHeap(heapType* h); // 루트 노드를 반납하고 다시 MaxHeap 형태로
void printHeap(heapType* h);

int getMax(int* arr, int size); // 배열에서 가장 큰 값을 찾아주는 함수
void countingSort(int* arr, int size, int place); // 라딕스 정렬 시 필요
void radixSort(int* arr, int size);

