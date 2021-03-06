/*
 *  BOJ 3985. 롤 케이크
 *
 *  시간복잡도 : O(N*L)
 *
 *  각 사람이 가져갈케익이 있으면 가져가게 하고 없으면 못 가져가게 하여
 *  각 사람이 챙긴 케익의 개수를 세면서 답을 구하면 된다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
using namespace std;
#define MXN 1002

int L, N;
int cake[MXN + 1];// i번째 케익이 있는지 없는지를 나타낸다.

int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	fastio();
	cin >> L >> N;
	int fi, si;
	int fans = 0, sans = 0;
	int a, b;
	for (int i = 1; i <= N; i++) {
		cin >> a >> b;
		int cnt = 0;// 현재 사람이 가져간 케익의 개수를 나타낸다.
		// 가장 많은 조각을 받을 것으로 기대하고 있던 방청객의 번호 처리
		if (b - a > fans) {
			fi = i;
			fans = b - a;
		}
		// 실제로 가장 많은 조각을 받은 방청객의 번호 처리 두 번째 답 처리
		for (int j = a; j <= b; j++) {
			if (cake[j] == 0) {
				cnt++;
				cake[j] = 1;
			}
		}
		if (sans < cnt) {
			sans = cnt;
			si = i;
		}
	}
	cout << fi << '\n' << si << '\n';
	return 0;
}
