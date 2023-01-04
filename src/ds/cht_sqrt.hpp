#include "../template.hpp"

using line = pair<ll,ll>;
struct sqrt_cht {
	int mn;
	int blksz;
	
	vector<line> hull, reserve;
	
	sqrt_cht(bool min_, int blksz_) {
		mn=min_?1:-1;
		blksz=blksz_;
	}

	bool optimal(line& a, line& b, line& c) {
		return double(b.yy-a.yy)*double(c.xx-b.xx)>double(b.yy-c.yy)*double(a.xx-b.xx);
	}
    	
	void insert(line a) {
		auto cmp = [](const line& a, const line& b) -> bool {
			if(a.xx==b.xx) {
				return a.yy>b.yy;
			}
			
			return a.xx>b.xx;
		};
		
		a.xx*=mn;a.yy*=mn;
		
		reserve.pb(a);
		
		if(sz(reserve)>=blksz) { 
            sort(all(reserve), cmp);
            
			vector<line> nhull;
            nhull.reserve(hull.size()+reserve.size());
            
			for(int i=0,j=0;i<sz(hull)||j<sz(reserve);) {
				if(i<sz(hull) && (j==sz(reserve) || (j<sz(reserve) && cmp(hull[i], reserve[j])))) {
					nhull.pb(hull[i++]);
				}else {
					nhull.pb(reserve[j++]);
				}
				
				while((sz(nhull)>=2 && nhull[sz(nhull)-1].xx==nhull[sz(nhull)-2].xx) ||
				      (sz(nhull)>=3 && !optimal(nhull[sz(nhull)-3], nhull[sz(nhull)-2], nhull[sz(nhull)-1]))) {
					line tmp=nhull.back();
					nhull.pop_back();
					nhull.pop_back();
					
					nhull.pb(tmp);
				}
			}
		
			reserve.resize(0);
			hull.swap(nhull);
		}
	}
	
	ll get(ll x) {
		ll ans=1LL<<62;
		for(auto i:reserve) {
			ans=min(ans, i.xx*x+i.yy);
		}

		if(hull.empty()) return mn*ans;
		
		int L=0, R=sz(hull)-1;
		while(L<R) {
			int mid=(L+R+1)/2;
			
			ll val1=hull[mid-1].xx*x+hull[mid-1].yy, val2=hull[mid].xx*x+hull[mid].yy;
			if(val1<val2) {
				R=mid-1;
			}else {
				L=mid;
			}
		}
		
		ans=min(ans, hull[L].xx*x+hull[L].yy);
		
		return ans*mn;
	}
};

