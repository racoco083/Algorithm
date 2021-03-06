/*
 *  BOJ 17136. 색종이 붙이기
 *
 *  시간복잡도 : O(시간복잡도 잘 모르겠다.)
 *
 *  10*10이니 이걸 1차원으로 본다 그래서 0 부터 맨 마지막은
 *  99가 된다. 이 값을 pos라고 할 때 100이 되면 기저사례다
 *  이때 pos위치의 배열을 보면서 area에 1이 있으면 여기에 놓을 수 있는 가장
 *  큰 사각형의 한 변의 길이 값 k를 구한다. 그리고 이 pos 위치에 한 변이1~5
 *  사각형을 전부 놓는 시도를 한다. 놓을 수 있다면 해당 영역
 *  전부 visited로 방문된 것 처리하고 다음 pos값과 블럭의 개수cnt+1
 *  을 매개변수로 하여 다음 자식에게 전달한다. 이런식으로 반복하면 된다.
 *  또 중요한 것이 pos영역이 visited되었거나 area가 1이 아닌 경우
 *  그냥 pos값을 1씩 증가시켜주면서 while문 안에서 반복해 주면 된다.
 *  이 때도 역시 pos가 N*N이 되는지 체크해 이 때의 cnt 값과
 *  ans값 중에 더 작은 값을 ans에 저장해야 한다.
 *
 */
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;
#define MXN 10

int area[MXN + 1][MXN + 1];
int visited[MXN + 1][MXN + 1];
int ans;
int N;
int ibc[6] = { 0,5,5,5,5,5 }; // individual_block_count
const int INF = 2e9;

int fms(int y, int x) { // find_max_size
	int k;
	for (k = 0; k < 5; k++) {
		int ny = y;
		int nx = x + k;
		// 밑의 코드 안 해주어 범위값 체크 안했다.
		if (x + k >= N || y + k >= N) return k;
		while (1) {
			if (ny >= N || !area[ny][nx] || visited[ny][nx]) return k;
			if (ny == y + k) break;
			ny++;
		}

		while (1) {
			if (nx < 0 || !area[ny][nx] || visited[ny][nx]) return k;
			if (nx == x) break;
			nx--;
		}
	}
	return k;
}// N^3으로만 생각했는데 앞으로 이렇게 N^2에 풀도록 노력하자

void fill_box(int y, int x, int k, int c) {
	for (int i = y; i < y + k; i++) {
		for (int j = x; j < x + k; j++) {
			visited[i][j] = c;
		}
	}
}

int min(int a, int b) {
	return a > b ? b : a;
}

void dfs(int pos, int cnt) {
	if (pos == N * N) {
		ans = min(ans, cnt);
		return;
	}

	while (1) {
		// pos / 5로 하는 실수를 했다 주의하자!
		int y = pos / N;
		int x = pos % N;
		if (area[y][x] && !visited[y][x]) {
			int idx = fms(y, x);
			for (int k = 1; k <= idx; k++) {
				if (ibc[k] == 0) continue;
				fill_box(y, x, k, 1);
				ibc[k]--;
				if (ans > cnt + 1) dfs(pos + 1, cnt + 1);
				ibc[k]++;
				fill_box(y, x, k, 0);
			}
			return;
		}
		pos++;
		if (pos == N * N) {
			// 바로 밑의 코드 없으면 틀린다.
			ans = min(ans, cnt);
			return;
		}
	}
}

int main() {
	fastio();
	ans = INF;
	N = 10;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> area[i][j];
		}
	}
	dfs(0, 0);
	if (ans == INF) cout << -1 << '\n';
	else cout << ans << '\n';
	return 0;
}


/*
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 1 1 1 1 1 0 0 0
0 0 1 1 1 1 1 0 0 0
0 0 1 1 1 1 1 0 0 0
0 1 1 1 1 1 1 0 0 0
0 1 1 1 1 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
*/// 답5다