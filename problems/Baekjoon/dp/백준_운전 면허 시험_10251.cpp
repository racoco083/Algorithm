/*
 *  시간복잡도 O(N^3)
 *
 *  cache[y][x][k][d] : 현재점이 y,x이고 방향이 d일 때 남은 방향전환 횟수가k일 때
 *  (N,N)까지 갈 때 사용한 연료의 최소값
 *
 *  한 칸씩 움직일 때마다 시간은 L이다. (1,1)에서 출발하여 방향 전환을 얼마나
 *  적게하여 연료도 G보다 작게 사용하여 (N,N)에 도착하는지를 구하는 문제이다.
 *  파라메트릭 처럼 총 사용가능한 방향전환 횟수 tk를 두어서 계속 dfs를 돌린다.
 *  tk가 가장 작을 때 값을 구하는거니 만약 이 tk에서 (1,1)에서 (N,N)에 도달했다면
 *  tk의 방향전환만 하여서 도달가능하고 이때 시간이 제일 적게걸린다.
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <string.h>
using namespace std;
#define MXN 105

int M, N, L, G;
int row[MXN][MXN];
int col[MXN][MXN];
int cache[MXN][MXN][MXN*2][2];
const int INF = 2e9;
int tk;// total_k 총 방향전환 개수

int min(int a, int b) {
	return a > b ? b : a;
}

// k는 현재의 방향전환 개수를 나타낸다.
int dfs(int y, int x, int k, int d) {
	if (y > M || x > N || k > tk) return INF;
	if (y == M && x == N) return 0;
	
	// tk-k는 앞으로 사용가능한 방향 전환 횟수이고 k는 현재까지 사용한 
	// 방향 전환 횟수이다. 재귀적으로 dp를 구현한 거니 더 작은 부분문제에서는
	// 앞으로 사용가능한 방향전환 횟수를 기준으로 해야 해서
	// 인덱스를 tk-k로 두었다. tk대신 k를 두면 틀린다.
	// 왜냐하면 k는 (1,1)부터 현재 점까지 오면서 사용한 방향전환 횟수를 나타내고
	// 우리가 구하려는 것은 현재점에서 (N,N)까지 갈 때의 연료의 최소값을 구하려는 것이다.
	int &ret = cache[y][x][tk-k][d];// 시간을 담는다.
	if (ret != -1) return ret;
	ret = INF;
	
	ret = min(ret, dfs(y, x + 1, k + (d != 0), 0) + row[y][x]);// 오른쪽
	ret = min(ret, dfs(y + 1, x, k + (d != 1), 1) + col[y][x]);// 밑쪽
	return ret;
}

int main() {
	fastio();
	int TC;
	cin >> TC;
	while (TC--) {
		cin >> M >> N >> L >> G;
		memset(cache, -1, sizeof(cache));
		for (int i = 1; i <= M; i++) {
			for (int j = 1; j < N; j++) {
				cin >> row[i][j];
			}
		}

		for (int i = 1; i < M; i++) {
			for (int j = 1; j <= N; j++) {
				cin >> col[i][j];
			}
		}
		int ans = -1;
		for (tk = 1; tk <= min(M, N) * 2; tk++) {
			if (dfs(1, 1, 0, 0) <= G || dfs(1, 1, 0, 1) <= G) {
				ans = tk + (M + N - 2)*L;
				break;
			}
		}
		cout << ans << '\n';
	}
}

/*
1
4 6 10 19
4 3 6 7 9
3 1 2 7 5
2 2 6 1 9
5 3 4 3 2
1 5 4 4 4 2
6 1 1 3 1 7
2 2 3 2 3 5
*/ //83