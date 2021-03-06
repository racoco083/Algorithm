// 위상 정렬(topological sorting)은 유향 그래프의 꼭짓점들(vertex)을 변의 방향을 거스르지 않도록 나열하는 것을 의미한다.

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;
vector<int> discovered;
vector<int> sccId;
stack<int> st;
int sccCounter, vertexCounter;

// 그래프에서 각 정점들의 리스트를 다확인하면서 dfs개념으로 방문되지 않는 정점들을
// 방문한다 만약 현재 점에서의 리스트 중에 방문되었는데 sccId가 -1이라는 것은 아직
// scc로 구분되지 않았다는 것이고, 그 점과 현재의 점중에 발견이 더 일찍 된 순서를 
// ret에 담는다. 만약 현재점의 발견순서와 현재점의 ret의 값이 같다는 것은 현재점이
// scc로 나누는 구획중에 root점이라는 소리다.

// here를 루트로 하는 서브트리에서 역방향 간선이나 교차 간선을
// 통해 갈 수 있는 장점 중 최소 발견 순서를 반환한다.
// (이미 scc로 묶인 정점으로 연결된 교차 간선은 무시한다.)
int scc(int here) {
	int ret = discovered[here] = vertexCounter++; // discovered는 발견된 순서를 담고, ret는 현재 점이 연결되 있는 것 중에 가장 발견 순서가 빠른 것을 담는다.
	st.push(here);
	for (int i = 0; i < adj[here].size(); i++) {
		int there = adj[here][i];
		// (here, there) 가 트리 간선
		if (discovered[there] == -1)
			ret = min(ret, scc(there));
		// there가 무시해야 하는 교차 간선이나 역 방향 간선이 아니라면 무시해도 되는 것은 이미 그룹을 형성하고 있으면 무시하지만 그룹을 형성하고 있지 않으면 같은 그룹이 될 수 있으므로 무시하면 안 된다.
		else if (sccId[there] == -1)
			ret = min(ret, discovered[there]); // if, else if로 나누었으니 방문이 되었는데 sccId는 -1이 넘은 결국 이전에 방문이 된 넘이네 
	}

	// ret와 discovered가 같다는 소리는 현재 점이 scc그룹의 루트라는 소리이다. 그러면 스택에서 현재점을 만날 때 까지 점을 그룹에 담고 pop해 주면 된다.
	// 왜냐하면 스택에서 현재점 위에 있는 것은 현재 점을 루트로 하는 같은 그룹이기 때문이다. 만약 1번 점 처럼 혼자이면 1번 점 혼자 그룹을 만든다.
	if (ret == discovered[here]) {
		while (1) {
			int t = st.top();
			st.pop();
			sccId[t] = sccCounter;
			if (here == t) break;
		}
		sccCounter++;
	}

	return ret;
}

vector<int> tarjanSCC() {
	sccId = discovered = vector<int>(7, -1);

	sccCounter = vertexCounter = 0;
	for (int i = 1; i < 7; i++)
		if (discovered[i] == -1) scc(i);
	return sccId;
}

void main() {
	adj = vector<vector<int>>(7);//행의 개수를 7개로 만든다.
	adj[1].push_back(2);
	adj[1].push_back(5);
	adj[2].push_back(3);
	adj[3].push_back(4);
	adj[4].push_back(2);
	adj[5].push_back(6);
	adj[6].push_back(4);
	adj[6].push_back(5);
	vector<int> ret = tarjanSCC();

	for (int i = 0; i < ret.size(); i++) {
		cout << ret[i] << " ";
	}
}
// 즉 SCC는 집합 내에서 정점들이 서로 왕복 가능한 최대 크기의 집합입니다.
// 이 타잔 알고리즘은 이 scc그룹을 나눠 주기 위한 알고리즘이라 생각하면 된다.
// http://jason9319.tistory.com/98?category=670441 이 사이트에 설명이 잘 되어 있다.