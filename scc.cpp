int n,m;

vector<int> adj[10001];
vector<int> badj[10001];

int sid=1;
set<int> sadj[10001];
int scc[10001], scc_sz[10001], scc_node[10001];

vector<int> ord;

int b1[10001];
void dfs1(int x) {
	b1[x]=1;
	for(auto i:adj[x]) {
		if(!b1[i]) dfs1(i);
	}
	
	ord.pb(x);
}

int b2[10001];
void dfs2(int x, int comp) {
	b2[x]=1;
	scc[x]=comp;
	scc_sz[comp]++;
	
	for(auto i:badj[x]) {
		if(!b2[i]) dfs2(i, comp);
	}
}

void do_scc() {
	for(int i=1;i<=n;++i) {
		if(!b1[i]) {
			dfs1(i);
		}
	}
	
	while(!ord.empty()) {
		int akt=ord.back();ord.pop_back();
		
		if(!b2[akt]) {
			scc_node[sid]=akt;
			dfs2(akt, sid++);
		}
	}
	
	for(int i=1;i<=n;++i) {
		for(int j:adj[i]) {
			if(scc[i]!=scc[j]) {
				sadj[scc[i]].insert(scc[j]);
			}
		}
	}
}

