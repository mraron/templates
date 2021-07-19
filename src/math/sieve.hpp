#include "../template.hpp"

const int MAXN = 1e6+1;
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