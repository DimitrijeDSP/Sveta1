public class FordFulkerson
{
    private boolean[] marked;   // true of s->v path in residual network
    private FlowEdge[] edgeTo;  // last edge on s->v path
    private double value;       // value of flow 

    public FordFulkerson(FlowNetwork G, int s, int t, double value) {
        this(G, s, t);
        this.value = value;
    }

    public FordFulkerson(FlowNetwork G, int s, int t) {
        value = 0.0;
        while (hasAugmentingPath(G, s, t)) {
            double bottle = Double.POSITIVE_INFINITY;
                                        // compute bottleneck capacity
            for (int v = t; v != s; v = edgeTo[v].other(v))
                bottle = Math.min(bottle, edgeTo[v].residualCapacityTo(v));
                                        // augment flow
            for (int v = t; v != s; v = edgeTo[v].other(v))
                edgeTo[v].addResidualFlowTo(v, bottle);

            value += bottle;
        }
    }

    // BFS 
    private boolean hasAugmentingPath(FlowNetwork G, int s, int t) {
        edgeTo = new FlowEdge[G.V()];
        marked = new boolean[G.V()];

        StdOut.printf("hasAugmentingPath s=%d t=%d\n", s, t);

        Queue<Integer> q = new Queue<Integer>();
        q.enqueue(s);
        marked[s] = true;
        while (!q.isEmpty()) {
            int v = q.dequeue();
            StdOut.printf("v=%d ", v);

            for (FlowEdge e: G.adj(v)) {
                int w = e.other(v);
                StdOut.printf("w=%d ", w);
                // found path from s to w in the residual network ?
                if (e.residualCapacityTo(w) > 0 && !marked[w]) {
                    edgeTo[w] = e;
                    marked[w] = true;
                    q.enqueue(w);
                }                    
            }
            StdOut.printf("\n");
        }
        // is t reachable from s in residual network ?
        return marked[t];
    }  

    public double value() {
        return value;
    }

    // is v reachable from s in residual network ?
    public boolean inCut(int v) {
        return marked[v];
    }

    public static void main(String[] args) {
        double value;
        int s, t;
        In in = new In(args[0]);
        s = Integer.parseInt(args[1]);
        t = Integer.parseInt(args[2]);
        value = Double.parseDouble(args[3]);
        FlowNetwork G = new FlowNetwork(in);
        StdOut.println(G);

        // compute maximum flow and minimum cut
        FordFulkerson maxflow = new FordFulkerson(G, s, t, value);
        StdOut.println("Max flow from " + s + " to " + t);
        for (int v = 0; v < G.V(); v++) {
            for (FlowEdge e : G.adj(v)) {
                if ((v == e.from()) && e.flow() > 0)
                    StdOut.println("   " + e);
            }
        }

        // print min-cut
        StdOut.print("Min cut: ");
        for (int v = 0; v < G.V(); v++) {
            if (maxflow.inCut(v)) StdOut.print(v + " ");
        }
        StdOut.println();

        StdOut.println("Max flow value = " +  maxflow.value());

    }

}