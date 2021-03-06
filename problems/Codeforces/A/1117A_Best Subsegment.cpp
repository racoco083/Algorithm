/*
 *  시간복잡도 : O(N)
 *
 *  (문제 설명)
 *  이어져 있는 구간의 수들의 합의 평균 중에 가장 큰 구간의 길이를 구해야 한다.
 *  이 때 평균이 같으면 길이가 더 긴것의 길이를 출력해야 한다.
 *
 *  (풀이)
 *  구간의 수들의 합의 평균 중에 가장 큰 것은 이 수들중 가장 큰 값 mxv=6 하나만 있어도
 *  평균은 6/1 = 6으로 이 값이 제일 크다. 그렇다면 같은 평균일 때 길이가 더 긴 것을 구해야 한다.
 *  6이 연속으로 여러개 붙어있는 것의 길이를 구하면 된다. 6,6이 있으면 이 구간의 평균은 역시 6이지만
 *  길이는 2로 6이 하나 있는 것 보다 더 크다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
using namespace std;
#define MXN 100002

int N;
int arr[MXN + 1];

int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	fastio();
	cin >> N;
	int cnt = 0, ans = 0, mxv = 0;
	for (int i = 0; i < N; i++) cin >> arr[i], mxv = max(mxv, arr[i]);
	for (int i = 0; i < N; i++) {
		if (arr[i] == mxv) cnt++;
		else {
			ans = max(ans, cnt);
			cnt = 0;
		}
	}
	cout << max(ans, cnt) << '\n';
	return 0;
}