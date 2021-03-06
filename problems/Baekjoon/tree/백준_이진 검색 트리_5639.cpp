// 이진 검색트리 삽입 함수를 만들어 값이 전위탐색한 순으로
// 들어오니 그것을 그대로 삽입함수를 통해서 삽입시켜
// 이진탐색트리를 만든다. 이것을 후위순회하며 출력하면
// 답이된다.

#pragma warning(disable:4996)
#include <cstdio>
using namespace std;

class Node {
public:
	int v;
	Node *l, *r;
	Node(int _v) : v(_v), l(NULL), r(NULL) {}
};

// 전위탐색이므로 값이 들어올때마다 이진탐색 트리에 값을 삽입해서
// 후위순회로 출력하면 된다.
Node *insert(Node *c, int v) {
	if (c == NULL) {
		return new Node(v);
	}
	if (c->v > v) c->l = insert(c->l, v);
	else c->r = insert(c->r, v);
	return c;
}

void post(Node *c) {
	if (c == NULL) return;
	post(c->l);
	post(c->r);
	printf("%d\n", c->v);
}

int main() {
	int in;
	Node *root = NULL;
	// visual에서는 scanf("%d", &in) != EOF이 안 통한다.
	while (scanf("%d", &in) != EOF) {
		root = insert(root, in);
	}
	post(root);
	return 0;
}