#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <string>
#include <set>
using namespace std;

char area[4][4];
set<string> ss;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

// string�� ����Ͽ� ���� ���� ���ڸ� �ٿ��ش�.
// dfs�� depth�� 7���� Ŭ������ ���� Ž���� �ϸ� 
// 7���� ũ�� s���� set�� ���� �ִ´�. 
// set�� size�� �� ���̴�.
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