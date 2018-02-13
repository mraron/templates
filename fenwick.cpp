struct fenwick {
	int arr[MAXN];
	
	fenwick() {memset(arr,0,sizeof arr);}
	
	void incr(int x, int by) {
		for(;x<MAXN;x+=(x&(-x))) {
			arr[x]+=by;
		}
	} 
	
	int sum(int x) {
		int sum=0;
		for(;x;x-=(x&(-x))) {
			sum+=arr[x];
		}
		
		return sum;
	}
};
