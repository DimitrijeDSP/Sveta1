public class SAP
{
    private static final int INFINITY = Integer.MAX_VALUE;
    private final Digraph dg;

    // constructor takes a digraph (not necessarily a DAG)
    public SAP(Digraph G)
    {
        dg = new Digraph(G);
    }

    // length of shortest ancestral path between v and w; -1 if no such path
    private int findPath(int v, int w, boolean mode)
    {
        boolean debug = false;
        int s1 = v;
        int s2 = w;
        DeluxeBFS bfs1 = new DeluxeBFS(dg, s1);
        DeluxeBFS bfs2 = new DeluxeBFS(dg, s2);
        ST<Integer, Integer> st1 = bfs1.getST();
        ST<Integer, Integer> st2 = bfs2.getST();
        int min = INFINITY;
        int ancestor = -1;
        int dist = INFINITY;
        if (debug) {
            for (int x : st1.keys())
                StdOut.println("s1="+s1+" x="+x+" d="+st1.get(x));
            for (int x : st2.keys())
                StdOut.println("s2="+s2+" x="+x+" d="+st2.get(x));
        }
        for (int x : st1.keys()) {
            if (!st2.contains(x)) {
                if (debug) StdOut.println("skip x="+x);
                continue;
            }
            dist = st1.get(x) + st2.get(x);
            if (dist < min) {
                min = dist;
                ancestor = x;
                if (debug) StdOut.println("NEW MIN x="
                           +x+" min="+min+" ancestor="+ancestor);
            }
        }
        if (ancestor == -1) min = -1;
        if (mode) return ancestor;
        return min;
    }

    private int findPath(Iterable<Integer> v, Iterable<Integer> w, boolean mode)
    {
        boolean debug = false;
        Iterable<Integer> s1 = v;
        Iterable<Integer> s2 = w;
        DeluxeBFS bfs1 = new DeluxeBFS(dg, s1);
        DeluxeBFS bfs2 = new DeluxeBFS(dg, s2);
        ST<Integer, Integer> st1 = bfs1.getST();
        ST<Integer, Integer> st2 = bfs2.getST();
        int min = INFINITY;
        int ancestor = -1;
        int dist = INFINITY;
        for (int x : st1.keys()) {
            if (!st2.contains(x)) {
                if (debug) StdOut.println("skip x="+x);
                continue;
            }
            dist = st1.get(x) + st2.get(x);
            if (dist < min) {
                min = dist;
                ancestor = x;
            }
        }
        if (ancestor == -1) min = -1;
        if (mode) return ancestor;
        return min;
    }


    // length of shortest ancestral path between v and w; -1 if no such path
    public int length(int v, int w)
    {
        if (v < 0 || v > dg.V() - 1)
            throw new java.lang.IndexOutOfBoundsException();
        if (w < 0 || w > dg.V() - 1)
            throw new java.lang.IndexOutOfBoundsException();
        return findPath(v, w, false);
    }

    // a common ancestor of v and w that participates
    // in a shortest ancestral path; -1 if no such path
    public int ancestor(int v, int w)
    {
        if (v < 0 || v > dg.V() - 1)
            throw new java.lang.IndexOutOfBoundsException();
        if (w < 0 || w > dg.V() - 1)
            throw new java.lang.IndexOutOfBoundsException();
        return findPath(v, w, true);
    }

    // length of shortest ancestral path between any vertex
    // in v and any vertex in w; -1 if no such path
    public int length(Iterable<Integer> v, Iterable<Integer> w)
    {
        for (int vx : v)
            if (vx < 0 || vx > dg.V() - 1)
                throw new java.lang.IndexOutOfBoundsException();
        for (int wx : v)
            if (wx < 0 || wx > dg.V() - 1)
                throw new java.lang.IndexOutOfBoundsException();
        return findPath(v, w, false);
    }

    // a common ancestor that participates in
    // shortest ancestral path; -1 if no such path
    public int ancestor(Iterable<Integer> v, Iterable<Integer> w)
    {
        for (int vx : v)
            if (vx < 0 || vx > dg.V() - 1)
                throw new java.lang.IndexOutOfBoundsException();
        for (int wx : v)
            if (wx < 0 || wx > dg.V() - 1)
                throw new java.lang.IndexOutOfBoundsException();
        return findPath(v, w, true);
    }

    // for unit testing of this class (such as the one below)
    public static void main(String[] args)
    {
        In in = new In(args[0]);
        Digraph G = new Digraph(in);
        SAP sap = new SAP(G);
        while (!StdIn.isEmpty()) {
            int v = StdIn.readInt();
            int w = StdIn.readInt();
            int length   = sap.length(v, w);
            int ancestor = sap.ancestor(v, w);
            StdOut.printf("length = %d, ancestor = %d\n", length, ancestor);
        }
    }
}
