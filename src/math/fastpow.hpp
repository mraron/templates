#include "../template.hpp"

const int mod=1e9+7;
template<typename T> 
T fastpow(T a, int b) {
	return fastpow<T>(a, b, mod);
}

template<typename T> 
T fastpow(T a, int b, T mod) {
	T ans=1, mul=a;
	while(b>0) {
		if(b&1) {
			ans=ans*mul%mod;
		}
		
		mul=(mul*mul)%mod;
		b/=2;
	}

	return ans;
}