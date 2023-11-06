#include "../include/Hog.h"

int Hog::suffix_prefix_length(int i, int j){
    int cur = _strToTreeIndex[i];
    while(cur>=0){
        if(t[cur].from() >= j && t[cur].to() <= j){
            return t[cur].length();
        } 
        cur = t[cur].suf_link();
    }
    return cur;
}
