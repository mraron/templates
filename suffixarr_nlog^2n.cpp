const int MAXN=1001;

string t;
int sarr[MAXN], rang[MAXN], trang[MAXN];

int n;

void suffix_array() {
	for(int i=0;i<sz(t);++i) {
		rang[i]=t[i];
		sarr[i]=i;
	}
	
	for(int j=0;(1<<j)<sz(t);++j) {
		sort(sarr, sarr+sz(t), [&](int a, int b) -> bool {
			int p1=rang[a], p2=(a+(1<<j)>=sz(t))?0:rang[a+(1<<j)];
			int q1=rang[b], q2=(b+(1<<j)>=sz(t))?0:rang[b+(1<<j)];
			if(p1==q1) {
				if(p2==q2) {
					return a>b;
				}
				return p2<q2;
			}
		
		
			return p1<q1;
		});
		
		trang[sarr[0]]=0;
		for(int i=1;i<sz(t);++i) {
			int bef1=rang[sarr[i-1]], bef2=(sarr[i-1]+(1<<j)>=sz(t))?0:rang[sarr[i-1]+(1<<j)];
			int curr1=rang[sarr[i]], curr2=(sarr[i]+(1<<j)>=sz(t))?0:rang[sarr[i]+(1<<j)];
			
			if(bef1==curr1 && bef2==curr2) {
				trang[sarr[i]]=trang[sarr[i-1]];
			}else {
				trang[sarr[i]]=trang[sarr[i-1]]+1;
			}
		}
		
		for(int i=0;i<sz(t);++i) rang[i]=trang[i];
	}
}
