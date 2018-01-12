int par[MAXN], sz[MAXN];

void init() {
	memset(par, -1, sizeof par);
	FORN(i, MAXN) sz[i]=1;
}

int get(int x) {
	if(par[x]==-1) return x;
	return par[x]=get(par[x]);
}

void merge(int x, int y) {
	int px=get(x), py=get(y);
	
	if(px==py) return ;
	
	if(sz[px]>sz[py]) swap(px, py);
	
	par[px]=py;
	sz[py]+=sz[px];
}


