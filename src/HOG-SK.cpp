#include "HOG-SK.h"

using namespace std;

HOG_SK::HOG_SK() {}

HOG_SK::HOG_SK(const vector<string>& v) {
    add_strings(v);
    construct();
}

void HOG_SK::add_string(const std::string& s) {
    trie.add_string(s);
}

void HOG_SK::add_strings(const vector<string>& v) {
    int p = 0;
    for(auto &s:v) p += s.length();
    trie.leaves.reserve(v.size());
    trie.t.reserve(p);
    for(auto &s:v) add_string(s);
}

void HOG_SK::construct() {
    //construct l
    int root = 1;
    l.resize(trie.t.size()); //initialise l with empty lists
    for(int i=0;i<(int)trie.leaves.size();i++) {
        int curr = trie.get_link(trie.leaves[i]);
        while(curr != root) { // add to the list of each node on suffix path, except the leaf itself
            l[curr].push_back(i);
            curr = trie.get_link(curr);
        }
    }
    marked.resize(trie.t.size(), false); // inH
    marked[root] = true; //root is in HOG
    s.resize(trie.leaves.size());
    is_unmarked.resize(trie.leaves.size(), false);
    dfs(root);
}

void HOG_SK::dfs(int node) {
    if(trie.t[node].is_leaf()) {
        marked[node] = true; // leaves are implicitly in HOG
        for(int x:unmarked) { // iterate over all stacks with unmarked tops
            if(is_unmarked[x]) {
                marked[s[x].top()] = true;
                is_unmarked[x] = false;
            }
        }
        unmarked.clear();
    }

    // node visited for the first time
    for(int x:l[node]) {
        s[x].push(node);
        if(!is_unmarked[x]) {
            is_unmarked[x] = true;
            unmarked.push_back(x);
        }
    }
    for(int i=0;i<alphabet;i++) {
        if(trie.t[node].next[i] != 0) {
            dfs(trie.t[node].next[i]);
        }
    }

    // node visited for the last time
    for(int x:l[node]) {
        s[x].pop();
        if((!s[x].empty()) && (!marked[s[x].top()])) {
            if(!is_unmarked[x]) {
                is_unmarked[x] = true;
                unmarked.push_back(x);
            }
        } else {
            is_unmarked[x] = false;
        }
    }
}
void HOG_SK::print_details(){
    std::cout << "Aho-Corasick Size: " << trie.t.size() << "\n";
    int hsz = 0;
    for(bool a:marked)hsz+=a;
    std::cout << "HOG Size: " << hsz << "\n";
}