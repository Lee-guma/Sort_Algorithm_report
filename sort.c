#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

void exchangeSort(int *arr, int size) {
	// i : 바꿀 자리 인덱스
	// j : i와 비교할 인덱스

	// printf("<Exchange Sort>");
	int i, j, tmp;

	for (i = 0; i < size - 1; i++) {
		for (j = i + 1; j < size; j++) {
			if (arr[i] > arr[j]) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

void merge(int* arr, int low, int mid, int high) {
	int sorted[MAX_SIZE]; // 병합정렬에 사용할 임시 리스트 
	int i = low;	// 비교할 때 사용할 왼쪽 배열의 인덱스
	int j = mid + 1;	// 비교할 때 사용할 오른쪽 배열의 인덱스
	int k = 0;	// sorted 배열 인덱스. 정렬된 값 넣을 때 사용
	int l;

	// 한쪽에 남은 요소가 없을 때까지
	while (i <= mid && j<= high) {	// i가 mid까지 갔을 때까진 비교해야 함
		if (arr[i] <= arr[j]) {
			sorted[k] = arr[i];
			k++;
			i++;
		}
		else {
			sorted[k] = arr[j];
			j++;
			k++;
		}
	}
	// while 문을 나오면 어느 한쪽은 빈 배열이 된다

	while (i <= mid) { // 왼쪽 배열에 값이 남아 있다면
		sorted[k] = arr[i];
		k++;
		i++;
	}

	while (j <= high) {	// 오른쪽 배열에 값이 남아 있다면
		sorted[k] = arr[j];
		j++;
		k++;
	}
	// 다 끝나면 k도 빈곳을 가리키고 있음
	// 배열이 빈 공간이 있다면 괜찮지만 딱 맞는 크기였다면 위험
	k--;

	// 임시로 만들어준 정렬된 배열의 값을 arr에 옮겨주자
	while (k >= 0) {
		arr[low + k] = sorted[k]; // 재귀함수로 돌다보니 항상 마지막 병합은 아님 그래서 low + k
		k--;
	}
}

void mergeSort(int *arr, int low, int high) {
	int mid;

	if (low < high) {
		mid = (low + high) / 2;
		mergeSort(arr, low, mid);
		mergeSort(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}

	else
		return;
}


int partition(int* arr, int left, int right) {
	int pivot = arr[right]; // 피봇을 오른쪽 끝에 두고 사용할 것
	int i;	// 피봇보다 작은 수의 개수를 나타내주는 역할
	int index = left;

	int tmp;

	for (i = left; i < right; i++) {
		if (arr[i] <= pivot) {
			tmp = arr[i];
			arr[i] = arr[index];
			arr[index] = tmp;
			index++;
		}
	}
	tmp = arr[index];
	arr[index] = arr[right];
	arr[right] = tmp;

	// 끝났을 때 i가 여기까지가 피벗보다 작은 애들이다 하는 역할

	// 적어도 이 인덱스(피벗의 위치) 왼쪽이 인덱스(피벗) 값보다 작다는걸 보여준다
	// -> 이 인덱스 값은 이 위치에서 움직일 필요가 없다
	// partition() 함수 한번 돌 때 마다 한개의 요소의 위치 확정
	return index;
}

void quickSort(int* arr, int left, int right) {
	if (left < right) {
		int p = partition(arr, left, right);

		quickSort(arr, left, p - 1);
		quickSort(arr, p + 1, right);
	}
	else
		return;
}

void insertHeap(heapType* h, int item) {
	int index; // 현재 노드

	// 삽입이 되는 상태인지 예외처리
	if (h->size >= (MAX_SIZE - 1)) {
		printf("heap is Full\n");
		return;
	}

	// 어느 자리에 원소를 삽입하는가?
	// h->data[h->size]에는 데이터가 들어있음. (size + 1)에 넣는다

	h->size++; // size는 배열에 들어있는 유효원소수와 같으니까 삽입 시 증가필요
	index = h->size;
	h->data[index] = item; // 여기까지가 완전 이진트리 형태를 유지하며 아이템 삽입하는 것
	
	// 이제 부모 자식을 비교하면서 큰 값을 위로 올려줘야 함
	/* 
		멈추는 조건
		1. 루트노드까지 갔을 때 : index = 1
		2. 부모 노드 값이 더 클때
	*/

	while ((index != 1) && (h->data[index] > h->data[index / 2])) {
		int tmp = h->data[index / 2];
		h->data[index / 2] = h->data[index];
		h->data[index] = tmp;

		index = index / 2; // 교환했으니까 부모노드로 올라가서 작업 계속
	}
}

int getHeap(heapType* h) {
	int topdata = h->data[1];
	int index, child; // index : 끝에서 루트로 끌고온 값의 인덱스, child : 비교할 자식 노드
	int tmp;

	// 예외처리 : 힙에 값이 없을 때
	if (h->size == 0) {
		printf("Heap is Empty\n");
		return -1;
	}

	h->data[1] = h->data[h->size]; // 마지막 노드를 루트로 끌고 옴
	h->size--;

	index = 1; // 루트로 끌고 왔으니까 루트 값

	while ((index*2) <= h->size) { // 왼쪽 자식이 있는 동안 반복
		child = index * 2; // 일단 왼쪽 자식 노드를 비교할 자식 노드에 대입

		// 오른쪽 자식이 있고 그 값이 왼쪽 자식보다 크다면 
		if ((child + 1) <= h->size && (h->data[child] < h->data[child+1])) 	
			child++; // 비교할 자식 노드를 오른쪽 자식 노드로

		if (h->data[child] <= h->data[index]) // 자식중에 큰 값보다 내가 크면
			break;

		tmp = h->data[child];
		h->data[child] = h->data[index];
		h->data[index] = tmp;

		index = child; // 내려가면서 계속 반복
	}

	return topdata;
}

void printHeap(heapType* h) {
	int i;
	printf("Heap : ");
	for (i = 1; i <= h->size; i++)
		printf("%d ", h->data[i]);
	printf("\n\n");
}

int getMax(int* arr, int size) {
	int max = arr[0];
	for (int i = 1; i < size; i++) {	// 1인덱스부터 비교
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}

void countingSort(int* arr,int size, int place) {
	int tmp[MAX_SIZE]; // 정렬된 값 넣을 함수
	int count[10];

	for (int i = 0; i < 10; i++)
		count[i] = 0;

	for (int i = 0; i < size; i++) 
		count[(arr[i] / place) % 10]++;
	
	for (int i = 1; i < 10; i++)	// 누적 합
		count[i] += count[i - 1];

	for (int i = size - 1; i >= 0; i--) {
		tmp[count[((arr[i] / place) % 10)] - 1] = arr[i];
		count[(arr[i] / place) % 10]--;
	}

	for (int i = 0; i < size; i++)
		arr[i] = tmp[i];
}

void radixSort(int* arr, int size) {
	int max = getMax(arr, size);

	for (int place = 1; max / place > 0; place *= 10)
		countingSort(arr, size, place);
}
