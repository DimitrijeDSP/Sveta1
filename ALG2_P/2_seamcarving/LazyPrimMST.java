public class LazyPrimMST
{
    private double weight;       // total weight of MST
    private boolean[] marked;       // MST vetrices
    private Queue<Edge> mst;        // MST edges
    private MinPQ<Edge> pq;         // PQ of edges

    public LazyPrimMST(EdgeWeightedGraph G)
    {
        weight = 0.0;
        pq = new MinPQ<Edge>();
        mst = new Queue<Edge>();
        marked = new boolean[G.V()];

//        for (int v = 0; v < G.V(); v++)
//            if (!marked[v]) prim(G, v);
          prim(G, 2);
    }

    private void prim(EdgeWeightedGraph G, int s) {
        visit(G, s);
        while (!pq.isEmpty())
        {
            Edge e = pq.delMin();
            int v = e.either(), w = e.other(v);
            if (marked[v] && marked[w]) continue; // Lazy, not remove
            mst.enqueue(e);
            weight += e.weight();
            if (!marked[v]) visit(G, v);
            if (!marked[w]) visit(G, w);
        }
    }

    public double weight() {
        return weight;
    }

    private void visit(EdgeWeightedGraph G, int v)
    {
        marked[v] = true;
        for (Edge e : G.adj(v))
            if (!marked[e.other(v)])
                pq.insert(e);
    }

    public Iterable<Edge> mst()
    {
        return mst;
    }

    public static void main(String[] args) {
        In in = new In(args[0]);
        EdgeWeightedGraph G = new EdgeWeightedGraph(in);
        LazyPrimMST mst = new LazyPrimMST(G);
        for (Edge e : mst.mst()) {
            StdOut.println(e);
        }
        StdOut.printf("%.5f\n", mst.weight());
    }
}