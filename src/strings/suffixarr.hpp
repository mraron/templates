#include "../template.hpp"

namespace suffixarr {

struct suffix_array {
	vector<int> sarr, inv, lcp;
	suffix_array(string t) {
		sarr.assign(sz(t)+1, 0);
		inv.assign(sz(t)+1, 0);

		sarr[0]=sz(t);
		iota(sarr.begin()+1, sarr.end(), 0);

		inv[sz(t)]=0;

		sort(sarr.begin()+1, sarr.end(), [&](int i, int j) -> bool {
			return t[i]<t[j];
		});

		inv[sarr[1]]=1;
		for(int i=2;i<=sz(t);++i) {
			int a=sarr[i-1], b=sarr[i];
			if(t[a]==t[b]) {
				inv[b]=inv[a];
			}else {
				inv[b]=i;
			}
		}

		for(int len=1;len<=sz(t);len*=2) {
			vector<int> nxt(sz(t)+1);
			iota(nxt.begin(), nxt.end(), 0);

			vector<int> sarr_orig(sarr);
			vector<int> inv_orig(inv);
			
			for(int i:sarr_orig) {
				if(i-len>=0) {
					sarr[nxt[inv[i-len]]++]=i-len;
				}
			}
			
			inv[sarr[1]]=1;
			for(int i=2;i<=sz(t);++i) {
				int a=sarr[i-1], b=sarr[i];
				if(inv_orig[a] == inv_orig[b] && (a+len>sz(t) || b+len>sz(t) || inv_orig[a+len]==inv_orig[b+len])) {
					inv[b]=inv[a];
				}else {
					inv[b]=i;
				}
			}
		}
	}

	void print_dbg(string t) {
		for(int i=1;i<=sz(t);++i) {
			cerr<<t.substr(sarr[i])<<"\n";
		}
	}
};

}