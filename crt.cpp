//x = y_1 (z_1)
//x = y_2 (z_2)
//...
//x = y_n (z_n)
//legyen prod = z_1 * z_2 * ... * z_n
//legyen q_i = prod/z_i
//továbbá r_i = q_i^-1 (mod z_i)
//x = y_1*q_1*r_1+y_2*q_2*r_2+...+y_n*q_n*r_n (prod)
//=> ekkor mindegyik teljesül
pair<ll,ll> crt(vector<pair<ll,ll>>& t) {
    ll prod=1;
    for(int i=0;i<(int)t.size();++i) {
	prod*=t[i].second;
    }
    
    pair<ll,ll> sol;
    for(int i=0;i<(int)t.size();++i) {
	sol.first+=(t[i].first%prod)*(prod/t[i].second)%prod*inverse(prod/t[i].second, t[i].second)%prod;
	sol.first%=prod;
    }
    sol.second=prod;
    
    for(int i=0;i<(int)t.size();++i) {
	assert((sol.first%t[i].second-t[i].first)%t[i].second==0);
    }
    
    return sol;
}

ll inverse(ll a, ll m) {
	ll x,y;
	extended_gcd(a,m,&x,&y);
	assert((x*a-1)%m==0);
	return x;
}
