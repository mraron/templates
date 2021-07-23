#include "../template.hpp"

const int MAXN = 1e6+10;
int lp[MAXN];
vector<int> ps;

void sieve() {
	for(int i=2;i<MAXN;++i) {
		if(!lp[i]) {
			lp[i]=i;
			ps.push_back(i);
		}
		
		for(int j=0;j<sz(ps) && i*ps[j]<MAXN && ps[j]<=lp[i];++j) {
			lp[i*ps[j]]=ps[j];
		}
	}
}

vector<pair<int,int>> pfactors(int x) {
	vector<pair<int,int>> res;
	while(x>1) {
		int p=lp[x];
		res.push_back({p, 0});
		while(x%p==0) x/=p, res.back().yy++;
	}
	return res;
}


void divs_gen(int ind, int div, vector<pair<int,int>>& pfacts, vector<int>& res) {
	if(ind==sz(pfacts)) {
		res.push_back(div);
		return ;
	}
	
	divs_gen(ind+1, div, pfacts, res);
	for(int i=0;i<pfacts[ind].yy;++i) {
		div*=pfacts[ind].xx;
		divs_gen(ind+1, div, pfacts, res);
	}
}

vector<int> divs(int x) {
	vector<int> res;
	vector<pair<int,int>> pfacts=pfactors(x);
	divs_gen(0, 1, pfacts, res);

	return res;
}