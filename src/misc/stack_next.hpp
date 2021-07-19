vector<int> calc_next(vector<int>& t, function<bool(int,int)>, bool rev=false) {
	if(rev) reverse(all(t));
	vector<int> ans(sz(t));
	
	stack<pair<int,int>> st; //val,pos
	for(int i=0;i<sz(t);++i) {
		while(!st.empty() && cmp(st.top().xx, t[i])) st.pop();
		ans[i]=(st.empty()?-1:st.top().yy);
		st.push({t[i], i});
	}
	
	if(rev) {
		reverse(all(t));
		reverse(all(ans));
		for(auto& i:ans) i=sz(t)-i-1;
	}
	
	return ans;
}

