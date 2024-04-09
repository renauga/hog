#include <bits/stdc++.h>
using namespace std;
#include "../malloc_count/malloc_count.h"
#ifdef SSP

#include "HOG-SSP.h"
typedef HOG_SSP HOG;

#elif SK

#include "HOG-SK.h"
typedef HOG_SK HOG;

#elif BCER

#include "HOG-BCER.h"
typedef HOG_BCER HOG;

#elif EC

#include "HOG-EC.h"
typedef HOG_EC HOG;

#else
#include "HOG-SSP.h"
typedef HOG_SSP HOG;

#endif

#include "EHOG.h"
#include "Aho-Cora.h"
#include "timer.h"

double aho_construct_and_print(const vector<string> &v, const string fileOutputName){
    timer time_aho;
    AhoCorasick aho(v);
    double time_aho_build = time_aho.end();
    ofstream fout;
    fout.open(fileOutputName);
    aho.file_output(fout);
    cout << "," << aho.memory_required() << "," << time_aho_build;
    return time_aho_build;
}

void real_data_test(string fname, bool verbose) {
    string data_path = "data/";
    cout<<fname;
    fstream fin;
    fin.open(data_path+fname, ios::in);
    if(!fin) {
        cout<<"couldn't open file: "<<fname<<endl;
        return;
    }
    long long n, total_length = 0;
    fin>>n;
    vector<string> v(n);
    for(int i=0;i<n;i++) {
        fin>>v[i];
        total_length += v[i].length();
    }
    if(verbose){
        cout<<"Number of strings = "<<v.size()<<'\n'<<"Sum of lengths = "<<total_length<<'\n';
    }
    else{
        cout<<","<<v.size()<<","<<total_length;
    }
    string ahoDumpPath = "./dump/aho_dump/" + fname;
    aho_construct_and_print(v, ahoDumpPath);
}

int main(int argc, char **argv){
    real_data_test(argv[1], false);
}