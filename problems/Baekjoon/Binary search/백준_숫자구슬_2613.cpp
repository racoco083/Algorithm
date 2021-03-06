/*
 *  BOJ 2613. 숫자구슬
 * 
 *  시간복잡도 : O(Nlog(3*10^4))
 *  공간복잡도 : O(N)
 *
 *  이분탐색을 통해 mid값을 각 그룹의 구슬들의 합의 최대값으로 설정하고
 *  그룹을 구한다. gc안의 원소값은 각 그룹의 구슬개수를 의미하고
 *  연속된 구슬들이 그룹이 되어야 하니 gc의 원소가 4 2 2 라고 한다면
 *  1,2,3,4 구슬이 첫 번째 그룹, 5, 6 구슬이 두번째 그룹, 7, 8구슬이
 *  3번째 그룹에 있다는 것을 뜻한다. 그룹의 수가 M가 같거나 더 작다면
 *  mid값을 낮추어 주고 (가능한 가장 작은 mid값을 구해야 하므로)
 *  그룹수가 M보다 더 크다면 mid값을 높여 그룹수를 줄인다. 
 *
 */

#include <iostream>
#include <vector>
using namespace std;
#define MXN 302

int N, M;
int marble[MXN];
vector<int> av;// answer_vector => 가능한 mid값이 최소값일 때 각 그룹의 구슬 개수를 담는다. 
vector<int> gc;// group_count

bool solve(int dl) {// deadline
	gc.clear();
	int cnt = 0;
	int sum = 0;
	for (int i = 0; i < N; i++) {
		// 모든 구슬은 그룹에 속해야 하는데 구슬 하나자체의 값이
		// dl보다 크다면 이 구슬은 그룹에 속할수가 없다.
		// 그러므로 dl를 더 높여야 한다.
		if (marble[i] > dl) return false;
		if (sum + marble[i] <= dl) {
			cnt++;
			sum += marble[i];
		}
		else {
			gc.push_back(cnt);
			sum = marble[i];
			cnt = 1;
		}
	}
	gc.push_back(cnt);
	return true;
}

int bs(int s, int e) {
	int ans = 0;
	while (s <= e) {
		int m = (e + s) / 2;
		bool chk = solve(m);
		// 그룹의 수가 M보다 작으면 특정 그룹들을 여러개의 그룹으로
		// 만들어서 그룹의 수를 M으로 맟추어도 상관이 없다.
		// 4 4
		// 3 1 1 1
		// 위의 데이터로 예를 들어보자.
		// m이 3이라고 했을 때 연속된 구슬의 숫자합이 m보다 작으면 다 같은
		// 그룹에 포함되어 그룹은 2개의 그룹이 생기고 각 그룹의
		// 구슬 수는 순서대로 1 3이다. 하지만 그룹 수를 4개로 만들어야 한다면
		// 현재의 그룹을 쪼개어 그룹을 더 만들어 주어야 한다. 이 때 첫 번째 구슬을
		// 제외한 모든 구슬의 값은 m보다 두 번째 그룹을 3개의 그룹으로 만들어 준다.
		// 그렇게 해도 여전히 각 그룹의 구슬 숫자 합은 m보다 작기 때문이다. 
		if (chk && gc.size() <= M) {
			e = m - 1;
			ans = m;
			av.clear();
			av = gc;
		}
		else s = m + 1;
	}
	return ans;
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> marble[i];
	}

	cout << bs(1, 30001) << '\n';
	// 그룹수를 M으로 맞추어 주어야 한다. 그룹수가 M보다 작으면 해당 그룹에 있는
	// 구슬들을 꺼내서 그룹 만들어 그룹의 수를 늘려주면 된다.
	int diff = M - av.size();
	for (int i = 0; i < av.size(); i++) {
		// av는 각 그룹의 구슬 개수를 원소로 갖는다.
		// 이 값이 1보다 크다는 것은 여기서 구슬을 꺼내어 또 다른 그룹을
		// 만들어 줄 수 있다는 뜻이다. diff가 0이 되때까지 이런 av의 원소들을
		// 찾아 그룹을 새로 만들어 주면서 각 원소를 출력해 주면 된다.
		while (diff && av[i] > 1) {
			cout << 1 << ' ';
			av[i]--;
			diff--;
		}
		cout << av[i] << ' ';
	}
	return 0;
}
























