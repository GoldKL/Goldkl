#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
struct Edge{
	int v,n;
	double w;
}edge[200005],edge2[200005];
int head[5005],num_edge;
int head2[5005],num_edge2;
void add_edge(int u,int v,double w)
{
	num_edge++;
	edge[num_edge].v=v;
	edge[num_edge].w=w;
	edge[num_edge].n=head[u];
	head[u]=num_edge;
	return;
}
void add_edge2(int u,int v,double w)
{
	num_edge2++;
	edge2[num_edge2].v=v;
	edge2[num_edge2].w=w;
	edge2[num_edge2].n=head2[u];
	head2[u]=num_edge2;
	return;
}
double h[5005],E;
struct Point{
	int u;
	double g,f;
	bool operator<(const Point a)const
	{
		return this->f>a.f;
	}
};
priority_queue<Point>qa;
int ans;
bool v[5005];
int ct[5005];
int read()
{
    int z=0,f=1;char k;
    while(k<'0'||k>'9'){if(k=='-')f=-1;k=getchar();}
    while(k>='0'&&k<='9'){z=(z<<3)+(z<<1)+k-'0';k=getchar();}
    return z*f;
}
int n,m;
void spfa()
{
	queue<int>q1;
	for(int i=1;i<=n;++i)h[i]=0x7fffffff;
	h[n]=0;
	v[n]=true;
	q1.push(n);
	while(!q1.empty())
	{
		int qu=q1.front();
		q1.pop();
		v[qu]=false;
		for(int i=head2[qu];i;i=edge2[i].n)
		{
			if(h[edge2[i].v]>h[qu]+edge2[i].w)
			{
				h[edge2[i].v]=h[qu]+edge2[i].w;
				if(!v[edge2[i].v])
				{
					v[edge2[i].v]=true;
					q1.push(edge2[i].v);
				}
			}
		}
	}
}
int main()
{
	n=read();
	m=read();
	scanf("%lf",&E);
	for(int i=1;i<=m;++i)
	{
		int a,b;
		a=read();
		b=read();
		double c;
		scanf("%lf",&c);
		add_edge(a,b,c);
		add_edge2(b,a,c);
	}
	spfa();
	memset(ct,0,sizeof(ct));
	Point st;
	st.u=1;
	st.g=0;
	st.f=st.g+h[st.u];
	qa.push(st);
	int IDI=E/h[1];
	qa.size();
	while(!qa.empty())
	{
		Point qu=qa.top();
		qa.pop();
		if(qu.f>E)continue;
		ct[qu.u]++;
		if(qu.u==n)
		{
			E-=qu.f;
			ans++;
			continue;
		}
		if(ct[qu.u]>IDI)continue;
		for(int i=head[qu.u];i;i=edge[i].n)
		{
			Point tem=qu;
			tem.g+=edge[i].w;
			tem.u=edge[i].v;
			tem.f=tem.g+h[tem.u];
			qa.push(tem);
		}
	}
	printf("%d",ans);
	return 0;
}