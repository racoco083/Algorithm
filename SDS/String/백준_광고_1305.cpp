/*
 *  BOJ 1305. 광고
 *
 *  시간복잡도 : O(문자열 길이)
 *
 *  가능한 광고의 최소길이를 출력하는 문제로 길이 L이 주어지면 이 문자열에서
 *  접미사와 접두사의 최대길이를 L에 빼준 것이 정답이다. aabaaa를 예로들면
 *  접두사 aa와 접미사 aa가 서로 같으면서 최대길이가 된다. 이 말은
 *  접미사는 시간이 지나면 접두사가 된다는 뜻으로 이 길이에서 접미사 aa를 삭제해
 *  aaba가 되던가 접두사 aa를 삭제해 baaa가 가능한 광고의 최소길이가 된다.
 *  둘 다 길이는 4로 같다 그래서 4를 출력해주면 된다.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> getPartial(const string &S) {
	int sz = S.size();
	int begin = 1, matched = 0;
	vector<int> ret(sz, 0);
	while (begin + matched < sz) {
		if (S[begin + matched] == S[matched]) {
			matched++;
			ret[begin + matched - 1] = matched;
		}
		else {
			if (!matched) begin++;
			else {
				begin += matched - ret[matched - 1];
				matched = ret[matched - 1];
			}
		}
	}
	return ret;
}

int main() {
	int L;
	string S;
	cin >> L;
	cin >> S;
	vector<int> f = getPartial(S);
	cout << L - f[L - 1] << '\n';
}
