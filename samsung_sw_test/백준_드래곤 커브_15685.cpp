/*
 *  BOJ 15685. 드래곤 커브
 *
 *  시간복잡도 : O(x * y * g)
 *
 *  현재 세대에서 다음 세대는 정확히 * 2의 방향개수가 생기며 현재 방향이
 *  vector dir에 저장되어 있다고 한다면 현재 dir의 사이즈 = sz 만큰 맨 끝에 
 *  들어온 방향부터 꺼내주면서 이 방향에 반시계 방향의 값을 dir에 넣어주는 것을
 *  sz만큼 반복해 주면 된다. 그리고 또 다음세대로 갈 때 현재의 dir의 사이즈를
 *  sz에 갱신시키고 마지막 세대까지 반복하면 된다.
 *  이렇게 모든 방향을 담아서 시작점부터 area영역에 그린다.
 *  모든 드래곤 커브를 그리고 드래곤 커브가 지나간 정점을 가지고 있는
 *  정사각형의 개수를 구해 리턴하면 된다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#pragma warning(disable:4996)
#include <iostream>
#include <vector>
using namespace std;
#define MXN 100

int N;
bool area[MXN + 1][MXN + 1];
// 문제 설명에 나온 방향대로 처리하지 않고, 내가 맨날 하는대로 방향 만들어 틀렸다.
int dy[4] = { 0, -1, 0, 1 };
int dx[4] = { 1, 0, -1, 0 };

int main() {
	fastio();
	cin >> N;
	int x, y, d, g;
	for (int i = 0; i < N; i++) {
		vector<int> dir;
		cin >> x >> y >> d >> g;
		dir.push_back(d);
		while (g--) {
			int size = dir.size();
			for (int j = size - 1; j >= 0; j--) {
				dir.push_back((dir[j] + 1) % 4);
			}
		}
		area[y][x] = true;
		for (int i = 0; i < dir.size(); i++) {
			int ny = y + dy[dir[i]];
			int nx = x + dx[dir[i]];
			area[ny][nx] = true;
			y = ny;
			x = nx;
		}
	}
	int ans = 0;
	for (int i = 1; i <= MXN; i++) {
		for (int j = 1; j <= MXN; j++) {
			if (area[i - 1][j] && area[i - 1][j - 1] && area[i][j - 1] && area[i][j]) ans++;
		}
	}
	cout << ans << '\n';
	return 0;
}