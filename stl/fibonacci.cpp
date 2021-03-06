#include <iostream>
#include <string.h>
using namespace std;
#define MXN 30

// for문으로 dp적용
int dp[MXN + 1];

int main() {
	int N;
	cin >> N;
	dp[0] = 0;
	dp[1] = 1;

	for (int i = 2; i < N; i++) dp[i] = dp[i - 1] + dp[i - 2];
	for (int i = 0; i < N; i++) cout << dp[i] << ' ';
	
	return 0;
}

// 재귀에 dp적용
int cache[MXN + 1];

int fibo(int n) {
	int &ret = cache[n];
	if (cache[n] != -1) return ret;

	if (n == 0) return ret = 0;
	if (n == 1) return ret = 1;

	return ret = fibo(n - 1) + fibo(n - 2);
}

int main() {
	int N;
	cin >> N;
	memset(cache, -1, sizeof(cache));
	fibo(N);
	for (int i = 0; i < N; i++) cout << cache[i] << ' ';
	return 0;
}