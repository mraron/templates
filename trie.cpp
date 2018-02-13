struct trie {
	int id=1;
	
	int tree[MAXN][SIGMA];
	bool ending[MAXN];
	trie() {
		memset(tree,0,sizeof tree);
	}
	
	#define HASH(x) ((x)-'a')
	
	void insert(string& t) {
		int akt=1;
		for(auto i:t) {
			if(tree[akt][HASH(i)]==0) {
				tree[akt][HASH(i)]=++id;
			}
			
			akt=tree[akt][HASH(i)];
		}
		
		ending[akt]=true;
	}
	
	bool query(string &t) {
		int akt=1;
		for(auto i:t) {
			if(tree[akt][HASH(i)]==0) return false;
			akt=tree[akt][HASH(i)];
		}
		
		return ending[akt];
	}
	
	void remove(string& t) {
		int akt=1;
		for(auto i:t) {
			if(tree[akt][HASH(i)]==0) return ; //nincs benne
			akt=tree[akt][HASH(i)];
		}
		
		ending[akt]=false;
	}
};
