/* 
 *  BOJ 5566. 주사위 게임 
 *
 *  시간복잡도 : O(N)
 *  
 *  문제 설명대로 구현하면 되는 문제이다.
 *  
 */
 
#include <iostream>
using namespace std;
#define MXN 1002

int N, M;
int cmd[MXN + 1];

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) cin >> cmd[i];
	int dice;
	int ans = 0;
	int cp = 1;// current_position
	for (int i = 0; i < M; i++) {
		cin >> dice;
		cp += dice;
		if (cp >= N) { ans = i + 1; break; }
		if (cmd[cp] != 0) {
			cp += cmd[cp];
		}
		if (cp >= N) { ans = i + 1; break; }
	}
	cout << ans << '\n';
	return 0;
}