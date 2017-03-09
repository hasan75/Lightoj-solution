#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ii,int> iii;


#define N 51
#define M 250001
#define INF 100000000
#define PI acos(-1)
#define rep(i,a,b) for(int i = a; i < b; i++)
#define reps(i,a,b) for(int i = a; i >= b; i--)
#define sc scanf
#define pc printf
#define pb push_back
#define F first
#define S second

ll m,n;
vector<int>sol;
ll dp[2][2][40][40];

ll go(int pos,int isSmall,int isStart,ll val)
{
    //cout << pos << " " << isSmall << " " <<isStart << " " << val << endl;
    if(pos == sol.size()) return val;
    ll &ret = dp[isSmall][isStart][pos][val];
    //cout << "yes" << endl;
    if(ret != -1LL) return ret;
    ret = 0LL;
    int last = isSmall ? 9 : sol[pos];
    //cout << last << endl;
    if(!isStart){
        rep(i,0,last+1){
            ret += go(pos+1,isSmall | i < sol[pos],0,i == 0 ? val + 1LL : val);
        }
    }
    else{
        rep(i,1,last+1){
            ret += go(pos+1,isSmall | i < sol[pos],0,i == 0 ? val + 1LL : val);
        }
        ret += go(pos+1,1,1,0);
        //this one for reinitializing newer smaller digit number
        //suppose we give cal(100)
        //if you miss out this transition you can't produce two digit number
    }

    return ret;


}

ll cal(ll val)
{
    if(val < 0) return 0LL;
    if(val <= 9) return 1LL;
    sol.clear();
    while(val){
        sol.pb(val%10);
        val/=10;
    }
    reverse(sol.begin(),sol.end());
    //cout << sol.size() << endl;
    //rep(i,0,sol.size()) cout << sol[i] << " ";
    //cout << endl;
    memset(dp,-1LL,sizeof(dp));
    ll ans = go(0,0,1,0) + 1LL;
    return ans;
}

int main()
{
    int t = 0,T;
    sc("%d",&T);
    while(++t <= T){
        sc("%lld%lld",&m,&n);
        ll p1 = cal(m-1);
        //cout << p1 << endl;
        ll p2 = cal(n);
        //cout << p2 << endl;
        pc("Case %d: %lld\n",t,p2-p1);
    }

	return 0;
}






