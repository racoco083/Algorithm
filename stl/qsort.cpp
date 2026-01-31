#include <stdio.h>

int arr[100001]; // 예시 배열

// 스왑 함수 (값을 바꾸는 역할)
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 퀵 정렬 메인 함수
// left: 정렬 시작 인덱스, right: 정렬 끝 인덱스
void my_qsort(int data[], int left, int right) {
    int i = left;
    int j = right;
    int pivot = data[(left + right) / 2]; // 가운데를 피벗으로 잡음

    // 1. 피벗을 기준으로 왼쪽엔 작은 값, 오른쪽엔 큰 값으로 나눔
    while (i <= j) {
        while (data[i] < pivot) i++; // 피벗보다 큰 값 찾을 때까지 오른쪽으로
        while (data[j] > pivot) j--; // 피벗보다 작은 값 찾을 때까지 왼쪽으로

        if (i <= j) {
            swap(&data[i], &data[j]); // 서로 엇갈리지 않았으면 교환
            i++;
            j--;
        }
    }

    // 2. 나뉜 두 그룹에 대해 재귀 호출
    if (left < j) my_qsort(data, left, j);   // 왼쪽 덩어리 정렬
    if (i < right) my_qsort(data, i, right); // 오른쪽 덩어리 정렬
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) scanf("%d", &arr[i]);

    // 사용법: 배열, 시작인덱스(0), 끝인덱스(N-1)
    my_qsort(arr, 0, N - 1);

    for (int i = 0; i < N; i++) printf("%d ", arr[i]);
    
    return 0;
}
