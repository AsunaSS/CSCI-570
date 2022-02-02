//
//  main.cpp
//  拓扑排序
//
//  Created by 李超予 on 2021/9/28.
//

#include<iostream>
#include<unordered_map>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<sstream>
#include<set>
#include<map>
#include<stack>
using namespace std;
#define MAX_NUM 100
#define INF 0x7fffffff
/*拓扑排序*/
int indegree[MAX_NUM];//用以表示每个顶点的入度
bool visited[MAX_NUM];//用以表示该顶点是否入栈
class Graph
{
public:
    int vertexNum;//顶点个数
    int arcNum;//弧的个数
    int vertex[MAX_NUM];//顶点表
    int arc[MAX_NUM][MAX_NUM]= {{0,1,1},{INF,0,1},{INF,INF,0}}; //弧信息表
};
void Initindegree(Graph G)//初始化入度数组
{
    memset(indegree,0,sizeof(indegree));
    for(int i = 0; i < G.vertexNum; i++)
        for(int j = 0; j < G.vertexNum; j++)
        {
            if(i != j && G.arc[i][j] != INF)
                indegree[j]++;//注意此处增加的是顶点vj的入度
        }
    memset(visited,0,sizeof(visited));
}
bool TuoPu(Graph G)
{
    stack<int> s;
    int cnt = 0;//用于记录拓扑序列中节点的个数
    for(int i = 0 ; i < G.vertexNum; i++)
        if(indegree[i] == 0)
        {
            s.push(i);
            visited[i] = true;//修改入栈顶点的入栈标记数组
 
        }
    while(!s.empty())
    {
        int v = s.top();
        cnt++;//顶点出栈得到时候，计数器加1
        s.pop();
 
        for(int i = 0; i < G.vertexNum; i++)
        {
            if(v != i && G.arc[v][i] != INF && visited[i] == false)//将所有顶点v的未入栈的邻接点的入度都减去1
            {
                indegree[i]--;
                if(indegree[i] == 0)//如果减1后入度为0了，此时需要将该邻接点入栈，且修改入栈标记数组
                {
                    visited[i] = true;
                    s.push(i);
                }
            }
 
 
        }
    }
    return cnt == G.vertexNum ? true : false;
}
int main()
{
    Graph G;
    G.vertexNum = 3;
    Initindegree(G);
    cout<<TuoPu(G)<<endl;
 
}
