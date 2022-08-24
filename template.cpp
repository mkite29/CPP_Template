#pragma comment(linker, "/stack:200000000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include<bits/stdc++.h>
using namespace std;


#define int                    long long
#define ll                     long long
#define fi                     first
#define se                     second
#define pb                     push_back
#define vi                     vector<int>
#define ump                    unordered_map<int,int>
#define pqd                    priority_queue<int>
#define pqi                    priority_queue<int,vi,greater<int> >
#define pii                    pair<int,int>
#define setbits(x)             __builtin_popcountll(x)
#define sp(a,x)                fixed<<setprecision(x)<<a
#define Mod                    1000000007
#define mod                    998244353
#define PI                     3.141592653589793238
#define pi                     31415926
#define linf                   1000000000000000000
#define iinf                   INT_MAX
#define loop(i,k,n)            for(int i = k;i<n;i++)
#define endl                     "\n"
#define fio                     ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

//1.Normal Method for a Power b in O(log b)
int powab(int a,int b)
{
    int result = 1;

    while(b > 0)
    {
        if(b%2 == 0)
        {
            a = a*a;
            b = b/2;
        }
        else
        {
            result = result * a;
            b = b - 1;
        }
    }
    
    return result;    
}

//1.1 Power (a,b) Recursively
int powabR(int a,int b)
{    
    //base case
    if(b == 0)
        return 1;

    //recursive approach
    int subtask1 = powabR(a,b/2);

    //self work

    return (b%2 == 0) ? subtask1*subtask1 : a*subtask1*subtask1;

    // if(b%2 == 0)
    //     return subtask1*subtask1;
    
    // else
    //     return a*subtask1*subtask1;
}


//2.Mod power pow(a,b,m) Recursively
int powMR(int a,int b,int m)
{
    if(b == 0)
        return 1;

    else if(b%2 == 0)
    {
        int t = powMR(a ,b/2,m);
        return (1LL*t*t) % m;
    }
    else
    {
        int t = powMR(a,b/2,m);
        return ((((1LL*t*t)%m) * a )%m);
    }
}

//Power mod Iteratively
int powMI(int a ,int b,int m)
{
    int ans = 1;
    int r = 1;

    if( b == 0)
    {
        return 1 % m;
    }

    while(r <= b)
    {
        if(r & b)
        {
            ans = ( (1LL * ans * a) % m );
        }

        a = ((1LL * a * a) % m);

        r <<= 1;
    }

    return ans;

}

//Modular Inverse in O(logm) time assuming m is prime.
int modI(int t ,int m)
{
    return powMI(t , m-2 , m); 
}

//Find simple nCr % m using precomputation
int nCr(int N ,int r, int m)
{
    int fact[N+1];
    int inverfact[N+1];
    
    fact[0] = 1;
    for(int i = 1;i <= N;i++)
        fact[i] = (1LL * i * fact[i-1]) % m;

    inverfact[0] = 1;
    for(int i=1;i<=N;i++)
    {
        inverfact[i]=modI(fact[i],m);
    }

    return (fact[N]*(inverfact[r]*inverfact[N-r])%m)%m;
}

//Finding nCr % m. m is prime number > n
int nCrM(int n ,int r ,int m)
{    
    
    int fact[n+1];
    fact[0] = 1;

    for(int i = 1;i <= n;i++)
    {
        fact[i] = (1LL * i * fact[i-1]) % m;
    }

    return (fact[n] * (modI(fact[r],m)%m * modI(fact[n-r],m)%m )% m);

}


bool cmp1(pii a , pii b)
{
    return a.first < b.first;
}

bool cmp2(pii a , pii b)
{
    return a.first > b.first;
}

bool cmp3(pii a , pii b)
{
    return a.second < b.second;
}

bool cmp4(pii a , pii b)
{
    return a.second > b.second;
}


void show(vector<pii> &v)
{
    for(auto i : v)
        cout<<i.first<<' '<<i.second<<' ';
}



void show(vector <int> &v)
{
    for(auto i:v)
        cout<<i<<"\n";

    cout<<endl;
}

bool mysort(pii a , pii b){

    if(a.second == b.second){
        return a.first < b.first;
    }

    return a.second > b.second;
}

void printArray(vector<int> &arr){
    for(auto &i : arr){
        cout<<i<<" ";
    }
    cout<<endl;
}

bool value1 =  false;
bool value2 = false;

int minMoves(vector<int> &arr, int left, int right,vector<vector<int>> &dp,int m, int M){

    if(left - right > 0)
        return INT_MAX;

    if(left == right)
        return 0;

    if(dp[left][right] != -1)
        return dp[left][right];

    
    int l = minMoves(arr,left+1,right,dp,m,M) + 1;
    int r = minMoves(arr,left,right-1,dp,m,M) + 1;

    if(arr[left] == m || arr[right] == m)value1 = true;

    if(arr[right] == M || arr[left] == M)value2 = true;


    if(value1 && value2)
        return min(l,r);

    return dp[left][right] = min(l,r);
}


int minCost(int sr, int sc, int dr, int dc, vector<vector<int>> &arr, vector<vector<int>> &dp){

    if(sr > dr || sc > dc)
        return INT_MAX;

    if(sr == dr && sc == dc)
        return arr[sr][sc];

    if(dp[sr][sc] != -1)
        return dp[sr][sc];

    int right = minCost(sr,sc+1,dr,dc,arr,dp) + arr[sr][sc];
    int down = minCost(sr+1,sc,dr,dc,arr,dp) + arr[sr][sc];

    return dp[sr][sc] = min(right,down);
}


int memo(int sr, int sc, int dr, int dc, vector<vector<int>> &arr, vector<vector<int>> &dp){
    
    if(sr > dr || sc > dc)
        return 0;

    if(sr == dr && sc == dc){
        return arr[sr][sc];
    }
    
    if(dp[sr][sc] != INT_MAX)
        return dp[sr][sc];


    int r = memo(sr,sc+1,dr,dc,arr,dp) + arr[sr][sc];
    int d = memo(sr+1,sc,dr,dc,arr,dp) + arr[sr][sc];


    return dp[sr][sc] = (r + d);


   
    //bitmaksing
}


bool isGood(vector<int> &nums, int mid){

    for(int i = 0;i<nums.size();i++)
    {
        if(nums[i] < mid){
            mid -= nums[i];
        }

    }

    return (mid > 0) ? true : false;
}


int maxd(int src , vector<int> *adj , vector<bool> &vis){

    if(vis[src])
        return 0;

    vis[src] = 1;
    int curr = 1;
    for(const auto &i : adj[src]){
        curr += maxd(i,adj,vis);
    }

    return curr;
}


void solve(){

    int n;
    cin>>n;

    vector<int> arr(n);
    for(int i = 0;i<n;i++)
        cin>>arr[i];


    vector<int> *adj = new vector<int>[n + 1];
    for(int i = 1;i<=n;i++){

        if(arr[i] != -1){
            adj[i].push_back(arr[i]);
        }
    }

    vector<bool> vis(n+1,0);
    for(int i = 1;i<=n;i++){
        cout<<maxd(i,adj,vis)<<endl;
    }



}

//Let's Start The Magic
int32_t main(){    
fio;

solve();

cerr << "Time : " << 1000 * ((double)clock()) / (double)CLOCKS_PER_SEC << "ms\n";
return 0;

}
