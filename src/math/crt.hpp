#include "../template.hpp"

#include "gcd_extended.hpp"

// Adottak:
// x \equiv y_1 (z_1)
// x \equiv y_2 (z_2)
// ...
// x \equiv y_n (z_n)
//
// Legyen prod = z_1 * z_2 * ... * z_n
// és q_i = prod/z_i
// továbbá r_i \equiv q_i^-1 (mod z_i)
// x \equiv y_1*q_1*r_1+y_2*q_2*r_2+...+y_n*q_n*r_n (prod)
// => ekkor mindegyik teljesül

pair<ll,ll> crt(vector<pair<ll,ll>>& t) {
    ll prod=1;
    for(int i=0;i<sz(t);++i) {
        prod*=t[i].yy;
    }
    
    pair<ll,ll> sol={0, prod};
    for(int i=0;i<sz(t);++i) {
	    sol.xx+=(t[i].xx%prod)*(prod/t[i].yy)%prod*inverse(prod/t[i].yy, t[i].yy)%prod;
        sol.xx%=prod;
    }

    return sol;
}
