/*
 *  시간복잡도 : O(N)
 *
 *  (문제 설명)
 *  입력으로 받은 문자열에서 부분문자열 하나를 지워서 모든 알파벳이 같거나 없게
 *  만들 수 있는 부분 스트링의 개수를 출력하라.
 *
 *  (풀이)
 *  밑에 코드와 함께 설명 참조!
 *  
 */
#include <iostream>
#include <string>
using namespace std;
#define MOD 998244353
// 곱하면 ll까지 되는데 이것때문에 몇 번 틀렸다.
typedef long long ll;

ll N, p, s;// prefixcnt, suffixcnt
string str;

int main() {
	cin >> N >> str;
	// 앞에서 연속한 알파벳의 개수 p
	// 뒤에서 연속한 알파벳의 개수 s
	for (; p<N&&str[0] == str[p]; p++);
	for (; s<N&&str[N - 1] == str[N - s - 1]; s++);
	// 앞과 뒤가 다르면 atbb같은 경우
	if (str[0] != str[N - 1]) cout << (p + s + 1) % MOD;
	// 모둔 문자의 알파벳이 같은 경우 알파벳을 하나만 지우는 경우 + 
	// 두개만 지우는 경우 + 세개만 지우는 경우 ... + N개 다 지우는 경우
	else if (p + s >= N) cout << (N * (N + 1) / 2) % MOD;
	// aabtyaa일때는 총 3*3으로 답이 9이다. aa(bty), (bty)aa를 지우는 것을 다 신경써준걸
	// 곱해주면 된다. bty같은 지워야 할 중간 서브스트링은 한개로 치면 된다.
	// bty를 b로 보면 aab, baa이고 aab부터 하면 aab, ab, b를 지우면 되고
	// baa는 b, ba, baa를 지우면 된다. 각 개수 3*3을 해 주면 된다.
	// 그러면 aab*b = aab, ab, b가 되고(b와 b가 곱해져도 서브스트링으로 하나로 쳐 진다.)
	// aab * ba = aaba, ab*ba = aba, ba,
	// aab * baa = aabaa, ab*baa = abaa, baa
	// 로 총 9개가 된다.
	else cout << (p + 1)*(s + 1) % MOD;
	return 0;
}
/*
5
aabaa
*/ //답 9