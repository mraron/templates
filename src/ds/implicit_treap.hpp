template<typename T>
struct treap {
	struct node {
		node *L, *R;
		
		T key;
		int pri;
		
		node(T t) : L(nullptr), R(nullptr), key(t) {
			pri=rand()%int(1e9); //windows may have 16bit range...
		}
		
		int cnt=1;
		void pull() {
			cnt=(L==nullptr?0:L->cnt)+(R==nullptr?0:R->cnt)+1;
		}
		
		void push() {
		
		}
	};
	
	node* root=nullptr;
	void split(node* root, node*& L, node*& R, int key, int add=0) {
		if(root==nullptr) {
			L=R=nullptr;
			return ;
		}
		
		root->push();
		
		int left=(root->L!=nullptr?root->L->cnt:0);
		int real_key=left+add;
		
		if(key<=real_key) {
			split(root->L, L, root->L, key, add);R=root;
		}else {
			split(root->R, root->R, R, key, add+1+left);L=root;
		}
		
		root->pull();
	}
	
	void merge(node*& root, node* L, node* R) {
		if(L!=nullptr) L->push();
		if(R!=nullptr) R->push();
		
		if(L==nullptr) {
			root=R;
			return ;
		}else if(R==nullptr) {
			root=L;
			return ;
		}
		
		if(L->pri<R->pri) {
			merge(L->R, L->R, R);root=L;
		}else {
			merge(R->L, L, R->L);root=R;
		}
		
		root->pull();
	}
	
	void insert(int pos, T elem) {
		node *e=new node(elem);
		node *L, *R;
		split(root, L, R, pos);
		merge(L, L, e);
		merge(root, L, R);
	}
	
	void dbg(node* root) {
		if(root==nullptr) return ;
		tr->push();
		dbg(root->L);
		cerr<<root->key<<" ";
		dbg(root->R);
	}
};
