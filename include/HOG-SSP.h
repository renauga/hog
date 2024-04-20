#pragma once

#include <bits/stdc++.h>

#include "EHOG.h"
#include "HOG-BASE.h"
#include "Common-Trie.h"
struct HOG_SSP : public HOG_BASE {
    HOG_SSP(EHOG &ehog);
    HOG_SSP(AhoCorasick &ahocora);
    HOG_SSP(CommonTrie &trie);
    private:
};

