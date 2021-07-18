void print_suffix_array(vector<int>& sarr, string& t) {
	for(auto i:sarr) {
		cout<<t.substr(i)<<"\n";
	}
}

vector<int> suffix_array(string& t) {
	vector<int> rang(sz(t)), temp_rang(sz(t)), sarr(sz(t));
	vector<int> xx(sz(t)), yy(sz(t));
	for(int i=0;i<sz(t);++i) {
		rang[i]=t[i];
		sarr[i]=i;
	}
	
	for(int j=1;j<sz(t);j*=2) {
		for(int i=0;i<sz(t);++i) {
			xx[sarr[i]]=rang[sarr[i]];
			yy[sarr[i]]=(sarr[i]+j>=sz(t))?0:rang[sarr[i]+j];
		}
		
		sort(sarr.begin(), sarr.end(), [&](int a, int b) -> bool {
			if(xx[a]==xx[b]) {
				if(yy[a]==yy[b]) {
					return a>b;
				}
				return yy[a]<yy[b];
			}
		
		
			return xx[a]<xx[b];
		});
		
		temp_rang[sarr[0]]=0;
		for(int i=1;i<sz(t);++i) {			
			if(xx[sarr[i-1]]==xx[sarr[i]] && yy[sarr[i-1]]==yy[sarr[i]]) {
				temp_rang[sarr[i]]=temp_rang[sarr[i-1]];
			}else {
				temp_rang[sarr[i]]=temp_rang[sarr[i-1]]+1;
			}
		}
		
		rang.swap(temp_rang);
		
	}
	
	return sarr;
}



vector<int> calc_lcp(string& t, vector<int>& sarr) {
	vector<int> inv(sz(t));
	for(int i=0;i<sz(t);++i) {
		inv[sarr[i]]=i;
	}
	
	vector<int> lcp(sz(t));

	int k=0;
	for(int i=0;i<sz(t);++i) {
		if(inv[i]==sz(t)-1) {
			k=0;
			continue ;
		}
		
		int j=sarr[inv[i]+1];
		
		while(i+k<sz(t) && j+k<sz(t) && t[i+k]==t[j+k]) k++;
		
		lcp[inv[i]]=k;
		
		if(k>0) k--;
	}
	
	return lcp;
}
