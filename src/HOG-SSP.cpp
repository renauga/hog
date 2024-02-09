#include "HOG-SSP.h"

using namespace std;

extern map<string,double> trial_results;

HOG_SSP::HOG_SSP() {}

HOG_SSP::HOG_SSP(const vector<string>& v) {
    add_strings(v);
    construct();
}

void HOG_SSP::add_string(const string& s) {
    trie.add_string(s);
}

void HOG_SSP::add_strings(const vector<string>& v) {
    int p = 0;
    for(auto &s:v) p += s.length();
    trie.leaves.reserve(v.size());
    trie.t.reserve(p);
    for(auto &s:v) add_string(s);
    // trie.construct();
    trial_results["aho_memory"] = sizeof(AhoCorasick) + sizeof(AhoNode)*trie.t.capacity() + sizeof(int)*trie.leaves.capacity();
}

void HOG_SSP::construct() {
    const int root = 1, p = (int)trie.t.size();
    marked.resize(p, false);

    vector<int> up(p), down(p), subTreeCnt(p, 0), oneChild(p);
    for(int i:trie.leaves) subTreeCnt[trie.t[i].p] = 1;
    for(int i=p-1;i>=root;i--) {
        if(subTreeCnt[i] == 1) down[i] = down[oneChild[i]];
        else down[i] = i;
        subTreeCnt[trie.t[i].p]++;
        oneChild[trie.t[i].p] = i;
    }
    up[root] = root;
    for(int i=root+1;i<p;i++) {
        if(subTreeCnt[trie.t[i].p] == 1) up[i] = up[trie.t[i].p];
        else up[i] = trie.t[i].p;
    }

    // int suff_path = 0, mod_len = 0, do_while = 0;// track suffix path lengths, modified list lengths, and iterations of do while loop
    vector<int> subTreeLeft(subTreeCnt), modified;
    marked[root] = true; //root is implicitly marked
    int u,v;
    for(int i:trie.leaves) {
        marked[i] = true; //leaves are implicitly marked
        v = trie.get_link(i); // iterate over proper suffixes of i, that are prefix (may not be proper) of some string
        // suff_path++;
        while(v!=root) {
            if(subTreeLeft[down[v]] != 0) { //if the subtree of v (including v) contains a split node having subtrees left
                marked[v] = true;
                modified.push_back(down[v]);
                subTreeLeft[down[v]] = 0;
                u = v;
                do {
                    u = up[u];
                    subTreeLeft[u]--; //remove subtree of u containing v
                    // do_while++;
                } while((u!=root) && (subTreeLeft[u]==0));
                modified.push_back(u); // add only last u to modified as all other up nodes are already in modified
            }
            v = trie.get_link(v);
            // suff_path++;
        }
        // mod_len += modified.size();
        for(int x:modified) subTreeLeft[x] = subTreeCnt[x];
        modified.clear();
    }
    // trial_results["suff_path"] = suff_path;
    // trial_results["mod_len"] = mod_len;
    // trial_results["do_while"] = do_while;
}