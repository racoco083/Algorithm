/*
 *  시간복잡도 : O(100N)
 *
 *  (문제 설명)
 *  N개의 입력으로 각 기계들의 파워가 주어진다. 어떤 기계의 파워를 x로 나누면
 *  다른 기계의 파워를 x로 곱할 수 있다. (x로 나눈 나머지는 0이어야 한다.)
 *  딱 두 기계를 선택해 파워를 줄이고 줄인 기계말고 선택된 다른 기계는 
 *  파워를 올린다. 기계를 선택하지 않아도 된다. 
 *  이 때 기계 전체 파워의 최소값을 구한다.
 *
 *  (풀이)
 *  기계의 파워가 담긴 배열 arr을 정렬한다.
 *  1<j<arr[i]라고 하고 j를 arr[i]-1부터 시작해 2가 될때까지 1씩 줄여나가면
 *  i번째 기계의 파워가 j로 나누어 떨어지는지 본다. 만약 나누어 떨어진다면
 *  가장 파워가 작은 arr[0]에는 j를 곱하고 arr[i]에는 j를 나눈 모든 기계 파워의
 *  합을 구해서 ans와 비교해 더 작은 값을 ans에 갱신한다.
 *  
 */
#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
#include <algorithm>
using namespace std;
#define MXN 50005

int arr[MXN + 1];
int N;

int min(int a, int b) {
	return a > b ? b : a;
}

int main() {
	fastio();
	cin >> N;
	int sum = 0;
	for (int i = 0; i < N; i++) cin >> arr[i], sum += arr[i];
	sort(arr, arr + N);
	int ans = sum;
	for (int i = 1; i < N; i++) {
		for (int j = arr[i] - 1; j > 1; j--) {
			if (arr[i] % j) continue;
			ans = min(ans, sum - arr[0] - arr[i] + arr[0] * j + arr[i] / j);
		}
	}
	cout << ans << '\n';
	return 0;
}