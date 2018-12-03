struct rolling_hash { 
	vector<ll> lst;
	vector<ll> hatv;
	
	ll p;
	ll mod; 

	rolling_hash(string& t, ll p_, ll mod_) {
		lst.resize(sz(t));
		hatv.resize(sz(t));
		
		p=p_;
		mod=mod_;
		
		ll curr=p;
		
		lst[0]=t[0]%mod;
		hatv[0]=1;
		for(int i=1;i<sz(t);++i) {
			lst[i]=(lst[i-1]+curr*t[i])%mod;
			hatv[i]=curr;
			curr=(curr*p)%mod;
		}
	}
	
	ll base_hash(ll l, ll r) { //mod should be prime for this
		ll hsh=(lst[r]-(l>0?lst[l-1]:0)+mod);
		return (hsh*fastpow(hatv[l], mod-2, mod))%mod;
	}
	
	bool probably_equal(ll l1, ll r1, ll l2, ll r2) {				
		if(r1-l1!=r2-l2) return false;

		if(l1>l2) {
			swap(l1, l2);
			swap(r1, r2);
		}
				
		ll egyik=(lst[r2]-(l2>0?lst[l2-1]:0)+mod), masik=(lst[r1]-(l1>0?lst[l1-1]:0)+mod);
		return (egyik-(masik*hatv[l2-l1]))%mod==0; //WATCH OUT FOR THIS KIND OF ERROR!!
	}
};
