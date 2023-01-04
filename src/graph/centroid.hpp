#include "../template.hpp"

struct centroid_decomp {
    vector<vector<int>> adj;
    vector<bool> banned;
    vector<int> sz;
    
    centroid_decomp(){}
    
    centroid_decomp(int n) {
        adj.resize(n);
        banned.resize(n);
        sz.resize(n);
        cpar.resize(n);
        cadj.resize(n);
    }
    
    void add_edge(int x, int y) {
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    
    vector<vector<int>> cadj;
    vector<int> cpar;
    int decompose(int x=0) {
        dfs0(x);
        
        int centroid=dfs1(x,-1,sz[x]);
        banned[centroid]=1;
        
        for(auto i:adj[centroid]) {
            if(!banned[i]) {
                int child=decompose(i);
                cadj[centroid].pb(child);
                cpar[child]=centroid;
            }
        }
        
        return centroid;
    }
    
    void dfs0(int x, int p=-1) {
        sz[x]=1;
        for(auto i:adj[x]) {
            if(i==p ||  banned[i]) continue ;
            
            dfs0(i, x);
            sz[x]+=sz[i];
        }
    }

    int dfs1(int x, int p, int nn) {
        int ind=-1;
    
        for(auto i:adj[x]) {
            if(banned[i] || i==p) continue ;
            if(sz[i]>nn/2) ind=i;
        }
        
        if(ind!=-1) return dfs1(ind, x, nn);
        
        return x;
    }
};
