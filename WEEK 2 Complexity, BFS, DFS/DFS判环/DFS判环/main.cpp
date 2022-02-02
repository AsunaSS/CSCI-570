//
//  main.cpp
//  DFS判环
//
//  Created by 李超予 on 2021/9/28.
//

#define MAX_NUM 100
#define INF 0x7fffffff
/*DFS判断无向图中是否有环*/
class Graph
{
    public:
    int vertexNum;//顶点个数
    int arcNum;//弧的个数
    int vertex[MAX_NUM];//顶点表
    int arc[MAX_NUM][MAX_NUM];//弧信息表
};
int visited[MAX_NUM];//顶点访问表
int father[MAX_NUM];//父节点表
void DFS(int v,Graph G)
{
    visited[v] = 1;
    for(int i = 0 ; i < G.vertexNum; i++)
    {
        if(i != v && G.arc[v][i] != INF)//邻接矩阵中节点v的邻接点
        {
            if(visited[i] == 1 && father[v] != i)//vi不是父节点，而且还访问过(而且为状态1，说明不是回溯过来的顶点)，说明存在环(判断i不是v的父节点)
            {
                cout<<"图存在环";
                int temp = v;
                while(temp != i)
                {
                    cout<<temp<<"<-";//输出环
                    temp = father[temp];
                }
                cout<<temp<<endl;
            }
            else
                if(visited[i] == 0)
                {
                    father[i] = v;//更新father数组
                    DFS(i,G);
                }
 
        }
    }
    visited[v] = 2;//遍历完所有的邻接点才变为状态2
}
void DFSTraverse(Graph G)
{
    memset(visited,0,sizeof(visited));
    memset(father,-1,sizeof(father));
    for(int i = 0 ; i < G.vertexNum; i++)
        if(!visited[i])
            DFS(i,G);
}
