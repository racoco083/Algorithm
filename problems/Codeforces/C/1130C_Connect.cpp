/*
 *  시간복잡도 : O(N^4)
 *
 *  (문제 설명)
 *  시작좌표와 도착좌표가 주어지고, 1과 0으로 이루어진 N*N공간이 주어진다.
 *  0은 땅이고, 1은 물이다. 땅은 움직일 수 있지만 물위에서는 움직일 수 없다.
 *  물과 땅위에 터널을 만들어 움직일 수 있는데 터널은 하나만 만들 수 있으며 
 *  시작점에서 도착지점까지 갈 때의 시작 터널과 도착 터널의 좌표차이
 *  solve = (r1 - r2)^2 + (c1 - c2)^2의 값이 최소가 되는 값을 구해라.
 *
 *  (풀이)
 *  시작 지점을 시작으로 bfs나 dfs로 인접한 땅인 공간 전부 다 벡터 f에 넣고
 *  도착 지점을 시작으로 bfs나 dfs로 인접한 땅인 공간 전부 다 벡터 s에 넣고
 *  f,s에 대해 2차원 for문을 돌려 solve의 값이 가장 작은 값을 구한다.
 *  
 */
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <vector>
using namespace std;
#define MXN 52
typedef pair<int, int> pi;

char area[MXN + 1][MXN + 1];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
int N;
bool visited[MXN + 1][MXN + 1];
pi S, D;
vector<pi> f, s;

void dfs(int y, int x, vector<pi>& t) {
	visited[y][x] = true;
	t.push_back({y,x});
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 1 || ny > N || nx < 1 || nx > N || area[ny][nx] == '1' || visited[ny][nx]) continue;
		// 밑의 코드에서 t대신 f 넣어 틀렸었다.
		dfs(ny, nx, t);
	}
}

int min(int a, int b) {
	return a > b ? b : a;
}

int main() {
	cin >> N;
	cin >> S.first >> S.second;
	cin >> D.first >> D.second;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> area[i][j];
		}
	}
	dfs(S.first, S.second, f);
	dfs(D.first, D.second, s);

	int ans = 2e9;
	for (int i = 0; i < f.size(); i++) {
		for (int j = 0; j < s.size(); j++) {
			ans = min(ans, (f[i].first - s[j].first) * (f[i].first - s[j].first) + (f[i].second - s[j].second) * (f[i].second - s[j].second));
		}
	}
	cout << ans << '\n';
	return 0;
}
