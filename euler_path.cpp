struct EulerPath {
	int n,eid;
	bool dir;
	vector<vector<pair<int,int>>> adj;
	vector<int> indeg, outdeg;
	EulerPath(int n_, bool dir_=false) : n(n_), eid(0), dir(dir_), adj(n_+1), indeg(n_+1), outdeg(n_+1) {
		
	}
	
	void add_edge(int a, int b) {
		adj[a].push_back({b,eid});outdeg[a]++;indeg[b]++;
		if(!dir) adj[b].push_back({a,eid});
		eid++;
	}
	
	vector<int> find(int from) {
		bool ok=true;
		if(!dir) {
			int cnt=0;
			int is_from=0;
			for(int i=1;i<=n;++i) {
				if(adj[i].size()&1) {
					cnt++;
					if(i==from) is_from=1;
				}
			}
			
			if(cnt==0) ok=true;
			else if(cnt==2) {
				ok=is_from;
			}else {
				ok=false;
			}
		}else {
			vector<int> st,en;
			for(int i=1;i<=n;++i) {
				if(indeg[i]!=outdeg[i]) {
					if(abs(indeg[i]-outdeg[i])!=1) ok=false;
					else if(indeg[i]>outdeg[i]) {
						en.push_back(i);
					}else {
						st.push_back(i);
					}
				}
			}
			
			ok&=(st.size()==1 && st[0]==from && en.size()==1) || st.size()+en.size()==0;
		}
		
		if(!ok) return {};
		
		vector<int> volt(eid);
		vector<int> ord;
		
		stack<int> st;
		st.push(from);
		
		while(!st.empty()) {
			int x=st.top(); 
			while(!adj[x].empty() && volt[adj[x].back().second]) adj[x].pop_back();
			
			if(!adj[x].empty()) {
				volt[adj[x].back().second]=1;
				st.push(adj[x].back().first);
			}else {
				ord.push_back(x);
				st.pop();
			}
		}
		
		reverse(ord.begin(), ord.end());
		
		return ord;
	}
};
