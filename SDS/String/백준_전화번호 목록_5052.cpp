#include <iostream>
#include <string>
using namespace std;

class Node {
public:
	// value는 필요 없다. 0~9까지 있는지 없는지는 *c[10]로 확인 가능
	Node *c[10];
	bool e;
	Node() {
		e = false;
		for (int i = 0; i < 10; i++) c[i] = NULL;
	}
};

int N;
Node *root;
bool ans;

void insert(string num) {
	// root를 받아서 root가 가리키는 곳을 수정하면 된다.
	Node *n = root;
	int cnt = 0;
	for (int i = 0; i < num.size(); i++) {
		int idx = num[i] - '0';
		// 현재 num으로 tree구성 중에 n->e가 true라는 것은
		// 현재의 i에서 끝나는 전화번호가 있고 그 전화번호를 현재num이
		// 포함한다는 말이다. 그러면 일관성이 없으므로 ans에 true를 넣어준다.
		// 예를들어 911, 9114의 경우 911를 처리하고 9114를 처리하면 두번째 1부분에서
		// n->e가 true가 된다. 9114는 911을 포함한다.
		if (n->e) ans = true;
		if (!n->c[idx]) {
			n->c[idx] = new Node();
			n = n->c[idx];
			continue;
		}
		n = n->c[idx];
		cnt++;
	}
	n->e = true;
	// 만약 9114로 트리를 만들고, 911을 트리로 만든다고 하면 n->e가 true인 경우는 없다.
	// 하지만 이 두 개는 일관성이 없다. 911로 트리가 만들어지면 9114에는 전화를 걸 수가
	// 없기 때문이다. 그래서 911을 트리에 넣을 때 한 번도 new Node를 하지 않았다는 것은
	// 어떤 번호에 자신의 번호가 포함되어 있다는 것을 뜻한다. 그래서 9114 다음에 911을 처리하면
	// new Node를 하지 않은 개수가 911의 사이즈와 같다면 911은 어떤 번호에 포함되어 있다는 것을
	// 뜻한다.
	if (cnt == num.size()) ans = true;
}

int main() {
	int TC;
	cin >> TC;
	while (TC--) {
		string num;
		cin >> N;
		root = new Node();
		// ans가 false이면 일관성이 있는 것이고 true이면 일관성이 없는 것이다.
		ans = false;
		for (int i = 0; i < N; i++) {
			cin >> num;
			insert(num);
		}
		if (ans) cout << "NO" << '\n';
		else cout << "YES" << '\n';
	}
	return 0;
}