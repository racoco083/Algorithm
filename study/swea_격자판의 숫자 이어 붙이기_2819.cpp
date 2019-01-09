#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <string>
#include <set>
using namespace std;

char area[4][4];
set<string> ss;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

// string을 사용하여 다음 값의 숫자를 붙여준다.
// dfs로 depth가 7보다 클때까지 깊이 탐색을 하며 
// 7보다 크면 s값을 set에 집어 넣는다. 
// set의 size가 곧 답이다.
void dfs(int y, int x, int d, string s) {// depth, set
	if (d >= 7) {
		ss.insert(s);
		return;
	}

	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || ny >= 4 || nx < 0 || nx >= 4) continue;
		dfs(ny, nx, d + 1, s + area[ny][nx]);
	}
}

int main() {
	fastio();
	int TC;
	cin >> TC;
	for (int T = 1; T <= TC; T++) {
		ss.clear();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cin >> area[i][j];
			}
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				dfs(i, j, 0, "");
			}
		}
		cout << '#' << T << ' ' << ss.size() << '\n';
	}
	return 0;
}