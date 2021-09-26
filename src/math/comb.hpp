#include "../template.hpp"

#include "fastpow.hpp"

const int MAXN=3000101;

ll fact[MAXN], ifact[MAXN], inv[MAXN];
void init_comb() {
	fact[0]=fact[1]=1;
	ifact[0]=ifact[1]=1;
	inv[1]=1;
	for(ll i=2;i<MAXN;++i) {
		fact[i]=fact[i-1]*i%mod;
		inv[i]=(mod-(mod/i)*inv[mod%i]%mod)%mod;
		ifact[i]=ifact[i-1]*inv[i]%mod;
	}
}

ll C(ll x, ll y) {
	if(x<y||y<0) return 0;
	return fact[x]*ifact[x-y]%mod*ifact[y]%mod;
}