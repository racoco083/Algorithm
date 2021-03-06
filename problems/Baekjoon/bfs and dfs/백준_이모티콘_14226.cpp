/*
 *  BOJ 14226. 이모티콘
 *  
 *  시간복잡도 : O(N^2)
 *
 *  문제 설명대로 풀면 되는데 이 문제에서 중요한 것은 visited 2차원 배열을
 *  이용해서 한 개의 인덱스는 현재 화면의 이모티콘의 개수를 나머지 인덱스는
 *  클립보드에 저장된 이모티콘의 개수를 나타낸다. 화면 이모티콘 하나만 인덱스로 한
 *  1차원 visited배열을 사용할 수 있지 않겠냐고 생각할 수 있지만 그렇게 하면
 *  안된다. 왜냐하면 정점의 값이 같더라도 클립보드에 어떤 내용이 들어있는지에 
 *  따라 향후 탐색할 수 있는 정점이 달라지기 때문이다. 인덱스 100인곳에 나중에 
 *  방문한 얘가 먼저 이모티콘의 개수가 S인 위치에 방문할 수 있기 때문이다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <queue>
using namespace std;
#define MXN 1000
typedef pair<int, int> pi;

int visited[MXN + 1][MXN + 1];
int S;
const int INF = 2e9;

int min(int a, int b) {
	return a > b ? b : a;
}

int bfs(int ec, int cc) { // emoticon_cnt, clipboard_cnt
	queue<pi> qu;
	qu.push({ ec,cc });
	visited[ec][cc] = 1;
	while (!qu.empty()) {
		int ec = qu.front().first;
		int cc = qu.front().second;
		qu.pop();

		if (ec == S) return visited[ec][cc] - 1;

		for (int i = 0; i < 3; i++) {
			if (i == 0 && !visited[ec][ec]) {
				visited[ec][ec] = visited[ec][cc] + 1;
				qu.push({ ec,ec });
			}
			if (i == 1 && ec + cc <= 1000 && !visited[ec+cc][cc]) {
				visited[ec+cc][cc] = visited[ec][cc] + 1;
				qu.push({ ec+cc, cc });
			}
			if (i == 2 && 0 < ec - 1 && !visited[ec-1][cc]) {
				visited[ec - 1][cc] = visited[ec][cc] + 1;
				qu.push({ ec - 1, cc });
			}
		}
	}
	return -1;
}

int main() {
	fastio();
	cin >> S;
	cout << bfs(1, 0) << '\n';
	return 0;
}

// 밑의 코드는 위와 로직은 같은데 dfs에 dp를 적용하여 푼것이지만 
// stack overflow가 나와 풀지 못한다.

#define MXN 1000

int cache[MXN + 1][MXN + 1];
int S;
const int INF = 2e9;

int min(int a, int b) {
	return a > b ? b : a;
}

int dfs(int ec, int cc) { // emoticon_cnt, clipboard_cnt
	if (ec == S) return 0;

	int &ret = cache[ec][cc];
	if (ret != -1) return ret;
	
	ret = dfs(ec, ec) + 1;// 1
	if (0 < ec - 1) {
		ret = min(ret, dfs(ec - 1, cc) + 1);// 3
	}
	if (ec + cc <= 1000) {// 2
		ret = min(ret, dfs(ec + cc, cc) + 1);
	}

	return ret;
}

int main() {
	cin >> S;
	memset(cache, -1, sizeof(cache));
	cout << dfs(1, 0) << '\n';
	return 0;
}