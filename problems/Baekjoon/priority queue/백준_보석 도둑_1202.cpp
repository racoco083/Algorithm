/*
 *  BOJ 1202. 보석 도둑
 *
 *  시간복잡도 : O(NlogN + K)
 *  
 *  wv배열을 무게 오름차순으로 정렬하고, beg도 무게로 오름차순 정렬한다.
 *  i번째 가방부터 시작한다고 하면, i번째 가방에 들어갈 수 있는 모든 보석을
 *  pq에 다 담는다. pq는 value를 기준으로 maxHeap이다. ans += pq.top()해 주며
 *  i번째에서 가방에 들어갈 수 있는 보석 중 가장 큰 가치를 ans에 더해준다.
 *  이 과정을 i번 반복하면 된다. pq에는 총 N개의 원소가 들어갈수 있으므로
 *  시간복잡도는 NlogN이다.
 *  
 */

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
#define MXN 300002

int N, K;
pi wv[MXN];// weight_value
int beg[MXN];
priority_queue<int> pq;

int main() {
	cin >> N >> K;
	for (int i = 0; i < N; i++) cin >> wv[i].first >> wv[i].second;
	for (int i = 0; i < K; i++) cin >> beg[i];

	sort(wv, wv + N);
	sort(beg, beg + K);

	ll ans = 0;
	for (int i = 0, j = 0; i < K; i++) {
		while (j < N && wv[j].first <= beg[i]) pq.push(wv[j++].second);

		if (!pq.empty()) {
			ans += pq.top();
			pq.pop();
		}
	}
	cout << ans << '\n';
	return 0;
}