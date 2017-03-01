#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll,int> iii;

#define INF 1000000007
#define N 105
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

int n,m;
vector<int>adj[N];
bool is,isColor[N][2];

void go(int u,int which)
{
    queue<ii>qu;

    qu.push(ii(u,1));
    //isColor[u][which] = 1;

    while(!qu.empty()){
        ii top = qu.front();
        qu.pop();
        //cout << "old " << top.F << " " << top.S <<endl;
        //cout << is << endl;
        rep(j,0,adj[top.F].size()){
            int col = 1 - top.S;
            int v = adj[top.F][j];

            if(!isColor[v][col]){
                //cout << "hihi " << v << endl;
                isColor[v][col] = 1;
                qu.push(ii(v,col));
            }

        }
    }
}

int main()
{
    int t = 0,T;
    sc("%d",&T);
    while(++t <= T){
        is = 0;
        rep(i,0,101){
            adj[i].clear();
            isColor[i][0] = isColor[i][1] = 0;
        }
        sc("%d%d",&n,&m);
        rep(i,0,m){
            int x,y;
            sc("%d%d",&x,&y);
            adj[x].pb(y);
            adj[y].pb(x);
        }
        go(1,1);
        //cout << endl;

        int ans = 0;
        rep(i,1,n+1){
            if(isColor[i][1]){
                //cout << i << endl;
                ans++;
            }
        }

        pc("Case %d: %d\n",t,ans);

    }


	return 0;
}







