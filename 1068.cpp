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
int k;
vector<int>sol;
ll dp[2][2][10][90][90];

ll go(int pos,int isSmall,int isStart,int val,int num)
{
//here val is the (sum of the digits)%k
//num is the num%k
//if both are zero then the condition is fullfilled
    if(pos == sol.size()){
        if(val == 0 && num == 0){
            return 1LL;
        }
        else return 0LL;
    }
    ll &ret = dp[isSmall][isStart][pos][val][num];

    if(ret != -1LL) return ret;
    ret = 0LL;
    int last = isSmall ? 9 : sol[pos];

    if(!isStart){
        rep(i,0,last+1){
            ret += go(pos+1,isSmall | i < sol[pos],0,(val+i)%k,(num*10 + i)%k);
        }
    }
    else{
        rep(i,1,last+1){
            ret += go(pos+1,isSmall | i < sol[pos],0,(val+i)%k,(num*10+i)%k);
        }
        ret += go(pos+1,1,1,0,0);
    }

    return ret;


}

ll cal(ll val)
{
    if(val < k) return 0LL;
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
    ll ans = go(0,0,1,0,0LL);
    return ans;
}

int main()
{
    int t = 0,T;
    sc("%d",&T);
    while(++t <= T){
        sc("%lld%lld%d",&m,&n,&k);
        if(k > 81 || n < k){
            pc("Case %d: 0\n",t);
            continue;
        }

        ll p1 = cal(m-1);
        if(p1 > 0) p1--;
        //As num 0 is counted we have to substruct that from answer
        //cout << p1 << endl;
        ll p2 = cal(n);
        if(p2 > 0) p2--;
        //cout << p2 << endl;
        pc("Case %d: %lld\n",t,p2-p1);
    }

	return 0;
}



