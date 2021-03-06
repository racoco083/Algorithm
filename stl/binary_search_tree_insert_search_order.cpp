#include <iostream>
using namespace std;

class Tree {
public:
	Tree *l, *r;
	int v;

	Tree() { l = NULL, r = NULL; }
	Tree(int _v) : v(_v) { l = NULL, r = NULL; }
};

void preOrder(Tree *cur) {
	if (cur == NULL) return;
	cout << cur->v << '\n';
	preOrder(cur->l);
	preOrder(cur->r);
}

void inOrder(Tree *cur) {
	if (cur == NULL) return;
	inOrder(cur->l);
	cout << cur->v << '\n';
	inOrder(cur->r);
}

void postOrder(Tree *cur) {
	if (cur == NULL) return;
	postOrder(cur->l);
	postOrder(cur->r);
	cout << cur->v << '\n';
}

Tree *insert(Tree *cur, int v) {
	if (cur == NULL) return new Tree(v);
	/*
	if (cur->v < v) return cur->r = insert(cur->r, v);
	return cur->l = insert(cur->l, v);
	밑의 코드 처럼 안하고 주석친 위의 코드처럼 하여 틀렸다.
	트리를 유지하기 위해서는 cur을 넘겨주어야 하는데 자식만 넘겨주었다.
	그래서 root의 사이즈가 계속 1이 될 수 밖에 없었다.
	*/
	if (cur->v < v) cur->r = insert(cur->r, v);
	else cur->l = insert(cur->l, v);

	return cur;
}

bool search(Tree *cur, int v) {
	if (cur == NULL) return false;
	if (cur->v == v) return true;

	return search(cur->l, v) || search(cur->r, v);
}



int main() {
	Tree *root = NULL;
	root = insert(root, 5);
	root = insert(root, 3);
	root = insert(root, 1);
	root = insert(root, 4);
	root = insert(root, 8);
	root = insert(root, 6);
	root = insert(root, 9);
	
	cout << search(root, 5) << '\n';
	cout << search(root, 2) << '\n';

	cout << "start preOrder" << '\n';
	preOrder(root);
	cout << " start inOrder" << '\n';
	inOrder(root);
	cout << "start postOrder" << '\n';
	postOrder(root);
	return 0;
}