#include "../template.hpp"

#ifndef _FASTPOW_HPP
#define _FASTPOW_HPP

const ll mod=1e9+7;

ll fastpow(ll a, ll b, ll mod) {
	ll ans=1, mul=a%mod;
	while(b>0) {
		if(b&1) {
			ans=ans*mul%mod;
		}
		
		mul=(mul*mul)%mod;
		b/=2;
	}

	return ans;
}

ll fastpow(ll a, ll b) {
	return fastpow(a, b, mod);
}

#endif //_FASTPOW_HPP
