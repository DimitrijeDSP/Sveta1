public class BellmanFord
{
	private DirectedEdge[] edgeTo;
	private double[] distTo;

    private boolean[] onQueue;             
    private Queue<Integer> queue;          
    private int cost;                      
    private Iterable<DirectedEdge> cycle;  
    private int[] pass;             


	public BellmanFord(EdgeWeightedDigraph G, int s)
	{
		edgeTo = new DirectedEdge[G.V()];
		distTo = new double[G.V()];
        onQueue = new boolean[G.V()];
        pass = new int[G.V()];

		for (int v = 0; v < G.V(); v++) {
			distTo[v] = Double.POSITIVE_INFINITY;
            pass[v] = -1;
        }
		distTo[s] = 0.0;
        pass[s] = 0;

        queue = new Queue<Integer>();
        queue.enqueue(s);
        pass[s] = 0;
        StdOut.println("ENQUEUE "+s);
        onQueue[s] = true;
        while (!queue.isEmpty() && !hasNegativeCycle()) {
            int v = queue.dequeue();
            onQueue[v] = false;
            relax(G, v);
        }
	}

   private void relax(EdgeWeightedDigraph G, int v) {
        StdOut.println("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Relax "+v+" in pass "+pass[v]+" @@@@@@@@@@@@@@@@@@@@@@@@@@");
        for (DirectedEdge e : G.adj(v)) {
            int w = e.to();
            if (distTo[w] > distTo[v] + e.weight()) {
                StdOut.println("------------- Relaxed "+v+"->"+w+" ------------------");
                distTo[w] = distTo[v] + e.weight();
                edgeTo[w] = e;
                if (!onQueue[w]) {
                    queue.enqueue(w);
                    pass[w] = pass[v]+1;
                    StdOut.println("ENQUEUE "+v+"->"+w+" ");
                    onQueue[w] = true;
                }
            }
            if (cost++ % G.V() == 0)
                findNegativeCycle();
        }
        printDist();
    }


    private void findNegativeCycle() {
        int V = edgeTo.length;
        EdgeWeightedDigraph spt = new EdgeWeightedDigraph(V);
        for (int v = 0; v < V; v++)
            if (edgeTo[v] != null)
                spt.addEdge(edgeTo[v]);

        EdgeWeightedDirectedCycle finder = new EdgeWeightedDirectedCycle(spt);
        cycle = finder.cycle();
    }

    public boolean hasNegativeCycle() {
        return cycle != null;
    }

    public Iterable<DirectedEdge> negativeCycle() {
        return cycle;
    }

    public void printDist() {
        for (int t = 0; t < distTo.length; t++) {
            StdOut.printf("%.0f ", distTo[t]);
        }
        StdOut.println(" ");
    }

    public double distTo(int v) {
        return distTo[v];
    }

    public boolean hasPathTo(int v) {
        return distTo[v] < Double.POSITIVE_INFINITY;
    }

    public Iterable<DirectedEdge> pathTo(int v) {
        if (!hasPathTo(v)) return null;
        Stack<DirectedEdge> path = new Stack<DirectedEdge>();
        for (DirectedEdge e = edgeTo[v]; e != null; e = edgeTo[e.from()]) {
            path.push(e);
        }
        return path;
    }

    public static void main(String[] args) {
        In in = new In(args[0]);
        EdgeWeightedDigraph G = new EdgeWeightedDigraph(in);
        int s = Integer.parseInt(args[1]);

        // compute shortest paths
        BellmanFord sp = new BellmanFord(G, s);

        // print shortest path
        for (int t = 0; t < G.V(); t++) {
            if (sp.hasPathTo(t)) {
                StdOut.printf("%d to %d (%.2f)  ", s, t, sp.distTo(t));
                if (sp.hasPathTo(t)) {
                    for (DirectedEdge e : sp.pathTo(t)) {
                        StdOut.print(e + "   ");
                    }
                }
                StdOut.println();
            }
            else {
                StdOut.printf("%d to %d         no path\n", s, t);
            }
        }
    }
}