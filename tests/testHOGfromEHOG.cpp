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

double hog_construct(EHOG &ehog){
    timer time_hog;
    HOG hog(ehog);
    double time_hog_build = time_hog.end();
    hog.print_details(false);
    cout<< "," << time_hog_build;
    return time_hog_build;
}

void real_data_test(string fname, bool verbose) {
    string data_path = "./dump/ehog_dump/";
    ifstream fin;
    fin.open(data_path+fname, ios::in);
    if(!fin) {
        cout<<"couldn't open file: "<<fname<<endl;
        return;
    }
    EHOG ehog(fin);
    hog_construct(ehog);
}

int main(int argc, char **argv){
    real_data_test(argv[1], false);
}