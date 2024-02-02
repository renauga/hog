#include<bits/stdc++.h>
using namespace std;

#include "timer.h"
#include "trace.h"

#include "HOG-SKx.h"
typedef HOG_SKx HOG;

const int TRIALS = 10;
#define SEED 634
void test_validity_queries(){
    cout << "\nTesting validity of queries\n";
    vector<string> v = {"aabaa", "dbdaa", "aadbd"};
    HOG hog(v);
    trace(hog.marked);
    // assert(hog.marked == vector<bool>({0,1,0,1,0,0,1,0,0,1,0,0,1,0,1}));
    Hog hg = hog.make_hog();
    assert(hg.suffix_prefix_length(0,2)==2);
    assert(hg.suffix_prefix_length(2,0)==0);
    assert(hg.suffix_prefix_length(0,1)==0);
    assert(hg.suffix_prefix_length(1,0)==2);
    assert(hg.suffix_prefix_length(2,1)==3);
    assert(hg.suffix_prefix_length(1,2)==2);
    assert((hg.one_to_all(0) == std::vector<int>{5, 0, 2}));
    assert((hg.one_to_all(1) == std::vector<int>{2, 5, 2}));
    assert((hg.one_to_all(2) == std::vector<int>{0, 3, 5}));
    trace(hg.top(0,3));
    trace(hg.top(1,3));
    trace(hg.top(2,3));
    cout<<"All tests passed\n";
}

pair<double, double> get_mean_and_sd(vector<double> &a) {
    sort(a.begin(), a.end());
    double sum = 0, sq_sum = 0, cnt=0;
    for(int i=a.size()/10;i<(int)(9*a.size()/10);i++) {
        sum += a[i];
        sq_sum += a[i]*a[i];
        cnt++;
    }
    double avg = sum/cnt, sd = sqrt(sq_sum/cnt - avg*avg);
    return {avg, sd};
}

void stress_test_with(const vector<string>& v, int seed) {
    HOG hog;
    hog.add_strings(v);
    timer t1;
    hog.construct();
    std::cout << t1.end() << std::endl;

    timer t2;
    Hog hg = hog.make_hog();
    std::cout << t2.end() << "\n";
    std::cout << "Construction Finished" << std::endl;
    srand(seed);
    vector<pair<int,int>>queries(TRIALS);
    for(int i = 0;i<TRIALS;i++){
        int a = rand()%hg.sorted_order_conversion.size();
        int b = rand()%hg.sorted_order_conversion.size();
        if(a==b)i--;
        else{
            queries[i] = {a,b};
        }
    }
    // trace(hg.suffix_prefix_length(46113,32788));
    timer q_time;
    for(int i = 0;i<TRIALS;i++){
        trace(queries[i].first, queries[i].second);
        if(hg.suffix_prefix_length(queries[i].first, queries[i].second) == -1){
            cout << queries[i].first << " " <<  queries[i].second << "\n";
            break;
        }
        std::cout << hg.suffix_prefix_length(queries[i].first, queries[i].second) << "\n";
    }
    for(int i = 0;i<TRIALS;i++){
        trace(hg.one_to_all(rand()%hg.sorted_order_conversion.size()));
    }
    double tot_time = q_time.end();
    std::cout << "Time Taken for " << TRIALS << "queries is " << tot_time << "\n";
}

void stress_test_with_all(const vector<string>& v, int seed) {
    HOG hog;
    hog.add_strings(v);
    timer t1;
    hog.construct();
    std::cout << t1.end() << std::endl;

    timer t2;
    Hog hg = hog.make_hog();
    std::cout << t2.end() << "\n";
    std::cout << "Construction Finished" << std::endl;
    srand(seed);
    timer q_time;
    for(int i = 0;i<TRIALS;i++){
        trace(hg.one_to_all(rand()%hg.sorted_order_conversion.size()));
    }
    double tot_time = q_time.end();
    std::cout << "Time Taken for " << TRIALS << "queries is " << tot_time << "\n";
}
void stress_test_with_top(const vector<string>& v, int seed) {
    HOG hog;
    hog.add_strings(v);
    timer t1;
    hog.construct();
    std::cout << t1.end() << std::endl;

    timer t2;
    Hog hg = hog.make_hog();
    std::cout << t2.end() << "\n";
    std::cout << "Construction Finished" << std::endl;
    srand(seed);
    timer q_time;
    for(int i = 0;i<TRIALS;i++){
        trace(hg.top(rand()%hg.sorted_order_conversion.size(), rand()%hg.sorted_order_conversion.size() + 1).second);
    }
    double tot_time = q_time.end();
    std::cout << "Time Taken for " << TRIALS << "queries is " << tot_time << "\n";
}
void real_data_test() {
    string data_path = "../hog/data/";
    // vector<string> filenames = {"clementina", "sinensis", "trifoliata", "elegans"};
    vector<string> filenames = {"trifoliata"};
    // vector<string> filenames = { "A_hydrophila_HiSeq",
    //                             "B_cereus_HiSeq",
    //                             "B_cereus_MiSeq",
    //                             "B_fragilis_HiSeq" ,
    //                             "M_abscessus_HiSeq" ,
    //                             "M_abscessus_MiSeq",
    //                             "R_sphaeroides_HiSeq" ,
    //                             "R_sphaeroides_MiSeq" ,
    //                             "S_aureus_HiSeq",
    //                             "V_cholerae_HiSeq" ,
    //                             "V_cholerae_MiSeq",
    //                             "X_axonopodis_HiSeq"}; 
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

        stress_test_with_top(v, SEED);
    }
}

int main(){
    test_validity_queries();
    real_data_test();
}