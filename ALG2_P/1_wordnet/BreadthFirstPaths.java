public class BreadthFirstPaths
{
    private boolean[] marked;
    private int[] edgeTo;

    public BreadthFirstPaths(Graph G, int s)
    {
        marked = new boolean[G.V()];
        edgeTo = new int[G.E()];
        bfs(G, s);
    }

    private void bfs(Graph G, int s)
    {
        Queue<Integer> q = new Queue<Integer>();
        q.enqueue(s);
        marked[s] = true;
        while(!q.isEmpty())
        {
            int v = q.dequeue();
            StdOut.println("dequeued="+(char)(v+65));
            for (int w : G.adj(v))
            {
                if (!marked[w])
                {
                    q.enqueue(w);
                    marked[w] = true;
                    edgeTo[w] = v;
                }
            }
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
         BreadthFirstPaths a = new BreadthFirstPaths(G,0);
     }


}