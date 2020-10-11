template<typename T>
struct fenwick {
	vector<T> arr;
	
	fenwick(size_t sz) {
		arr.assign(sz,0);
	}
	
	void incr(size_t x, T by) {
		for(;x<arr.size();x+=(x&(-x))) {
			arr[x]+=by;
		}
	} 
	
	T sum(T x) {
		T sum=0;
		for(;x>0;x-=(x&(-x))) {
			sum+=arr[x];
		}
		
		return sum;
	}
};
