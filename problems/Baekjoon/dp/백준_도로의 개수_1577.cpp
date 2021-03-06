/*
 *  BOJ 1577. 도로의 개수
 *
 *  시간복잡도 : O(N^2 * logK)
 *
 *  1,1의 좌표부터 시작해서 행과열의 인덱스를 높이며 현재 위치의
 *  위쪽, 왼쪽으로 오는 경로의 가짓수를 현재 위치에 더해나간다.
 *  이 때 위쪽 좌표와 현재 좌표의 값을 이용해 set에 담아
 *  해당 도로를 유일하게 구별할 수 있도록 한다. 이 때 더 작은 좌표인 위쪽 좌표를
 *  앞에 두고 현재 더 큰 좌표를 뒤에 두는식으로 하여 좌표를 유일하게 구별하도록 하였다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pi;
#define MXN 101

class Chk {
public:
	ll a, b, c, d;
	Chk() {}
	Chk(int _a, int _b, int _c, int _d) : a(_a), b(_b), c(_c), d(_d) {}
};

int N, M, K;
set<vector<ll>> st;
ll dp[MXN + 3][MXN + 3];
int dy[2] = { -1, 0 };
int dx[2] = { 0, -1 };
pi road[2];

int main() {
	fastio();
	cin >> N >> M >> K;
	int a, b, c, d;
	for (int i = 0; i < K; i++) {
		cin >> a >> b >> c >> d;
		road[0] = { a + 1, b + 1 };
		road[1] = { c + 1, d + 1 };
		sort(road, road + 2);
		vector<ll> vc = { road[0].first, road[0].second, road[1].first, road[1].second };
		st.insert(vc);
	}
	dp[0][1] = 1;
	for (int i = 1; i <= N + 1; i++) {
		for (int j = 1; j <= M + 1; j++) {
			for (int k = 0; k < 2; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];

				if (st.count(vector<ll>{ny, nx, i, j})) continue;
				else dp[i][j] += dp[ny][nx];
			}
		}
	}
	cout << dp[N + 1][M + 1] << '\n';
	return 0;
}
