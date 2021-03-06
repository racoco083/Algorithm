/*
 *  BOJ 14891. 톱니바퀴
 *
 *  시간복잡도 : O(K)
 *
 *  N번 톱니바퀴를 돌릴 때 마다 해당 번호에서 bfs를 하여 인접한 톱니바퀴가
 *	현재의 톱니바퀴와 마주보는 극이 다른 경우에 인접한 톱니바퀴의 번호를 
 *  qu에 담았다. 그리고 현재 톱니바퀴를 방향에 맞게 돌렸다. 이걸 반복하면 된다.
 *
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <deque>
#include <queue>
using namespace std;
typedef pair<int, int> pi;

deque<char> dq[4];
int K, N, D;

void rotation(int n, int d) {
	if (d == 1) {
		dq[n].push_front(dq[n].back());
		dq[n].pop_back();
	}
	else {
		dq[n].push_back(dq[n].front());
		dq[n].pop_front();
	}
}

void bfs(int n, int d) {
	bool visited[4] = { 0, };
	queue<pi> qu;
	qu.push({ n, d });
	visited[n] = true;
	while (!qu.empty()) {
		int cn = qu.front().first;
		int cd = qu.front().second;
		qu.pop();

		if (cn - 1 >= 0 && !visited[cn - 1] && dq[cn][6] != dq[cn - 1][2]) {
			visited[cn - 1] = true;
			// -cd를 -d라 넣는 실수하였다.
			qu.push({ cn - 1, -cd });
		}

		if (cn + 1 <= 3 && !visited[cn + 1] && dq[cn][2] != dq[cn + 1][6]) {
			visited[cn + 1] = true;
			qu.push({ cn + 1, -cd });
		}
		rotation(cn, cd);
	}
}

int calc() {
	int ret = 0;
	for (int i = 0; i < 4; i++) {
		// if (dq[i][0] == 1) 이 실수 하였다. char형이다.
		if (dq[i][0] == '1') {
			ret += (1 << i);
		}
	}
	return ret;
}

void print() {
	cout << '\n';
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			cout << dq[i][j] << ' ';
		}
		cout << '\n';
	}
}

int main() {
	fastio();
	char a;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			cin >> a;
			dq[i].push_back(a);
		}
	}
	cin >> K;
	for (int i = 0; i < K; i++) {
		cin >> N >> D;
		bfs(N - 1, D);
		//print();
	}

	cout << calc() << '\n';
	return 0;
}