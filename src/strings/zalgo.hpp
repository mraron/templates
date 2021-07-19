#include "../template.hpp"

namespace zalgo {

vector<int> zalgo(string& str) {
	vector<int> z(sz(str));
	int L=0, R=0;
	for(int i=1;i<sz(str);++i) {
		if(i>R) {
			L=i;R=i;
			while(R<sz(str) && str[R]==str[R-L]) R++;
			z[i]=R-L;
			R--;
		}else {
			if(z[i-L]+i<R) {
				z[i]=z[i-L];
			}else {
				L=i;
				while(R<sz(str) && str[R]==str[R-L]) R++;
				z[i]=R-L;
				R--;
			}
		}
	}
	
	return z;
}

}