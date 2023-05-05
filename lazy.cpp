#include <bits/stdc++.h>
using namespace std;
#define int long long

//  https://ideone.com/gvipU8

class ST
{

    vector<int> seg;
    vector<int> lazy;

public:
    ST(int n)
    {
        seg.resize(4 * n);
        lazy.resize(4 * n);
    }

    void build(int ind, int low, int high, vector<int> &arr)
    {
        if (low == high)
        {
            seg[ind] = arr[low];
            return;
        }

        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    void update(int ind, int low, int high, int l, int r, int val)
    {
        // update the previous remaining updates
        // and propagate downwards
        if (lazy[ind] != 0)
        {
            seg[ind] += (high - low + 1) * lazy[ind];
            if (low != high)
            {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;
        }

        // no overlap

        if (high < l || low > r)
        {
            return;
        }

        // complete overlap

        if (low >= l && high <= r)
        {
            seg[ind] += (high - low + 1) * val;
            if (low != high)
            {
                lazy[2 * ind + 1] += val;
                lazy[2 * ind + 2] += val;
            }
            return;
        }

        // partial overlap

        int mid = (low + high) / 2;
        update(2 * ind + 1, low, mid, l, r, val);
        update(2 * ind + 2, mid + 1, high, l, r, val);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    int query(int ind, int low, int high, int l, int r){
        // update the previous remaining updates
        // and propagate downwards
        if (lazy[ind] != 0)
        {
            seg[ind] += (high - low + 1) * lazy[ind];

            if (low != high)
            {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;
        }

        // no overlap

        if (high < l || low > r)
        {
            return 0;
        }

        // complete overlap
        if(low>=l && high<=r){
            return seg[ind];
        }

        // partial overlap
        
        int mid = (low + high) / 2;
        int left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 2, mid + 1, high, l, r);
        return left + right;


    }
};

void f()
{
     int n; cin>>n;
        vector<int> arr(n);
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }

        ST st(n);
        st.build(0,0,n-1,arr);

        int q; cin>>q;
        while(q--){
            int type; cin>>type;
            if(type==1){
                int l,r; cin>>l>>r;
                cout<<st.query(0,0,n-1,l,r)<<endl;
            }
            else{
                int l,r,val; cin>>l>>r>>val;
                st.update(0,0,n-1,l,r,val);
            }
        }

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