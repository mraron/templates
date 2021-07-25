#include "../template.hpp"

struct segtree {
	struct node {
		ll a = 0, lazy = 0; //default value
		
		node() {}
		node(ll a) : a(a) {}
		
		void apply(int L, int R, ll x) {
			a+=x*(R-L+1);
		}

		node operator+(const node& b) {
			const node& a=*this;
			
			node res(a.a+b.a);
			return res;
		} 
	};

	void push(int ind, int L, int R) {
		if(tree[ind].lazy!=0) {
			tree[ind].apply(L, R, tree[ind].lazy);
			if(L!=R) {
				tree[2*ind].lazy+=tree[ind].lazy;
				tree[2*ind+1].lazy+=tree[ind].lazy;
			}
			
			tree[ind].lazy=0;
		}
	}

	inline void pull(int ind, int L, int R) {
		tree[ind]=tree[2*ind]+tree[2*ind+1];
	}

	int n;
	vector<node> tree;
	
	segtree(int n) : n(n) {
		tree.resize(4*n, node{});
	}
	
	void build() {
		build(1, 0, n-1);
	}
	
	void build(int ind, int L, int R, const vector<ll>& arr) {
		if(L==R) {
			tree[ind].apply(L, R, arr[L]);
		}else { 
			build(2*ind, L, (L+R)/2, arr);
			build(2*ind+1, (L+R)/2+1, R, arr);
			
			pull(ind, L, R);
		}
	}

	void build(int ind, int L, int R) {
		if(L!=R) { 
			build(2*ind, L, (L+R)/2);
			build(2*ind+1, (L+R)/2+1, R);
			
			pull(ind, L, R);
		}
	}
	
	node query(int i, int j) {
		return query(1, 0, n-1, i, j);
	}
	
	void incr(int i, int j, int x) {
		incr(1, 0, n-1, i, j, x);
	}
	
	node query(int ind, int L, int R, int i, int j) {
		if(R<i||j<L) return node{};
		push(ind, L, R);
		
		if(i<=L && R<=j) {
			return tree[ind];
		}
		
		return query(2*ind, L, (L+R)/2, i, j)+query(2*ind+1, (L+R)/2+1, R, i, j);
	}
	
	
	void incr(int ind, int L, int R, int i, int j, int x) {
		push(ind, L, R);
		if(R<i||j<L) return ;
		
		if(i<=L && R<=j) {
			tree[ind].lazy+=x;
			push(ind, L, R);
			return ;
		}
		
	
		incr(2*ind, L, (L+R)/2, i, j, x);
		incr(2*ind+1, (L+R)/2+1, R, i, j, x);

		pull(ind, L, R);
	}
};
