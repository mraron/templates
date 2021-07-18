struct trie {
	int id=1;
	
	int tree[MAXN][SIGMA];
	int sz[MAXN];
	trie() {
		clear();
	}
	
	void clear() {
		id=1;
		memset(tree,0,sizeof tree);
		memset(sz,0,sizeof sz);
	}
	
	int size() {
		return id;
	}
	
	#define HASH(x) ((x)-'a')
	
	void insert(string& t) {
		int akt=1;
		for(auto i:t) {
			if(tree[akt][HASH(i)]==0) {
				tree[akt][HASH(i)]=++id;
			}
			
			sz[akt]++;
			akt=tree[akt][HASH(i)];
		}
		
		sz[akt]++;
	}
	
	bool query(string &t) {
		int akt=1;
		for(auto i:t) {
			if(sz[tree[akt][HASH(i)]]==0) return false;
			akt=tree[akt][HASH(i)];
		}
		
		return sz[akt]>0;
	}
	
	void remove(string& t) {
		int akt=1;
		for(auto i:t) {
			if(sz[tree[akt][HASH(i)]]==0) {
				return ; //nincs benne
			}
			
			sz[akt]--;
			akt=tree[akt][HASH(i)];
		}
		
		sz[akt]--;
	}
	
	#define BITS 18
	void insert_bits(int x) {
		int akt=1;
		for(int i=BITS;i>=0;i--) {
			int bit=(x&(1<<i))!=0;
			if(tree[akt][bit]==0) {
				tree[akt][bit]=++id;
			}
			sz[akt]++;
			akt=tree[akt][bit];
		}		
		sz[akt]++;
	}
	
	void remove_bits(int x) {
		int akt=1;
		for(int i=BITS;i>=0;i--) {
			int bit=(x&(1<<i))!=0;
			if(tree[akt][bit]==0) {
				return ;
			}
			sz[akt]--;
			akt=tree[akt][bit];
		}		
		sz[akt]--;
	}
	
	int biggest_xor_with(int x) {
		int opt=0;
		int akt=1;
		for(int i=BITS;i>=0;i--){
			int bit=(x&(1<<i))!=0;
			if(bit==1 && sz[tree[akt][0]]) {
				akt=tree[akt][0];
			}else if(bit==0 && sz[tree[akt][1]]) {
				opt|=1<<i;
				akt=tree[akt][1];
			}else {
				if(sz[tree[akt][0]]) akt=tree[akt][0];
				else if(sz[tree[akt][1]]) {
					opt|=1<<i;
					akt=tree[akt][1];
				}
				else return x;
			}
		}
		return opt;
	}
};
