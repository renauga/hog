#pragma once
#include <bits/stdc++.h>
#include "Aho-Cora.h"


struct EHOG_NODE {
    int p; // index of parent
    int link = 0; // index of suffix link
    bool output = false; // is this node an exact match
    int aho_index; // index corresponding to aho-corasick tree
    std::vector<int>childs;
    inline EHOG_NODE(){}
    inline EHOG_NODE(int par) : p(par) {}
    inline bool is_leaf() {return output;}
    void dump(std::ofstream& out){
        out<<p<<" "<<link<<" "<<output<<" ";
        out<<childs.size()<<" ";
        for(int a:childs)out<<a<<" ";
        // out<<"\n";
    }
    void inp(std::ifstream& in){
        in>>p>>link>>output;
        int numChild;
        in>>numChild;
        childs.resize(numChild);
        for(int i = 0;i<numChild;i++){in>>childs[i];}
    }
    int memory_calculate(){
        return childs.size()*sizeof(int);
    }
};


struct EHOG{
    AhoCorasick trie;
    std::vector<bool>marked;
    std::vector<EHOG_NODE> t; // the nodes in the automaton
    std::vector<int>conversion; // ehog node equivalent to which aho corasik node;
    std::vector<int> leaves;

    EHOG();

    void construct();
    void dfs(int v, int par);
    int get_link(int v);
    void dump(std::ofstream& out);
    void add_string(const std::string& s);
    void add_strings(const std::vector<std::string>& v);
};