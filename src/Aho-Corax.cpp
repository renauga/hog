#include "Aho-Corax.h"
#include "trace.h"

using namespace std;

AhoCoraxsick::AhoCoraxsick() {
    t.emplace_back(-1, -1); //garbage node
    t.emplace_back(0, '$'); //root node
    t[1].link = 1;
    str_count=0;
}

void AhoCoraxsick::add_string(string const& s) {
    int v = 1;
    str_count++;
    for (char ch : s) {
        int c = ch - 'a';
        if (t[v].next[c] == 0) {
            t[v].next[c] = t.size();
            t.emplace_back(v, ch);
            // t[t.size()-1].str_index = str_count-1;
            t[t.size()-1].length = t[v].length+1;
        }
        v = t[v].next[c];
    }
    if(t[v].output == true){
        str_count--;
    }
    else{
        t[v].output = true;
        leaves.push_back(v);
        t[v].str_index = str_count-1;
    }
}

int AhoCoraxsick::get_link(int v) {
    #ifdef DDEBUG
    assert(v>0);
    #endif
    if (t[v].link == 0) {
        if (t[v].p == 1)
            t[v].link = 1;
        else
            t[v].link = go(get_link(t[v].p), t[v].pch);
    }
    return t[v].link;
}

int AhoCoraxsick::go(int v, char ch) {
    #ifdef DDEBUG
    assert(v>0);
    assert((ch>='a') && (ch-'a'<alphabet));
    #endif
    int c = ch - 'a';
    if (t[v].go[c] == 0) {
        if (t[v].next[c] != 0)
            t[v].go[c] = t[v].next[c];
        else
            t[v].go[c] = (v == 1 ? 1 : go(get_link(v), ch));
    }
    return t[v].go[c];
}


std::vector<int> AhoCoraxsick::sorted_order(){
    std::vector<int> leaves_in_order;
    int leaves_visited = 0;
    dfs(1, leaves_in_order, leaves_visited);
    return leaves_in_order;
}

void AhoCoraxsick::dfs(int v, std::vector<int>&leaves_in_order, int &leaves_visited){
    if(t[v].is_leaf()){
        t[v].l = t[v].r = leaves_visited;
        // t[v].str_index = leaves_visited;
        leaves_in_order.push_back(t[v].str_index);
        leaves_visited++;
    }
    for(int i = 0;i<alphabet;i++){
        if(t[v].next[i] != 0){
            dfs(t[v].next[i], leaves_in_order, leaves_visited);
        }
    }
    for(int i = 0;i<alphabet;i++){
        if(t[v].next[i] != 0){
            t[v].l = min(t[t[v].next[i]].l, t[v].l);
            break;
        }
    }
    for(int i = alphabet-1;i>=0;i--){
        if(t[v].next[i] != 0){
            t[v].r = max(t[t[v].next[i]].r, t[v].r);
            break;
        }
    }
}