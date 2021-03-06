/*
 *  BOJ 9328. 열쇠
 *
 *  시간복잡도 : O(H*W)
 *
 *  상근이는 빌딩의 밖에서 부터 시작해서 방문할 수 있는 공간은 다 방문하는데
 *  문을 만나 열쇠가 있으면 들어가고 없으면 이 문의 종류(A~Z)와 위치를
 *  저장해둔다. 나중에 이 문을 열 수 있는 열쇠를 주웠을 때 이 위치에서
 *  다시 퍼져나가게 하기 위해서다. 열쇠(a~z)를 주울 때는 해당 열쇠로 열 수 있는
 *  문의 위치를 저장해둔 door벡터를 통해 해당 문들을 모두 qu에 담아준다.
 *  초기화를 조심해야 하는 문제다!
 *  
 */
#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
#include <string.h>
#include <string>
#include <queue>
using namespace std;
#define MXN 102
typedef pair<int, int> pi;

int H, W;
char area[MXN + 1][MXN + 1];
bool visited[MXN + 1][MXN + 1];
vector<pi> door[26];
bool key[26];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int bfs() {
	queue<pi> qu;
	qu.push({ 0,0 });
	int ret = 0;
	visited[0][0] = true;
	while (!qu.empty()) {
		int cy = qu.front().first;
		int cx = qu.front().second;
		qu.pop();
		
		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			if (ny<0 || ny>H + 1 || nx<0 || nx>W + 1 || area[ny][nx] == '*' || visited[ny][nx]) continue;
			visited[ny][nx] = true;
			if (area[ny][nx] == '$') ret++;
			else if ('a' <= area[ny][nx] && area[ny][nx] <= 'z') {
				int idx = area[ny][nx] - 'a';
				key[idx] = true;
				for (int j = 0; j < door[idx].size(); j++) {
					qu.push(door[idx][j]);
				}
				door[idx].clear();
			}
			else if ('A' <= area[ny][nx] && area[ny][nx] <= 'Z') {
				int idx = area[ny][nx] - 'A';
				if (key[idx] == 0) {
					door[idx].push_back({ ny,nx });
					continue;
				}
			}
			qu.push({ ny, nx });
		}
	}
	return ret;
}

int main() {
	fastio();
	int TC;
	string s;
	cin >> TC;
	while (TC--) {
		memset(area, 0, sizeof(area));
		memset(visited, 0, sizeof(visited));
		memset(key, 0, sizeof(key));
		for (int i = 0; i < 26; i++) door[i].clear();
		cin >> H >> W;
		for (int i = 1; i <= H; i++) 
			for (int j = 1; j <= W; j++) 
				cin >> area[i][j];
		cin >> s;
		for (int i = 0; i < s.size(); i++) {
			if (s[0] == '0') break;
			key[s[i] - 'a'] = true;
		}
		cout << bfs() << '\n';
	}
	return 0;
}
