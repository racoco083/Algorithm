/*
 *  BOJ 16986. 인싸들의 가위바위보
 *
 *  시간복잡도 : O(N! * K)
 *
 *  지우의 모든 손동작 1~N값을 넥퍼뮤한다. 0,1,2번 중에 경기를 해야하는 사람
 *  두 명 구해서 경기를 시키고 이긴 사람은 나두고 진사람은 빼고 다른 사람을 넣고
 *  누군가 K승을 할 때 까지 또는 지우가 모든 손동작을 다 쓸 때 까지 경기를 계속 진행한다.
 *
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <algorithm>
using namespace std;
#define MXN 10

int area[MXN + 1][MXN + 1];
int N, K;
int hands[3][21];

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int main() {
	fastio();
	cin >> N >> K;
	// 인덱스 실수 하였다. i = 0; i < N;로 하여서 0부터 값을 채워넣었다.
	// 하지만 손동작은 1부터 N까지다 이걸 인덱스로 했으니 틀렸었다.
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> area[i][j];
		}
	}

	for (int i = 1; i < 3; i++) {
		for (int j = 0; j < 20; j++) {
			cin >> hands[i][j];
		}
	}

	for (int i = 0; i < N; i++) hands[0][i] = i + 1;

	do {
		int f = 0, s = 1;
		int ho[3] = { 0, }; // hand_order
		int wc[3] = { 0, }; // win_count

		while (1) {
			if (area[hands[f][ho[f]++]][hands[s][ho[s]++]] == 2) {// f가 이긴다.
				wc[f]++;
				s = 3 - (f + s);
			}
			else {// 비기거나 s가 이긴다.
				wc[s]++;
				f = 3 - (f + s);
			}

			// 진행순서가 항상 s가 뒤가 되도록 만들어 준다.
			if (f > s) swap(f, s);

			if (wc[0] == K) {
				cout << 1;
				return 0;
			}
			else if (ho[0] == N || wc[1] == K || wc[2] == K) break;
		}
	} while (next_permutation(hands[0], hands[0] + N));
	cout << 0;
	return 0;
}