// type이 1 일 때는 문자를 트라이에 삽입시켜준다. 이 때 부모 부터 자식으로
// 가면서 방문한 노드들의 cnt값을 전부 1씩 증가시켜준다.
// type이 2이면 해당 문자열에 대해 트라이를 탐색해서 이 문자열로 끝나는
// 문자열이 있으면 이 문자열의 마지막 인덱스의 노드의 cnt값을 리턴해주면
// 된다. cnt의 값이 곧 해당 문자를 지나간 문자열의 개수가 된다.

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
	int cnt;// 현재 문자로 시작하는 단어들의 개수를 뜻한다.
	bool e;// e가 true이면 현재 문자로 끝나는 단어가 있다는 뜻이다.
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