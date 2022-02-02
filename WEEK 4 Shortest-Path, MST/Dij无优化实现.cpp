//
//  main.cpp
//  P1359
//
//  Created by 李超予 on 2021/9/16.
//

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>

using namespace std;

const int inf=999999999;
int g[205][205],n;
int dis[205],book[205];

void init()
{
    for (int i=1; i<=n; i++)
        for (int j=1; j<=n; j++)
            if (i==j)
                g[i][j]=0;
            else g[i][j]=inf;
    for (int i=1; i<=n-1; i++)
        for (int j=i+1; j<=n; j++)
            scanf("%d",&g[i][j]);
    for (int i=1; i<=n; i++)
        dis[i]=inf;
}

void dijstkra()
{
    
    for (int i=1; i<=n; i++)
        dis[i]=g[1][i];             //初始化distance
    memset(book,0,sizeof(book));
    book[1]=1;                      //book集合里只装了点1
    for (int i=1; i<=n-1; i++)      //只需要循环n-1次就能求1-n最短路径
    {
        int minn=inf;
        int u=0;
        for (int j=1; j<=n; j++)    //寻找当前距离最近的节点
            if (book[j]==0 && dis[j]<minn)  //当前点一定要还没被加入集合book里才会考虑
            {
                minn=dis[j];
                u=j;
            }
        book[u]=1;
        for (int v=1; v<=n; v++)
        {
            if (g[u][v]<inf)        //如果u->v存在一条路，松弛
            {
                if (dis[v]>dis[u]+g[u][v])
                    dis[v]=dis[u]+g[u][v];
            }
        }
    }
    printf("%d\n",dis[n]);
}

void floyd()
{
    for (int k=1; k<=n; k++)
        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++)
                if (g[i][j]>g[i][k]+g[k][j])
                    g[i][j]=g[i][k]+g[k][j];
    printf("%d\n",g[1][n]);
}

void spfa()
{
    for (int i=1; i<=n; i++)
        dis[i]=g[1][i];
    memset(book,0,sizeof(book));
    queue<int> q;
    q.push(1);
    book[1]=1;
    while(!q.empty())
    {
        int cur=q.front();
        //cout<<cur<<endl;
        for (int i=1; i<=n; i++)
        {
            //cout<<g[cur][i]<<" "<<dis[cur]<<" "<<dis[i]<<endl;
            if (g[cur][i]<inf && dis[i]>=dis[cur]+g[cur][i])
            {
                dis[i]=dis[cur]+g[cur][i];
                if (book[i]==0)
                {
                    //cout<<"i:"<<i<<endl;
                    q.push(i);
                    book[i]=1;
                }
            }
        }
        q.pop();
        book[cur]=0;
    }
    //for (int i=1; i<=n; i++)
    //    printf("%d ",dis[i]);
    printf("%d\n",dis[n]);
}

int main()
{
    scanf("%d",&n);
    init();
    //for (int i=1; i<=n; i++)
    //{
    //    for (int j=1; j<=n; j++)
    //        printf("%d ",g[i][j]);
    //    cout<<endl;
    //}
    //dijstkra();
    //floyd();
    spfa();
    return 0;
}
