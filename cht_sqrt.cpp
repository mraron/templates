//
// SQRT time convex hull trick
//

typedef pair<ll,ll> line;

struct sqrt_CHT {
	int mn;
	int blksz;
	
	vector<line> hull, reserve;
	
	sqrt_CHT(bool min_, int blksz_) {
		mn=min_?1:-1;
		blksz=blksz_;
	}
		
	//
	// Checks wheter b is optimal if a<b<c holds
	// Complexity: O(1)
	//
	
	bool optimal(line& a, line& b, line& c) {
		return double(b.yy-a.yy)*double(c.xx-b.xx)>double(b.yy-c.yy)*double(a.xx-b.xx);
	}
	
	//
	// Inserts linear function into the hull
	// Complexity: O(1) if reserve is not full else O(sz(hull) log sz(hull) + blksz)
	//
	
	void insert(line a) {
		a.xx*=mn;a.yy*=mn;
		
		reserve.pb(a);
		
		if(sz(reserve)>=blksz) {
			for(auto i:reserve) {
				hull.pb(i);
			}
			
			reserve.resize(0);
			
			sort(all(hull), [](const line& a, const line& b) -> bool {
				if(a.xx==b.xx) {
					return a.yy>b.yy;
				}
				
				return a.xx>b.xx;
			});
			
			vector<line> nhull;
			for(auto i:hull) {
				nhull.pb(i);
				
				while((sz(nhull)>=2 && nhull[sz(nhull)-1].xx==nhull[sz(nhull)-2].xx) ||
				      (sz(nhull)>=3 && !optimal(nhull[sz(nhull)-3], nhull[sz(nhull)-2], nhull[sz(nhull)-1]))) {
					line tmp=nhull.back();
					nhull.pop_back();
					nhull.pop_back();
					
					nhull.pb(tmp);
				}
			}
			
			hull.swap(nhull);
		}
	}
	
	
	//
	// Gets the optimal (minimal or maximal) value of inserted function at a given x point
	// Complexity: O(log(sz(hull)) + blksz)
	//
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
	
	private: 
};


