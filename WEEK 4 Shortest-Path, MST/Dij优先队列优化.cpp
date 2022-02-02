//
//  main.cpp
//  P1396
//
//  Created by 李超予 on 2021/9/23.
//

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cstdlib>

using namespace std;

typedef pair<int,int> pii;

struct Edge
{
    int next,to,w;
}edge[50005];

int n,m,s,t;
int cnt,dis[50005],vis[50005],head[50005];

void addedge(int u,int v, int w)
{
    cnt++;
    edge[cnt].to=v;
    edge[cnt].next=head[u];
    edge[cnt].w=w;
    head[u]=cnt;
}

void dijkstra(int s)
{
    memset(dis,0x3f3f3f3f,sizeof(dis));
    priority_queue<pii, vector<pii>, greater<pii>> q;
    dis[s]=0;
    q.push(make_pair(0,s));
    while(!q.empty())
    {
        int x=q.top().second;
        //printf("%d\n",x);
        q.pop();
        if (vis[x]==1) continue;
        vis[x]=1;
        for (int i=head[x]; i; i=edge[i].next)
        {
            //printf("head:%d\n",i);
            int v=edge[i].to,w=edge[i].w;
            //printf("to:%d\n",v);
            if (dis[v]>max(dis[x],w))
                dis[v]=max(dis[x],w);
            q.push(make_pair(dis[v],v));
        }
    }
}

int main()
{
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for (int i=1; i<=m; i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        addedge(a,b,c);
        addedge(b,a,c);
    }
    dijkstra(s);
    /*for (int i=1; i<=m; i++)
        printf("%d ",dis[i]);
    printf("\n");*/
    printf("%d\n",dis[t]);
    return 0;
}
