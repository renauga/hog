#pragma once

#include<bits/stdc++.h>
#include "memprofile.h"
struct timer {
    timer();
    ~timer();
    double end();
    
    private:
    std::chrono::_V2::system_clock::time_point start_time;
    bool completed;
};

