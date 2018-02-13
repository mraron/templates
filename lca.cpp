const int maxn=100001, hgt=22;
int par[maxn], b[maxn], lvl[maxn];
int dp[maxn][hgt];

void dfs_lca(int x, int p=-1, int lev=0) {
	b[x]=1;
	par[x]=p;
	lvl[x]=lev;
	
	for(auto i:adj[x]) {
		if(!b[i]) {
			dfs_lca(i,x,lev+1);
		}
	}
	
	b[x]=2;
}

void init_lca() {
	memset(dp, -1, sizeof dp);
	
	for(int i=1;i<=n;++i) {
		dp[i][0]=par[i];
	}
	
	for(int j=1;j<hgt;++j) {
		for(int i=1;i<=n;++i) {
			if(dp[i][j-1]!=-1) {
				dp[i][j]=dp[dp[i][j-1]][j-1];
			}
		}
	}
}

int lca(int p, int q) {
	if(lvl[p]>lvl[q]) swap(p,q);
	for(int i=hgt-1;i>=0;i--) {
		if(dp[q][i]!=-1 && lvl[p]<=lvl[dp[q][i]]) q=dp[q][i];
	}
	
	if(p==q) return p;
	
	for(int i=hgt-1;i>=0;i--) {
		if(dp[q][i]!=-1 && dp[q][i]!=dp[p][i]) {
			p=dp[p][i];
			q=dp[q][i];
		}
	}
	
	return dp[p][0];
}

int kth(int p, int k) {
	for(int i=0;i<hgt;++i) {
		if(k&(1<<i)) {
			p=dp[p][i];
		}
	}
	
	return p;
}

int dist(int a, int b) {
	int l=lca(a,b);
	return lvl[a]+lvl[b]-2*lvl[l];
}
