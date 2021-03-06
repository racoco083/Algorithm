/*
 *  BOJ 1592. 영식이와 친구들
 *
 *  시간복잡도 : O(TKN)
 *
 *  문제 설명대로 각 사람의 공의 받은 횟수를 카운트 하면서 이 횟수가
 *  홀수이면 시계방향의 L번째 사람에게 던지고, 짝수이면 반시계 방향의
 *  L번째 사람에게 던지는 것을 반복하면서 공을 M번 받게 되는 사람이
 *  존재하게 되면 그 때의 받은 횟수를 출력하면 된다.
 *  
 */
#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
#include <algorithm>
using namespace std;
#define MXN 1002

int N, M, L;
int rc[MXN + 1]; // receive_cnt

int main() {
	fastio();
	cin >> N >> M >> L;
	int c = 0;
	int ans = 0;
	while (1) {
		rc[c]++;
		if (rc[c] == M) break;
		ans++;
		if (rc[c] % 2 == 0) c = (c + N - L) % N;
		else c = (c + L) % N;
	}
	cout << ans << '\n';
	return 0;
}