/*
 *  시간복잡도 : O(N)
 *
 *  (문제 설명)
 *  두 줄의 수가 있을 때 연속적이지 않게 고른 수의 합의 최대
 *  값을 구하는 문제이다.
 *
 *  (풀이)
 *  dp를 사용하여서 이번 턴 첫번째 값 + 이전 턴의 두 번째 세번째 값 중 큰값
 *  두 번째 턴, 세 번째 턴도 마찬가지로 이전의 자신의 턴을 제외한 값 중
 *  큰 값을 더해나가면서 마지막에 가장 큰 값을 출력하면 된다.
 *  
 */

#include<iostream>

using namespace std;
typedef long long ll;
#define MXN 100001

ll dp[3][MXN + 1];
int N;

ll max(ll a, ll b) {
	return a > b ? a : b;
}

void solve() {
	for (int i = 1; i < N; i++) {
		dp[0][i] += max(dp[1][i - 1], dp[2][i - 1]);
		dp[1][i] += max(dp[0][i - 1], dp[2][i - 1]);
		dp[2][i] += max(dp[0][i - 1], dp[1][i - 1]);
	}
}

void print() {
	cout << '\n';
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < N; j++) {
			cout << dp[i][j] << ' ';
		}
		cout << '\n';
	}
}

int main() {
	cin >> N;
	
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < N; j++) {
			cin >> dp[i][j];
		}
	}
	solve();
	cout << max(dp[0][N-1], max(dp[1][N-1], dp[2][N-1])) << '\n';
	return 0;
}

/*
5
9 3 5 7 3
5 8 1 4 5
*/ //답은 29다