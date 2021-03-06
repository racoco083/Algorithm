/*
*   BOJ 2004. 조합 0의 개수
*
*	시간 복잡도 : O(logN)
*   공간 복잡도 : O(1)
*
*   끝에 0의 개수는 곧 그 값의 5와 2의 개수 중 더 작은 것의 개수입니다.
*	nCm = n!/m!(n-m)! 에서 각 팩토리얼의 5와 2의 개수를 세어
*	n!의 2와 5의 개수에 m!과 (n-m)!의 2와 5의 개수를 빼주어
*   구하려는 조합의 0의 개수를 구했습니다.
*/

#include <iostream>
using namespace std;
typedef long long ll;
int N, M;
int ca[3][2];

void fzc(int n, int f) { //find_zero_count
	// i의 값이 int범위를 넘어갈 수 있다.
	// 1부터 N까지 수 중에 i를 약수로 가지고 있는 수의 개수를 구한다.
	for (ll i = 2; i <= n; i *= 2) ca[f][0] += (n / i);
	for (ll i = 5; i <= n; i *= 5) ca[f][1] += (n / i);
}

int main() {
	cin >> N >> M;
	fzc(N, 0);
	fzc(N - M, 1);
	fzc(M, 2);
	// nCm의 2의 개수와 5의 개수를 구한다.
	int tc = ca[0][0] - ca[1][0] - ca[2][0];
	int fc = ca[0][1] - ca[1][1] - ca[2][1];
	if (tc < fc) cout << tc << '\n';
	else cout << fc << '\n';
	return 0;
}

// reference
https://ksj14.tistory.com/entry/BackJoon1676-%ED%8C%A9%ED%86%A0%EB%A6%AC%EC%96%BC-0%EC%9D%98-%EA%B0%9C%EC%88%98
