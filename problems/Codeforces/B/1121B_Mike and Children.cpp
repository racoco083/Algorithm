/*
 *  시간복잡도 : O(N^2)
 *
 *  (문제 설명)
 *  N개의 숫자는 서로 다르다. 이 숫자들 중에 두개의 쌍의 합이 같은 것의
 *  최대 개수를 구하라.
 *
 *  (풀이)
 *  두 개의쌍으로 만들 수 있는 모든 수를 이중 포문으로 만들어가며
 *  만든 숫자를 인덱스로 하여 chk배열의 값을 증가시킨다.
 *  chk배열 안에 있는 값 중 가장 큰 값이 곧 답이다.
 *
 *  처음에 이분탐색으로 풀 수 있을 것 같았는데 가능은 한데 구현하다
 *  틀렸다. 가능은 할 듯 시간복잡도는 O(Nlog20000)이다.
 *  
 */
#include <iostream>
#include <algorithm>
using namespace std;
#define MXN 1000

int N;
int arr[MXN + 1];
int chk[200002];

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> arr[i];
	for (int i = 0; i < N-1; i++) 
		for (int j = i+1; j < N; j++) 
			chk[arr[i] + arr[j]]++;
		
	sort(chk, chk + 200001);
	cout << chk[200000];
	return 0;
}