#pragma once

#include <bits/stdc++.h>

#include "EHOG.h"
#include "HOG-BASE.h"
#include "Common-Trie.h"

struct HOG_SK : public HOG_BASE{
    HOG_SK(EHOG &ehog);
    HOG_SK(AhoCorasick &ahocora);
    HOG_SK(CommonTrie &trie);
    
    private:
    std::vector<std::vector<int>> l; //list of string indexes that have the i'th node on their suffix path
    std::vector<std::stack<int>> s;
    std::vector<int> unmarked; // list of indices of stacks that have unmarked tops
    std::vector<bool> is_unmarked; // whether the top of this stack is unmarked
};

