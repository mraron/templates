
typedef pair<ll,ll> line;

//
// Implements convex hull trick with Li Chao segment tree
//

struct LiChao {
	int mn;	
	int n, left, right;
	
	vector<line> tree;
	vector<int> vis;
	
	LiChao(bool min_, int n_) {
	    mn=min_?1:-1;
	    n=n_;
	    left=0;
	    right=n-1;
	    tree.resize(4*n, make_pair(0, 0));
		vis.resize(4*n, 0);
	}
	
	LiChao(bool min_, int l, int r) {
		mn=min_?1:-1;
		n=r-l+1;
		left=l;
		right=r;
		tree.resize(4*n, make_pair(0, 0));
		vis.resize(4*n, 0);
	}
	
	//
	// Inserts a line into the data structure
	// Complexity: O(log n)
	//
	void insert(line a) {
		a.xx*=mn;a.yy*=mn;
		
		insert(a, 1, left, right);
	}
	
	//
	// Finds the optimal (maximal or minimal) value at point x 
	// Complecity: O(log n)
	//
	ll get(ll x) {
		return mn*get(x, 1, left, right);
	}
	
	private:
	
	ll f(line& y, ll x) {
		return y.xx*x+y.yy;
	}
	
	void insert(line a, int ind, int L, int R) {
		if(!vis[ind]) {
			vis[ind]=1;
			tree[ind]=a;
			
			return;
		}
		
		int mid=(L+R)/2;
		bool l=f(a, L)<f(tree[ind], L); 
		bool m=f(a, mid)<f(tree[ind], mid); 
		
		if(m) {
			swap(tree[ind], a);
		}
		
		if(R==L) {
			return ;
		}
		
		if(l!=m) {
			insert(a, 2*ind, L, mid);
		}else {
			insert(a, 2*ind+1, mid+1, R);
		}
	}
	
	ll get(ll x, int ind, int L, int R) {
		ll val=tree[ind].xx*x+tree[ind].yy;
		if(!vis[ind]) val=1LL<<62LL;
		
		if(L==R) {
			return val;
		}
		
		if(x<=(L+R)/2) {
			return min(get(x, 2*ind, L, (L+R)/2), val); 
		}
		
		return min(get(x, 2*ind+1, (L+R)/2+1, R), val);
	}
	
};
