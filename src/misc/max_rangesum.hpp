int kadane(vector<int>& t) {
	int max_until=0, max_so_far=t[0];
	for(int i=0;i<(int)t.size();++i) {
		max_until=max(max_until+t[i], t[i]);
		max_so_far=max(max_so_far, max_until);
	}
	
	return max_so_far;
}

int max2drangesum(vector<vector<int>>& t) {
	int n=t.size();
	int m=t[0].size();
	int ans=t[0][0];
	for(int i=0;i<n;++i) {
		vector<int> sum(m);
		for(int j=i;j<n;++j) {
			for(int k=0;k<m;++k) {
				sum[k]+=t[j][k];
			}
			
			ans=max(ans, kadane(sum));
		}
	}
	
	return ans;
}
