public class Percolation
{
    private int np, np2;
    private boolean[][] opened;
    private WeightedQuickUnionUF uf;
    private WeightedQuickUnionUF uf1;

    public Percolation(int N)    // create N-by-N grid, with all sites blocked
    {
        np = N;
        np2 = np*np;
        opened = new boolean[np][np];
        for (int i = 0; i < np; i++)
           for (int j = 0; j < np; j++)
                opened[i][j] = false;
        uf = new WeightedQuickUnionUF(np2+2);
        uf1 = new WeightedQuickUnionUF(np2+1);
    }

    private boolean outij(int i, int j)
    {
         if (i < 0 || i > np-1 || j < 0 || j > np-1) return (true);
         return (false);
    }

    private int ind(int pos, int i, int j)
    {
         int ix, jx;
         // positions C  U  D  L  R
         //           E  P  O  E  I
         //           N     W  F  G
         //           T     N  T  H
         //           E           T
         //           R
         //     pos = 0  1  2  3  4
         int[] ii = { 0, -1, 1,  0, 0};
         int[] jj = { 0,  0, 0, -1, 1};
         ix = i+ii[pos];
         jx = j+jj[pos];
         if (ix < 0 || ix > np-1 || jx < 0 || jx > np-1) return (-1);
         return (ix*np+jx);
    }

    public void open(int i, int j)  // open site (row i, column j) if it is not
    {
        int i1 = i-1, j1 = j-1;
        if (outij(i1, j1))
            throw new IndexOutOfBoundsException("index i or j out of bounds");
        if (!opened[i1][j1]) {
             opened[i1][j1] = true;
             int x1 = ind(0, i1, j1);
             for (int k = 1; k <= 4; k++) {
                 int x2 = ind(k, i1, j1);
                 if (x2 >= 0 && opened[x2 / np][x2 % np]) { // union only with neighb
                     uf.union(x1, x2);
                     uf1.union(x1, x2);
                 }
             }
             if (i1 == 0) uf.union(x1, np2);
             if (i1 == 0) uf1.union(x1, np2);
             if (i1 == np-1) uf.union(x1, np2+1);
         }
    }

    public boolean isOpen(int i, int j)    // is site (row i, column j) open?
    {
        int i1 = i-1, j1 = j-1;
        if (outij(i1, j1))
             throw new IndexOutOfBoundsException("index i or j out of bounds");
        return (opened[i1][j1]);
    }

    public boolean isFull(int i, int j)   // is site (row i, column j) full?
    {
        int i1 = i-1, j1 = j-1;
        if (outij(i1, j1))
             throw new IndexOutOfBoundsException("index i or j out of bounds");
        int x = ind(0, i1, j1);
        return (uf1.connected(x, np2));
    }

    public boolean percolates()            // does the system percolate?
    {
        return (uf.connected(np2, np2+1));
    }
}