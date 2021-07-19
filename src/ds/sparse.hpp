//not working
struct sparse {
	int mi;
	vector<int> arr;
	
	sparse(vector<int>& arr_, bool mi_) {
		mi=mi_?1:-1;
		arr=arr_,
		
		init();
	}
	
	void query(int x, int y) {
		int i;
		for(i=0;i<sz(dp) && (1<<i)<=(y-x+1);++i);
		i--;
		
		return mn*min(dp[i][x], dp[i][x-(1<<i)]);
	}
	
	private:
	vector<vector<int>> dp; 
	
	void init() {
		dp.resize(log2(sz(arr))+1);
		for(auto& i:dp) {
			i.resize(sz(arr));
		}
		
		for(int i=0;i<sz(arr);++i) {
			dp[0][i]=mi*arr[i];
		}
		
		for(int j=1;j<sz(dp);++j) {
			for(int i=0;i<sz(arr);++i) {
				dp[i][j]=dp[i][j-1];
				if(i+(1<<(j-1))<sz(arr)) dp[i][j]=min(dp[i][j], dp[i+(1<<(j-1))][j-1]);
			}
		}		
	}
};

