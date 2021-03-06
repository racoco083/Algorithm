// cache[i][j] : 왼쪽 덱의 카드가 i개 버려졌고, 오른쪽 덱의 카드가 j개 버려졌을 때의 최대 점수
// 오른쪽 덱의 카드만 버릴 때, 두 덱의 카드 모두 버릴 때, 왼쪽의 카드만 모두 버릴때에 대한
// 모든 경우를 다 봐주었고 시간을 줄이기 위해 cache를 사용한 메모이제이션 기법을 사용했다. 

#include <iostream>
#include <string.h>
using namespace std;
#define MXN 2001

int N;
int ld[MXN];// left_deck
int rd[MXN];// right_deck
int cache[MXN][MXN];

int max(int a, int b) {
	return a > b ? a : b;
}

int dfs(int li, int ri) {//left_index, right_index
	if (li >= N || ri >= N) return 0;
	int &ret = cache[li][ri];
	if (ret != -1) return ret;
	ret = 0;

	if (ld[li] > rd[ri]) ret = max(ret, dfs(li, ri + 1) + rd[ri]);
	ret = max(ret, max(dfs(li + 1, ri), dfs(li + 1, ri + 1)));
	return ret;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> ld[i];
	for (int i = 0; i < N; i++) cin >> rd[i];
	memset(cache, -1, sizeof(cache));

	cout << dfs(0, 0) << '\n';

	return 0;
}
