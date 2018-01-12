struct SegTree {
	vector<int> t;
	vector<int> tree;
	vector<int> lazy;
	
	SegTree(vector<int>& t_) {
		t=t_;
		tree.assign(4*sz(t), 0);
		lazy.assign(4*sz(t), -1);
	}
	
	void build() {
		build(1, 0, sz(t)-1);
	}
	
	int query(int i, int j) {
		return query(1, 0, sz(t)-1, i, j);
	}
	
	void update(int i, int j, int val) {
		update(1, 0, sz(t)-1, i, j, val);
	}
	
	void update(int i, int val) {
		updatept(1, 0, sz(t)-1, i, val);
	}
	
	private:
	
	inline int combine(int x, int y) {
		return x+y;
	}
	
	void propogate(int ind, int L, int R) {
		if(lazy[ind]!=-1) {
			if(L==R) {
				tree[ind]=lazy[ind];
			}else {
				tree[ind]=lazy[ind]*(R-L+1);
				lazy[2*ind]=lazy[2*ind+1]=lazy[ind];
			}
			
			lazy[ind]=-1;
		}
	}
	
	void pull(int ind, int L, int R) {
		propogate(2*ind, L, (L+R)/2);
		propogate(2*ind+1, (L+R)/2+1, R);
		tree[ind]=combine(tree[2*ind], tree[2*ind+1]);
	}
	
	void build(int ind, int L, int R) {
		if(L==R) {
			tree[ind]=t[L];
		}else {
			build(2*ind, L, (L+R)/2);
			build(2*ind+1, (L+R)/2+1, R);
			
			pull(ind, L, R);
		}
	}
	
	int query(int ind, int L, int R, int i, int j) {
		if(R<i || j<L) return 0;
		
		propogate(ind, L, R);
		
		if(i<=L && R<=j) return tree[ind];
			
		return combine(query(2*ind, L, (L+R)/2, i, j), query(2*ind+1, (L+R)/2+1, R, i, j));
	}
	
	void update(int ind, int L, int R, int i, int j, int val) {
		if(R<i || j<L) return ;
		
		propogate(ind, L, R);
		
		if(i<=L && R<=j) {
			lazy[ind]=val;
			propogate(ind, L, R);

			return ;
		}
		
		update(2*ind, L, (L+R)/2, i, j, val);
		update(2*ind+1, (L+R)/2+1, R, i, j, val);
		
		pull(ind, L, R);
	}
	
	void updatept(int ind, int L, int R, int i, int val) {
		if(R<i || i<L) return ;
		
		propogate(ind, L, R);
		
		if(L==R) {
			lazy[ind]=val;
			propogate(ind, L, R);
			
			return ;
		}
		
		updatept(2*ind, L, (L+R)/2, i, val);
		updatept(2*ind+1, (L+R)/2+1, R, i, val);
		
		pull(ind, L, R);
	}
};
