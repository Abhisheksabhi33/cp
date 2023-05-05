#include <bits/stdc++.h>
using namespace std;
#define int long long

void build(int ind, int low, int high, vector<int> &arr, vector<int> &seg)
{
    if (low == high)
    {
        seg[ind] = arr[low];
        return;
    }
    int mid = (low + high) / 2;
    build(2 * ind + 1, low, mid, arr, seg);
    build(2 * ind + 2, mid + 1, high, arr, seg);
    seg[ind] = (seg[2 * ind + 1] + seg[2 * ind + 2]);
}

int query(int ind, int low, int high, int l, int r, vector<int> &seg)
{
    if (low >= l && high <= r)
    {
        return seg[ind];
    }
    if (high < l || low > r)
    {
        return 0;
    }
    int mid = (low + high) / 2;
    int left = query(2 * ind + 1, low, mid, l, r, seg);
    int right = query(2 * ind + 2, mid + 1, high, l, r, seg);
    return (left + right);
}

void update(int ind, int low, int high, int i, int val, vector<int> &seg)
{
    if (low == high)
    {
        seg[ind] = val;
        return;
    }

    int mid = (low + high) / 2;
    if (i <= mid)
        update(2 * ind + 1, low, mid, i, val, seg);

    else
        update(2 * ind + 2, mid + 1, high, i, val, seg);

    seg[ind] = (seg[2 * ind + 1]+ seg[2 * ind + 2]);
}

void f()
{

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    vector<int> seg(4 * n);
    build(0, 0, n - 1, arr, seg);
    
    int q;
    cin >> q;
    while (q--)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            int l, r;
            cin >> l >> r;
            l--;r--;
            cout << query(0, 0, n - 1, l, r, seg) << endl;
        }
        else
        {
            int i, val;
            cin >> i >> val;
            i--;
            update(0, 0, n - 1, i, val, seg);
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