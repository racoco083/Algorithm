// 0123~9876(특정 값을 i라 하겠다.)까지 값 중에 중복되지 않는 값 i를 pv배열에 담아준다.
// num_chk[i]를 true로 두어 가능한 값으로 둔다. pv[i]값을 query에 넣어주면서
// strike1와 ball1값을 구한다. 만약 strike값이 4라면 순서와 값이 다똑같다는 것으로 
// 리턴한다. 아니라면 num_chk[p[i]] 를 false로 두고 pv의 모든 값을 뒤지며
// 이때의 값을 pv[j]라 하겠다. pv[i]와 pv[j]를 비교해서 strike2, ball2를 구한다.
// 만약 strike1 == strike2 && ball1 == ball2가 같다면 입력 받은 숫자4자리 값 a와
// pv[j]값이 같을 수 있다는 말이다. 다르면 pv[j]값은 절대 a와 같을 수 없다.
// a와 pv[i]를 비교해 strike1와 ball1을 구하고 pv[i], pv[j]를 비교해
// strike2와 ball2를 구하기 때문이다.

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

// 중복되지않고 범위안에 들어가는 숫자인지 체크한다.
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

	// 위 코드 통과하면 이제 중복된 값이 아닌 유효한 값이라는 뜻이다.

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