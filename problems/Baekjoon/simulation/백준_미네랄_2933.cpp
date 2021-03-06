/*
 *  BOJ 2933. 미네랄 
 *
 *  시간복잡도 : O(NRC)
 *
 *  막대를 던져서 처음 부딪치는 x 하나를 부시고 그것과 인접한 x들을
 *  각각 bfs로 visited 1로 체크한다. 돌면서 해당 클러스터가 땅과 닿으면(y == 0) 
 *  무시하고 땅과 닿지 않으면(y != 0)  공중에 떠 있는 것으로
 *  이 클러스터가 각 열 중에 다른 클러스터나 땅으로 부터 가장
 *  가장 가까운 거리를 구해 그 거리만큼 공중에 떠 있는 클러스터를 다운시킨다.
 *  N개의 막대를 던지면서 이 과정을 반복하면 된다.
 *  
 */
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
#define MXN 102
typedef pair<int, int> pi;

char area[MXN + 1][MXN + 1];
int R, C, N;
bool visited[MXN + 1][MXN + 1];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

// 땅과 닿으면 true, else false;
bool bfs(int y, int x) {
	queue<pi> qu;
	qu.push({ y,x });
	// 밑의 코드를 주석쳐서 틀렸었다. 왜 주석친지는 모르겠다. 으 시뮬..
	visited[y][x] = true;
	while (!qu.empty()) {
		int cy = qu.front().first;
		int cx = qu.front().second;
		qu.pop();

		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			if (ny < 0 || ny >= R || nx < 0 || nx >= C || area[ny][nx] == '.' || visited[ny][nx]) continue;
			visited[ny][nx] = true;
			qu.push({ ny, nx });
			// 땅과 붙어 있는 클러스터로 ture 리턴
			if (ny == 0) return true;
		}
	}
	// 땅과 붙어 있지 않은 클러스터로 false 리턴
	return false;
}

int min(int a, int b) {
	return a > b ? b : a;
}

void down_cluster() {
	// 최소거리 계산
	int md = 2e9;// min_dist
	for (int i = 0; i < C; i++) {
		int dist = 0;
		for (int j = 0; j < R; j++) {
			// 각 열의 밑에서 부터 위로 가면서
			// X로 부터 공중에 떠 있는 클러스터인 1까지의 거리를 구한다.
			// 그래서 md는 if(visited[j][i])에 넣고 구해야 했는데
			// md = min(md, dist); 이 부분을 바깥으로 빼서 틀렸었다.
			if (visited[j][i]) {
				md = min(md, dist);
				break;
			}
			if (area[j][i] == '.') dist++;
			else dist = 0;
		}
	}
	// md가 1이 나와야하는데 INF가 나온다.
	// 클러스터 최소 거리만큼 이동
	for (int i = 0; i < C; i++) {
		for (int j = 0; j < R; j++) {
			if (visited[j][i]) {
				area[j][i] = '.';
				area[j - md][i] = 'x';
			}
		}
	}
}

// 0이면 동쪽, 1이면 서쪽
void cast_stick(int row, int d) {
	pi rm = { -1,-1 };//remove_mineral
	if (d == 0) {
		for (int i = 0; i < C; i++) {
			if (area[row][i] == 'x') {
				rm = { row, i };
				area[row][i] = '.';
				break;
			}
		}
	}
	else {
		for (int i = C-1; i >=0; i--) {
			if (area[row][i] == 'x') {
				rm = { row, i };
				area[row][i] = '.';
				break;
			}
		}
	}
	if (rm.first == -1) return;
	
	for (int i = 0; i < 4; i++) {
		int ny = rm.first + dy[i];
		int nx = rm.second + dx[i];
		if (ny < 0 || ny >= R || nx < 0 || nx >= C || area[ny][nx] == '.') continue;
		memset(visited, 0, sizeof(visited));
		if (!bfs(ny, nx)) {// 땅과 닿지 않는 클러스터라면
			down_cluster();
		}
		// 닿으면 그냥 넘어감
	}
}

int main() {
	fastio();
	cin >> R >> C;
	for (int i = R - 1; i >= 0; i--) {
		for (int j = 0; j < C; j++) {
			cin >> area[i][j];
		}
	}
	cin >> N;
	int row;
	// 0이면 왼쪽에서, 1은 오른쪽에서
	for (int i = 0; i < N; i++) {
		cin >> row;
		row--;
		cast_stick(row, i % 2);
	}
	//cout << row << '\n';
	for (int i = R - 1; i >= 0; i--) {
		for (int j = 0; j < C; j++) {
			cout << area[i][j];
		}
		cout << '\n';
	}
	return 0;
}



