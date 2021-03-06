/*
 *  범위 s, e를 투포인터로하여 dfs에 이 범위를 넣고  
 *  모든 점을 방문하여 K의 개수가 kcnt와 같아지면 
 *  그 때의 범위의 길이를 ans값과 비교해 더 작은 값을
 *  ans에 담으면 된다. 만약 dfs를 한 값이 kcnt와 같다면
 *  s를 올려서 범위를 줄일 수 있다. 아니면 e를 증가시켜
 *  범위를 늘려 모든 K를 방문할 수 있도록 한다.
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

class Pos {
public:
	int y, x;
	Pos() {}
	Pos(int _y, int _x) : y(_y), x(_x) {}
};

int N;
char area[55][55];// area
int het[55][55];// height
int ran[2600];// range
bool visited[55][55];
int dy[8] = { -1, 0, 0, 1, -1, -1, 1, 1 };
int dx[8] = { 0, -1, 1, 0, -1, 1, -1, 1 };
Pos start;// 출발점 P를 나타낸다.
int kcnt;// 배달해야하는 곳 K의 개수를 센다.
int ri;// range_index

int min(int a, int b) {
	return a > b ? b : a;
}

// ran[s]~ran[e]까지를 범위로 잡아 출발점 y,x로 부터 시작하여 범위 안에
// 드는 모든 정점을 방문하면서 K의 개수를 총 세아린 K의 개수를 리턴한다.
int dfs(int y, int x, int s, int e) {
	// 범위에 들지 않으면 부모 노드가 0을 받는다. => 단말노드가 된다.
	if (het[y][x] < ran[s] || ran[e] < het[y][x]) return 0;

	int ret = 0;
	if (area[y][x] == 'K') ret++;
	// ran범위 안에 들었다면 한 번만 방문하면 된다.
	// 범위 안에 방문가능한 점을 모조리 찾는 것이기 때문에
	// return ret전에 visited[y][x] = flase; 안 해줘도 된다.
	visited[y][x] = true;

	for (int i = 0; i < 8; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || ny >= N || nx < 0 || nx >= N || visited[ny][nx]) continue;
		ret += dfs(ny, nx, s, e);
	}
	// 루트는 방문한 K의 개수를 리턴한다.
	return ret;
}

int main() {
	fastio();
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> area[i][j];
			if (area[i][j] == 'P') {
				start = Pos(i, j);
			}

			if (area[i][j] == 'K') {
				kcnt++;
			}
		}
	}

	// het을 1차원 식으로 저장한 배열이 ran이다.
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> het[i][j];
			ran[ri++] = het[i][j];
		}
	}
	sort(ran, ran + ri);
	int ruc = 1;//range_unique_cnt
	// 정렬을 통해 똑같은 값은 지워버리면서 다른 값을 앞으로 땡겨준다.
	// 유니크한 값만 오름차순 정렬된 상태로 남게된다.
	for (int i = 1; i < ri; i++) {
		if (ran[i - 1] != ran[i]) ran[ruc++] = ran[i];
	}
	int ans = 2e9;
	int s = 0, e = 0;
	// 파라메트릭 서치로서 범위를 설정하면서 모든 가능한 범위값을
	// 다 체크하면서 그 범위값의 길이가 가장 짧은 것의 값을 ans에
	// 담는다. e와 s가 최대 2500까지 갈수 있고 dfs도 50*50으로 2500되므로
	// 시간복잡도는 2500*2500이라고 보면 된다.
	// e가 ruc와 같거나 커지면 할 수 있는 범위를 벗어났으므로 끝내면 된다.
	while (e < ruc) {
		memset(visited, 0, sizeof(visited));

		if (dfs(start.y, start.x, s, e) == kcnt) {
			ans = min(ans, ran[e] - ran[s]);
			s++;
		}
		else e++;
	}
	cout << ans << '\n';
	return 0;
}
