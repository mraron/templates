struct HunKuhn {
	vector<vector<int>> adj;
	vector<int> L,R;
	vector<int> b;
	
	HunKuhn(int n, int m): adj(n), L(n,-1), R(m,-1), b(n) {
		
	}
	
	void add_edge(int a, int b) {
		adj[a].push_back(b);
	}
	
	bool dfs(int x) {
		if(b[x]) return false;
		b[x]=true;
		for(auto i:adj[x]) {
			if(R[i]==-1 || dfs(R[i])) {
				L[x]=i;
				R[i]=x;
				return true;
			}
		}
		
		return false;
	}
	
	int match() {
		while(1) {
			bool ok=false;
			fill(b.begin(), b.end(), 0);
			for(int i=0;i<(int)L.size();++i) {
				if(L[i]==-1) {
					ok|=dfs(i);
				}
			}
			if(!ok) break ;
		}
		
		int res=0;
		for(int i=0;i<(int)L.size();++i) {
			res+=L[i]!=-1;
		}
		
		return res;
	}
};
