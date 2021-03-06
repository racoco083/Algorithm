class Comparator {
public:
	vector<int>& group;
	int t;
	Comparator(vector<int>& _group, int _t) : group(_group), t(_t) {
		group = _group;
		t = _t;
	}
	bool operator() (int a, int b) {
		//cout << a << " " << b << endl;
		if (group[a] != group[b]) return group[a] < group[b];
		return group[a + t] < group[b + t];
	}
	//group[a+t]와 group[a+b]가 무조건 배열 범위 밖일수 있는데 신경쓰지 않아도 된다.
	//이 경우 a+t와 b+t는 최대n이다. 따라서 group[n]을 아죽 작은 값으로 두면 
	//group[9]는 i이고 group[7]은 ipi의 i이다 이때 t가 2라면 group[9+2]는 무조건
	//group[10]의 값을 보게되고 group[7+2]는 group[9]의 값을 보게된다.
};

vector<int> getSuffixArray(const string& s) {
	int n = s.size();
	int t = 1;

	vector<int> group(n + 1);
	for (int i = 0; i < n; i++) group[i] = s[i];
	group[n] = -1;//0을 넣어도 상관없는데 쓰지 않는 공간이라 -1을 넣어놓음
				  //Comparator가 group[n]에 접근하기 때문에 필요하다. 그룹의 크기를 
				  //group(n+1)로 한거다.
	vector<int> perm(n);
	for (int i = 0; i < n; i++) perm[i] = i;
	while (t < n) {
		Comparator compareUsing2T(group, t);
		sort(perm.begin(), perm.end(), compareUsing2T);
		//group[perm[i]]값을 오름차순으로 정렬하면서 이때의 group의 인덱스인 perm[i]값
		//compareUsing2T(perm[i - 1], perm[i])위의 식은 이거랑 같게 compareUsing2T(perm.begin()~perm.end())
		//이럭식으로 해석하면 된다. 전체배열을 다 비교한다는데서 다르긴하지만 이런느낌이다.
		t *= 2;//이 값이 적용되는 순간은 Comparator compareUsing2T(group, t);후이다. 그래서 밑의 식에서는 이 값 이전의 t를 사용한다.
		if (t >= n) break;
		vector<int> newGroup(n + 1);
		newGroup[n] = -1;
		newGroup[perm[0]] = 0;
		for (int i = 1; i < n; i++) {
			if (compareUsing2T(perm[i - 1], perm[i]))
				newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;//다른 그룹
			else
				newGroup[perm[i]] = newGroup[perm[i - 1]];//같은 그룹
														  //이미 t에 대해서 오름차순으로 sort가 되어있다 그래서 group[a] > group[b]나 group[a+t] > group[b+t]에 대해서는
														  //생각할 필요가 없고 if문이 true가 나오면 group[a] < group[b] or group[a+t]<group[b+t]가 되는것이고
														  //false가 나오는 것은 이 접미사 문자열이 a~t까지 b~t까지 같다는 것을 의미한다.
		}
		//이렇게 그룹을 t값에 따라 사전순이 낮을수록 우선순위가 높게 정해
		//그룹을 만들면 위에서 sort시에 2*t값에 따라 다른 그룹을 방문하게 되고 
		//이 그룹은 벌써 자기인덱스a+2*t, b+2*t에서부터 +t까지를 정렬해 놓은 상태이다
		//그래서 group[a+2*t]에 접근하면 group[a+2*t+t]까지는 정렬된 상태이다. 
		//t가 문자열길이보다 같거나 커질때까지 반복하면 모든 접미사 문자열에 대해서
		//정렬이 된다.
		group = newGroup;
	}
	return perm;
}

int commonPrefix(const string& s, int i, int j) {
	int k = 0;
	while (i < s.size() && j < s.size() && s[i] == s[j]) {
		i++; j++; k++;
	}
	return k;
}

int countSubstring(const string& s) {
	int n = s.size();
	vector<int> a = getSuffixArray(s);
	int cp;
	int ret = 0;
	for (int i = 0; i < a.size(); i++) {
		cp = 0;
		if (i > 0) cp = commonPrefix(s, a[i - 1], a[i]);
		ret += n - a[i] - cp;
		//banana에서 i가 5인 접미사a의 
		//앞에오는 문자의 개수는 a[i]개이다 
		cout << ret << endl;
	}
	return ret;
}

int main() {
	countSubstring("banana"); //답은 15다
}