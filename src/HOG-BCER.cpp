#include "HOG-BCER.h"
using namespace std;

HOG_BCER::HOG_BCER(EHOG &ehog) {
    vector<bool>bHOG(ehog.t.size(), false);
    build_rl(ehog);
    marked.resize(ehog.t.size());
    mark_hog(1, ehog);
}

void HOG_BCER::build_rl(EHOG &ehog){
    rl.resize(ehog.t.size());
    for(int v:ehog.leaves){
        int temp = v;
        int str_index = ehog.t[v].strIndex;
        while(temp!=1){
            rl[temp].push_back(str_index);
            temp = ehog.get_link(temp); 
        }
        rl[1].push_back(str_index); 
    }
}

vector<bool> HOG_BCER::mark_hog(int v, EHOG &ehog){
    if(ehog.t[v].is_leaf()){
        vector<bool>C(ehog.leaves.size(), false);
        marked[v] = true;
        return C;
    }
    vector<bool> C(ehog.leaves.size(), true);
    for(int u:ehog.t[v].childs){
        vector<bool> temp = mark_hog(u, ehog);
        for(int i = 0;i<(int)C.size();i++){
            C[i] = C[i]&temp[i];
        }
    }
    for(int x:rl[v]){
        if(C[x] == false)marked[v] = true;
        C[x] = true;
    }
    return C;
}
