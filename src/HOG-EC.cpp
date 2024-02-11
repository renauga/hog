#include "HOG-EC.h"
#include "trace.h"

using namespace std;

HOG_EC::HOG_EC() {}

// HOG_EC::HOG_EC(const vector<string>& v) {
//     add_strings(v);
//     construct();
// }

// void HOG_EC::add_string(const std::string& s) {
//     _etrie.trie.add_string(s);
//     // dictionary.push_back(s);
// }

// void HOG_EC::add_strings(const vector<string>& v) {
//     int p = 0;
//     for(auto &s:v) p += s.length();
//     _etrie.trie.leaves.reserve(v.size());
//     _etrie.trie.t.reserve(p);
//     for(auto &s:v) add_string(s);
//     _etrie.construct();
// }

void HOG_EC::construct(){
    int n = leaves.size();
    marked.resize(t.size());
    segtree S(n);
    for(int u:leaves){
        marked[u] = true;
        std::vector<pair<int,int>>oper;
        while(u!=1){
            u = get_link(u);
            if(S.segtree_min(0, 0, n-1,t[u].l, t[u].r) == 0){
                marked[u] = true;
            }
            S.segtree_update(0,0,n-1, t[u].l, t[u].r,1);
            oper.push_back({t[u].l, t[u].r});
        }
        for(auto p:oper){
            S.segtree_update(0,0,n-1,p.first,p.second,-1);
        }
    }   
}
void HOG_EC::print_details(){
    // std::cout << "Aho-Corasick Size: " << trie.t.size() << "\n";
    std::cout << "EHOG Size: " << t.size() << "\n";
}