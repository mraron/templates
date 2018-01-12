
const int mod=1e9+7;
template<typename T> 
T fastpow(T x, int a) {
	if(a==1) return x;
	
	T fele=fastpow(x, a/2);
	T ans=(fele*fele)%mod;
	
	if(a&1) ans=(ans*x)%mod;
	
	return ans;
}

template<typename T> 
T fastpow(T x, int a, T mod) {
	if(a==1) return x;
	
	T fele=fastpow(x, a/2);
	T ans=(fele*fele)%mod;
	
	if(a&1) ans=(ans*x)%mod;
	
	return ans;
}
