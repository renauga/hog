#pragma once
#include <bits/stdc++.h>
#include "Aho-Corax.h"


struct EHOG_NODE {
    int p; // index of parent
    int link = 0; // index of suffix link
    bool output = false; // is this node an exact match
    int aho_index; // index corresponding to aho-corasick tree
    std::vector<int>childs;
    std::vector<int>rl;
    int l, r;
    inline EHOG_NODE(int par) : p(par) {}
    inline bool is_leaf() {return output;}
};


struct EHOG{
    AhoCoraxsick trie;
    std::vector<bool>marked;
    std::vector<EHOG_NODE> t; // the nodes in the automaton
    std::vector<int>conversion; // ehog node equivalent to which aho corasik node;
    std::vector<int> leaves;

    EHOG();

    void construct();
    void build_rl();
    void dfs(int v, int par);
    int get_link(int v);
};