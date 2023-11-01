public class KosarajuSharirCC
{
    private boolean marked[];
    private int[] id;
    private int count;

    public KosarajuSharirCC(Digraph G)
    {
        marked = new boolean[G.V()];
        id = new int[G.V()];
//        DepthFirstOrder dfs = new DepthFirstOrder(G.reverse());
        DirectedDFS dfs = new DirectedDFS(G.reverse(),0);
        for (int v : dfs.reversePost())
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

    private void dfs(Digraph G, int v)
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
         Digraph G = new Digraph(in);

         for (int v = 0; v < G.V(); v++)
            for (int w: G.adj(v))
                StdOut.println(v + "-" + w);
         KosarajuSharirCC a = new KosarajuSharirCC(G);

        for (int j=0; j< G.V(); j++)
           StdOut.print(a.id(j)+" ");
        StdOut.println(" ");
     }

}