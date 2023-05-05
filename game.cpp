#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
#define endl "\n"
using namespace __gnu_pbds;
using namespace std;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
#define int long long
const int MX = 1e5 + 10;

int mod = 1e9 + 7;

int getRandomNumbers(int lower, int upper)
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

bool isPalindrome(string s)
{

    for (int i = 0; i < s.size() / 2; i++)
        if (s[i] != s[s.size() - i - 1])
            return false;
    return true;
}

bool isPrime(int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int findGCD(vector<int> arr, int n)
{
    int result = arr[0];
    for (int i = 1; i < n; i++)
    {
        result = gcd(arr[i], result);

        if (result == 1)
        {
            return 1;
        }
    }
    return result;
}

vector<int> primeFactors(int n)
{
    vector<int> v;
    while (n % 2 == 0)
    {
        v.push_back(2);
        n = n / 2;
    }

    for (int i = 3; i <= sqrt(n); i = i + 2)
    {
        while (n % i == 0)
        {
            v.push_back(i);
            n = n / i;
        }
    }

    if (n > 2)
        v.push_back(n);
    return v;
}

vector<int> allFactors(int n)
{
    vector<int> v;
    for (int i = 1; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            if (n / i == i)
                v.push_back(i);

            else
            {
                v.push_back(i);
                v.push_back(n / i);
            }
        }
    }
    return v;
}

vector<int> factorize(int n)
{
    vector<int> res;
    for (int i = 2; i * i <= n; i++)
    {
        while (n % i == 0)
        {
            res.push_back(i);
            n /= i;
        }
    }
    if (n > 1)
        res.push_back(n);
    return res;
}

int nCr(int n, int r)
{
    int p = 1, k = 1;
    if (n - r < r)
    {
        r = n - r;
    }
    if (r != 0)
    {
        while (r)
        {
            p *= n;
            k *= r;
            int m = gcd(p, k);
            p /= m;
            k /= m;
            n--;
            r--;
        }
    }
    else
    {
        p = 1;
    }
    return p;
}

int power(int x, int y)
{
    int res = 1;
    while (y > 0)
    {
        if (y & 1)
            res = res % mod * x % mod;
        y = y >> 1;
        x = x % mod * x % mod;
    }
    return res;
}

class SGTree
{

    vector<int> seg;

public:
    SGTree(int n)
    {
        seg.resize(4 * n + 1);
    }

    void build(int ind, int low, int high, int arr[])
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

    int query(int ind, int low, int high, int l, int r)
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
        int left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 2, mid + 1, high, l, r);
        return left + right;
    }

    void update(int ind, int low, int high, int i, int val)
    {
        if (low == high)
        {
            seg[ind] += val;
            return;
        }

        int mid = (low + high) / 2;
        if (i <= mid)
            update(2 * ind + 1, low, mid, i, val);

        else
            update(2 * ind + 2, mid + 1, high, i, val);

        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }
};

void f()
{
    int n;
    cin >> n;
    int arr[n];
    int mx = -1;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        mx = max(mx, arr[i]);
    }

    mx += 1;
    int freq[mx];

    memset(freq, 0, sizeof(freq));

    for (int i = 0; i < n; i++)
    {
        freq[arr[i]]++;
    }

    SGTree sg(mx);

    sg.build(0, 0, mx - 1, freq);

    int cnt = 0;

    for (int i = 0; i < n; i++)
    {
        freq[arr[i]]--;
        sg.update(0, 0, mx - 1, arr[i], -1);

        cnt += sg.query(0, 0, mx - 1, 1, arr[i] - 1);
    }

    cout << cnt << endl;
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
    cin >> t;

    for (int i = 1; i <= t; i++)
    {
        // cout<<"Case #"<<i<<": ";
        f();
    }

    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
    return 0;
}