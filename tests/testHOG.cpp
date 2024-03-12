#include<bits/stdc++.h>
using namespace std;

#include "timer.h"
#include "trace.h"

#ifdef SSP

#include "HOG-SSP.h"
typedef HOG_SSP HOG;
#include "EHOG.h"
typedef EHOG EHOG;
#elif SK

#include "HOG-SK.h"
typedef HOG_SK HOG;
#include "EHOG.h"
typedef EHOG EHOG;
#elif BCER

#include "HOG-BCER.h"
typedef HOG_BCER HOG;
// #include "EHOGx.h";
typedef EHOGx EHOG;
typedef EHOGx_NODE EHOG_NODE;
#elif EC

#include "HOG-EC.h"
typedef HOG_EC HOG;
// #include "EHOGx.h";
typedef EHOGx EHOG;
typedef EHOGx_NODE EHOG_NODE;
#else
#include "HOG-SK.h"
typedef HOG_SK HOG;
#include "EHOG.h";
typedef EHOG EHOG;
#endif


const int TRIALS = 1;

pair<double, double> get_mean_and_sd(vector<double> &a) {
    sort(a.begin(), a.end());
    double sum = 0, sq_sum = 0, cnt=0;
    for(int i=0;i<(int)a.size();i++) {
        sum += a[i];
        sq_sum += a[i]*a[i];
        cnt++;
    }
    double avg = sum/cnt, sd = sqrt(sq_sum/cnt - avg*avg);
    return {avg, sd};
}
// #ifdef EHOG_CONSTRUCTION
void stress_test_with_ehog(const vector<string>& v, std::string filename) {
    vector<double> ehog_times(TRIALS), hog_times(TRIALS), tot_times(TRIALS);
    ofstream fout;
#ifdef SSP
    fout.open("./ehog_dump/"+filename+"_ehog_object", ios::out);
#elif SK
    fout.open("./ehog_dump/"+filename+"_ehog_object", ios::out);
#elif EC
    fout.open("./ehog_dump/"+filename+"_ehogx_object", ios::out);
#else
    fout.open("./ehog_dump/"+filename+"_ehogx_object", ios::out);
#endif
    
    if(!fout) {
        cout<<"couldn't open file: "<<filename<<endl;
        return;
    }
    for(int i=0;i<TRIALS;i++) {
        EHOG ehog;
        timer ehog_t;
        ehog.add_strings(v);
        ehog_times[i] = ehog_t.end();
        ehog.dump(fout);
        // cout << ehog.t.size() << "\n";
        // cout << ehog.leaves.size() << "\n";
    }
    auto ehog_data = get_mean_and_sd(ehog_times);
    cout<<fixed<<setprecision(6);
    // cout<<"EHOG: "<<ehog_data.first<<' '<<ehog_data.second<<std::endl;
    cout<<","<<ehog_data.first<<','<<ehog_data.second<<std::endl;
}
// #else
void stress_test_with_hog(std::string filename) {
    vector<double> hog_times(TRIALS);
    ifstream fin;
#ifdef SSP
    fin.open("./ehog_dump/"+filename+"_ehog_object", ios::in);
#elif SK
    fin.open("./ehog_dump/"+filename+"_ehog_object", ios::in);
#elif EC
    fin.open("./ehog_dump/"+filename+"_ehogx_object", ios::in);
#else
    fin.open("./ehog_dump/"+filename+"_ehogx_object", ios::in);
#endif
    
    if(!fin) {
        cout<<"couldn't open file: "<<filename<<endl;
        return;
    }
    // cout << "here" << std::endl;
    long long memehog;
    for(int i=0;i<TRIALS;i++) {
        HOG hog;
        hog.inp(fin);
        memehog = sizeof(EHOG_NODE)*(hog.t.size()) + sizeof(int)*(hog.leaves.size());
        for(int i = 0;i<(int)hog.t.size();i++){
            memehog+=hog.t[i].memory_calculate();
        }
        timer hog_t;
        hog.construct();
        hog_times[i] = hog_t.end();
        if(i == TRIALS-1)hog.print_details(false);
    }
    auto hog_data = get_mean_and_sd(hog_times);
    cout<<fixed<<setprecision(6);
    // cout<<"ehog memory: "<<memehog<<"\n";
    // cout<<"hog: "<<hog_data.first<<' '<<hog_data.second<<std::endl;
    cout<<","<<memehog<<","<<hog_data.first<<','<<hog_data.second<<std::endl;
}
// #endif
void random_strings_stress_test(int n, int p, int seed) {
    assert(p>=n);
    int len = p/n;
    // cout << "\nTesting on randomly generated strings...\n" << "N = " << n << ", P = " << p << '\n';
    cout << n << ' ' << p << ' ';
    srand(seed);
    vector<string> v;
    for(int i=0;i<n;i++) {
        string s = "";
        for(int j=0;j<len;j++) {
            s += ('a'+rand()%alphabet);
        }
        v.push_back(s);
    }

    // stress_test_with(v);
}

void random_string_reads_stress_test(int n, int p, double overlap, int seed) {
    assert(p>=n);
    assert(0.0<overlap);
    assert(overlap<1.0);
    int len = p/n;
    int total_len = p*(1.0-overlap) + len*overlap;
    // cout << "\nTesting on randomly generated reads on a randomly generated string...\n" << "N = " << n << ", P = " << p << ", o = " << overlap << '\n';
    cout << n << ' ' << p << ' ' << overlap << ' ';
    srand(seed);
    string complete_string = "";
    for(int i=0;i<total_len;i++) complete_string += ('a' + rand()%alphabet);
    vector<string> v;
    // might miss a few ending characters
    for(double i=0;(int)i<=total_len-len;i+=(double)len*(1.0-overlap)) {
        v.push_back(complete_string.substr((int)i,len));
    }

}

void real_data_test(std::string dataset_name) {
    string data_path = "/home/user/parth/data/";
    vector<string> filenames = {dataset_name};

    for(string fname:filenames) {
        // cout<<fname<<":\n";
        cout<<fname;
#ifdef EHOG_CONSTRUCTION
        fstream fin;
        fin.open(data_path+fname, ios::in);
        if(!fin) {
            cout<<"couldn't open file: "<<fname<<endl;
            continue;
        }
        long long n, total_length = 0;
        fin>>n;
        vector<string> v(n);
        for(int i=0;i<n;i++) {
            fin>>v[i];
            total_length += v[i].length();
        }
        // cout<<"Number of strings = "<<v.size()<<'\n'<<"Sum of lengths = "<<total_length<<'\n';
        cout<<","<<v.size()<<","<<total_length;
        stress_test_with_ehog(v,fname);
#else
        stress_test_with_hog(fname);
#endif
    }
}

int main(int argc, char **argv) {
    // #ifdef SSP
    //     cout<<"\nUsing algo by SSP...\n";
    // #elif SK
    //     cout<<"\nUsing algo by SK...\n";
    // #elif BCER
    //     cout<<"\nUsing algo by BCER...\n";
    // #else
    //     cout<<"\nUsing algo by EC...\n";
    // #endif
    // int seed = chrono::system_clock::now().time_since_epoch().count();
    // int n = pow(10, stod(argv[1])/10), p = pow(10, stod(argv[2])/10),seed = 42;
    // double o = stod(argv[3]);
    // test_validity();
    // test_validity_queries();
    // random_strings_stress_test(n, p, seed);
    // random_string_reads_stress_test(n, p, o, seed);
    real_data_test(argv[1]);
    return 0;
}