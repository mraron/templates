const int MAXP=1e6+55;

vector<int> primes(MAXP+1), cnt(MAXP+1), hatv(MAXP+1), d(MAXP+1);

void sieve() {
	const int sqr=sqrt(MAXP);
	
	primes[1]=0;
	for(int i=2;i<=MAXP;++i) {
		if(primes[i]==0) {
			primes[i]=i;
			cnt[i]=1;
			hatv[i]=i;
			
			if(i<=sqr) {
				for(int j=i*i;j<=MAXP;j+=i) {
					if(!primes[j]) {
						primes[j]=i;
						hatv[j]=1;
						
						int akt=j;
						while(akt%i==0) {
							cnt[j]++;
							akt/=i;
							hatv[j]*=i;
						}
					}
				}
			}
		}
	}
	
	d[1]=1;
	for(int i=2;i<=MAXP;++i) {
		d[i]=d[(i/hatv[i])]*(cnt[i]+1);
	}
}
