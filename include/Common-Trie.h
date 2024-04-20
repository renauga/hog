#pragma once

#include <bits/stdc++.h>
#ifdef MEMORY_READING

#include "memprofile.h"

#endif
// const int alphabet = 4;

struct CommonTrieNode {
    int p; // index of parent
    int link = 0; // index of suffix link
    char pch; // character of parent edge
    int strIndex = -1;
    int aho_index;
    // int next[alphabet]= {0}; // direct transition from this node using a character
    std::list<std::pair<char, int>> childs;

    inline CommonTrieNode(int par, char ch) : p(par), pch(ch) {}

    inline bool is_leaf() { 
        if(strIndex != -1)return true;
        else return false;
    }
};

struct CommonTrie{
    std::vector<CommonTrieNode*> t;
    std::vector<int> leaves;
    bool isEHOG = false;

    CommonTrie(const std::vector<std::string> &v);
    CommonTrie(std::ifstream &in);
    void convert_aho_to_ehog();
    void add_string(std::string const& s);
    int get_link(int v);
    int traverse(int v, std::string s);
    int traverse(int v, char ch);
};
