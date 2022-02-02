//
//  main.cpp
//  拓扑排序+DP求DAG最长路径
//
//  Created by 李超予 on 2021/9/28.
//

public class AcyclicLP {
    // distTo[v]保存顶点v到源点s的最长路径，初始时，distTo[s]=0，其它为负无穷大
    private double[] distTo;
    // edgeTo[v]保存指向顶点v的最长路径，即s->v的路径上的最后一条路径
    private DirectedEdge[] edgeTo;
 
    public AcyclicLP(EdgeWeightedDigraph G, int s) {
        distTo = new double[G.V()];
        edgeTo = new DirectedEdge[G.V()];
        for (int v = 0; v < G.V(); v++)
            distTo[v] = Double.NEGATIVE_INFINITY;
        distTo[s] = 0.0;
 
        // relax vertices in toplogical order
        Topological topological = new Topological(G);
        if (!topological.hasOrder())
            throw new IllegalArgumentException("Digraph is not acyclic.");
        for (int v : topological.order()) {
            for (DirectedEdge e : G.adj(v))
                aRelax(e);
        }
    }
    private void aRelax(DirectedEdge e) {
        int v = e.from(), w = e.to();
        if (distTo[w] < distTo[v] + e.weight()) {
            distTo[w] = distTo[v] + e.weight();
            edgeTo[w] = e;
        }
    }
    public double distTo(int v) {
        return distTo[v];
    }
    public boolean hasPathTo(int v) {
        return distTo[v] > Double.NEGATIVE_INFINITY;
    }
    public Iterable<DirectedEdge> pathTo(int v) {
        if (!hasPathTo(v)) return null;
        Stack<DirectedEdge> path = new Stack<DirectedEdge>();
        for (DirectedEdge e = edgeTo[v]; e != null; e = edgeTo[e.from()]) {
            path.push(e);
        }
        return path;
    }
}
