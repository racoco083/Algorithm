/*
 *  NHN 4. 점령지 확장
 *
 *  시간복잡도 : O(turn * N^2)
 *
 *  일단 나라와 장애물을 area, obs 두 개의 다른 2차원 배열에 담았다.
 *  area를 브루트 탐색하며 '0'인 곳의 4방향을 다 뒤져서 인접한 영토의 개수가
 *  가장 많은 나라를 현재의 위치를 점령하도록 하였다. 이 때 장애물을 파악해서
 *  현재위치 y,x, 그리고 인접한 위치 ny, nx에도 장애물이 있는지 없는지 봐야 한다.
 *  그리고 영토가 확장되었으면 계속 위과정을 반복하고 한 턴 동안 확장된 영토가
 *  없으면 다음 턴에도 없으므로 종료하면 된다.
 *
 */
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
#define MXN 11

int N;
char area[MXN + 1][MXN + 1];
int obs[MXN + 1][MXN + 1];
char _next[MXN + 1][MXN + 1];
int alpha[26];
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

void printA() {
	cout << '\n';
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << area[i][j] << ' ';
		}
		cout << '\n';
	}
}

void printB() {
	cout << '\n';
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << obs[i][j] << ' ';
		}
		cout << '\n';
	}
}

bool put_alpha(int y, int x) {
	int check[4] = { 0, };
	int idx[4] = { 0, };
	for (int i = 0; i < 26; i++) {
		check[alpha[i]]++;
		idx[alpha[i]] = i;
	}
	for (int i = 3; i >= 1; i--) {
		if (check[i] == 1) {
			_next[y][x] = idx[i] + 'A';
			return true;
		}
	}
	return false;
}

bool calc_area(int y, int x) {
	memset(alpha, 0, sizeof(alpha));
	for (int i = 0; i < 4; i++) {
		if (obs[y][x] & (1 << i)) continue;
		int ny = y + dy[i];
		int nx = x + dx[i];
		int nd = (i % 2 == 0) ? i + 1 : i - 1;
		if (ny < 0 || ny >= N || nx < 0 || nx >= N || area[ny][nx] == '0') continue;
		// (obs[ny][nx] & nd) 해서 틀렸다. 위에는 잘 해놓고 밑에서 틀리네..
		if (obs[ny][nx] & (1<<nd)) continue;
		alpha[area[ny][nx] - 'A']++;
	}
	return put_alpha(y, x);
}

bool calc() {
	bool ret = false;
	memcpy(_next, area, sizeof(area));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (area[i][j] == '0') {
				// 여기 실수 했다. ret = calc_area(i,j)로 해서 틀렸다.
				// ret는 계속 값을 받는데 한 번이라도 true를 받으면 그 값을
				// 저장해 놓아야 한다. 그런데 true를 받고도 false가 넘어오면 ret는
				// false 갱신되도록 해서 틀렸다.
				int tmp = calc_area(i, j);
				if (!ret) ret = tmp;
			}
		}
	}
	memcpy(area, _next, sizeof(area));
	return ret;
}

int main() {
	fastio();
	cin >> N;
	string a;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> a;
			if (a.size() == 1) {
				if ('A' <= a[0] && a[0] <= 'Z') {
					area[i][j] = a[0];
				}
				else {
					area[i][j] = '0';
					obs[i][j] = a[0] - '0';
				}
			}
			else if (a.size() == 2) {
				area[i][j] = '0';
				obs[i][j] = stoi(a);
			}
		}
	}
	while (calc());
	printA();
	
	return 0;
}

/*
보기 입력 1
5
A 0 0 0 0
0 0 6 0 D
0 0 B 0 0
0 C 8 0 0
0 0 0 0 0
출력 1
3
A A A D D
A A D D D
0 0 B B D
C C C B D
C C C 0 D
*/