/*
 *  BOJ 1347. 미로 만들기
 *
 *  시간복잡도 : O(N^2)
 *
 *  R과 L이면 회전하고, F가 앞으로 가면서 방문한 area에 '.'을 넣어준다.
 *  그리고 area에서 '.'이 곳 중에 가장 왼쪽, 오른쪽, 밑쪽, 위쪽의 인덱스를 
 *  다 구해 그 범위만 출력하면 된다.
 *  
 */
#include <iostream>
using namespace std;
#define MXN 120
typedef pair<int, int> pi;

int N;
char str[MXN + 1];
char area[MXN + 1][MXN + 1];
int dy[4] = { -1, 0,1, 0 };
int dx[4] = { 0, 1, 0, -1 };
const int INF = 2e9;

int min(int a, int b) {
	return a > b ? b : a;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	cin >> N >> str;
	int d = 2;
	int y = 55, x = 55;
	area[y][x] = '.';
	for (int i = 0; i < N; i++) {
		if (str[i] == 'R') d = (d + 1) % 4;
		else if (str[i] == 'L') d = (d + 3) % 4;
		else {
			int ny = y + dy[d];
			int nx = x + dx[d];
			area[ny][nx] = '.';
			y = ny, x = nx;
		}
	}

	int l, r, t, b;
	l = r = t = b = 55;
	for (int i = 0; i < MXN; i++) {
		for (int j = 0; j < MXN; j++) {
			if (area[i][j] != '.') continue;
			l = min(l, j);
			r = max(r, j);
			t = min(t, i);
			b = max(b, i);
		}
	}

	for (int i = t; i <= b; i++) {
		for (int j = l; j <= r; j++) {
			if (area[i][j] == 0) cout << '#';
			else cout << area[i][j];
		}
		cout << '\n';
	}
	return 0;
}