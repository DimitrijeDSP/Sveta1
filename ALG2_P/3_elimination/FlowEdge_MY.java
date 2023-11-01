public class FlowEdge
{
    private final int v, w;         // from and to
    private final double capacity;  // capacity
    private double flow;            // flow

    public FlowEdge(int v, int w, double capacity)
    {
        this.v = v;
        this.w = w;
        this.capacity = capacity;
        this.flow = 0.0;
    }

    public FlowEdge(int v, int w, double flow, double capacity)
    {
        this.v = v;
        this.w = w;
        this.flow = flow;
        this.capacity = capacity;
    }

    public int from() { 
        return v;
    }

    public int to() {
        return w;
    }

    public int other(int vertex) {
        if (vertex == v) 
            return w;
        else if (vertex == w)
            return v;
        else
            throw new RuntimeException("Illegal endpiont");
    }

    public double capacity() {
        return capacity;
    }

    public double flow() {
        return flow;
    }

    public double residualCapacityTo(int vertex) {
        if (vertex == v) 
            return flow;
        else if (vertex == w) 
            return capacity - flow;
        else
            throw new IllegalArgumentException();
    }

    public void addResidualFlowTo(int vertex, double delta) {
        if (vertex == v) 
            flow -= delta;
        else if (vertex == w) 
            flow += delta;
        else
            throw new IllegalArgumentException();
    }

    public String toString() {
        return v + "->" + w + " " + flow + "/" + capacity;
    }
}