#pragma once
#include <bits/stdc++.h>
#include "EHOGx.h"

struct segtree{
    std::vector<int>nim, add;
    segtree(int N){
        nim.resize(4*N+5,0);
        add.resize(4*N+5,0);
    }
    int segtree_min(int v, int l, int r, int ql, int qr){
        if(r<l)return 1e9;
        if(ql<=l && r<=qr){
            return nim[v];
        }
        else if(ql > r || l > qr){
            return 1e9;
        }
        nim[2*v+1]+=add[v];
        add[2*v+1]+=add[v];
        nim[2*v+2]+=add[v];
        add[2*v+2]+=add[v];
        add[v] = 0;
        return std::min(segtree_min(2*v+1, l, (l+r)/2, ql, qr), segtree_min(2*v+2,(l+r)/2 + 1, r, ql, qr));
    }
    void segtree_update(int v, int l, int r, int ql, int qr, int val){
        if(r<l)return;
        if(ql<=l && r<=qr){
            nim[v]+=val;
            add[v]+=val;
            return;
        }
        else if(ql > r || l > qr){
            return;
        }
        nim[2*v+1]+=add[v];
        add[2*v+1]+=add[v];
        nim[2*v+2]+=add[v];
        add[2*v+2]+=add[v];
        add[v] = 0;
        segtree_update(0, l, (l+r)/2, ql, qr, val);
        segtree_update(0, (l+r)/2 + 1, r, ql, qr, val);
        nim[v] = std::min(nim[2*v+1], nim[2*v+2]);
        return;
    }
};
struct HOG_EC{
public:

    // std::vector<bool>marked_ehog;
    std::vector<bool>marked;
    std::vector<EHOGx_NODE> t;
    std::vector<int> leaves;
    HOG_EC();
    // HOG_EC(const std::vector<std::string>& v);

    void construct();
    void print_details();
    void inp(std::ifstream& in){
        int treeSize, leavesSize;
        in>>treeSize;
        t.resize(treeSize);
        for(int i = 0;i<treeSize;i++)t[i].inp(in);
        in>>leavesSize;
        leaves.resize(leavesSize);
        for(int i = 0;i<leavesSize;i++)in>>leaves[i];
    }
private:

    // AhoCorasick trie;
    // EHOGx _etrie;
    std::vector<std::string>dictionary;
    void EHOG_construct();
    inline int get_link(int node){
        return t[node].link;
    }
};