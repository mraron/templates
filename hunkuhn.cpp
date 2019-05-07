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
	
	vector<int> vL, vR;
	void dfs2(int x) {
		if(vL[x]) return ;
		
		vL[x]=1;
		for(int i:adj[x]) {
			if(!vR[i]) {
				
				vR[i]=1;
				if(R[i]!=-1) dfs2(R[i]);
			}
		}
	}
	
	pair<vector<int>,vector<int>> minimal_vertex_cover() {
		int n=L.size(), m=R.size();

		vL.assign(n, 0);
		vR.assign(m, 0);
	
		for(int i=0;i<n;++i) {
			if(L[i]==-1) dfs2(i);
		}
		
		pair<vector<int>, vector<int>> res;
		
		for(int i=0;i<n;++i) {
			if(!vL[i]) res.xx.pb(i);
		}
		
		for(int i=0;i<m;++i) {
			if(vR[i]) res.yy.pb(i);
		}
		
		return res;
	}
};
