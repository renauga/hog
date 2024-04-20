#include "Common-Trie.h"

using namespace std;

// CommonTrieNode::CommonTrieNode(ifstream&in){
//     in >> p  >> link >> pch >> strIndex;
//     for(int i = 0;i<alphabet;i++)in >> next[i];
// }

// void CommonTrieNode::file_output(ofstream& out){
//     out << p << " " << link << " " << pch << " " << strIndex << " ";
//     for(int i = 0;i<alphabet;i++){
//         out << next[i]<< " ";
//     } 
// }

// CommonTrie::CommonTrie() {
//     t.emplace_back(-1, -1); //garbage node
//     t.emplace_back(0, '$'); //root node
//     t[1].link = 1;
// }

CommonTrie::CommonTrie(const std::vector<std::string> &v){
    t.emplace_back(new CommonTrieNode(-1, -1)); //garbage node
    t.emplace_back(new CommonTrieNode(0, '$')); //root node
    t[1]->link = 1;

    int p = 0;
    for(auto &s:v) p += s.length();
    leaves.reserve(v.size());
    t.reserve(p);
    for(auto &s:v) add_string(s);

}

// CommonTrie::CommonTrie(std::ifstream &in){
//     int treeSize;
//     in >> treeSize;
//     for(int i = 0;i<treeSize;i++)t.emplace_back(in);
//     int leavesSize;
//     in >> leavesSize;
//     leaves.resize(leavesSize);
//     for(int i = 0;i<leavesSize;i++)in >> leaves[i];
// }

// void CommonTrie::file_output(std::ofstream &out){
//     out << t.size() << " ";
//     for(int i = 0;i<(int)t.size();i++)t[i].file_output(out);
//     out << leaves.size() << " ";
//     for(int i = 0;i<(int)leaves.size();i++)out << leaves[i] << " ";
// }
 
int CommonTrie::traverse(int v, char ch){
    for(auto &[a,b] : t[v]->childs){
        if(a == string(1,ch)){
            return b;
        }
    }
    return 0;
}

void CommonTrie::add_string(string const& s) {
    int v = 1;
    for (char ch : s) {
        int child = traverse(v, ch);
        if(child == 0){
            t.emplace_back(new CommonTrieNode(v, ch));
            child = t.size()-1;
            t[v]->childs.emplace_back(make_pair(string(1,ch), child));
        }
        v = child;
    }
    if(t[v]->strIndex == -1) {
        leaves.push_back(v);
        t[v]->strIndex = leaves.size()-1;
    }
}

int CommonTrie::get_link(int v) {
    #ifdef DDEBUG
    assert(v>0);
    #endif
    if (t[v]->link == 0) {
        if (t[v]->p == 1) // if child of root
            t[v]->link = 1;
        else {
            int x = get_link(t[v]->p);
            char c = t[v]->pch;
            while(traverse(x, c) == 0 && x != 1){
                x = get_link(x);
            }
            t[v]->link = traverse(x, c);
            t[v]->link = (t[v]->link == 0 ? 1 : t[v]->link);
        }
    }
    return t[v]->link;
}

// long long CommonTrie::memory_required(){
//     return (t.capacity())*(sizeof(t)) + leaves.capacity()*(sizeof(int));
// }

void CommonTrie::convert_aho_to_ehog(){
    std::vector<bool>marked(t.size());
    for(int v:leaves){
        int temp = v;
        while(temp != 1){
            marked[temp] = true;
            temp = get_link(temp);
        }
    }
    std::vector<CommonTrieNode*>ehog_t;
    ehog_t.emplace_back(nullptr); // garbage node
    marked[1] = true;
    std::vector<int>conversion(t.size());
    std::function<void(int, int)> dfs;
    dfs = [&marked, &conversion, this, &ehog_t, &dfs](int v, int par){
        if(marked[v] == true){
            int eind = ehog_t.size();
            if(par)ehog_t[par]->childs.emplace_back(make_pair(".", eind));
            ehog_t.push_back(t[v]);
            ehog_t[eind]->p = par;
            ehog_t[eind]->aho_index = v;
            ehog_t[eind]->strIndex = t[v]->strIndex;
            conversion[v] = eind;
            std::list<std::pair<std::string, int>> childs_copy;
            swap(childs_copy, t[v]->childs);
            for(auto &[a,b] : childs_copy){
                dfs(b, eind);
            }
        }
        else{
            std::list<std::pair<std::string, int>> childs_copy;
            swap(childs_copy, t[v]->childs);
            for(auto &[a,b] : childs_copy){
                dfs(b, par);
            }
        }
    };
    dfs(1, 0);
    for(int i = 1;i<(int)ehog_t.size();i++){
        ehog_t[i]->link = conversion[get_link(ehog_t[i]->aho_index)];
    }
    for(int i = 1;i<(int)t.size();i++){
        if(marked[i] == false){
            delete t[i];
        }
    }
    for(int i = 0;i<(int)leaves.size();i++){
        leaves[i] = conversion[leaves[i]];
    }
    swap(ehog_t, t);
    isEHOG = true;
}

// EHOG::EHOG(std::ifstream &in){
//     int treeSize;
//     in >> treeSize;
//     for(int i = 0;i<treeSize;i++)t.emplace_back(in);
//     int leavesSize;
//     in >> leavesSize;
//     leaves.resize(leavesSize);
//     for(int i = 0;i<leavesSize;i++)in >> leaves[i];
// }

// void EHOG::file_output(std::ofstream &out){
//     out << t.size() << " ";
//     for(int i = 0;i<(int)t.size();i++)t[i].file_output(out);
//     out << leaves.size() << " ";
//     for(int i = 0;i<(int)leaves.size();i++)out << leaves[i] << " ";
// }

// long long EHOG::memory_required(){
//     long long mem = (t.capacity())*(sizeof(t)) + leaves.capacity()*(sizeof(int));
//     for(int i = 0;i<(int)t.size();i++){
//         mem += t[i].memory_required();
//     }
//     return mem;
// }
