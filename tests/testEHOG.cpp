#include <bits/stdc++.h>
using namespace std;

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

double ehog_construct_and_print(const vector<string> &v, const string fileOutputName){
    timer time_ehog;
    AhoCorasick aho(v);
    EHOG ehog(aho);
    double time_ehog_build = time_ehog.end();
    ofstream fout;
    fout.open(fileOutputName);
    ehog.file_output(fout);
    cout << "," << ehog.memory_required() << "," << time_ehog_build;
    return time_ehog_build;
}

void real_data_test(string fname, bool verbose) {
    string data_path = "data/";
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
    string ehogDumpPath = "./dump/ehog_dump/" + fname;
    ehog_construct_and_print(v, ehogDumpPath);
}

int main(int argc, char **argv){
    real_data_test(argv[1], false);
}