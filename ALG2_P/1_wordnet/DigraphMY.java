public class Digraph
{
    private final int V;
    private int E;
    private Bag<Integer>[] adj;

    Digraph(int V)
    {
        this.V = V;
        this.E = 0;
        adj = (Bag<Integer>[]) new Bag[V];
        for (int v = 0; v < V; v++)
            adj[v] = new Bag<Integer>();
    }

    public Digraph(In in) {
        this(in.readInt());
        int E = in.readInt();
        for (int i = 0; i < E; i++) {
            int v = in.readInt();
            int w = in.readInt();
            addEdge(v, w);
        }
    }

    public void addEdge(int v, int w)
    {
        adj[v].add(w);
        E++;
    }

    public Iterable<Integer> adj(int v)
    {
        return adj[v];
    }

    public int V() {
        return V;
    }

    public int E() {
        return E;
    }

    public String toString() {
        StringBuilder s = new StringBuilder();
        String NEWLINE = System.getProperty("line.separator");
        s.append(V + " vertices, " + E + " edges " + NEWLINE);
        for (int v = 0; v < V; v++) {
            s.append((char)(65+v) + ": ");
            for (int w : adj[v]) {
                s.append((char)(65+w) + " ");
            }
            s.append(NEWLINE);
        }
        return s.toString();
    }

    public static int degree(Graph G, int v)
    {
        int degree = 0;
        for (int w : G.adj(v)) degree++;
        return degree;
    }

    public static int maxDegree(Graph G)
    {
        int max = 0;
        for (int v = 0; v < G.V(); v++)
            if (degree(G, v) > max)
                max = degree(G, v);
        return max;
    }

    public static double averageDegree(Graph G)
    {
        return 2.0 * G.E() / G.V();
    }

     public static int numberOfSelfLoops(Graph G)
     {
        int count = 0;
        for (int v = 0; v < G.V(); v++)
            for (int w : G.adj(v))
                if (v == w) count ++;
                return count /2;
     }

    public Digraph reverse()
    {
        Digraph x = new Digraph(V);
        for (int i = 0; i < V; i++)
             for (int j : adj[i])
                 x.addEdge(j, i);
        return x;
    }

     public static void main(String[] args)
     {
        In in = new In(args[0]);
        Graph G = new Graph(in);

        for (int v = 0; v < G.V(); v++)
            for (int w: G.adj(v))
                StdOut.println(v + "->" + w);
     }
}
