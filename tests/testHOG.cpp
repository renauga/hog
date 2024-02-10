#include<bits/stdc++.h>
using namespace std;

#include "timer.h"
#include "trace.h"

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
#include "HOG-SK.h"
typedef HOG_SK HOG;
#endif

const int TRIALS = 3;

//TODO : write bigger validity test comparing dumps from both algos
void test_validity() {
    cout << "\nTesting validity of algorithm\n";
    vector<string> v = {"aabaa", "aadbd", "dbdaa"};
    // vector<string> v = {"aabaab"};
    HOG hog(v);
    trace(v);
    assert(hog.marked == vector<bool>({0,1,0,1,1,1,0,1,1}));
    cout<<"All tests passed\n";
}

void test_with(const vector<string>& v) {
    HOG hog;
    cout<<"Building Aho-Corasick automaton..."; cout.flush();
    timer ahocora_t;
    hog.add_strings(v);
    cout<<"Elapsed time: " << ahocora_t.end() << "s\n";
    
    cout<<"Constructing HOG..."; cout.flush();
    timer hog_t;
    hog.construct();
    cout<<"Elapsed time: " << hog_t.end() << "s\n";

    int cnt = 0;
    for(auto b:hog.marked) cnt+=b;
    cout << "Size of Aho-Corasick trie: " << hog.marked.size()-1 << ", Size of HOG: " << cnt
         << ", Compression factor: "<< (double)cnt/(hog.marked.size()-1) << '\n';
}

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

void stress_test_with(const vector<string>& v) {
    vector<double> aho_times(TRIALS), hog_times(TRIALS), tot_times(TRIALS);
#ifdef DATASET_MEMORY
    exit(0);
#endif
    for(int i=0;i<TRIALS;i++) {
        HOG hog;
        timer ahocora_t;
        hog.add_strings(v);
        aho_times[i] = ahocora_t.end();
#ifdef AHO_CORASICK_MEMORY
    exit(0);
#endif
        timer hog_t;
        hog.construct();
        hog_times[i] = hog_t.end();
        tot_times[i] = aho_times[i] + hog_times[i];
        if(i == TRIALS - 1)hog.print_details();
    }
    auto aho_data = get_mean_and_sd(aho_times);
    auto hog_data = get_mean_and_sd(hog_times);
    auto tot_data = get_mean_and_sd(tot_times);
    cout<<fixed<<setprecision(6);
    cout<<"Aho: "<<aho_data.first<<' '<<aho_data.second<<'\n';
    cout<<"HOG: "<<hog_data.first<<' '<<hog_data.second<<'\n';
    cout<<"Tot: "<<tot_data.first<<' '<<tot_data.second<<std::endl;
}

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

    stress_test_with(v);
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

    stress_test_with(v);
}

void real_data_test(std::string dataset_name) {
    string data_path = "data/";
    // vector<string> filenames = {"clementina", "sinensis", "trifoliata", "elegans"};
    vector<string> filenames = {dataset_name};

    for(string fname:filenames) {
        cout<<'\n'<<fname<<":\n";
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
        cout<<"Number of strings = "<<v.size()<<'\n'<<"Sum of lengths = "<<total_length<<'\n';

        stress_test_with(v);
    }
}

int main(int argc, char **argv) {
    #ifdef SSP
        cout<<"\nUsing algo by SSP...\n";
    #elif SK
        cout<<"\nUsing algo by SK...\n";
    #elif BCER
        cout<<"\nUsing algo by BCER...\n";
    #else
        cout<<"\nUsing algo by EC...\n";
    #endif
    // int seed = chrono::system_clock::now().time_since_epoch().count();
    // int n = pow(10, stod(argv[1])/10), p = pow(10, stod(argv[2])/10),seed = 42;
    // double o = stod(argv[3]);
    std::string d_name = argv[1];
    // test_validity();
    // test_validity_queries();
    // random_strings_stress_test(n, p, seed);
    // random_string_reads_stress_test(n, p, o, seed);
    real_data_test(argv[1]);
    return 0;
}