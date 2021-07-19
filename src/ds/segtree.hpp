//@TODO null_elem helyett index és -1 ha null elem
//@TODO templatew
struct Node {
	ll sum, lazy;
	
	Node(ll val, bool null_elem=false) {
		sum=val;
		lazy=0;
		if(null_elem) {
			sum=0;
			lazy=0;
		}
	}
	
	Node operator+(const Node& masik) const {
		Node res(sum+masik.sum);
		return res;
	}
};

struct SegmentTree {
	int n;
	vector<ll> arr;
	vector<Node> tree;
	
	SegmentTree(vector<ll>& arr_) {
		arr=arr_;
		n=sz(arr);
		tree.resize(4*n, Node(0));
	}
	
	void build() {
		build(1, 0, n-1);
	}
	
	void build(int ind, int L, int R) {
		if(L==R) {
			tree[ind]=Node(arr[L]);
		}else {
			build(2*ind, L, (L+R)/2);
			build(2*ind+1, (L+R)/2+1, R);
			
			tree[ind]=tree[2*ind]+tree[2*ind+1];
		}
	}
	
	Node query(int i, int j) {
		return query(1, 0, n-1, i, j);
	}
	
	void incr(int i, int j, int x) {
		incr(1, 0, n-1, i, j, x);
	}
	
	void push(int ind, int L, int R) {
		if(tree[ind].lazy!=0) {
			if(L==R) {
				tree[ind].sum+=tree[ind].lazy;
			}else {
				tree[2*ind].lazy+=tree[ind].lazy;
				tree[2*ind+1].lazy+=tree[ind].lazy;
				
				tree[ind].sum+=(R-L+1)*tree[ind].lazy;
				
			}
			tree[ind].lazy=0;
		}
	}
	
	Node query(int ind, int L, int R, int i, int j) {
		if(R<i||j<L) return Node(0,true);
		push(ind, L, R);
		
		if(i<=L && R<=j) {
			return tree[ind];
		}
		
		return query(2*ind, L, (L+R)/2, i, j)+query(2*ind+1, (L+R)/2+1, R, i, j);
	}
	
	
	void incr(int ind, int L, int R, int i, int j, int x) {
		if(R<i||j<L) return ;
		push(ind, L, R);
		
		if(i<=L && R<=j) {
			tree[ind].lazy+=x;
			return ;
		}
		
	
		incr(2*ind, L, (L+R)/2, i, j, x);
		incr(2*ind+1, (L+R)/2+1, R, i, j, x);
	}
};
