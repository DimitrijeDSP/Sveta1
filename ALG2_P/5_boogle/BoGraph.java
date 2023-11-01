

public class BoGraph {
    private BoggleBoard bb;
    
    public BoGraph(BoggleBoard bb) {
        this.bb = bb;
    }
        
    public int V() {
        return bb.rows() * bb.cols();
    }

    public Iterable<Integer> adj(int v) {
        Bag<Integer> ax = new Bag<Integer>();
        int rows = bb.rows();
        int cols = bb.cols();
        int ir = v / cols;
        int ic = v % cols;
        int[] delta = {-1, 0, 1};
        int irx, icx, ix;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                icx = ic + delta[j];
                irx = ir + delta[i];
                if (irx < 0 || irx >= rows) continue;
                if (icx < 0 || icx >= cols) continue;
                ix = cols*irx + icx;
                if (ix == v) continue;
                ax.add(ix);
            }
        } 
        return ax;
    }

    public char getBBL(int v) {
        int cols = bb.cols();
        int ir = v / cols;
        int ic = v % cols;
        return bb.getLetter(ir, ic);
    }

    public String toString() {
        StringBuilder s = new StringBuilder();
        String NEWLINE = System.getProperty("line.separator");
        s.append(V() + " vertices" + NEWLINE);
        for (int v = 0; v < V(); v++) {
            s.append(String.format("%d: ", v));
            for (int w : adj(v)) {
                s.append(String.format("%d ", w));
            }
            s.append(NEWLINE);
        }
        return s.toString();
    }

    public String toChars() {
        StringBuilder s = new StringBuilder();
        String NEWLINE = System.getProperty("line.separator");
        s.append(V() + " vertices" + NEWLINE);
        for (int v = 0; v < V(); v++) {
            s.append(String.format("%c: ", getBBL(v)));
            for (int w : adj(v)) {
                s.append(String.format("%c ", getBBL(w)));
            }
            s.append(NEWLINE);
        }
        return s.toString();
    }

    public static void main(String[] args) {
        BoggleBoard x = new BoggleBoard();
        BoGraph G = new BoGraph(x);
        StdOut.println(G);
        StdOut.println(G.toChars());
    }
}
