/*
 *  BOJ 2624. 동전바꿔주기
 *  
 *  시간복잡도 : O(TKN)
 *
 *  기존 동전가짓수 문제에 각 동전의 개수가 추가된 문제이다.
 *  이 개수에 대해서 for문을 하나 더 만들어주어 풀면된다.
 *  예를 들어 1원 짜리 동전 5개에 대해서 0, 1...5원까지의 가짓수의 경우의 수를 구하면
 *  각각 1이다. 그리고 5원 짜리 하나를 처리하면 dp[5] 값에 dp[5-5]의 값을 더해주면 된다.
 *  0원의 경우의 수에서 5원을 추가하면 5원을 만들 수 있기 때문이다.
 *  
 */
 
#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> pi;

int T, K;
pi li[101];
int dp[101][10001];

int main() {
	fastio();
	cin >> T >> K;
	for (int i = 1; i <= K; i++) {
		cin >> li[i].first >> li[i].second;
	}
	sort(li + 1, li + K + 1);

	dp[0][0] = 1;
	for (int i = 1; i <= K; i++) {
		int cnt = li[i].second;
		for (int j = 0; j <= cnt; j++) {
			for (int k = 0; k <= T; k++) {
				if (k + li[i].first * j > T) break;
				// += dp[i - 1][k] + 1로 밑의 코드를 수정해버리면 예제의 1원 동전 5개를 처리했을 때
				// dp의 1번째 행은
				// 0 1 2 3 4 5 6 7...20
				// 1 1 1 1 1 1 0 0... 0 이 되어야 하는데
				// 1 1 1 1 1 1 1 1... 1 이렇게 된다. 주의하자!
				dp[i][k + li[i].first * j] += dp[i - 1][k];
			}
		}
	}
	cout << dp[K][T] << '\n';
	return 0;
}