public class SP
{
    SP(EdgeWeightedDigraph G, int s)
    {
    }

    public double distTo(int v)
    {
        return distTo[v];
    }

    public Iterable <DirectedEdge> pathTo(int v)
    {
        Stack<DirectedEdge> path = new Stack<DirectedEdge>();
        for (DirectedEdge e = edgeTo[v]; e != null; e = edgeTo[e.from()])
            path.push(e);
        return path;
    }

    private void relax(DirectedEdge e)
    {
        int v = e.from(), w = e.to();
        if (distTo[w] > distTo[v] + e.weight())
        {
            distTo[w] = distTo[v] + e.weight();
            edgeTo[w] = e;
        }
    }

    public static void main(String[] args)
    {
        SP sp = new SP(G, s);
        for (int v = 0; v < G.V(); v++)
        {
            StdOut.printf("%d to %d (%.2f): ", s, v, sp.distTo(v));
            for (DirectedEdge e : sp.pathTo(v))
                StdOut.print(e + " ");
            StdOut.println();
        }
    }
}