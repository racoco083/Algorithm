// 벨만 - 포드 알고리즘
// 다익스트라 알고리즘에서 추가해 음수 사이클까지 확인할 수 있는 알고리즘이다.
// 하지만 시간복잡도는 O(|V||E|)로 다익스트라 O(|E|log|E|)보다 더 오래 걸린다.

#include <iostream>
#include <vector>
using namespace std;
#define MAX_V 1001
int V;
const int INF = 2000000000;

vector<pair<int, int>> adj[MAX_V];

vector<int> bellmanFord(int src) {
	vector<int> upper(V, INF);
	upper[src] = 0;
	bool updated;

	for (int iter = 0; iter < V; iter++) {
		// 이iter의 숫자가 0일때 의미하는 것은 각 정점에서 모든 첫번째 간선까지의 거리를 계산하고
		// iter가 2가되면 각 정점에서 첫번째+두번째 간선까지의 거리를 계산한다.
		// 만약 점4개가 있는데 최단경로의 간선의 수는 최대가3이므로 0=V-4, 1=V-3, 2=V-2까지만
		// 계산하면 최단거리를 구할 수 있다. 만약 그 경로 중 음수 사이클이 존재한다면 3=V-1번째에도
		// upper배열의 원소가 갱신이되어 updated가 true로 바뀌고 이것이 의미하는 것은 
		// 음수 사이클이 경로 중에 존재한다는 소리이다. 
		updated = false; //모든 간선에 대해 upper의 갱신이 되었나 안 되었나 확인 위해.
		for (int here = 0; here < V; here++) {
			for (int i = 0; i < adj[here].size(); i++) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				if (upper[there] > upper[here] + cost) {
					upper[there] = upper[here] + cost;
					updated = true;
				}
			}
		}
		// 모든 간선에 대해 완화가 실패했을 경우 V-1번도 돌 필요 없이 곧장 종료한다.(upper = {0, INF, INF, INF}) =>이런 상황
		// 모든 간선에 대해 완화가 실패하면 더 이상 위의 코드를 실행 할 필요가 없다.
		// 루트인 a로부터 iter가 0일 때는 a에서 직접적으로 붙은 간선만을 upper에 저장하고
		// iter가 1일 때는 a에서 직접붙은 간선을 거쳐 두번째 가는간선으로 최단거리를 구한다.
		// 이 때 만약 iter가 1일때 upper의 원소중에 갱신된 것이 없다고 한다면 iter가 0일 때가
		// 최단경로라는 것을 알 수 있고, a로부터 첫번째간선이 a로부터 첫번째를 거쳐 두번째 간선을 통한 거리보다 짧다는 뜻이다.
		// iter가 2일 때는 a로 부터 첫번째 간선을 거쳐 두번째 간선을 또 거쳐 세번째 간선을 거친 거리는 의미가 없다는 거다
		// 왜냐하면 이미 a로 부터 첫번째 간선이 a로부터 첫번째 간선을 거쳐 두번째 간선을 간 거리보다 짧기 때문이다. 
		if (!updated) break;
		// 쉽게말해 root로 부터 첫번째 간선까지 거리 전체가 루트로부터 첫번째를 지나 두번째 간선 까지의 거리보다 짧다면
		// 위의 코드를 실행해 봤자 같은짓을 되풀이하는거다
	}
	// (i==V-1)번째 순회에서도 완화가 성공해 updated가 갱신되었다면 음수 사이클이 있다.
	if (updated) upper.clear();
	return upper;// 다익스트라 알고리즘에서 dist와 같은 역할을 한다.
				 // 만약 v번째에 이하로 upper의 값들 중 갱신 된 것이 없고 
				 // upper가 빈 배열이 아니라면 이 그래프는 음수 사이클이 
				 // 아니라는 뜻이고 루트로부터 각 정점들까지의 가장 가까운 거리
				 // 담은 upper 반환한다.
}

void main() {
	vector<int> dist;
	V = 4;
	adj[0].push_back(make_pair(1, 8));
	adj[0].push_back(make_pair(3, 1));
	adj[2].push_back(make_pair(1, 1));
	adj[3].push_back(make_pair(2, 1));
	dist = bellmanFord(0);
	for (int i = 0; i < V; i++)
		cout << dist[i] << " ";// 답은 0,3,2,1이 되어야 한다.
}
// 이 알고리즘은 전체 그래프에서 음수 사이클이 있는지 판단한다.