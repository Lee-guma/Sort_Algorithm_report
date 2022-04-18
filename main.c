#define _CTR_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // malloc(), rand()
#include "sort.h"
#include <time.h>

int main() {
	int size, num;
	clock_t start1, end1, start2, end2, start3, end3, start4, end4, start5, end5;
	float res1, res2, res3, res4, res5;

	printf("배열 사이즈 : ");
	scanf_s("%d", &size);

	int* arr1 = (int*)malloc(sizeof(int) * size);
	if (arr1 == NULL) return -1;
	for (int k = 0; k < size; k++) {
		num = (rand() % size) + 1;
		arr1[k] = num;
	}

	
	int* arr2 = (int*)malloc(sizeof(int) * size);
	if (arr2 == NULL) return -1;
	for (int k = 0; k < size; k++) {
		num = (rand() % size) + 1;
		arr2[k] = num;
	}

	int* arr3 = (int*)malloc(sizeof(int) * size);
	if (arr3 == NULL) return -1;
	for (int k = 0; k < size; k++) {
		num = (rand() % size) + 1;
		arr3[k] = num;
	}

	int* arr4 = (int*)malloc(sizeof(int) * size);
	if (arr4 == NULL) return -1;
	for (int k = 0; k < size; k++) {
		num = (rand() % size) + 1;
		arr4[k] = num;
	}

	int* arr5 = (int*)malloc(sizeof(int) * size);
	if (arr5 == NULL) return -1;
	for (int k = 0; k < size; k++) {
		num = (rand() % size) + 1;
		arr5[k] = num;
	}
	

	/*
	printf("<정렬 전>\n");
	for (int k = 0; k < size; k++)
		printf("%d ", arr[k]);
	printf("\n\n");
	*/

	start1 = clock();
	exchangeSort(arr1, size);
	end1 = clock();
	res1 = (float)(end1 - start1) / CLOCKS_PER_SEC;
	
	start2 = clock();
	mergeSort(arr2, 0, size - 1);
	end2 = clock();
	res2 = (float)(end2 - start2) / CLOCKS_PER_SEC;
	
	start3 = clock();
	quickSort(arr3, 0, size - 1);
	end3 = clock();
	res3 = (float)(end3 - start3) / CLOCKS_PER_SEC;
	
	start4 = clock();
	radixSort(arr4, size);
	end4 = clock();
	res4 = (float)(end4 - start4) / CLOCKS_PER_SEC;

	/*
	printf("    <정렬 후>\n");
	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);
	*/
	
	
	// 힙 정렬 부분
	heapType heap;
	heap.size = 0;

	start5 = clock();
	for (int k = 0; k < size; k++)	// 배열 크기를 length로 할껄 그랬다 
		insertHeap(&heap, arr5[k]);

	// printHeap(&heap); 
	// printf("<Heap sort>\n");
	for (int k = 0; k < size; k++) {
		// printf("%d ", getHeap(&heap));
		getHeap(&heap);
	}
	end5 = clock();
	res5 = (float)(end5 - start5) / CLOCKS_PER_SEC;


	printf("<<<소요 시간>>>\n");
	printf("Exchange Sort : %.3f \n", res1);
	printf("Merge Sort : %.3f \n", res2);
	printf("Quick Sort : %.3f \n", res3);
	printf("Radix Sort : %.3f \n", res4);
	printf("Heap Sort : %.3f \n", res5);


	free(arr1);
	free(arr2);
	free(arr3);
	free(arr4);
	free(arr5);
	

	return 0;
}
