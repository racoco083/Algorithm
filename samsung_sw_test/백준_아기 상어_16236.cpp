/*
 *  BOJ 16236. 아기 상어
 *
 *  시간복잡도 : O(N^4)
 *  먹이 찾는데 bfs통해 N^2 먹이가 먹이의 최대 수 N^2
 *
 *  bfs를 통해 아기 상어가 먹을 수 있는 가장 거리가 짧은 먹이를 찾고 
 *  그 먹이를 먹고 그 먹이의 위치를 초기값으로 해서 다시 bfs를 돌려
 *  계속 먹이를 찾고 bfs 돌리고를 반복한다. 이때 같은 거리에 있는 먹이가
 *  여러 마리라면 y,x값에 대해 정렬을 해서 가장 위쪽에 있으면서,
 *  가장 왼쪽에 있는 먹이를 먹는다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <algorithm>
#include <queue>
#include <string.h>
#include <vector>
using namespace std;
#define MXN 20
typedef pair<int, int> pi;

int N;
int area[MXN + 1][MXN + 1];
bool visited[MXN + 1][MXN + 1];
pi bp; // baby_position
int bs; // baby_size
int ec; // eat_count
int ttime;
vector<pi> die;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

bool cmp(const pi& a, const pi& b) {
	if (a.first == b.first) {
		return a.second < b.second;
	}
	return a.first < b.first;
}

// 잡아 먹었다면 true 아니면 false를 리턴한다
bool bfs() {
	queue<pi> qu;
	qu.push({ bp.first, bp.second });
	visited[bp.first][bp.second] = true;
	while (!qu.empty()) {
		int qs = qu.size();
		ttime++;
		for (int i = 0; i < qs; i++) {
			int cy = qu.front().first;
			int cx = qu.front().second;
			qu.pop();

			for (int j = 0; j < 4; j++) {
				int ny = cy + dy[j];
				int nx = cx + dx[j];
				if (ny < 0 || ny >= N || nx < 0 || nx >= N || visited[ny][nx] || area[ny][nx] > bs) continue;
				visited[ny][nx] = true;
				// || !area[ny][nx] 이 부분을 빼먹는 실수를 하였다.
				if (bs == area[ny][nx] || !area[ny][nx]) qu.push({ ny, nx });
				else if (bs > area[ny][nx]) die.push_back({ ny, nx });
			}
		}
		if (!die.empty()) return true;
	}
	return false;
}

int main() {
	fastio();
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> area[i][j];
			if (area[i][j] == 9) {
				area[i][j] = 0;
				bp = { i,j };
			}
		}
	}
	bs = 2;
	ec = 0;
	int ans = 0;
	while (1) {
		ttime = 0;
		die.clear();
		memset(visited, 0, sizeof(visited));
		if (!bfs()) break;
		// 잡아먹은 위치에서 다시 bfs를 하자
		sort(die.begin(), die.end(), cmp);
		bp = die[0];
		area[bp.first][bp.second] = 0;
		ans += ttime;
		ec++;
		if (ec == bs) {
			bs++;
			ec = 0;
		}
	}
	cout << ans << '\n';
	return 0;
}