// 0123~9876(Ư�� ���� i�� �ϰڴ�.)���� �� �߿� �ߺ����� �ʴ� �� i�� pv�迭�� ����ش�.
// num_chk[i]�� true�� �ξ� ������ ������ �д�. pv[i]���� query�� �־��ָ鼭
// strike1�� ball1���� ���Ѵ�. ���� strike���� 4��� ������ ���� �ٶȰ��ٴ� ������ 
// �����Ѵ�. �ƴ϶�� num_chk[p[i]] �� false�� �ΰ� pv�� ��� ���� ������
// �̶��� ���� pv[j]�� �ϰڴ�. pv[i]�� pv[j]�� ���ؼ� strike2, ball2�� ���Ѵ�.
// ���� strike1 == strike2 && ball1 == ball2�� ���ٸ� �Է� ���� ����4�ڸ� �� a��
// pv[j]���� ���� �� �ִٴ� ���̴�. �ٸ��� pv[j]���� ���� a�� ���� �� ����.
// a�� pv[i]�� ���� strike1�� ball1�� ���ϰ� pv[i], pv[j]�� ����
// strike2�� ball2�� ���ϱ� �����̴�.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define N 4
#define MAX_QUERYCOUNT 1000000

static int digits[N];
static int digits_c[10];

static int T;

extern void doUserImplementation(int guess[]);

static int querycount;

// the value of limit_query will be changed in evaluation
static const int limit_query = 2520;

typedef struct {
	int strike;
	int ball;
} Result;

// �ߺ������ʰ� �����ȿ� ���� �������� üũ�Ѵ�.
static bool isValid(int guess[]) {
	int guess_c[10];

	for (int count = 0; count < 10; ++count) guess_c[count] = 0;
	for (int idx = 0; idx < N; ++idx) {
		if (guess[idx] < 0 || guess[idx] >= 10 || guess_c[guess[idx]] > 0) return false;
		guess_c[guess[idx]]++;
	}
	return true;
}

// API : return a result for comparison with digits[] and guess[]
Result query(int guess[]) {
	Result result;

	if (querycount >= MAX_QUERYCOUNT) {
		result.strike = -1;
		result.ball = -1;
		return result;
	}

	querycount++;

	if (!isValid(guess)) {
		result.strike = -1;
		result.ball = -1;
		return result;
	}

	// �� �ڵ� ����ϸ� ���� �ߺ��� ���� �ƴ� ��ȿ�� ���̶�� ���̴�.

	result.strike = 0;
	result.ball = 0;

	for (int idx = 0; idx < N; ++idx)
		if (guess[idx] == digits[idx])
			result.strike++;
		else if (digits_c[guess[idx]] > 0)
			result.ball++;

	return result;
}

bool num_chk[9877];
int pv[9877];// possible_value
int idx;

void setting() {
	for (int i = 0; i < 9877; i++) num_chk[i] = false;

	idx = 0;
	int a, b, c, d;
	for (int i = 123; i < 9877; i++) {
		a = i / 1000;
		b = i % 1000 / 100;
		c = i % 100 / 10;
		d = i % 10;

		if (a == b || a == c || a == d || b == c || b == d || c == d) continue;
		num_chk[i] = true;
		pv[idx++] = i;
	}
}

Result cmp(int v1, int v2) {
	Result ret;
	ret.strike = 0;
	ret.ball = 0;
	int chk[10] = { 0, };

	for (int i = 0; i < 4; i++) {
		if (v1 % 10 == v2 % 10) ret.strike++;
		else {
			chk[v1 % 10]++;
			chk[v2 % 10]++;
		}
		if (chk[v1 % 10] == 2) ret.ball++;
		if (chk[v2 % 10] == 2) ret.ball++;

		v1 /= 10;
		v2 /= 10;
	}
	return ret;
}

void doUserImplementation(int guess[]) {
	setting();

	for (int i = 0; i < idx; i++) {
		if (!num_chk[pv[i]]) continue;
		guess[0] = pv[i] / 1000;
		guess[1] = pv[i] % 1000 / 100;
		guess[2] = pv[i] % 100 / 10;
		guess[3] = pv[i] % 10;
		Result tmp;
		Result ret = query(guess);

		if (ret.strike == 4) return;
		else num_chk[pv[i]] = false;

		for (int j = 0; j < idx; j++) {
			if (!num_chk[pv[j]]) continue;
			tmp = cmp(pv[i], pv[j]);

			if (tmp.strike != ret.strike || tmp.ball != ret.ball)
				num_chk[pv[j]] = false;
		}
	}
}

static void initialize() {
	for (int count = 0; count < 10; ++count) digits_c[count] = 0;
	for (int idx = 0; idx < N; ++idx) {
		char c;
		do scanf("%c", &c); while (c < '0' || c > '9');
		digits[idx] = c - '0';
		digits_c[digits[idx]]++;
	}

	querycount = 0;
}

static bool check(int guess[]) {
	for (int idx = 0; idx < N; ++idx)
		if (guess[idx] != digits[idx]) return false;
	return true;
}

int main() {
	int total_score = 0;
	int total_querycount = 0;

	// freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	scanf("%d", &T);
	for (int testcase = 1; testcase <= T; ++testcase) {
		initialize();

		int guess[N];
		doUserImplementation(guess);

		if (!check(guess)) querycount = MAX_QUERYCOUNT;
		if (querycount <= limit_query) total_score++;
		printf("#%d %d\n", testcase, querycount);
		total_querycount += querycount;
	}
	if (total_querycount > MAX_QUERYCOUNT) total_querycount = MAX_QUERYCOUNT;
	printf("total score = %d\ntotal query = %d\n", total_score * 100 / T, total_querycount);
	return 0;
}

/*
5
8975
6142
5047
1860
5419
*/

/*
#1 6
#2 8
#3 7
#4 8
#5 7
total score = 100
total query = 36
*/