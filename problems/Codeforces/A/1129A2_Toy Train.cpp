/*
 *  시간복잡도 : O(N^2)
 *
 *  (문제 설명)
 *  기차는 최대 1개만 사탕을 실을 수 있고, 정점이 N개라고 하고 5라고 하면   
 *  1->2->3->4->5->1 이렇게만 이동할 수 있다. 1<=i<=N이라고 할 때, 각 i의 
 *  정점에서 시작할 때, 모든 캔디를 출발정점에서 가지고가 도착 정점에 가져다
 *  놓을 때 최소 이동 거리를 구한다. 현재 정점에서 다른 정점으로 가면
 *  이동거리가 1이다.
 *  
 *  (풀이)
 *  각 정점에 옮겨야 할 캔디의 개수를 세아린다. 캔디의 개수가 가장 많은 곳은
 *  N*(캔디의 개수-1) 만큼은 이동해야한다. 그리고 원형 순회에서
 *  출발정점에서 도착정점까지의 거리를 구해야 하면 (end + N - start) % N이다.
 *  예를 들어 N이 5이고 start가 1이고 end가 2이면 거리 차이는 1이다.
 *  dist = (2 + 5 - 1) % 5 = 1이 된다. start가 2이고 end가 1이면 거리 차이는
 *  4이다. dist = (1 + 5 - 2) % 5 = 4가 나오는 것을 알 수 있다.
 *  그리고 sd[a]를 구할 때 a로 부터 가장 먼 정점을 구하는 것이 아닌 가까운
 *  정점을 구해야 한다. a정점에 옮겨야 할 캔디가 3개이고 a로 부터 
 *  (캔디개수 - 1) 2번은 순회를 해야한다. 이때 a로 부터 거리가 먼것들을 처리하면
 *  남은 캔디 하나는 a로 부터 가장 가까운 거리로 옮기면 된다.
 *
 */

#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include<iostream>
using namespace std;
#define MXN 5001
int N, M;
int cnt[MXN + 1];
int sd[MXN + 1];// shortest_dist
int ans;

int min(int a, int b) {
	return a > b ? b : a;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	fastio();
	cin >> N >> M;
	int a, b;
	for (int i = 1; i <= N; i++) sd[i] = MXN;
	while (M--) {
		cin >> a >> b;
		cnt[a]++, sd[a] = min(sd[a], (b + N - a) % N);
	}

	for (int i = 1; i <= N; i++) {
		ans = 0;
		for (int j = 1; j <= N; j++) {
			if (cnt[j] == 0) continue;
			ans = max(ans, (j + N - i) % N + (cnt[j] - 1)*N + sd[j]);
		}
		cout << ans << ' ';
	}
}
