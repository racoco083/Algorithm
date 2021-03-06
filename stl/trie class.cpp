#include <iostream>
using namespace std;

#define TRSZ 26
#define OFFSET 'a'
using namespace std;

struct Node {
	Node* c[TRSZ];
	bool e;
};

int scmp(char a[], char b[]) {
	int i, j;
	i = j = 0;
	while (a[i]) {
		if (a[i++] != b[j++]) {
			--i, --j;
			break;
		}
	}
	return a[i] - b[j];
}

int slen(const char* a) {
	int len = 0;
	while (*a != 0) a++, len++;
	return len;
}

class Trie {
public:
	Node *root;

	Trie() {
		root = create_node();
	}

	Node* create_node() {
		Node* p = new Node();
		for (int i = 0; i < TRSZ; i++)
			p->c[i] = 0;
		p->e = false;
		return p;
	}

	void insert(char* v) {
		int len = slen(v);
		Node* p = root;
		for (int i = 0; i<len; i++) {
			int idx = v[i] - OFFSET;
			if (!p->c[idx]) // 없으면
				p->c[idx] = create_node();
			p = p->c[idx];
		}
		p->e = true;
	}

	bool search(char* v) {
		int len = slen(v);
		Node* p = root;
		for (int i = 0; i<len; i++) {
			int idx = v[i] - OFFSET;
			if (!p->c[idx])
				return false;
			p = p->c[idx];
		}
		return p->e;
	}

	void dfs(Node *root) {
		Node *p = root;
		for (int i = 0; i < TRSZ; ++i) {
			if (p->c[i])
				dfs(p->c[i]);
		}
		delete p;
	}

	void del() {
		dfs(root);
		root = create_node();
	}
};


int N;

Trie title, oth, genre;

int main() {
	char str[10];
	char arr1[8][10] = { "abcd", "abcde", "abcdef", "abcr", "abcu", "ab", "abb", "abcl" };
	char arr2[8][10] = { "abcd", "abcde", "abcdef", "abcr", "abcu", "ab", "abb", "abcl" };
	char arr3[8][10] = { "abcd", "abcde", "abcdef", "abcr", "abcu", "ab", "abb", "abcl" };

	int cnt = 3;
	while (cnt--) {
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> str;
			title.insert(str);
			oth.insert(str);
			genre.insert(str);
		}

		for (int i = 0; i < 8; i++) {
			cout << title.search(arr1[i]) << '\n';
		}
		cout << '\n';
		for (int i = 0; i < 8; i++) {
			cout << oth.search(arr2[i]) << '\n';
		}
		cout << '\n';
		for (int i = 0; i < 8; i++) {
			cout << genre.search(arr3[i]) << '\n';
		}
		cout << '\n';

		title.del();
		oth.del();
		genre.del();

		for (int i = 0; i < 8; i++) {
			cout << title.search(arr1[i]) << '\n';
		}
		cout << '\n';
		for (int i = 0; i < 8; i++) {
			cout << oth.search(arr2[i]) << '\n';
		}
		cout << '\n';
		for (int i = 0; i < 8; i++) {
			cout << genre.search(arr3[i]) << '\n';
		}
		cout << '\n';
	}
	return 0;
}

/*
5
abcd abcde ab abb abcl
*/