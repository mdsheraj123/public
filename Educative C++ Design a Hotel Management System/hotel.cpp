/* author: Mohammad Sheraj */
/* email: mdsheraj123@gmail.com */
/* Clang++17 */
// freopen("input.txt", "r", stdin);
// freopen("output.txt", "w", stdout);
// Use long long instead of long for answer too
// ios_base::sync_with_stdio(0);
// cin.tie(0);
// cout.tie(0);
//////////////
// printf("%.2lf",double_value); // cout.precision(17);
// cout<<"Case #"<<test_case<<": "<<answer<<endl;
///////////////////////////////////////////////////////////////
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <stack>
#include <queue> //includes priority_queue <int, vector<int>, greater<int> > pq
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <set> //sorts by value
#include <map> //sorts by key
#include <algorithm> //max/min //lower_bound/upper_bound //binary_search //reverse //next_permutation
#include <math.h> //ceil/floor
#include <climits> //INT_MIN
// #include <fstream>
// #include <numeric> //gcd //there will be sqiggly red line but no compilation error
// #include <time.h> //clock_t clock() //CLOCKS_PER_SEC
// #include <chrono> //time
// #include <thread> // std::thread
// #include <mutex> // std::mutex
using namespace std;
//////////////////////////////////////////////////////////////////////////

void solve(int a,int b,int c,int answer) {
    if(a+b+c>answer) {
        answer = a+b+c;
    }
    if(a+b*c>answer) {
        answer = a+b*c;
    }

    if((a+b)*c>answer) {
        answer = (a+b)*c;
    }

    if(a*b+c>answer) {
        answer = a*b+c;
    }

    if(a*(b+c)>answer) {
        answer = a*(b+c);
    }
    if(a*b*c>answer) {
        answer = a*b*c;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #ifdef SHERAJ
        freopen("input.txt"  , "r", stdin);
    #endif
    // int T;
    // cin>>T;
    // for(int test_case = 1;test_case<=T;test_case++) {
    // }
    int a,b,c;
    cin>>a>>b>>c;

    int answer = INT_MIN;
    solve(a,b,c,answer);
    cout<<answer<<endl;
}