/*  
 *  BOJ 2449. 전구
 *
 *  cache[i][j] : i~j까지 구간의 색변경 최소 횟수
 *
 *  입력의 시작 start부터 입력의 끝 end까지 구간의 색변경 최소 횟수를 구해야한다.  
 *  이걸 구하기 위해서는 start~end의 구간을 더 작은 구간으로 나누어서 값을 구해야 한다.
 *  입력이 2, 3, 4, 1이라고 하면 밑과 같이 더 작은 구간의 값을 이용해서 최종값을 구한다.
 *  그래서 dp를 적용한 재귀가 적합한 문제이다.
 *
 *  (2, 3, 2, 1)
 *  (2, 3, 2), (1) 
 *  (2), (3, 2)
 *      (3), (2)
 *  int diff = (arr[k] != arr[k+1]) ? 1 : 0; 이 코드는 틀린코드이고
 *  k와 k+1자리에 (s, k+1), (k, e), (s, e)를 해야 맞는 코드가 된다.
 *  틀린코드를 적용하면 위의 재귀그림에서 (3), (2)는 색이 달라 diff가
 *  1이 되어 부모에게 리턴한다. 하지만 (2), (3, 2) 에서는 diff가 0이어야 
 *  하는데 1이 되어 버린다. 이 문제에서는 중간 숫자를 양쪽의 숫자와 같게
 *  만들어 나가야 한다. 틀린코드로 하면 (3), (2) 에서 색깔을 3으로 통일시켜
 *  (3), (3)이 되고, (2), (3, 2)에서 다시 (2)와 (3, 2)의 3이 비교되어 (2)를
 *  (3)으로 만들어 주는 격이다. 이걸 방지하기 위해 (s, e)값을 적용시키면
 *  (2), (3)에서 바꾸는 횟수는 1번만 필요하고 (2), (3, 2)에서는 바꾸지 않아도
 *  된다.
 *
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <string.h>
using namespace std;
#define MXN 202

int N, K;
int arr[MXN];
int cache[MXN][MXN];
const int INF = 2e9;

int min(int a, int b) {
	return a > b ? b : a;
}

int dfs(int s, int e) {
	if (s >= e) return 0;

	int &ret = cache[s][e];
	if (ret != -1) return ret;
	ret = INF;

	// (앞, 뒤), (뒤, 뒤), (앞, 앞)은 옳은 결과값이 나오지만 (뒤, 앞)은 틀린다.
	for (int k = s; k < e; k++) {
		int diff = (arr[k] != arr[k+1]) ? 1 : 0;
		ret = min(ret, dfs(s, k) + dfs(k + 1, e) + diff);
	}
	return ret;
}

int main() {
	fastio();
	cin >> N >> K;
	memset(cache, -1, sizeof(cache));
	int a;
	cin >> arr[0];
	int idx = 0;
	// 연속되는 수들은 어차피 하나이므로 하나만 arr에 저장해 나간다.
	// 111222333222가 들어오면 1232만 저장된다.
	for (int i = 1; i < N; i++) {
		cin >> a;
		if (arr[idx] != a) {
			arr[++idx] = a;
		}
	}

	int ans = dfs(0, idx);
	cout << ans << '\n';
	return 0;
}