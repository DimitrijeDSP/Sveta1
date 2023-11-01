public class BoPaths {
    private boolean[] marked;  // marked[v] = true if v is reachable from s
    private int[] edgeTo;      // edgeTo[v] = last edge on path from s to v
    private final int s;       // source vertex
    TST<Integer> dict;

    public BoPaths(Bograph G, TST<Integer> dict, int s) {
        marked = new boolean[G.V()];
        edgeTo = new int[G.V()];
        this.s = s;
        this.dict = dict;
        dfs(G, s);
    }

    private void dfs(Bograph G, int v) { 
        marked[v] = true;
        for (int w : G.adj(v)) {
            if (!marked[w]) {
                edgeTo[w] = v;
                dfs(G, w);
            }
        }
    }

    public boolean hasPathTo(int v) {
        return marked[v];
    }

    public Iterable<Integer> pathTo(int v) {
        if (!hasPathTo(v)) return null;
        Stack<Integer> path = new Stack<Integer>();
        for (int x = v; x != s; x = edgeTo[x])
            path.push(x);
        path.push(s);
        return path;
    }

    public static void main(String[] args) {
        BoggleBoard bb = new BoggleBoard();
        Bograph G = new Bograph(bb);
        // StdOut.println(G);

        int s = Integer.parseInt(args[0]);
        BoPaths dfs = new BoPaths(G, null, s);

        for (int v = 0; v < G.V(); v++) {
            if (dfs.hasPathTo(v)) {
                StdOut.printf("%c (%d) to %c (%d):  ", G.getBBL(s), s, G.getBBL(v), v);
                for (int x : dfs.pathTo(v)) {
                    if (x == s) StdOut.print(G.getBBL(x));
                    else        StdOut.print("-" + G.getBBL(x));
                }
                StdOut.println();
            }

            else {
                StdOut.printf("%d to %d:  not connected\n", s, v);
            }

        }
    }

}
