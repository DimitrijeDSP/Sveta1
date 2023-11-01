public class EdgeWeightedDigraph
{
    private final int V;
    private final int E;
    private final Bag<DirectedEdge>[] adj;

    public EdgeWeightedDigraph(int V)
    {
        this.V = V;
        this.E = 0;
        adj = (Bag<DirectedEdge>[]) new Bag[V];
        for (int v = 0; v < V; v++)
            adj[v] = new Bag<DirectedEdge>();
    }

    public EdgeWeightedDigraph(In in) {
        this(in.readInt());
        int E = in.readInt();
        for (int i = 0; i < E; i++) {
            int v = in.readInt();
            int w = in.readInt();
            double weight = in.readDouble();
            DirectedEdge e = new DirectedEdge(v, w, weight);
            addEdge(e);
        }
    }

    public int V() {
        return V;
    }

    public int E() {
        return E;
    }

    public void addEdge(DirectedEdge e)
    {
        int v = e.from();
        adj[v].add(e);
    }

    public Iterable<DirectedEdge> adj(int v)
    {
        return adj[v];
    }

//    public Iterable<DirectedEdge> edges() {
//        Bag<DirectedEdge> list = new Bag<DirectedEdge>();
//        for (int v = 0; v < V; v++) {
//            int selfLoops = 0;
//            for (Edge e : adj(v)) {
//                if (e.other(v) > v) {
//                    list.add(e);
//                }
//                else if (e.other(v) == v) {
//                    if (selfLoops % 2 == 0) list.add(e);
//                    selfLoops++;
//                }
//            }
//        }
//        return list;
//    }

//    public static void main(String[] args)
//    {
//        In in = new In(args[0]);
//        EdgeWeightedGraph G = new EdgeWeightedGraph(in);
//        MST mst = new MST(G);
//        for (Edge e: mst.edges())
//            StdOut.println(e);
//        StdOut.printf("%.2f\n", mst.weight());
//    }
}