/*
 *  BOJ 2250. 트리의 높이와 너비
 *
 *  우선 입력에 따라 트리를 구성한다. 문제의 그림을 보면
 *  중위 순회하여 방문한 순서 값이 곧 해당 정점의 열의 번호가 된다.
 *  중위 순회를 하며 레벨마다 최소 열 값과 최대 열값을 구한다.
 *  그리고 모든 레벨을 뒤져서 최대 열값과 최소 열의 차이(너비)가 가장 큰
 *  레벨을 찾고 레벨과 너비를 출력하면 된다.
 *  
 */

#include <iostream>
using namespace std;
#define MXN 10001

class Node {
public:
	int n;
	Node *l, *r;
	Node() { l = r = NULL; }
	Node(int _n) : n(_n) { l = r = NULL; }
};
int N;
int gn;//global_number
int mid[MXN];// min_depth 레벨마다의 최소값 저장
int mxd[MXN];// max_depth
int ncn[MXN];// node_column_number

Node *insert(Node *c, int n, int l, int r) {
	if (c == NULL) return NULL;
	if (c->n == n) {
		if (l != -1) c->l = new Node(l);
		if (r != -1) c->r = new Node(r);
		return c;
	}
	c->l = insert(c->l, n, l, r);
	c->r = insert(c->r, n, l, r);
	return c;
}

int min(int a, int b) {
	return a > b ? b : a;
}

int max(int a, int b) {
	return a > b ? a : b;
}

void inorder(Node *c, int d) {// cur, depth
	if (c == NULL) return;
	inorder(c->l, d + 1);
	ncn[c->n] = (++gn);
	mid[d] = min(mid[d], ncn[c->n]);
	mxd[d] = max(mxd[d], ncn[c->n]);
	inorder(c->r, d + 1);
}

void init() {
	for (int i = 0; i < MXN; i++) {
		mid[i] = 2e9;
	}
}

int main() {
	cin >> N;
	int n, l, r;
	init();
	cin >> n >> l >> r;
	Node *root = new Node(n);
	if (l != -1) root->l = new Node(l);
	if (r != -1) root->r = new Node(r);
	for (int i = 1; i < N; i++) {
		cin >> n >> l >> r;
		root = insert(root, n, l, r);
	}
	inorder(root, 0);
	int mxv = 0;
	int mxn = 0;
	for (int i = 0; i < N; i++) {
		if (mxv < mxd[i] - mid[i]) {
			mxv = mxd[i] - mid[i];
			mxn = i;
		}
	}
	cout << mxn + 1 << ' ' << mxv + 1 << '\n';
	return 0;
}
















