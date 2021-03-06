/*
 *  BOJ 3197. 백조의 호수
 *
 *  시간복잡도 : O(RClog(3000))
 *
 *  물과 인접한 빙하의 위치를 모두 구한다. 이분 탐색을 통해 mid를 구하고
 *  구한 인접한 빙하위치에서 너비탐색을 mid번 만큼 하면서 빙하인 곳만
 *  물로 바꾸어준다. 그리고 S백에서 bfs를 하여 E백조에 도달하는지 본다.
 *  된다면 mid값을 낮추어 다시 돌린다. 이 과정을 이분탐색이 종료될 때까지
 *  하며 S백조가 E백조를 만난 것 중에 mid값이 제일 작은 것이 답이다.
 *  
 *  처음에 두 백조사이의 빙하의 최소 개수/2가 답인 줄 알았는데
 *  밑과 같은 반례가 있다.
 *  .XX..XX.
 *  LXX..XXL
 *  .XX..XX.
 *  .XX..XX.
 *  이런 경우 처음 풀이는 2를 리턴하지만 답은 1이다.
 *  물과 만나는 빙하는 첫 날에 다 녹기 때문이다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <queue>
#include <string.h>
using namespace std;
#define MXN 1501
typedef pair<int, int> pi;

int R, C;
char oarea[MXN + 1][MXN + 1];// original_area
char area[MXN + 1][MXN + 1];
bool visited[MXN + 1][MXN + 1];
bool ovfb[MXN + 1][MXN + 1];// original_visited_for_break_ice
bool vfb[MXN + 1][MXN + 1];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
queue<pi> oqu;// original_queue
pi S, E;

// S백조와 E백조가 만나면 true, 아니면 false
bool bfs() {
	queue<pi> qu;
	qu.push(S);
	visited[S.first][S.second] = true;
	while (!qu.empty()) {
		int cy = qu.front().first;
		int cx = qu.front().second;
		qu.pop();

		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			if (ny < 0 || ny >= R || nx < 0 || nx >= C || area[ny][nx] == 'X' || visited[ny][nx]) continue;
			if (ny == E.first && nx == E.second) return true;
			qu.push({ ny, nx });
			visited[ny][nx] = true;
		}
	}
	return false;
}

// oqu에 저장된 물과인접한 빙하에서부터 시작해 m번 만큼 깨진다. 
bool break_ice(int m){
	queue<pi> qu = oqu;
	memcpy(vfb, ovfb, sizeof(vfb));
	memcpy(area, oarea, sizeof(area));
	int day = 0;// 날짜를 센다.
	while (!qu.empty()) {
		if (day >= m) break;
		int size = qu.size();
		for (int i = 0; i < size; i++) {
			int cy = qu.front().first;
			int cx = qu.front().second;
			qu.pop();

			area[cy][cx] = '.';
			for (int i = 0; i < 4; i++) {
				int ny = cy + dy[i];
				int nx = cx + dx[i];
				if (ny < 0 || ny >= R || nx < 0 || nx >= C || area[ny][nx] == '.' || vfb[ny][nx]) continue;
				qu.push({ ny, nx });
				vfb[ny][nx] = true;
			}
		}
		day++;
	}
	memset(visited, 0, sizeof(visited));
	return bfs();
}

// 시작 빙하로 부터 너비로 m번 빙하까지 깰 때 m값을 구해 break_ice실행
int bs(int s, int e) {
	int ans;
	while (s <= e) {
		int m = (e + s) / 2;
		if (break_ice(m)) {
			e = m - 1;
			ans = m;
		}
		else s = m + 1;
	}
	return ans;
}

// 물과 인접한 빙항의 위치를 oqu에 담는다.
void find_wnti() {// water_next_to_ice
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (oarea[i][j] == 'X') {
				for (int k = 0; k < 4; k++) {
					int ny = i + dy[k];
					int nx = j + dx[k];
					if (ny < 0 || ny >= R || nx < 0 || nx >= C) continue;
					if (oarea[ny][nx] == '.') {
						oqu.push({ i,j });
						ovfb[i][j] = true;
						break;
					}
				}
			}
		}
	}
}

int main() {
	fastio();
	cin >> R >> C;
	S = { 0,0 };
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> oarea[i][j];
			if (oarea[i][j] == 'L' && S.first == 0) S = { i,j };
			else if (oarea[i][j] == 'L') E = { i,j };
			if (oarea[i][j] == 'L') oarea[i][j] = '.';
		}
	}
	find_wnti();
	cout << bs(0, 3001) << '\n';
	return 0;
}