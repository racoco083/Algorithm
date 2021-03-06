/*
 *  BOJ 2668. 숫자고르기
 *
 *  방향 그래프에서 사이클 도는 정점들 찾는 문제로 모든 정점의
 *  자식은 하나지만 부모는 0~(N-1)개가 될 수 있다.
 *  이걸 생각하면 사이클을 쉽게 찾을 수 있다.
 *  자세한 설명은 밑에서 하겠다.
 *
 */

#include <iostream>
#include <vector>
#include <set>
using namespace std;
#define MXN 101

int N;
vector<int> adj[MXN];
int visited[MXN];
set<int> ans;



int dfs(int c) {
	// 방문 되었는데 또 방문되었다는 것은 이 정점을 시작과 끝으로 하는
	// 사이클이 존재한다는 뜻이다. 그 사이클에 속하는 정점들을 모두
	// set에 담아야 한다. 예를 들어 4->1->2->3->1이 사이클을 이룬다고 하면
	// 1이 마지막으로 한 번 더 방문된다. 이 때 1은 자신이 사이클의 시작과
	// 끝이라느 것을 부모에게 알리기 위해 자신의 정점 번호를 부모에게 리턴한다.
	// 3은 이 값을 받아 자신이 사이클에 속한다는 것을 알고
	// (ret가 0이 아니면 사이클에 속한다.) 자신을 set에 넣는다.
	// 그리고 다른 정점이 3에 다시 방문하지 못 하도록 visited[3] = -1해 준다.
	// 2에게도 1값을 리턴한다. 2도 3과 같이 자신이 사이클에 속한다는 것을 알고
	// 자신을 set에 담고 역시 visited[2] = -1해 준다. 2의 부모인 1에게 1값을 똑같이
	// 리턴 해준다. 1은 ret값이 자신의 정점번호와 같은 걸 아니 자신이 사이클의 시작
	// 이면서 끝이라는 것을 알 수 있다. 자신을 set에 담고 자신의 부모는 이제 사이클에
	// 속하지 않으니 ret=0을 담아 리턴하고 리턴하기 전에 역시 다른 정점들이 자신에게
	// 방문하지 못하도록 visited[1] = -1 해준다.
	if (visited[c] == 1) return c;
	visited[c]++;
	int ret = 0;
	int next = adj[c][0];
	if (visited[next] != -1) {
		ret = dfs(next);
		// ret가 c와 같다면 현 정점이 사이클의 시작과 끝이라는 것을 알 수 있다. 이 정점을 set에 담는다.
		// 이 정점의 부모로 올라가도 부모는 set에 포함되지 않도록 ret를 0으로 만들어준다.
		if (ret == c) {
			ans.insert(c);
			ret = 0;
		}
		// ret가 0이 아니면서 현재 정점의 값과도 다르다면 현 정점은 사이클에
		// 속하는 정점이라는 것을 알 수 있다. set에 현 정점을 담는다.
		else if (ret != 0) ans.insert(c);
	}
	// 방문된 모든 정점들은 다시 방문되지 않도록 하기 위해
	// 해당 정점의 visited 값을 -1로 만들어 준다.
	visited[c] = -1;
	return ret;
}

int main() {
	cin >> N;
	int a;
	for (int i = 1; i <= N; i++) {
		cin >> a;
		adj[i].push_back(a);
	}

	for (int i = 1; i <= N; i++) {
		if (visited[i] != -1) dfs(i);
	}

	cout << ans.size() << '\n';
	for (set<int>::iterator it = ans.begin(); it != ans.end(); it++) {
		cout << *it << '\n';
	}
	return 0;
}












