#pragma once
#include <bits/stdc++.h>
#include "memprofile.h"

class HOG_BASE{
protected:
    HOG_BASE(){};
public:
    void print_details(bool verbose);
    std::vector<bool>marked;
};
