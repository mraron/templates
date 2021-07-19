
vector<int> lis(vector<int>& t) {
	vector<pair<int,int>> dp;
	vector<int> prev(t.size(), -1);
	
	for(int i=0;i<(int)t.size();++i) {
		auto it=lower_bound(dp.begin(), dp.end(), make_pair(t[i],0));
		if(it==dp.end()) {
			prev[i]=dp.empty()?-1:dp.back().second;
			dp.push_back(make_pair(t[i],i));
		}else {
			int ind=it-dp.begin();
			prev[i]=ind==0?-1:dp[ind-1].second;
			dp[ind]=make_pair(t[i], i);
		}
	}
	
	vector<int> lis;
	
	int akt=dp.back().second;
	while(akt!=-1) {
		lis.push_back(t[akt]);
		akt=prev[akt];
	}
	
	reverse(lis.begin(), lis.end());
	
	return lis;
}
