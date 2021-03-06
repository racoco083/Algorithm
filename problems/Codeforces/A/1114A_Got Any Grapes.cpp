/*
 *  시간복잡도 : O(1)
 *
 *  (문제 설명)
 *  1,2,3 세사람, 4,5,6세 종류의 포도가 있는데 1번은 4번만 먹으며, 2번은 4,5번만
 *  먹으며 3은 모든 종류의 포도를 먹는다. 각 사람의 먹고 싶어하는 포도의 개수와
 *  각 종류의 포도의 개수가 주어진다. 모든 사람이 원하는 타입의 포도를 먹고 싶은
 *  개수만큼 먹을 수 있으면 YES를 아니면 NO를 출력하면 된다.
 *
 *  (풀이)
 *  1번 부터 차례대로 먹을 수 있는 포도를 먹으면서 해당 포도의 개수를 줄이고
 *  1번의 먹고 싶어하는 포도의 개수도 줄여나가면 된다. 먹을 수 있는 모든 종류의
 *  포도를 다 뒤졌는데 원하는 만큼 포도를 먹지 못 했으면 NO를 출력하면 된다.
 *  다른 사람도 이과정을 반복하면 된다.
 *  
 */
#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
using namespace std;

int p[3];// people
int gc[3];// grape_cnt

int main() {
	fastio();
	bool ans = true;
	for (int i = 0; i < 3; i++) cin >> p[i];
	for (int i = 0; i < 3; i++) cin >> gc[i];

	// i번째 사람이 먹을 수 있는 포도의 타입만 먹는데, i번째 사람이
	// 원하는 개수의 포도를 먹을 수 없으면 NO를 출력
	// 모든 사람이 각자 먹을 수 있는 타입만 원하는 개수의 포도를 먹으면
	// YES가 된다.
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j <= i; j++) {
			if (p[i] > gc[j]) {
				p[i] -= gc[j];
				gc[j] = 0;
			}
			else {
				gc[j] -= p[i];
				p[i] = 0;
			}
		}
		if (p[i]) {
			ans = false;
			break;
		}
	}
	if (ans) cout << "YES" << '\n';
	else cout << "NO" << '\n';
}