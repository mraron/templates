
struct twoSAT {
	int vars;
	SCC scc;
	
	twoSAT(int vars_) : vars(vars_), scc(2*vars_) {
		
	}
	
	void equal(int var1, int var2) {
		scc.add_edge(2*var1, 2*var2);
		scc.add_edge(2*var2, 2*var1);
		
		scc.add_edge(2*var1+1, 2*var2+1);
		scc.add_edge(2*var2+1, 2*var1+1);
	}
	
	void different(int var1, int var2) {
		scc.add_edge(2*var1+1, 2*var2);
		scc.add_edge(2*var1, 2*var2+1);
		
		scc.add_edge(2*var2+1, 2*var1);
		scc.add_edge(2*var2, 2*var1+1);
	}
	
	bool ok() {
		scc.do_scc();
		
		bool k=true;
		for(int i=0;i<vars;++i) {
			k&=scc.scc[2*i]!=scc.scc[2*i+1];
			//truth value is scc.scc[2*i]<scc.scc[2*i+1]
		}
		
		return k;
	}
	
	int solutions() {
		//@TODO
		return -1;
	}
	
};
