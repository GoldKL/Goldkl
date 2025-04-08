#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct Node{
	int sum;
	Node *l,*r;
};
Node* Create(int sum,int l,int r)
{
    Node *id=(Node*)malloc(sizeof(Node));
    //id =new Node;
	id->sum=sum;
	id->l=NULL;
	id->r=NULL;
	return id;
}
int arr[100005],num[200005],lqx;
Node* Root[100005];
void Dele(Node* &root)
{
    if(root->l)Dele(root->l);
    if(root->r)Dele(root->r);
    free(root);
    root=NULL;
}
void Add(Node* &root,int val,int l,int r,int add)
{
    if(!root)root=Create(0,0,0);
	root->sum+=add;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(val<=mid)Add(root->l,val,l,mid,add);
	else Add(root->r,val,mid+1,r,add);
	if((root->sum)==0)
    {
        free(root);
        root=NULL;
    }
}
void BIT_Add(int x,int val,int n,int add)
{
    while(x<=n)
    {
        Add(Root[x],val,1,lqx,add);
        x+=x&(-x);
    }
}
Node *Larr[100005],*Rarr[100005];
int Lcnt,Rcnt;
int Query(int l,int r,int k)
{
	if(l==r)return l;
	int mid=(l+r)>>1;
	int sum=0;
	for(int i=0;i<Rcnt;++i)if((Rarr[i]!=NULL)&&((Rarr[i]->l)!=NULL))sum+=(Rarr[i]->l)->sum;
	for(int i=0;i<Lcnt;++i)if((Larr[i]!=NULL)&&((Larr[i]->l)!=NULL))sum-=(Larr[i]->l)->sum;
	if(k<=sum)
    {
        for(int i=0;i<Rcnt;++i)if(Rarr[i]!=NULL)Rarr[i]=Rarr[i]->l;
        for(int i=0;i<Lcnt;++i)if(Larr[i]!=NULL)Larr[i]=Larr[i]->l;
        return Query(l,mid,k);
    }
	else
    {
        for(int i=0;i<Rcnt;++i)if(Rarr[i]!=NULL)Rarr[i]=Rarr[i]->r;
        for(int i=0;i<Lcnt;++i)if(Larr[i]!=NULL)Larr[i]=Larr[i]->r;
        return Query(mid+1,r,k-sum);
    }
}
int BIT_Query(int r,int l,int k)
{
    Lcnt=0;
    Rcnt=0;
    while(l)
    {
        Larr[Lcnt++]=Root[l];
        l-=l&(-l);
    }
    while(r)
    {
        Rarr[Rcnt++]=Root[r];
        r-=r&(-r);
    }
    return Query(1,lqx,k);
}

char cz[100005][4];
int czn[100005][3];
int main()
{
    int T=1;
    
    while(T--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&arr[i]);
            num[i]=arr[i];
            if(Root[i])Dele(Root[i]);
        }
        lqx=n;
        for(int i=1;i<=m;++i)
        {
            scanf("%s",cz[i]);
            if(cz[i][0]=='Q')
            {
                scanf("%d%d%d",&czn[i][0],&czn[i][1],&czn[i][2]);
            }
            else
            {
                scanf("%d%d",&czn[i][0],&czn[i][1]);
                lqx++;
                num[lqx]=czn[i][1];
            }
        }
        sort(num+1,num+1+lqx);
        lqx=unique(num+1,num+1+lqx)-(num+1);
        for(int i=1;i<=n;++i)
        {
            int tem=lower_bound(num+1,num+1+lqx,arr[i])-num;
            //Insert(root[i],root[i-1],tem,1,lqx);
            BIT_Add(i,tem,n,1);
        }
        for(int i=1;i<=m;++i)
        {
            if(cz[i][0]=='Q')
            {
                printf("%d\n",num[BIT_Query(czn[i][1],czn[i][0]-1,czn[i][2])]);
            }
            else
            {
                int tem1=lower_bound(num+1,num+1+lqx,arr[czn[i][0]])-num;
                int tem2=lower_bound(num+1,num+1+lqx,czn[i][1])-num;
                BIT_Add(czn[i][0],tem1,n,-1);
                BIT_Add(czn[i][0],tem2,n,1);
                arr[czn[i][0]]=czn[i][1];
            }
        }
    }

	return 0;
}