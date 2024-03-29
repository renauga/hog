#include "HOG-EC.h"
#include "trace.h"

using namespace std;

HOG_EC::HOG_EC(EHOG &ehog) {
    l.resize(ehog.t.size());
    r.resize(ehog.t.size());

    int leaves_visited = 0;
    function<void(int)> dfs;
    dfs = [&leaves_visited, &ehog, &dfs, this](int v){
        if(ehog.t[v].is_leaf()){
            l[v] = r[v] = leaves_visited;
            leaves_visited++;
        }
        for(int child:ehog.t[v].childs){
            dfs(child);
        }
        for(int child:ehog.t[v].childs){
            l[v] = min(l[v], l[child]);
        }
        for(int child:ehog.t[v].childs){
            r[v] = min(r[v], r[child]);
        }
    };

    dfs(1);

    int n = ehog.leaves.size();
    marked.resize(ehog.t.size());
    segtree S(n);
    for(int u:ehog.leaves){
        marked[u] = true;
        std::vector<pair<int,int>>oper;
        while(u!=1){
            u = ehog.get_link(u);
            if(S.segtree_min(0, 0, n-1,l[u], r[u]) == 0){
                marked[u] = true;
            }
            S.segtree_update(0,0,n-1, l[u], r[u],1);
            oper.push_back({l[u], r[u]});
        }
        for(auto p:oper){
            S.segtree_update(0,0,n-1,p.first,p.second,-1);
        }
    } 
}