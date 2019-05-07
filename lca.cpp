const int MAXN=100001, hgt=22;
// to make it compatible with hld implementation we also calculate sz
int par[MAXN], b[MAXN], lvl[MAXN], sz[MAXN];
int dp[MAXN][hgt];

void dfs_lca(int x) {
	b[x]=1;
	sz[x]=1;
	
	for(auto i:adj[x]) {
		if(!b[i]) {
			par[i]=x;
			lvl[i]=lvl[x]+1;
			dfs_lca(i);
			sz[x]+=sz[i];
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
	if(p==q) return p;
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


pair<int,int> lca2(int& a, int& b) {
	int p=a, q=b;
	if(lvl[p]>lvl[q]){
		 swap(p,q);
		 swap(a,b);
	 }
	for(int i=hgt-1;i>=0;i--) {
		if(dp[q][i]!=-1 && lvl[p]<lvl[dp[q][i]]) q=dp[q][i];
	}
	
	if(lvl[p]!=lvl[q]) {
		if(p==par[q]) return {q,q};
		q=par[q];
	}
	
	assert(lvl[p]==lvl[q]);
	for(int i=hgt-1;i>=0;i--) {
		if(dp[q][i]!=-1 && dp[q][i]!=dp[p][i]) {
			p=dp[p][i];
			q=dp[q][i];
		}
	}
	
	return {p,q};
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
