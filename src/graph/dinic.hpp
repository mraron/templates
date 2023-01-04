#include "../template.hpp"

struct dinic {
    const ll inf = 1LL<<60;
    struct edge {
        int from, to;
        ll cap, flow;
    };

    int n,m;
    vector<vector<int>> adj;
    vector<int> lvl, st, ptr;
    vector<edge> edgs;

    dinic(int n) : n(n), m(0) {
        adj.resize(n);
    }

    void add_edge(int u, int v, ll flow, ll revf=0) {
        edgs.push_back({u,v,flow+revf,revf});
        edgs.push_back({v,u,revf+flow,flow});
        adj[u].push_back(m);
        adj[v].push_back(m+1);
        m+=2;
    }

    void bfs(int s) {
        lvl.assign(n, 0);
        st.assign(n,0);

        queue<int> q;
        q.push(s);
        st[s]=1;
        while(!q.empty()) {
            int fr=q.front();q.pop();
            for(auto i:adj[fr]) {
                if(edgs[i].cap-edgs[i].flow>0 && !st[edgs[i].to]) {
                    lvl[edgs[i].to]=lvl[fr]+1;
                    st[edgs[i].to]=1;
                    q.push(edgs[i].to);
                }
            }
        }
    }

    ll dfs(int x, int t, ll push) {
        if(0==push) return 0;
        if(x==t) return push;

        for(int& i=ptr[x];i<sz(adj[x]);++i) {
            auto& edg=edgs[adj[x][i]];
            if(lvl[edg.to]!=lvl[x]+1 || edg.cap-edg.flow==0) continue ;
            
            ll flow=dfs(edg.to, t, min(edg.cap-edg.flow, push));
            if(flow>0) {
                edg.flow+=flow;
                edgs[adj[x][i]	^1].flow-=flow;
                return flow;
            }
        }

        return 0;
    }

    ll flow(int s, int t) {
        ll mf=0;
        while(1) {
            bfs(s);
            
            if(!lvl[t]) {
                break ;
            }

            ptr.assign(n, 0);
            while(ll f=dfs(s,t,inf)) {
                mf+=f;
            }
        }

        return mf;
    }
};