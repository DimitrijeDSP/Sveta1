public class DepthFirstPaths
{
    private boolean[] marked;
    private int[] edgeTo;
 //   private int s;

    public DepthFirstPaths(Graph G, int s)
    {
        marked = new boolean[G.V()];
        edgeTo = new int[G.E()];
        dfs(G,s);
    }

    private void dfs(Graph G, int v)
    {

        marked[v] = true;
        StdOut.println("marked="+(char)(65+v));
        for (int w : G.adj(v))
            if (!marked[w])
            {
                dfs(G, w);
                edgeTo[w] = v;
            }
    }

     public static void main(String[] args)
     {
         In in = new In(args[0]);
         Graph G = new Graph(in);

         StdOut.println(G);
         for (int v = 0; v < G.V(); v++)
            for (int w: G.adj(v))
                StdOut.println(v + "-" + w);
         DepthFirstPaths a = new DepthFirstPaths(G,0);
     }
}