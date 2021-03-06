/*
 *  시간복잡도 : O(N)
 *
 *  (문제 설명)
 *  책은 여러 챕터로 이루어져 있고, 각 챕터의 시작 페이지와 끝 페이지가
 *  주어지고, 마지막으로 특정 페이지가 주어진다. 이 페이지가 속한 챕터를
 *  말하면 된다.
 *
 *  (풀이)
 *  코드만 봐도 쉽게 풀 수 있다.
 *  
 */

#include <iostream>
using namespace std;
#define MXN 102

int arr[MXN + 1];
int N;

int main() {
	cin >> N;
	int a, b, k;
	for (int i = 0; i < N; i++) {
		cin >> a >> b;
		arr[i] = b;
	}
	cin >> k;
	int ans = 0;
	for (int i =0; i < N; i++) {
		if (k <= arr[i]) {
			ans = N - i;
			break;
		}
	}
	cout << ans << '\n';
	return 0;
}









































