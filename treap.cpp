
struct Treap {
	int key, pri;
	int sz;
	
	Treap *L,*R;
	
	Treap() {}
	
	Treap(int item) : L(NULL), R(NULL) {
		key=item;
		pri=rand();
	}
};

typedef Treap * pTreap;

void update(pTreap& root) {
	if(root==NULL) return ;
	
	root->sz=(root->L==NULL?0:root->L->sz)+(root->R==NULL?0:root->R->sz)+1;
}

void split(pTreap root, int key, pTreap& L, pTreap& R) {
	if(root==NULL) {
		L=NULL;
		R=NULL;
	}else if(key < root->key) {
		split(root->L, key, L, root->L);
		R=root;
	}else {
		split(root->R, key, root->R, R);
		L=root;	
	}
	
	update(root);
}

void insert(pTreap& root, pTreap item) {
	if(root==NULL) {
		root=item;
	}else if(root->pri < item->pri) {
		split(root, item->key, item->L, item->R);
		root=item;
	}else {
		insert(item->key < root->key ? root->L : root->R, item);
	}
	
	update(root);
}

void merge(pTreap& root, pTreap L, pTreap R) {
	if(L==NULL || R==NULL) {
		root=(L!=NULL?L:R);
	}else if(L->pri < R->pri) {
		merge(R->L, L, R->L);
		root=R;
	}else {
		merge(L->R, L->R, R);
		root=L;
	}
	
	update(root);
}

void erase(pTreap& root, int key) {
	if(root->key == key) {
		merge(root, root->L, root->R);
	}else {
		erase(key< root->key ? root->L : root->R, key);
	}
	
	update(root);
}

int meret(pTreap root) {
	if(root==NULL) return 0;
	return root->sz;
}

pTreap kthquery(pTreap& root, int k) {
	if(meret(root->L)==k-1) return root;
	else if(meret(root->L)<k-1) return kthquery(root->R, k-meret(root->L)-1);
	return kthquery(root->L, k);
}

void print(pTreap root) {
	if(root==NULL) return ;
	print(root->L);
	cout<<root->key<<" ";
	print(root->R);
}
