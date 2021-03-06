/*
 *  BOJ 11658. 구간 합 구하기3
 *
 *  시간복잡도 : O(M*logN*logN)
 *
 *  https://www.acmicpc.net/blog/view/21 일 차원 펜윈에 대한 설명으로
 *  참조하면 이해가 잘 된다.
 *  
 *  한 행의 모든 열에 대해 펜윅을 적용하고 반복하여 모든 행에
 *  적용하여 2D 펜윅을 만들면 된다.
 *
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;
int tree[1030][1030];
int N, M;

// (i&-i)는 i의 맨 오른쪽 1비트의 위치를 알아낼 수 있다.
// 예를 들어 i = 101000 이면 이것의 1의 보수는 010111이다.
// 이 값을 2의 보수로 만들어 주면 011000이다. 
// 101000 & 011000을 하면 001000이다.

// 펜윅으로 v값을 포함해야 하는 모든 행, 열 비트에 v값을 누적한다.
void update(int x, int y, int v) {
	for (int i = x; i <= N; i += (i&-i)) {
		for (int j = y; j <= N; j += (j&-j)) {
			tree[i][j] += v;
		}
	}
}

// 펜윅으로 (0,0)에서 (x,y)까지의 숫자의 합을 구한다.
int sum(int x, int y) {
	int ret = 0;
	for (int i = x; i > 0; i -= (i&-i)) {
		for (int j = y; j > 0; j -= (j&-j)) {
			ret += tree[i][j];
		}
	}
	return ret;
}

// (a,b)에서 (c,d)까지의 숫자의 합을 구한다.
int getArea(int a, int b, int c, int d) {
	return sum(c, d) - sum(c, b - 1) - sum(a - 1, d) + sum(a - 1, b - 1);
}

void print() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << tree[i][j] << ' ';
		}
		cout << '\n';
	}
}

int main() {
	fastio();
	cin >> N >> M;
	int v;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> v;
			update(i, j, v);
		}
	}

	int q, a, b, c, d;
	for (int i = 0; i < M; i++) {
		cin >> q;
		if (q) {
			cin >> a >> b >> c >> d;
			cout << getArea(a, b, c, d) << '\n';
		}
		else {
			cin >> a >> b >> c;
			// tree는 펜윅으로 된 누적합 값을 저장한다. 
			// getArea(a, b, a, b);로 (a, b)의 숫자 값 t를 구한다.
			// c-t로 차이를 넘겨 (a,b)를 포함함는 모든 비트에 diff를 누적한다.
			int diff = c - getArea(a, b, a, b);
			update(a, b, diff);
		}
	}
	return 0;
}

