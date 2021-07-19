int banned[maxn];
int sz[maxn];
void dfs0(int x, int p=-1) {
	sz[x]=1;
	for(auto i:adj[x]) {
		if(i==p ||  banned[i]) continue ;
		
		dfs0(i, x);
		sz[x]+=sz[i];
	}
}

int dfs1(int x, int p, int nn) {
	int ind=-1;

	for(auto i:adj[x]) {
		if(banned[i] || i==p) continue ;
		if(sz[i]>nn/2) ind=i;
	}
	
	if(ind!=-1) return dfs1(ind, x, nn);
	
	return x;
}


vector<int> cadj[maxn];
int cpar[maxn];
int decompose(int x=1) {
	dfs0(x);
	
	int centroid=dfs1(x,-1,sz[x]);
	banned[centroid]=1;
	
	for(auto i:adj[centroid]) {
		if(!banned[i]) {
			int child=decompose(i);
			cadj[centroid].pb(child);
			cpar[child]=centroid;
		}
	}
	
	return centroid;
}
