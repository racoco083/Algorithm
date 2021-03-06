#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
#define MXN 502

int N;
int wet[MXN];// weight
vector<int> adj[MXN];
int cache[MXN];

int max(int a, int b) {
	return a > b ? a : b;
}

int dfs(int c) {
	int &ret = cache[c];
	if (ret != -1) return ret;
	ret = wet[c];
	
	for (int i = 0; i < adj[c].size(); i++) {
		int n = adj[c][i];
		// 자식으로부터 온 값 중에 제일 큰 값에 현재의 weight값을 더한 값이
		// 현재 정점의 최종 비용이다. 현재 정점이 완성되기 전에 모든 자식이
		// 완성이 되어야 하기 때문이다. 이걸 max가 아닌 min값으로 하여서 
		// 틀렸다. 주의하자!
		ret = max(ret, dfs(n) + wet[c]);
	}
	return ret;
}

int main() {
	cin >> N;
	memset(cache, -1, sizeof(cache));
	for (int i = 1; i <= N; i++) {
		cin >> wet[i];
		int a;
		while (1) {
			cin >> a;
			if (a == -1) break;
			adj[i].push_back(a);
		}
	}
	for (int i = 1; i <= N; i++) dfs(i);
	for (int i = 1; i <= N; i++) cout << cache[i] << '\n';
	return 0;
}