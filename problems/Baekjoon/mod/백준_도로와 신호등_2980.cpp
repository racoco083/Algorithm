/*
 *  BOJ 2980. 도로와 신호등
 *
 *  시간복잡도 : O(N)
 *
 *  각 신호등까지 가면서 각 신호등은 빨간색, 초록색 차레대로 r, g시간 유지하니
 *  상근이가 해당 신호등에 도착했을 때 (상근이가 여기까지 오는데 걸린시간)%(r+g) = rest
 *  가 r보다 크거가 같으면 초록색 불이라는 것이니 기다리지 않아도 되고, 그 반대는
 *  빨간 불이니 r-rest 시간 동안 기다려야 한다. 
 *
 */
#include <iostream>
using namespace std;
#define MXN 102

int N, L;

int main() {
	cin >> N >> L;
	int d, r, g;
	int tt = 0;// total_time
	int cp = 0;// cur_pos
	for (int i = 0; i < N; i++) {
		cin >> d >> r >> g;
		tt += (d - cp);
		cp = d;
		int rest = tt % (r + g);
		if (rest < r) tt += (r - rest);
	}
	tt += (L - cp);
	cout << tt << '\n';
	return 0;
}
