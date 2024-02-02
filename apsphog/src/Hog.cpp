#include "../include/Hog.h"
#include "trace.h"
int Hog::suffix_prefix_length(int i, int j){
    i = sorted_order_conversion[i];
    j = sorted_order_conversion[j];
    int cur = _strToTreeIndex[i];
    while(cur>1){
        if(t[cur].from() <= j && t[cur].to() >= j){
            return t[cur].length();
        } 
        cur = t[cur].suf_link();
    }
    // trace(cur);
    return t[cur].length();
}

std::vector<int> Hog::one_to_all(int i){
    i = sorted_order_conversion[i];
    std::vector<int> answer(sorted_order_conversion.size());
    int current = _strToTreeIndex[i];
    std::vector<int> nextRemaining(sorted_order_conversion.size());
    for(int i = 0;i<(int)nextRemaining.size();i++){
        nextRemaining[i] = i;
    }
    while(current>1){
        int start = t[current].from();
        int end = t[current].to();
        int curIndex = start;
        while(curIndex <= end){
            while(curIndex <= end && curIndex != nextRemaining[curIndex]){
                curIndex = nextRemaining[curIndex];
            }
            if(curIndex > end)break;
            answer[curIndex] = t[current].length();
            curIndex = curIndex+1;
        }
        nextRemaining[start] = end+1;
        current = t[current].suf_link();
    }
    std::vector<int>answerFinal(sorted_order_conversion.size());
    for(int i = 0;i<(int)sorted_order_conversion.size();i++){
        answerFinal[sorted_order_conversion[i]] = answer[i];
    }
    return answerFinal;
}

std::pair<std::vector<int>,std::vector<int>>  Hog::top(int i, int k){
    i = sorted_order_conversion[i];
    std::vector<int> answer;
    std::vector<int>answer2;
    int current = _strToTreeIndex[i];
    std::vector<int> nextRemaining(sorted_order_conversion.size());
    for(int i = 0;i<(int)nextRemaining.size();i++){
        nextRemaining[i] = i;
    }
    int currentCount = 0;
    while(true){
        int start = t[current].from();
        int end = t[current].to();
        int curIndex = start;
        while(curIndex <= end){
            while(curIndex <= end && curIndex != nextRemaining[curIndex]){
                curIndex = nextRemaining[curIndex];
            }
            if(curIndex > end)break;
            if(currentCount >= k)break;
            answer.push_back(curIndex);
            answer2.push_back(t[current].length());
            currentCount++;
            curIndex = curIndex+1;
        }
        if(currentCount >= k)break;
        nextRemaining[start] = end+1;
        current = t[current].suf_link();
    }
    return {answer,answer2};
}