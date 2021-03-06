// 감시 카메라 설치
#include <iostream>
#include <vector>
using namespace std;
#define MAX_V 1001

int v;
vector<int> adj[MAX_V];
vector<bool> visited;
const int UNWATCHED = 0;
const int WATCHED = 1;
const int INSTALLED = 2;

int installed;

int dfs(int here) {
	visited[here] = true;
	int children[3] = { 0,0,0 };
	for (int i = 0; i < adj[here].size(); i++) {
		int there = adj[here][i];
		if (!visited[there])
			children[dfs(there)]++;
	}

	if (children[UNWATCHED]) {
		installed++;
		return INSTALLED;
	}
	//if (children[UNWATCHED])가 먼저 수행되어야 한다.
	//자식 중에 안 보이는 것이 있으면 현재위치에 카메라를
	//설치하는 게 우선이기 때문이다.

	if (children[INSTALLED])
		return WATCHED;
	return UNWATCHED;
}

int installCamera() {
	installed = 0;
	visited = vector<bool>(v, false);
	for (int u = 0; u < v; u++)
		if (!visited[u] && dfs(u) == UNWATCHED)
			installed++;
	// 그래프가 두개로 나뉘어 져 있을 수 있기 때문에 이렇게
	// dfs를 정점 개수만큼 수행시킨다.
	// dfs(u) == UNWATCHED는 1,2번 정점이 연결되어있지 않고
	// 두 개의 그래프로 나뉘어 져 있다고 생각하면 두 개의 정점에 다
	// 카메라를 설치해야 한다.
	return installed;
}

void main() {
	v = 5;
	adj[0].push_back(1);
	adj[1].push_back(0);
	adj[1].push_back(2);
	adj[2].push_back(1);
	adj[3].push_back(4);
	adj[4].push_back(3);
	// 그래프를 두개로 만들었을 때도 적용이 된다.

	cout << installCamera();// 답은 2가 나온다(0-1-2, 3-4 이렇게 그래프 두개)
}