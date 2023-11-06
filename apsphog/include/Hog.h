#pragma once
#include "HogNode.h"
class Hog{
private:
    std::vector<HogNode> t;
    std::vector<int> _strToTreeIndex;
public:
    int suffix_prefix_length(int i, int j);
};