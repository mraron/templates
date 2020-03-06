ll extended_gcd(ll a, ll b, ll* x, ll* y) {
	if(b==0) {
		*x=1;
		*y=0;
		return a;
	}
	
	ll x0, y0;
	ll gcd=extended_gcd(b, a%b, &x0, &y0);
	
	*x=y0;
	*y=x0-(a/b)*y0;
	
	assert((*x)*a+(*y)*b==gcd);
	
	return gcd;
}

ll inverse(ll a, ll m) {
	ll x,y;
	extended_gcd(a,m,&x,&y);
	assert((x*a-1)%m==0);
	return x;
}
