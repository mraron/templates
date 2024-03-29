#include "../template.hpp"

namespace manacher {

string expand(const string& t) {
	string res="?";
	for(auto i:t) {
		res.push_back(i);
		res.push_back('?');
	}
	
	return res;
}

vector<int> manacher(const string& t) {
	vector<int> p(sz(t));
	int c=0, r=0;
	
	for(int i=0;i<sz(t);++i) {
		int mirror=c-(i-c);
		if(mirror>=0 && i+p[mirror]<r) {
			p[i]=p[mirror];
		}else {
			p[i]=r-i;
			
			while(i-p[i]>=0 && i+p[i]<sz(t) && t[i-p[i]]==t[i+p[i]]) p[i]++;
			p[i]--;
			
			if(i+p[i]>r) {
				c=i;
				r=i+p[i];
			}
		}
	}
	
	return p;
}

}