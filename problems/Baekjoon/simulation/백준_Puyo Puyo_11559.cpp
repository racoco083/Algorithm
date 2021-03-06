/*
 *  BOJ 11559. Puyo Puyo
 *
 *  시간복잡도 : O(13*7이므로 1로 바도 될 것 같다.)
 *
 *  bfs를 돌면서 블럭을 찾아 같은 블럭이 4개 이상 인접해 있으면
 *  bfs는 개수를 리턴하여 이번턴에 터진 블럭이 있음을 알려준다. 그리고
 *  터진 블럭이므로 시작값 y,x를 벡터에 집어 넣는다. 이렇게 모든 터질 블럭
 *  다 찾아서 시작 값 벡터에 넣고 벡터를 통해 모든 블럭의 시작값에서 다시 
 *  bfs를 돌려 모두 터지게 만들어준다. 그리고 블럭을 다운시켜준다.
 *  이렇게 블럭이 터진 경우가 없을 때까지 반복해 주면 된다.
 *  
 *  vector 초기화 안 해주는 실수를 했다.
 *  문제를 똑바로 안 읽었다. 같은 시간에 다 블럭이 빨강, 노랑 다 터져도
 *  이 시간을 1로 보고 1을 출력해야 한다.
 *  
 */
#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
#include <string.h>
#include <queue>
#include <vector>
using namespace std;
typedef pair<int, int> pi;

char area[13][7];
bool visited[13][7];
vector<pi> vc;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

// true면 변화가 있다는 것이고 false면 변화가 없다는 것이다.
int bfs(int y, int x) {
	queue<pi> qu;
	qu.push({ y,x });
	int cnt = 1;
	visited[y][x] = true;
	while (!qu.empty()) {
		int cy = qu.front().first;
		int cx = qu.front().second;
		qu.pop();
		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			if (ny < 0 || ny >= 12 || nx < 0 || nx >= 6 || visited[ny][nx] || area[ny][nx] == '.' || area[y][x] != area[ny][nx]) continue;
			cnt++;
			visited[ny][nx] = true;
			qu.push({ ny, nx });
		}
	}
	return cnt;
}

void remove_alpha() {
	memset(visited, 0, sizeof(visited));
	for (int v = 0; v < vc.size(); v++) {
		int y = vc[v].first;
		int x = vc[v].second;
		queue<pi> qu;
		qu.push({ y, x });
		visited[y][x] = true;
		while (!qu.empty()) {
			int cy = qu.front().first;
			int cx = qu.front().second;
			qu.pop();
			for (int i = 0; i < 4; i++) {
				int ny = cy + dy[i];
				int nx = cx + dx[i];
				if (ny < 0 || ny >= 12 || nx < 0 || nx >= 6 || visited[ny][nx] || area[ny][nx] == '.' || area[y][x] != area[ny][nx]) continue;
				visited[ny][nx] = true;
				area[ny][nx] = '.';
				qu.push({ ny, nx });
			}
		}
		area[y][x] = '.';
	}
}

void down_alpha() {
	for (int j = 0; j < 6; j++) {
		queue<char> qu;
		for (int i = 0; i < 12; i++) {
			if (area[i][j] != '.') {
				qu.push(area[i][j]);
				area[i][j] = '.';
			}
		}
		int idx = 0;
		while (!qu.empty()) {
			area[idx++][j] = qu.front();
			qu.pop();
		}
	}

}

int main() {
	fastio();
	for (int i = 11; i >= 0; i--) {
		for (int j = 0; j < 6; j++) {
			cin >> area[i][j];
		}
	}
	int ans = 0;
	bool isCon = true;
	while (1) {
		isCon = false;
		memset(visited, 0, sizeof(visited));
		vc.clear();
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 6; j++) {
				if (visited[i][j] == false && area[i][j] != '.') {
					if (bfs(i, j) >= 4) {
						isCon = true;
						vc.push_back({ i, j });
					}
				}
			}
		}
		if (!isCon) break;
		ans++;
		// 지워준다.
		remove_alpha();
		// 내려준다.
		down_alpha();
	}
	cout << ans << '\n';
	return 0;
}