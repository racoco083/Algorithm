// 곱하기가 있으니 int범위를 넘을 수 있다는 것을 망각하여 2번 틀렸다!!

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;

#define MAX_STACK 1001
#define MAX_INS 100001
typedef long long ll;

class Ins {
public:
	char instruc[5];
	ll v;
	Ins(char *_instruc, ll _v) : v(_v) {
		int i;
		for (i = 0; _instruc[i] != 0; i++) {
			instruc[i] = _instruc[i];
		}
		instruc[i] = 0;
	}
	Ins(char *_instruc) : v(0) {
		int i;
		for (i = 0; _instruc[i] != 0; i++) {
			instruc[i] = _instruc[i];
		}
		instruc[i] = 0;
	}
	Ins() {}
};

int N;
Ins ins[MAX_INS];
ll st[MAX_STACK];
int stI;
int insI;
bool Error;
const ll INF = 1e9;

int min(int a, int b) {
	return a > b ? b : a;
}

int slen(const char *a) {
	int len = 0;
	while (*a != 0) {
		a++;
		len++;
	}
	return len;
}

bool scmp(char *a, const char *b) {
	int al = slen(a);
	int bl = slen(b);
	if (al != bl) return false;
	for (int i = 0; i < al; i++) {
		if (a[i] != b[i]) return false;
	}
	return true;
}

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

ll ab(ll a) {
	return a < 0LL ? -a : a;
}

void solve() {
	for (int i = 0; i < insI; i++) {
		if (scmp(ins[i].instruc, "NUM")) {
			stI++;
			st[stI] = ins[i].v;
		}
		else if (scmp(ins[i].instruc, "POP")) {
			if (stI < 0) {
				Error = true;
				return;
			}
			--stI;
		}
		else if (scmp(ins[i].instruc, "INV")) {
			if (stI < 0) {
				Error = true;
				return;
			}
			st[stI] = -st[stI];
		}
		else if (scmp(ins[i].instruc, "DUP")) {
			if (stI < 0) {
				Error = true;
				return;
			}
			stI++;
			st[stI] = st[stI - 1];
		}
		else if (scmp(ins[i].instruc, "SWP")) {
			if (stI < 1) {
				Error = true;
				return;
			}
			swap(st[stI], st[stI - 1]);
		}
		else if (scmp(ins[i].instruc, "ADD")) {
			if (stI < 1) {
				Error = true;
				return;
			}
			st[stI - 1] += st[stI];
			stI--;
		}
		else if (scmp(ins[i].instruc, "SUB")) {
			if (stI < 1) {
				Error = true;
				return;
			}
			st[stI - 1] -= st[stI];
			stI--;
		}
		else if (scmp(ins[i].instruc, "MUL")) {
			if (stI < 1) {
				Error = true;
				return;
			}
			st[stI - 1] *= st[stI];
			stI--;
		}
		else if (scmp(ins[i].instruc, "DIV")) {
			if (stI < 1 || st[stI] == 0) {
				Error = true;
				return;
			}
			int sign = (st[stI - 1] * st[stI]) < 0 ? 1 : 0;
			ll share = ab(st[stI - 1]) / ab(st[stI]);
			st[stI - 1] = (sign) ? -share : share;
			stI--;
		}
		else if (scmp(ins[i].instruc, "MOD")) {
			if (stI < 1 || st[stI] == 0) {
				Error = true;
				return;
			}
			int sign = (st[stI - 1]) < 0 ? 1 : 0;
			ll rest = ab(st[stI - 1]) % ab(st[stI]);
			st[stI - 1] = (sign) ? -rest : rest;
			stI--;
		}
		else if (scmp(ins[i].instruc, "END")) break;
	}
}

int main() {
	fastio();
	char str[5];
	ll tmp = 0;
	while (1) {
		insI = 0;
		while (1) {
			cin >> str;
			if (scmp(str, "QUIT")) break;
			else if (scmp(str, "NUM")) {
				cin >> tmp;
				ins[insI] = Ins(str, tmp);
			}
			else if (scmp(str, "END")) {
				ins[insI] = Ins(str, 0);
				insI++;
				break;
			}
			else ins[insI] = Ins(str, 0);
			insI++;
		}
		if (scmp(str, "QUIT")) break;
		cin >> N;
		ll in = 0;
		for (int i = 0; i < N; i++) {
			cin >> in;
			stI = 0;
			st[0] = in;
			Error = false;
			solve();
			if (Error || (stI != 0) || st[stI] > INF || st[stI] < -INF) {
				cout << "ERROR" << '\n';
				continue;
			}
			cout << st[0] << '\n';
		}
		cout << '\n';
	}
	return 0;
}