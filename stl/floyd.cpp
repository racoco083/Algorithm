/*
 *  BOJ 11404 플로이드
 *
 *  시간복잡도 O(N^3)
 *
 *  floyd algorithm
 *  
 */

#include <iostream>
using namespace std;
#define MXN 101

int N, M;
int adj[MXN + 1][MXN + 1];
const int INF = 1e9;

void init() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			adj[i][j] = (i == j ? 0 : INF);
		}
	}
}

int min(int a, int b) {
	return a > b ? b : a;
}

void floyd() {
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
			}
		}
	}
}

void print() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (adj[i][j] == INF) cout << 0 << ' ';
			else cout << adj[i][j] << ' ';
		}
		cout << '\n';
	}
}

int main() {
	cin >> N >> M;
	init();
	int a, b, c;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		adj[a][b] = min(adj[a][b], c);
	}
	floyd();
	print();
}