#include<iostream>
#include<queue>
#include<iomanip>
#include<algorithm>
#include<cstdio>
#include<cstring> 
using namespace std;
struct Edge{
	int v,next,rev,cost;
	bool c;
}edge[500000];
int n,m;
int head[405],num_edge;//in x,out n+x
void add_edge(int u,int v,int cost)
{
	num_edge++;
	edge[num_edge].v=v;
	edge[num_edge].next=head[u];
	edge[num_edge].rev=num_edge+1;
	edge[num_edge].cost=cost;
	edge[num_edge].c=true;
	head[u]=num_edge;
	num_edge++;
	edge[num_edge].v=u;
	edge[num_edge].next=head[v];
	edge[num_edge].rev=num_edge-1;
	edge[num_edge].c=false;
	edge[num_edge].cost=-cost;
	head[v]=num_edge;
}
int ans1,ans2,dist[405],prevv[405],preve[405];
bool vis[405];
void min_cost(int s,int t)
{
	while(1)
	{
		memset(dist,0x7f,sizeof(dist));
		dist[s]=0;
		vis[s]=true;
		queue<int>q1;
		q1.push(s);
		while(!q1.empty())
		{
			int w=q1.front();
			vis[w]=false;
			q1.pop();
			for(int i=head[w];i!=0;i=edge[i].next)
			{
				if(edge[i].c&&dist[edge[i].v]>dist[w]+edge[i].cost)
				{
					dist[edge[i].v]=dist[w]+edge[i].cost;
					prevv[edge[i].v]=w;
					preve[edge[i].v]=i;
					q1.push(edge[i].v);
				}
			}
		}
		if(dist[t]==0x7f7f7f7f)return;
		int d;
		for(int v=t;v!=s;v=prevv[v])
		{
			if(edge[preve[v]].c)
			{
				d=1;
			}
		}
		ans1+=d;
		ans2+=dist[t]*d;
		for(int v=t;v!=s;v=prevv[v])
		{
			edge[preve[v]].c=false;
			edge[edge[preve[v]].rev].c=true;
		}
	}
	return;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=2;i<n;++i)add_edge(i,n+i,0);
	for(int i=1;i<=m;++i)
	{
		int aa,bb,cc;
		scanf("%d%d%d",&aa,&bb,&cc);
		if(aa!=1)add_edge(n+aa,bb,cc);
		else add_edge(1,bb,cc);
	}
	min_cost(1,n);
	printf("%d %d",ans1,ans2);
	return 0;
}