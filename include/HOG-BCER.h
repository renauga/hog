#pragma once
#include <bits/stdc++.h>
#include "EHOG.h"

struct HOG_BCER{
public:

    std::vector<bool>marked;

    HOG_BCER();
    HOG_BCER(const std::vector<std::string>& v);

    void add_string(const std::string &s);
    void add_strings(const std::vector<std::string>& v);
    void construct();

private:

    // AhoCorasick trie;
    EHOG _etrie;
    std::vector<bool>marked_ehog;
    void EHOG_construct();
    std::vector<bool> mark_hog(int v);
};