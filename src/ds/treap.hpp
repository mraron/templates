#include "../template.hpp"


//rewrite
template<typename T>
struct treap {
	struct node {
		node *L, *R;
		
		T key;
		int pri;
		
		node(T t) : L(nullptr), R(nullptr), key(t) {
			pri=rand()%int(1e9); //windows may have 16bit range...
		}
	};
	
	node* root=nullptr;
	void split(node* root, node*& L, node*& R, T key) {
		if(root==nullptr) {
			L=R=nullptr;
			return ;
		}
		
		if(root->key<key) {
			split(root->R, root->R, R, key);L=root;
		}else {
			split(root->L, L, root->L, key);R=root;
		}
	}
	
	void merge(node*& root, node* L, node* R) {
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
	}
	
	void insert(T elem) {
		node* e=new node(elem);
		insert(root, e);
	}
	
	void insert(node*& root, node* elem) {
		if(root==nullptr) {
			root=elem;
			return ;
		}
		
		if(elem->pri<root->pri) {
			split(root, elem->L, elem->R, root->key);
			root=elem;
			return ;
		}
		
		if(elem->key<root->key) insert(root->L, elem);
		else insert(root->R, elem);
	}
	
	node* lower_bound(node* root, T elem) {
		if(root==nullptr) return nullptr;
		if(root->key<elem) return lower_bound(root->L, elem);
		return lower_bound(root->R, elem);
	}
	
	bool erase(T elem) {
		return erase(root, elem);
	}
	
	bool erase(node*& root, T elem) {
		if(root==nullptr) return false;
		if(!(root->key<elem) && !(elem<root->key)) {
			merge(root, root->L, root->R);
			return true;
		}
		
		bool deleted=(elem<root->key?erase(root->L, elem):erase(root->R, elem));
		
		return deleted;
	}
};
