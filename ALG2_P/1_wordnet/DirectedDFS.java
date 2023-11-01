public class DirectedDFS
{
    Digraph g;
    private boolean[] marked;
    private int[] edgeTo;
 //   private int s;
    private int[] postorder;
    int ipost;

    public DirectedDFS(Digraph G, int s)
    {
        g = G;
        marked = new boolean[G.V()];
        edgeTo = new int[G.V()];
        postorder = new int[G.V()];
        ipost=0;
        for (int i=0; i<G.V(); i++)
            if (!marked[i])
                dfs(G,i);
    }

    public Iterable<Integer> reversePost() {
        Stack<Integer> reverse = new Stack<Integer>();
        for (int i = 0; i<g.V(); i++)
            reverse.push(postorder[i]);
        return reverse;
    }

    private void dfs(Digraph G, int v)
    {
        marked[v] = true;
        StdOut.println("marked="+(char)(65+v));
        for (int w : G.adj(v)) {
            if (!marked[w])
            {
                dfs(G, w);
                edgeTo[w] = v;
            }
        }
        postorder[ipost++] = v;
        StdOut.println("--------- done="+v+" "+(char)(65+v));
    }

     public void postord(Digraph G)
     {

         StdOut.println("POSTORDER");
         for (int i = 0; i < G.V(); i++)
             StdOut.print(postorder[i] + " ");
         StdOut.println(" ");
         for (int i = 0; i < G.V(); i++)
             StdOut.print((char)(postorder[i]+65) + " ");
         StdOut.println(" ");
         StdOut.println("REVERSE POSTORDER");
         for (int i = G.V()-1; i >=0; i--)
             StdOut.print(postorder[i] + " ");
         StdOut.println(" ");
         for (int i = G.V()-1; i >=0; i--)
             StdOut.print((char)(postorder[i]+65) + " ");
         StdOut.println(" ");
     }

     public static void main(String[] args)
     {
         In in = new In(args[0]);
         Digraph G = new Digraph(in);
         Digraph GR = G.reverse();

         StdOut.println(G);
         for (int v = 0; v < G.V(); v++)
            for (int w: G.adj(v))
                StdOut.println(v + "-" + w);
         StdOut.println("REVERSE");
         DirectedDFS ar = new DirectedDFS(GR,0);
         ar.postord(GR);
         StdOut.println("NORMAL");
         DirectedDFS a = new DirectedDFS(G,0);
         a.postord(G);
     }
}