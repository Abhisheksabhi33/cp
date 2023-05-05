#include <bits/stdc++.h>
using namespace std;
#define int long long

int getRandomNumbers(int lower, int upper)
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

struct Interactor{
    
    vector<int>arr;
    int n;

    int limitQueires = 0;
    int queries = 0;

    Interactor(int n_){
        n = n_;
        arr.resize(n);

        for(int i =0; i<n; i++){
            arr[i] = getRandomNumbers(1, 100);
        }

        cout<<" Hidden Array: ";
        for(auto i: arr){
            cout<<i<<" ";
        }
        cout<<endl;
    }
    
    int query(int l, int r){
        assert(l>=1 and r<=n and l<r);
        int sum = 0;
        for(int i=l; i<=r; i++){
            sum += arr[i-1];
        }
        return sum;
    }

    bool correctOutput(vector<int>output){
        assert(output.size() == n and output == arr);
        return true;
    }

};




void f(){

    
    // Interactor codeforces = Interactor(15);


    int n; 
    cin>>n;
    // n = codeforces.n;
       
   map<pair<int, int>, int>queriesMade;
   map<int, int>arr;
   int prev =-1;

   for(int i=2; i<=n; i++){
      cout<<"? "<<1<<" "<<i<<endl;
        int x;
         cin>>x;
        // x = codeforces.query(1, i);

        queriesMade[{1, i}] = x;
   }     

   cout<<"? "<<2<<" "<<n<<endl;
    int x; 
    cin>>x;
    // x = codeforces.query(2, n);

    queriesMade[{2, n}] = x;

    arr[1] = queriesMade[{1, n}] - queriesMade[{2, n}];
    int sum = arr[1];
    for(int i=2; i<=n; i++){
        arr[i] = queriesMade[{1, i}] - sum;
        sum += arr[i];
    }

    cout<<"! ";
    for(auto i: arr){
        cout<<i.second<<" ";
    }
    cout<<endl;

    
    // vector<int>output;
    // for(auto i: arr){
    //     output.push_back(i.second);
    // }

    // if(codeforces.correctOutput(output)){
    //     cout<<"Correct Output"<<endl;
    // }
    // else{
    //     cout<<"Wrong Output"<<endl;
    // }


}


signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("error.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    // cin >> t;

    for (int i = 1; i <= t; i++)
    {
        // cout<<"Case #"<<i<<": ";
        f();
    }

    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
    return 0;
}