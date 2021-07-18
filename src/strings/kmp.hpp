#include "../template.hpp"

namespace kmp {

vector<int> lps(string& pat) {
	if(pat.empty()) return {};

	vector<int> p(pat.size());

	for(int i=1;i<(int)pat.size();++i) {
		int j=p[i-1];
		
		while(j>0 && pat[i]!=pat[j]) {
			j=p[j-1];
		}

		if(pat[i]==pat[j]) j++;
		
		p[i]=j;
		
	}
		
	return p;
}

vector<int> kmp(string& pat, string& str) {
	vector<int> res;
	vector<int> p=lps(pat);
																								
	int state=0, pos=0;
	for(;;) {
		if(pos==(int)str.size()) break ;
		
		while(pat[state]==str[pos]) {
			state++;pos++;
			if(state==(int)pat.size()) {
				res.push_back(pos-(int)pat.size());
				break ;
			}
		}
		
		if(state>0) {
			state=p[state-1];
		}else {
			pos++;
		}
	}
	
	return res;
}

}