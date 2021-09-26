#include "../template.hpp"

struct line {
	ll m, b;
	
	line() : m(0), b(0) {}
	line(ll m, ll b) : m(m), b(b) {}
	
	ll at(ll x) {
		return m*x+b;
	}
	
	bool operator<(const line& other) const {
		return mp(m, b)<mp(other.m, other.b);
	}
};

struct static_cht {
	vector<line> lines;
	
	static_cht() {}
	
	bool intersect(const line& a, const line& b, const line& c) const {
		return (a.b-b.b)*(c.m-a.m)<=(a.b-c.b)*(b.m-a.m);
	}
	
	void init() {
		vector<line> cpy;
		cpy.swap(lines);
		
		sort(all(cpy));
		
		for(line i:cpy) {
			lines.pb(i);
			while(sz(lines)>=3 && intersect(lines[sz(lines)-3], lines[sz(lines)-2], lines[sz(lines)-1])) {
				swap(lines[sz(lines)-2], lines[sz(lines)-1]);
				lines.pop_back();
			}
		}
	}
	
	ll get(ll x) {		
		int L=0, R=sz(lines)-1;
		while(L<R) {
			int mid=(L+R)/2;
			if(lines[mid].at(x)<lines[mid+1].at(x)) {
				R=mid;
			}else {
				L=mid+1;
			}
		}
		
		return lines[L].at(x);
	}
};

struct dynamic_cht {
	vector<static_cht> lst;
	
	dynamic_cht() : lst(1, static_cht()) {}
	
	void add(line x) {
		lst[0].lines.pb(x);
		
		push();
	}
	
	void push() {
		for(int i=0;i<sz(lst);++i) {
			if(sz(lst[i].lines)>(1<<i)) {
				if(i+1==sz(lst)) {
					lst.pb(static_cht());
				}
				
				vector<line> res(sz(lst[i].lines)+sz(lst[i+1].lines));
				merge(all(lst[i].lines),all(lst[i+1].lines),res.begin());
				
				lst[i].lines.clear();
				lst[i+1].lines.swap(res);
				lst[i+1].init();
			}
		}
	}
	
	ll get(ll x) {
		ll ans=1LL<<60;
		for(int i=0;i<sz(lst);++i) {
			if(!lst[i].lines.empty()) {
				ans=min(ans, lst[i].get(x));
			}
		}
		
		return ans;
	}
};