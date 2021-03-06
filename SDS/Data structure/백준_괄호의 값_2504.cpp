/*
 *  일단 괄호가 옳은 괄호인지 체크한다. 옳은 괄호라면
 *  스택과 깊이에 따른 값을 처리할 depth값을 이용해 
 *  열린 괄호이면 깊이를 증가시켜주고, 닫힌 괄호이면
 *  자식괄호의 합에 부모괄호 값을 곱해주면 된다.
 *  예제를 예로들어보자
 *    ( ( ) [ [ ] ] ) ( [ ] ) 
 *  0 (             ) (     )
 *  1   ( ) [     ]     [ ]
 *  2         [ ]
 *  3
 *  열린 괄호 '(' 로 두 번 시작하므로 di는 2가 된다.
 *  이제 닫힌괄호 ')' 를 만났다. depth[di]는 0이니 1로 바꾸고 
 *  부모의 괄호값 2를 곱해준 값을 depth[di-1]에 저장. 사용한 depth[di]를 0으로 만들어 준 후
 *  di를 1감소시켜주며 depth[1] = 2가 된다. '['를 두번 만나니 di가 2증가 
 *  di는 3이 된다. 이제 ']'만나니 depth[di] = 0이므로 1로 바꾸어 주고
 *  부모의 괄호값 3과 곱한 값을 depth[di-1]에 저장. 사용한 depth[di]를 0으로 만들어 준후
 *  di를 1감소시켜주며 depth[2] = 3이 된다. 다시 닫힌 대괄호를 만나니
 *  depth[di] = 0이 아니므로 부모의 괄호값 3과 depth[di==2]를 곱해준 값을 
 *  부모의 자리 depth[di-1]에 저장한다. depth[di]는 사용했으므로 0으로 바꾸어 준 후
 *  di를 1감소시켜준다. 그러면 dpeth[1]에는 11이 들어가 있게 되고 다시 닫힌 괄호 ')'를
 *  만나니 depth[di-1 == 0] = depth[di==1]*2를 해주면 된다. 그러면 depth[0]에는 22가
 *  되어 있고 나머지 ([])도 똑같이 처리해주면 depth[0] = 28이 된다.
 */

#include <iostream>
using namespace std;
#define MXN 33

char str[MXN];
int depth[MXN];// 깊이에 따른 괄호값을 계산하여 저장

int slen(char *a) {
	int len = 0;
	while (a[len]) len++;
	return len;
}

// 괄호가 옳은지 아닌지 체크한다.
bool chk(char str[], int sl) {
	char st[MXN];
	int top = -1;

	for (int i = 0; i < sl; i++) {
		if (str[i] == '(' || str[i] == '[') {
			st[++top] = str[i];
		}
		else {
			if (top == -1) return false;
			// 정 가운데 &&대시 ||연산을 해서 틀렸다. 두 조건 중에 하나라도 false가 된다면 짝기 맞는
			// 현재 괄호 문자까지 짝이 맞는 괄호가 있다는 뜻으로 둘 다 ture가 되어야 맞는 괄호가 없다는 뜻이다.
			else if (!(str[i] == ')' && st[top] == '(') && !(str[i] == ']' && st[top] == '[')) return false;
			top--;
		}
	}
	return top == -1;
}

int main() {
	cin >> str;

	char st[MXN];// 괄호의 문자를 저장한다.
	int top = -1;
	int sl = slen(str);

	if (!chk(str, sl)) {
		cout << 0 << '\n';
		return 0;
	}

	int di = 0;// depth_index
	for (int i = 0; i < sl; i++) {
		// 열린 괄호가 있을 때마다 깊이를 1씩 증가시킨다.
		if (str[i] == '(' || str[i] == '[') {
			st[++top] = str[i];
			di++;
		}
		else {
			// 현재 깊이의 값이 0이면 부모의 괄호'(', '['에 따라 2나 3을 곱해주어야 하는데
			// 자식이 0일 때는 1로 만들어서 곱해준다. 자식에 값이 있을 때는 그 값을 곱해주면 된다.
			if (st[top] == '(') depth[di - 1] += (depth[di] == 0 ? 1 : depth[di]) * 2;
			else if (st[top] == '[') depth[di - 1] += (depth[di] == 0 ? 1 : depth[di]) * 3;
			// 자식 깊이의 값은 사용되었으므로 0으로 만들어주고 깊이를 1감소시킨다.
			depth[di--] = 0;
			top--;
		}
	}
	cout << depth[0] << '\n';
	return 0;
}