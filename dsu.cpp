struct dsu {
	vector<int> par;
	vector<int> sz;
	dsu(int n) : par(n,-1) {sz.assign(n,1);}
	
	int get(int x) {
		if(par[x]==-1) return x;
		return par[x]=get(par[x]);
	}
	
	void merge(int x, int y) {
		int px=get(x), py=get(y);
		if(px==py) return ;
		
		if(sz[px]>sz[py]) {
			swap(px,py);
			swap(x,y); //:) lyft
		}
		
		sz[py]+=sz[px];
		par[px]=py;
	}
};
