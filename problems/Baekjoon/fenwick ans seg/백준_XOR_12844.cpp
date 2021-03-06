/*
 *  BOJ 12844. XOR
 *
 *  시간복잡도 : O(MlogN)
 *
 *  a xor b xor c xor c == (a xor c) xor (b xor c) == a xor b
 *  a xor 0 == a, a xor a == 0
 *  위의 식을 통해 어떤 값 a에 xor c를 짝수번 하면 그 값은 a이다.
 *  그러므로 짝수번이면 xor해 줄 필요가 없고 홀수번일 때는 xor c를
 *  한 번만 해주면 된다. xor을 뺀 나머지 설명은 구간 합 구하기2의 설명과
 *  똑같다. 그리고 입력 값 a가 b보다 클 수 있으므로 swap을 해주어야 한다!
 *  
 */
#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
using namespace std;
#define MXN 500002

int N, M;
int arr[MXN+2];// 항상 +1을 해 주어 런타임 에러 조심하자
int tree[MXN * 4];
int lazy[MXN * 4];

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

// 초기화
int init(int idx, int s, int e) {
	if (s == e) return tree[idx] = arr[s];
	int m = (e + s) / 2;
	return tree[idx] = init(idx * 2, s, m) ^ init(idx * 2 + 1, m + 1, e);
}

// 일 처리 전파
// int m = (e + s) / 2;
// if ((m - s + 1) % 2)lazy[idx * 2] ^= lazy[idx];
// if ((e - m) % 2)lazy[idx * 2 + 1] ^= lazy[idx];
// ul함수에서 위와 같이 코드를 짜서 틀렸다. 전파는 자식으로 무조건 되어야 한다.
// 자식으로 전파되다가 홀수인 구간이 있을수도 짝수인 구간이 있을수도 있기 때문이다.
// if ((e - s + 1) % 2) tree[idx] ^= lazy[idx]; 이렇게 tree를 갱신할 때만
// 구간의 개수가 홀수개이면 xor를 한 번 해 주면 된다.
void ul(int idx, int s, int e) {// update_lazy
	if (lazy[idx] == 0) return;
	if ((e - s + 1) % 2) tree[idx] ^= lazy[idx];
	if (s != e) {
		lazy[idx * 2] ^= lazy[idx];
		lazy[idx * 2 + 1] ^= lazy[idx];
	}
	lazy[idx] = 0;
}

// 해당 구간의 값들을 c로 xor 해 준다.
void ur(int idx, int s, int e, int l, int r, int diff) {// update_range
	ul(idx, s, e);
	if (e<s || e<l || r<s) return;
	if (l <= s && e <= r) {
		if ((e - s + 1) % 2) tree[idx] ^= diff;
		if (s != e) {
			lazy[idx * 2] ^= diff;
			lazy[idx * 2 + 1] ^= diff;
		} 
		return;
	}
	int m = (e + s) / 2;
	ur(idx * 2, s, m, l, r, diff);
	ur(idx * 2 + 1, m + 1, e, l, r, diff);
	tree[idx] = tree[idx * 2] ^ tree[idx * 2 + 1];
}

// 해당 구간의 xor한 값을 얻는다.
int get_ans(int idx, int s, int e, int l, int r) {
	ul(idx, s, e);
	if (e<s || l>e || r < s) return 0;
	if (l <= s && e <= r) return tree[idx];
	int m = (e + s) / 2;
	return get_ans(idx * 2, s, m, l, r) ^ get_ans(idx * 2 + 1, m + 1, e, l, r);
}

int main() {
	fastio();
	cin >> N;
	for (int i = 0; i < N; i++) cin >> arr[i];
	init(1, 0, N - 1);
	cin >> M;
	int t, a, b, c;
	while (M--) {
		cin >> t >> a >> b;
		if (a > b) swap(a, b);
		if (t == 2) {// 출력 
			cout << get_ans(1, 0, N - 1, a, b) << '\n';
		}
		else {// 업데이트
			cin >> c;
			ur(1, 0, N - 1, a, b, c);
		}
	}
	return 0;
}