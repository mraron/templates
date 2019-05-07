//hld code to test
int pos[MAXN];
int root[MAXN];

int curr_pos=0;
void hld(int x, int id) {
	pos[x]=curr_pos++;
	root[x]=id;
	
	int best_child=-1;
	for(auto i_:adj[x]) {
		auto i=i_.xx;
		if(par[x]!=i) {
			if(best_child==-1 || sz[best_child]<sz[i]) {
				best_child=i;
			}
		}
	}
	
	if(best_child==-1) {
		return ;
	}
	
	hld(best_child, id);
	
	for(auto i_:adj[x]) {
		auto i=i_.xx;
		if(par[x]==i || i==best_child) continue ;
		hld(i, i);
	}
}

int query_up(int up, int down, function<void(int,int,int&)> query_func) {
	int ans=0;
	while(1) {
		if(root[up]==root[down]) {
			query_func(pos[up], pos[down], ans);
			break ;
		}else {
			query_func(pos[root[down]], pos[down], ans);
			down=par[root[down]];
		}
	}
	return ans;
}

int query(int a, int b, function<void(int,int,int&)> query_func) {
	auto l=lca2(a,b);
	if(l.xx==l.yy) {
		return query_up(l.xx, (lvl[a]<lvl[b]?b:a), query_func);
	}
	return max(query_up(l.xx, a, query_func), query_up(l.yy, b, query_func));
}
