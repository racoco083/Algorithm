/*
 *  시간복잡도 : O(1)
 *
 *  (문제 설명)
 *  항상 두 사각형은 위아래로 인접하며 왼쪽으로 붙어있다.
 *  이 때 이 두 사각형 주위로 상하좌우, 대각선 거리1에 초록색 빛이 덮인다.
 *  사각형이 있는 공간을 제외한 이 초록색 빛만 있는 곳의 개수를 세아린다.
 * 
 *  (풀이)
 *  각 사각형의 초록색 범위를 구하기 위해 각 사각형의 (높이+2)*(너비+2)를
 *  통해 구해서 두 사각형의 초록색 범위를 더하고 이 때 각 사각형의 범위를 빼고
 *  서로 겹치는 각 사각형의 너비 범위를 빼고 두 사각형의 너비차이를 한 번 더하면 된다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include<iostream>
using namespace std;
typedef long long ll;

int aba(int a) {
	return a < 0 ? -a : a;
}

int main() {
	fastio();
	ll w1, h1, w2, h2;
	cin >> w1 >> h1 >> w2 >> h2;
	ll ans = -(w1 * h1 + w2 * h2);
	w1 += 2, h1 += 2, w2 += 2, h2 += 2;
	ans += (w1 * h1 + w2 * h2) - w1 - w2 + abs(w1 - w2);
	cout << ans << '\n';
	return 0;
}
