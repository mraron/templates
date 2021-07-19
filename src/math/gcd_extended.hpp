#include "../template.hpp"

#ifndef _EGCD_HPP
#define _EGCD_HPP

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
	
	return gcd;
}

ll inverse(ll a, ll m) {
	ll x,y;
	extended_gcd(a,m,&x,&y);
	return x;
}

#endif //_EGCD_HPP