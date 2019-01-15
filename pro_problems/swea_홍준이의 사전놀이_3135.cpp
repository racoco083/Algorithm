// type�� 1 �� ���� ���ڸ� Ʈ���̿� ���Խ����ش�. �� �� �θ� ���� �ڽ�����
// ���鼭 �湮�� ������ cnt���� ���� 1�� ���������ش�.
// type�� 2�̸� �ش� ���ڿ��� ���� Ʈ���̸� Ž���ؼ� �� ���ڿ��� ������
// ���ڿ��� ������ �� ���ڿ��� ������ �ε����� ����� cnt���� �������ָ�
// �ȴ�. cnt�� ���� �� �ش� ���ڸ� ������ ���ڿ��� ������ �ȴ�.

#include <stdio.h>
#include <iostream>
using namespace std;

extern void init(void);

extern void insert(int buffer_size, char *buf);

extern int query(int buffer_size, char *buf);

#define TRSZ 26
#define OFFSET 'a'

class Node {
public:
	Node * c[TRSZ];// child
	int cnt;// ���� ���ڷ� �����ϴ� �ܾ���� ������ ���Ѵ�.
	bool e;// e�� true�̸� ���� ���ڷ� ������ �ܾ �ִٴ� ���̴�.
};

Node *root;

Node *cn() {// create_node
	Node *n = new Node();
	for (int i = 0; i < TRSZ; i++) {
		n->c[i] = 0;
	}
	n->cnt = 0;
	n->e = false;
	return n;
}

void init() {
	root = cn();
}

void insert(int s, char *v) {// size, value
	Node *r = root;
	for (int i = 0; i < s; i++) {
		int idx = v[i] - OFFSET;
		if (!r->c[idx])
			r->c[idx] = cn();
		r = r->c[idx];
		r->cnt++;
	}
	r->e = true;
}

int query(int s, char *v) {// size, value
	Node *r = root;
	for (int i = 0; i < s; i++) {
		int idx = v[i] - OFFSET;
		if (!r->c[idx]) return 0;
		r = r->c[idx];
	}
	return r->cnt;
}

int main(void) {
	//freopen("input.txt", "r", stdin);
	int TestCase;
	for (scanf("%d", &TestCase); TestCase--;) {
		int Query_N;
		scanf("%d", &Query_N);

		init();

		static int tc = 0;
		printf("#%d", ++tc);

		for (int i = 1; i <= Query_N; i++) {
			int type; scanf("%d", &type);

			if (type == 1) {
				char buf[15] = { 0, };
				scanf("%s", buf);

				int buffer_size = 0;
				while (buf[buffer_size]) buffer_size++;

				insert(buffer_size, buf);
			}
			else {
				char buf[15] = { 0, };
				scanf("%s", buf);

				int buffer_size = 0;
				while (buf[buffer_size]) buffer_size++;

				printf(" %d", query(buffer_size, buf));
			}
		}
		printf("\n");
		fflush(stdout);
	}
}