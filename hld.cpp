int chainId[MAXN], chainHead[MAXN], pos[MAXN];
int aktChain=1, aktPos=0;

void init_hld() {
	memset(chainId, -1, sizeof chainId);
	memset(chainHead, -1, sizeof chainHead);
	memset(pos, -1, sizeof pos);
}

void hld(int x) {
	chainId[x]=aktChain;
	pos[x]=aktPos++;
	if(chainHead[aktChain]==-1) {
		chainHead[aktChain]=x;
	}
	
	int mxChild=-1;
	for(auto i:adj[x]) {
		if(par[i]==x) continue;
		if(mxChild==-1 || sz[mxChild]<sz[i]) mxChild = i;
	}
	
	if(mxChild!=-1) {
		hld(mxChild);

		for(auto i:adj[x]) {
			if(par[i]==x || mxChild==i) continue;
			aktChain++;
			hld(i);
		}
	}
}
