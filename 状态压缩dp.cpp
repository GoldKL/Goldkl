#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int inf=2147483647;
int map[15][15];
int dis[15];
bool cmap[15][15];
int dp[1<<12];
int n,m;
void build(int x,int y,int w)
{
	map[x][y]=min(map[x][y],w);
	map[y][x]=min(map[y][x],w);
	cmap[x][y]=true;
	cmap[y][x]=true;
}
void dfs(int x)
{
	for(int i=1;i<=n;++i)
	{
		if(x&(1<<(i-1)))
		{
			for(int j=1;j<=n;++j)
			{
				if(!(x&(1<<(j-1)))&&cmap[i][j])
				{
					if(dp[x|(1<<(j-1))]>dp[x]+dis[i]*map[i][j])
					{
						int tem=dis[j];
						dis[j]=dis[i]+1;
						dp[x|(1<<(j-1))]=dp[x]+dis[i]*map[i][j];
						dfs(x|(1<<(j-1)));
						dis[j]=tem;
					}
				}
			}
		}
	}
}
int main()
{
	int ans=inf;
	memset(map,0x7f,sizeof(map));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		build(a,b,c);
	}
	for(int i=1;i<=n;++i)
	{
		memset(dis,0x7f,sizeof(dis));
		for(int S=0;S<(1<<n);++S)dp[S]=inf;
		int xx=1<<(i-1);
		dp[xx]=0;
		dis[i]=1;
		dfs(xx);
		ans=min(dp[(1<<n)-1],ans);
	}
	printf("%d",ans);
	return 0;
}