/*
 *  시간복잡도 : O(N)
 *
 *  (문제 설명)
 *  문자열 S와 T가 주어진다. S의 1과 0의 갯수는 바꾸지 않으면서
 *  순서는 자유롭게 바꿀 수 있다. 이때 T의 패턴의 개수를 최대화
 *  할 수 있는 문자열을 만드시오. 예를 들어 S = "1111000"
 *  T = "101"이라고 하면 답은 1010101 이다.
 *
 *  (풀이)
 *  S의 각 1을 개수와 0의 개수를 세어 놓는다. 이걸 이용해서
 *  T를 출력할 수 있는만큼 최대한을 출력하고 남은 1과 0은
 *  뒤에 아무렇게나 출력한다.
 *  하지만 문제설명의 예제에서 처럼 패턴이 101이면
 *  101101.. 이렇게 되어 틀리게 된다. 그래서 kmp를 이용해
 *  T의 반복되는 부분을 없앤다. 101이면 fail함수는 0,0,1이 되고
 *  맨 뒤에 한 칸을 없앤다. 그러면 T는 10으로 바뀌고 이렇게
 *  T를 바꾸고 풀면 풀린다.
 *  
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int chk[2];
string s, t;

// const string& N 이렇게 해서 틀렸다.
vector<int> getPartialMatch(const string N) {
	int m = N.size();
	vector<int> pi(m, 0);
	int matched = 0;
	int begin = 1;
	while (matched + begin < m) {
		if (N[begin + matched] == N[matched]) {
			matched++;
			pi[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0)
				begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}

int main() {
	cin >> s >> t;
	for(int i=0; i<s.size(); i++){
		if (s[i] == '1') chk[1]++;
		else chk[0]++;
	}
	int cnt = 0;
	vector<int> fail = getPartialMatch(t);
	int ret = fail[t.size() - 1];
	if (ret) t = t.substr(0, t.size() - ret);
	
	while (cnt < s.size()) {
		for (int i = 0; i < t.size(); i++) {
			cnt++;
			// 맨 아래 코드에서 while (chk[0]--)이 있기 때문에
			// 밑의 코드에서도 if(chk[t[i] - '0']--)를 하면
			// 맨 아래 코드에서는 chk[0]이 -1이 될 수 있고
			// 이것은 오류를 범한다.
			// 그래서 while(chk[0]--)라는 코드가 두 개 이상
			// 있는 경우를 조심하자!
			if (chk[t[i] - '0'] > 0) {
				chk[t[i] - '0']--;
				cout << t[i];
			}
			else break;
		}
	}
	while (chk[0]--) cout << 0;
	while (chk[1]--) cout << 1;
	return 0;
}
