template<typename T> 
struct Treap {
	T val;
	int pri;
	
	Treap *L,*R;
	
	Treap() {
		L=R=null;
		pri=rand();
	}
};
