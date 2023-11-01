public class CC
{
    private boolean marked[];
    private int[] id;
    private int count;

    public CC(Graph G)
    {
        marked = new boolean[G.V()];
        id = new int[G.V()];
        for (int v=0; v < G.V(); v++)
        {
            if (!marked[v])
            {
                dfs(G,v);
                count++;
            }
        }
    }

    public int count()
    {
        return count;
    }

    public int id(int v)
    {
        return id[v];
    }

    private void dfs(Graph G, int v)
    {
        marked[v] = true;
        id[v] = count;
        for (int w : G.adj(v))
            if (!marked[w])
                dfs(G, w);
    }

     public static void main(String[] args)
     {
         In in = new In(args[0]);
         Graph G = new Graph(in);

         for (int v = 0; v < G.V(); v++)
            for (int w: G.adj(v))
                StdOut.println(v + "-" + w);
         CC a = new CC(G);

        for (int j=0; j< G.V(); j++)
           StdOut.print(a.id(j)+" ");
        StdOut.println(" ");
     }

}