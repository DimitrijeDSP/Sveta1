public class DirectedBFS
{
    private boolean[] marked;
    private int[] edgeTo;

    public DirectedBFS(Digraph G, int s)
    {
        marked = new boolean[G.V()];
        edgeTo = new int[G.E()];
        for (int v = 0; v < G.V(); v++) {
           marked[v] = false;
        }
        bfs(G, s);
    }

    private void bfs(Digraph G, int s)
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
         Digraph G = new Digraph(in);
                  StdOut.println(G);


         for (int v = 0; v < G.V(); v++)
            for (int w: G.adj(v))
                StdOut.println(v + "-" + w);
         DirectedBFS a = new DirectedBFS(G,0);
     }


}