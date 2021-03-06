/*
 *  BOJ 8983. 사냥꾼
 *
 *  시간복잡도 : O(NlogM)
 *
 *  각 사대를 뒤지면서 동물이 범위에 속하는지 찾는 것은 logN만에 불가능한다.
 *  동물의 x, y값은 다 다르거나 같을 수 있기 때문이다. 하지만 사대의 y값은
 *  0으로 고정이다. 그러면 사대를 정렬해서 이분탐색을 할 수 있다. 그러면
 *  각 동물을 뒤지면서 가장가까운 사대를 logM에 찾을 수 있다.
 *  
 */
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <algorithm>
using namespace std;
#define MXN 100002
typedef pair<int, int> pi;

int M, N, L;
int sade[MXN + 1];
pi ani[MXN + 1];
const int INF = 2e9;

int abs(int a) {
	return a < 0 ? -a : a;
}

// 현재 동물의 x값 v와 좌표 x에 대해서만 가장가까운 사대와의 차이를 리턴한다.
int bs(int s, int e, int v) {
	int diff = INF;
	while (s <= e) {
		int m = (e + s) / 2;
		if (abs(v - sade[m]) < diff) diff = abs(v - sade[m]);
		if (sade[m]>v) e = m - 1;
		else s = m + 1;
	}
	return diff;
}

int main() {
	fastio();
	cin >> M >> N >> L;
	for (int i = 0; i < M; i++) cin >> sade[i];
	for (int i = 0; i < N; i++) cin >> ani[i].first >> ani[i].second;
	
	sort(sade, sade + M);

	int cnt = 0;// 사대에 포함되는 총 동물의 수를 나타낸다.
	for (int i = 0; i < N; i++) {
		// 동물이 L보다 높이 있으면 어떤 사대 범위에도 들어가지 않으므로 continue
		if (ani[i].second > L) continue;
		// 현 동물의 y값이 L에서 bs를 뺀 값보다 작으면 범위에 속하므로 카운트
		if (ani[i].second <= (L - bs(0, M - 1, ani[i].first))) cnt++;
	}
	cout << cnt << '\n';
	return 0;
}