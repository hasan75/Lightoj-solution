#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ii,int> iii;

#define INF 10000000
#define N 100005
#define M 16
#define MOD 1000000007
#define PI acos(-1)
#define rep(i,a,b) for(int i = a; i < b; i++)
#define reps(i,a,b) for(int i = a; i >= b; i--)
#define sc scanf
#define pc printf
#define pb push_back
#define F first
#define S second

vector<ii>sol;
int n,m,mx,smx,tot,root;
vector<int>adj[N];
bool vis[N];
int tree[N*4];

void init()
{
    rep(i,0,N){
        adj[i].clear();
        vis[i] = 0;
    }
    sol.clear();
    //sol1.clear();
}

void go(int u,int d)
{
    if(mx < d){
        mx = d;
        root = u;
    }
    tot++;
    vis[u] = 1;
    rep(j,0,adj[u].size()){
        int v =adj[u][j];
        if(!vis[v]){
            go(v,d+1);
        }
    }
}

void go1(int u,int pa,int d)
{
    if(smx < d){
        smx = d;
    }

    rep(j,0,adj[u].size()){
        int v = adj[u][j];
        if(v != pa){
            go1(v,u,d+1);
        }
    }
}

void build(int node,int ss,int se)
{
    if(ss == se){
        tree[node] = 0;
        return;
    }

    int mid = (ss + se) / 2;
    int lft = (node)<<1;
    int rgt = (lft|1);
    //cout <<node <<" " << lft << " " << rgt << endl;
    build(lft,ss,mid);
    build(rgt,mid+1,se);
    tree[node] = max(tree[lft],tree[rgt]);
}

void update(int node,int ss,int se,int in,int val)
{
    if(ss > in || se < in) return;
    if(ss >= in && se <= in){
        tree[node] = val;
        return;
    }

    int mid = (ss + se) / 2;
    int lft = (node)<<1;
    int rgt = (lft|1);
    //cout <<node <<" " << lft << " " << rgt << endl;
    update(lft,ss,mid,in,val);
    update(rgt,mid+1,se,in,val);
    tree[node] = max(tree[lft],tree[rgt]);
}

int query(int node,int ss,int se,int qs,int qe)
{
    if(ss > qe || se < qs) return 0;
    if(ss >= qs && se <= qe){
        return tree[node];
    }
    int mid = (ss + se) / 2;
    int lft = (node)<<1;
    int rgt = (lft|1);
    //cout <<node <<" " << lft << " " << rgt << endl;
    int a = query(lft,ss,mid,qs,qe);
    int b = query(rgt,mid+1,se,qs,qe);
    return max(a,b);

}

int main()
{
    int t = 0,T;
    sc("%d",&T);
    while(++t <= T){
        init();
        sc("%d%d",&n,&m);
        rep(i,0,m){
            int x,y;
            sc("%d%d",&x,&y);
            adj[x].pb(y);
            adj[y].pb(x);
        }

        rep(i,1,n+1){
            if(!vis[i]){
                tot = 0;
                mx = -1;
                smx = -1;
                root = 0;
                go(i,0);
                go1(root,-1,0);
                sol.pb(ii(tot,smx));
                //sol1.pb(ii(smx,tot));
            }
        }


        sort(sol.begin(),sol.end());

        int sz = sol.size();
        build(1,1,sz);
        rep(i,0,sz){
            int u = sol[i].S;
            //cout << u << endl;
            update(1,1,sz,i+1,u);
        }

        /*while(true){
            int u;
            sc("%d",&u);
            cout << query(1,1,sz,u,u);
        }*/
        //cout << sz << endl;

        int q;
        sc("%d",&q);
        pc("Case %d:\n",t);
        while(q--){
            int u;
            sc("%d",&u);
            if(u > n){
                puts("impossible");
                continue;
            }
            int pos = lower_bound(sol.begin(),sol.end(),ii(u,-1))-sol.begin();
            pos++;
            //cout << pos <<" " <<sz<< endl;
            int ans = query(1,1,sz,pos,sz);
            //cout << ans << endl;
            if(ans == 0){
                puts("impossible");
                continue;
            }
            //int totVer = lower_bound(sol1.begin(),sol1.end(),ii(ans,INF))-sol1.begin();
            //totVer--;
            //int total = sol1[totVer].S;
            if(ans >= u){
                pc("%d\n",u-1);
                continue;
            }
            int finAns = ans;
            int res = u - ans - 1;
            if(res > 0) finAns += res*2;

            pc("%d\n",finAns);
        }
        /*rep(i,0,sol.size()){
            cout << sol[i].F<< " " << sol[i].S << endl;
        }
        int pos = lower_bound(sol.begin(),sol.end(),ii(3,1000))-sol.begin();
        cout << pos;*/

    }




    //int pos = lower_bound(sol.begin(),sol.end(),ii(6,-1))-sol.begin();
    //cout << pos;


	return 0;
}

/*
1
14 11
2 4
2 5
1 3
3 6
6 7
10 9
10 8
8 12
8 11
7 14
10 13
*/





