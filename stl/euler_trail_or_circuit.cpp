
//오일러 서킷 : 깊이 우선 탐색을 이용해 풀 수 있는 또 다른 유명한 문제로, 그래프의
//모든 간선을 정확히 한 번씩 지나서 시작점으로 돌아오는 경로를 오일러 서킷이라한다.
//무향 그래프에서 오일러 서킷이 존재하려면 모든 정점에 차수가 짝수여야 한다.
//방향 그래프에서 오일러 서킷이 존재하려면 각 정점에 들어오는 간선의 수와 나가는
//간선의 수가 같아야만 합니다. 

//오일러 트레일 : 오일러 서킷처럼 그래프의 모든 간선을 정확히 한 번씩 지나지만, 시작점과
//끝점이 다른 경로를 오일러 트레일이라고 합니다.

//방향 그래프에서 오일러 트레일이 있으려면 나가는 간선이 하나 많은 시작점이 하나, 들어오는
//간선이 하나 많은 끝점이 하나 있어야 합니다. 나머지 간선은 나가는 간선, 들어오는 간선의
//수가 같아야 합니다. 이 조건이 만족되는 경우에도 그래프가 두 개
//이상으로 분리되어 있다면 오일러 서킷/트레일을 찾을 수 없으므로 마지막에 모든 간선을
//방문했는지 확인한다는 점 또한 눈여겨 보세요.

vector<string> words = { "dog", "god", "dragon", "peed" };
vector<vector<int>> adj;
vector<string> graph[26][26];

vector<int> indegree, outdegree;
void makeGraph(const vector<string>& words) {
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			graph[i][j].clear();
	adj = vector<vector<int>>(26, vector<int>(26, 0));
	indegree = outdegree = vector<int>(26, 0);
	for (int i = 0; i < words.size(); i++) {
		int a = words[i][0] - 'a';
		int b = words[i][words[i].size() - 1] - 'a';
		graph[a][b].push_back(words[i]);//graph[a][b] = words[i];
		adj[a][b]++;
		outdegree[a]++;
		indegree[b]++;
		//dog를 예로들면 d에서 나와서 g로 들어간다.
		//각 알파벳을 d, g, d, n, p, d 정점으로 보는 거다.
	}
}

void getEulerCircuit(int here, vector<int>& circuit) {
	for (int there = 0; there<adj.size(); there++)
		while (adj[here][there] > 0) {
			adj[here][there]--;
			getEulerCircuit(there, circuit);
		}
	circuit.push_back(here);
}

vector<int> getEulerTrailOrCircuit() {
	vector<int> circuit;
	//우선 트레일을 찾아본다
	for (int i = 0; i < 26; i++) {
		if (outdegree[i] == indegree[i] + 1) {
			getEulerCircuit(i, circuit);
			return circuit;//이 부분을 빼먹는 실수를 하네 조심하자
						   //이 부분을 안 넣으면 밑에서 또 검사가 되어 
						   //circuit에 들어가게 되고 결과
						   //circuit.size() != words.size()+1이 아니게 되고 
						   //무조건 impossble을 출력한다.
		}
	}
	//아니면 서킷이니, 간선에 인접한 아무 정점에서나 시작한다.
	for (int i = 0; i < 26; i++) {
		if (outdegree[i]) {
			getEulerCircuit(i, circuit);
			return circuit;//이 부분을 빼먹는 실수를 하네 조심하자
		}
	}
	//모두 실패한 경우 빈 배열을 반환한다.
	return circuit;
}

bool checkEuler() {
	int plus1 = 0, minus1 = 0;
	for (int i = 0; i < 26; i++) {
		int delta = outdegree[i] - indegree[i];
		//모든 정점의 차수는 -1, 1, 0 이어야 한다.
		if (delta < -1 || 1 < delta) return false;
		if (delta == 1)plus1++;
		if (delta == -1) minus1++;
	}
	return (plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0);
}

string solve(const vector<string>& words) {
	makeGraph(words);
	if (!checkEuler()) return "IMPOSSIBLE";
	vector<int> circuit = getEulerTrailOrCircuit();
	for (int i = 0; i < circuit.size(); i++)
		cout << circuit[i] << " ";
	//모든 간선을 방문하지 못했으면 실패!
	//오일러 서킷이 두개인 두 개의 그래프 같은 경우를 예방하기 위해서다.
	//한 오일러 서킷만 검사를 하게 되고 circuit안에는 한 오일러서킷 정점들만
	//가지고 있게 된다.
	if (circuit.size() != words.size() + 1) return "IMPOSSIBLE";
	reverse(circuit.begin(), circuit.end());
	string ret;
	for (int i = 1; i < circuit.size(); i++) {
		int a = circuit[i - 1], b = circuit[i];
		if (ret.size()) ret += " "; //흠 천재다 이걸 이렇게 간단하게.
		ret += graph[a][b].back();
		graph[a][b].pop_back();
	}
	return ret;
}

void main() {
	cout << solve(words);
}//이 코드의 시간 복잡도는 오일러 트레일을 찾는 함수에 의해 지배됩니다. 그래프를
 //만드는 과정과 답으로 출력할 문자열을 만드는 과정은 모두 단어의 수에 비례하는 시간이
 //걸리는데, 오일러 트레일을 찾는 함수의 수행 시간은 알파벳의 수A와 
 //단어의 수 n의 곱에 비례하기 때문이지요. 따라서 전체 시간 복잡도는 O(nA)가 됩니다.
