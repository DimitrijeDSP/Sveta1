public class Board
{
    private int N;
    private int[][] blk;

    // construct a board from an N-by-N array of blocks
    // (where blocks[i][j] = block in row i, column j)
    public Board(int[][] blocks) {
        int nn = blocks[0].length;
        blk = new int[nn][nn];
        N = nn;
        int cnt = 1;
        for (int i = 0; i < nn; i++)
            for (int j = 0; j < nn; j++)
                blk[i][j] = blocks[i][j];
    }

    // board dimension N
    public int dimension() {
        return N;
    }

    // number of blocks out of place
    public int hamming() {
        int ham = 0;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (blk[i][j] == 0) continue;
                if (blk[i][j] != i*N+j+1) ham++;
            }
        }
        return ham;
    }

    // sum of Manhattan distances between blocks and goal
    public int manhattan() {
        int man = 0, ix, jx;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (blk[i][j] == 0) continue;
                if (blk[i][j] == i*N+j+1) continue;
                if (blk[i][j] == 1) {
                    ix = 0;
                    jx = 0;
                }
                else {
                    ix = (blk[i][j] - 1) / N;
                    jx = (blk[i][j] - 1) % N;
                }
                // StdOut.println(" blk[i][j]="+blk[i][j]
                //           +" ix="+ix+" jx="+jx+" i="+i+" j="+j);
                man = man + Math.abs(ix - i) + Math.abs(jx - j);
            }
        }
        return man;
    }

    // is this board the goal board?
    public boolean isGoal() {
        return manhattan() == 0;
    }

    // a board obtained by exchanging two adjacent blocks in the same row
    public Board twin() {
        Board tb = new Board(blk);
        int temp;
        boolean zero;
        if (N < 2) return tb;
        for (int i = 0; i < N; i++) {
            zero = false;
            for (int j = 0; j < N; j++) {
                if (blk[i][j] == 0) zero = true;
            }
            if (zero) continue;
            temp = tb.blk[i][0];
            tb.blk[i][0] = tb.blk[i][1];
            tb.blk[i][1] = temp;
            break;
        }
        return tb;
    }

    public boolean equals(Object x) {      // does this board equal y?
        if (x == this) return true;
        if (x == null) return false;
        if (x.getClass() != this.getClass()) return false;
        int dim = this.dimension();
        Board that = (Board) x;
        if (that.dimension() != dim) return false;
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                if (that.blk[i][j] != this.blk[i][j]) return false;
            }
        }
        return true;
    }

    // all neighboring boards
    public Iterable<Board> neighbors()
    {
        Stack<Board> sb = new Stack<Board>();
        Board nb = null;
        int iz = -1, jz = -1;
        int i, j, in, jn, ix, jx, temp;

        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                if (blk[i][j] == 0) {
                    iz = i;
                    jz = j;
                    break;
                }
            }
            if (iz >= 0 && jz >= 0) break;
        }
        if (iz < 0 && jz < 0) return null;
        for (i = -1; i < 2; i++) {
            for (j = -1; j < 2; j++) {
                ix = iz + i;
                jx = jz + j;
                if (i == j) continue;
                if (i != 0 && j != 0) continue;
                if (ix == iz && jx == jz) continue;
                if (ix < 0 || ix > N-1) continue;
                if (jx < 0 || jx > N-1) continue;
                nb = new Board(blk);
                temp = nb.blk[ix][jx];
                nb.blk[ix][jx] = nb.blk[iz][jz];
                nb.blk[iz][jz] = temp;
                sb.push(nb);
            }
        }
        return sb;
    }

    // string representation of the board
    // (in the output format specified below)
    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append(N + "\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                s.append(String.format("%2d ", blk[i][j]));
            }
            s.append("\n");
        }
        return s.toString();
    }

    public static void main(String[] args) {
        // create initial board from file
        In in = new In(args[0]);
        int N = in.readInt();
        int[][] blocks = new int[N][N];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                blocks[i][j] = in.readInt();
        Board b = new Board(blocks);
        StdOut.println(b.toString());
        StdOut.println("manhattan="+b.manhattan());
        StdOut.println("isGoal="+b.isGoal());
        StdOut.println("tween=");
        StdOut.println((b.twin()).toString());
    }

}