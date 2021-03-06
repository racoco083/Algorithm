/*
 *  BOJ 16986. 인싸들의 가위바위보
 *
 *  시간복잡도 : O(N!)
 *
 *  처음 문제 이해를 잘 못해서 헤맸다.
 *  지우는 손 동작을 모두 다르게 하여 이긴다는 것은 N개의 손동작만 
 *  사용한다는 것이 었다. 경희, 민호의 20개의 손 동작이 들어오면
 *  이건 큐이다. 앞에것을 사용해야 뒤에 것을 사용할 수 있는 것이었다.
 *  그리고 나중에 경기에 참여한 사람이 이긴 사람과 경기를 할 때 비기면
 *  나중에 경기에 참여한 사람이 이기는 것이 아니고 지우<경희<민호가
 *  무조건 이기게 되는 것이다.
 *
 *  지우의 손 동작은 N개만 사용가능하므로 지우의 손 동작 배열에 1,2..N을
 *  집어 넣어서 next_permutation한다. 매 순열마다 경기를 해서 
 *  지우가 이기는 경우가 있는지 찾아낸다.
 *  
 */
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <algorithm>
using namespace std;
#define MXN 10
int p[3][21];// pattern
int mat[MXN + 1][MXN + 1];
int N, K;
void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}
bool can_win() {
	int ho[3] = { 0, };// hand_order
	int wc[3] = { 0, };// win_count

	int p1 = 0, p2 = 1;// player1, 2
	while (1) {
		// 진행 순서는 0,1,2로 시작하므로 2가 0,1과 비기면 이기고,
		// 1이 0과 비기면 이긴다.
		// 3 - p1 - p2; 이렇게 하면 현재 3명의 player 중에
		// p1, p2가 아닌 사람의 번호가 나온다.
		if (p1 > p2) swap(p1, p2);
		int p1h = p[p1][ho[p1]++];// player1 hand
		int p2h = p[p2][ho[p2]++];// player2 hand
		if (mat[p1h][p2h] == 2) {
			wc[p1]++;
			p2 = 3 - p1 - p2;
		}
		else {
			wc[p2]++;
			p1 = 3 - p1 - p2;
		}
		if (wc[0] == K) return true;
		else if (ho[0] >= N || wc[1] == K || wc[2] == K) return false;
	}
	return false;
}
int main() {
	fastio();
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> mat[i][j];
		}
	}
	for (int i = 0; i < N; i++) p[0][i] = i + 1;
	for (int i = 0; i < 20; i++) cin >> p[1][i];
	for (int i = 0; i < 20; i++) cin >> p[2][i];
	bool ans = false;

	do {
		if (can_win()) {
			ans = true;
			break;
		}
	} while (next_permutation(p[0], p[0] + N));
	cout << ans << '\n';
	return 0;
}