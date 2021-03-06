/*
 *  시간복잡도 : O(N)
 *
 *  (문제 설명)
 *  N개의 숫자가 주어지는데 이건 circle을 만든다. 인접한 숫자끼리의 차이가
 *  최소가 되도록 순서를 재배열하여 N개의 숫자 출력하면 된다.
 *
 *  (풀이)
 *  2 1 1 3 2 라는 숫자가 있으면
 *  이걸 정렬해서 1 1 2 2 3이 되도록 한 다음
 *  인덱스 0부터 인덱스를 2씩 증가시켜 1 2 3이 출력되도록 하고
 *  인덱스 3에서 부터 인덱스를 2씩 감소시켜 2 1이 출력 되도록 하면
 *  1 2 3 2 1이 최종적으로 출력 되는것을 볼 수 있다.
 *  그리디 한 방법인데 이게 최적이다. 차이는 1이고 인덱스 0과 4의 차이는 0 이다.
 *  
 */

#include <iostream>
#include <algorithm>
using namespace std;
#define MXN 102

int N;
int arr[MXN + 1];

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> arr[i];
	sort(arr, arr + N);
	for (int i = 0; i < N; i += 2) cout << arr[i] << ' ';
	for (int i = N - 1 - (N % 2); i >= 0; i -= 2) cout << arr[i] << ' ';
	return 0;
}