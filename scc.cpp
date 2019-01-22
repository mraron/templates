struct SCC {
	int n,sid;
	vector<vector<int>> adj;
	vector<vector<int>> badj;
	vector<int> ord;
	vector<int> scc, scc_sz, scc_root, b;
	
	SCC(int n_) : n(n_), sid(1), adj(n_), badj(n_), scc(n_), scc_sz(n_), scc_root(n_), b(n) {}
	
	void clear() {
		sid=0;
		for(auto& i:adj) i.clear();
		for(auto& i:badj) i.clear();
		
		ord.clear();
		scc.assign(n, 0);
		scc_sz.assign(n, 0);
		scc_root.assign(n, 0);
		b.assign(n, 0);
	}
	
	void add_edge(int x, int y) {
		adj[x].push_back(y);
		badj[y].push_back(x);
	}
	
	void dfs1(int x) {
		b[x]=1;
		for(auto i:adj[x]) {
			if(b[i]<=0) dfs1(i);
		}
		
		b[x]=2;
		ord.push_back(x);
	}
	
	void dfs2(int x, int comp) {
		b[x]=3;
		scc[x]=comp;
		scc_sz[comp]++;
		
		for(auto i:badj[x]) {
			if(b[i]<=2) dfs2(i, comp);
		}
		
		b[x]=4;
	}
	
	void do_scc() {
		for(int i=0;i<n;++i) {
			if(b[i]<=0) {
				dfs1(i);
			}
		}
		
		while(!ord.empty()) {
			int akt=ord.back();ord.pop_back();
			
			if(b[akt]<=2) {
				scc_root[sid]=akt;
				dfs2(akt, sid++);
			}
		}
	}

	vector<vector<int>> gen_sadj_linear() {
		vector<vector<int>> scc_cont(n);
		vector<vector<int>> sadj(sid);
		vector<int> last(sid, -1);
		
		for(int i=0;i<n;++i) {
			scc_cont[scc[i]].push_back(i);
		}
		
		for(int i=0;i<sid;++i) {
			for(auto j:scc_cont[i]) {
				for(auto k:adj[j]) {
					if(scc[k]==i) continue ;
					if(last[scc[k]]<i) {
						last[scc[k]]=i;
						sadj[scc[j]].push_back(scc[k]);
					}
				}
			}
		}
		
		return sadj;
	}
	
	vector<set<int>> gen_sadj_nlogn() {
		vector<set<int>> sadj(sid);
		for(int i=0;i<n;++i) {
			for(int j:adj[i]) {
				if(scc[i]!=scc[j]) {
					sadj[scc[i]].insert(scc[j]);
				}
			}
		}
		
		return sadj;
	}
};
