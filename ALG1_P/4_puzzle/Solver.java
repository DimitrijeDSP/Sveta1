public class Solver
{
    private static boolean debug = false;
    private int totnom;     // number of moves so far
    private SearchNode sinit1;
    private SearchNode sinit2;
    private MinPQ<SearchNode> pq1;
    private MinPQ<SearchNode> pq2;
    private Queue<Board> solqueue;
    private boolean solverstat;

    private class SearchNode implements Comparable<SearchNode>
    {
        private int nom;     // number of moves so far
        private Board cur;
        private SearchNode old;

        private SearchNode(Board bn)
        {
            cur = bn;
            nom = 0;
            old = null;
        }

        private SearchNode(SearchNode nold, Board bn)
        {
            cur = bn;
            nom = nold.getNom() + 1;
            old = nold;
        }

        private Board getBoard() {
            return cur;
        }

        private int getNom() {
            return nom;
        }

        private SearchNode getPrev() {
            return old;
        }

        public int compareTo(SearchNode that)
        {
            int s1 = that.getBoard().manhattan() + that.getNom();
            int s2 = this.getBoard().manhattan() + this.getNom();
            if (s1 == s2) return (0);
            if (s1 > s2) return (-1);
            if (s1 < s2) return (1);
            return (0);
        }

        public String toString() {
            int i1 = this.getBoard().manhattan();
            int i2 = this.getNom();
            StringBuilder s = new StringBuilder();
            s.append("manhattan" + i1 + "\n");
            s.append("moves    " + i2 + "\n");
            s.append("priority " + (i1 + i2) + "\n");
            s.append(this.getBoard().toString());
            return s.toString();
        }

    }

    // find a solution to the initial board (using the A* algorithm)
    public Solver(Board initial) {
        totnom = 0;
        sinit1 = new SearchNode(initial);
        sinit2 = new SearchNode(initial.twin());
        pq1 = new MinPQ<SearchNode>();
        pq2 = new MinPQ<SearchNode>();
        pq1.insert(sinit1);
        pq2.insert(sinit2);
        solqueue = new Queue<Board>();
        solqueue.enqueue(initial);
        solverstat = compute();
    }

    // is the initial board solvable?
    public boolean isSolvable() {
        return solverstat;
    }

    private boolean compute() {
        SearchNode x1, xp1, xt1, x2, xp2, xt2;
        Board bx1, bx2;
        boolean status = false, seen1 = false, seen2 = false;

        if (debug) StdOut.println("isSolvable: WHILE LOOP");
        while (!pq1.isEmpty() && !pq2.isEmpty()) {
            x1 = pq1.delMin();
            if (x1 == null) break;
            x2 = pq2.delMin();
            if (x2 == null) break;
            bx1 = x1.getBoard();
            if (bx1 == null) break;
            bx2 = x2.getBoard();
            if (bx2 == null) break;
            solqueue.enqueue(bx1);
            if (debug) StdOut.println("DELMIN");
            if (debug) StdOut.println(x1);
            if (bx1.isGoal()) {
                if (debug) StdOut.println("GOAL !!!!");
                status = true;
                totnom = x1.getNom();
                break;
            }
            if (bx2.isGoal()) {
                if (debug) StdOut.println("TWIN GOAL = NO SOLUTION !!!!");
                status = false;
                totnom = -1;
                solqueue = null;
                break;
            }
            xp1 = x1.getPrev();
            xp2 = x2.getPrev();
            if (debug) StdOut.println("===== START INSERT NEIGHBORS IN PQ ======");
            for (Board nx1 : bx1.neighbors()) {
                xt1 = x1.getPrev();
                seen1 = false;
                while (xt1 != null) {
                    if (nx1.equals(xt1.getBoard())) {
                        seen1 = true;
                        break;
                    }
                    xt1 = xt1.getPrev();
                }
                if (seen1) continue;
                if (debug) StdOut.println("manhattan="+nx1.manhattan());
                if (debug) StdOut.println("moves="+(x1.getNom()+1));
                if (debug) StdOut.println("priority="
                           +(nx1.manhattan()+x1.getNom()+1));
                if (debug) StdOut.println(nx1);
                pq1.insert(new SearchNode(x1, nx1));
            }
            if (debug) StdOut.println("==== STOP  INSERT NEIGHBORS IN PQ ======");
            if (debug) StdOut.println("===== START INSERT TWIN NEIGHBORS IN PQ ");
            for (Board nx2 : bx2.neighbors()) {
                xt2 = x2.getPrev();
                seen2 = false;
                while (xt2 != null) {
                    if (nx2.equals(xt2.getBoard())) {
                        seen2 = true;
                        break;
                    }
                    xt2 = xt2.getPrev();
                }
                if (seen2) continue;
                if (debug) StdOut.println("manhattan="+nx2.manhattan());
                if (debug) StdOut.println("moves="+(x2.getNom()+1));
                if (debug) StdOut.println("priority="
                           +(nx2.manhattan()+x2.getNom()+1));
                if (debug) StdOut.println(nx2);
                pq2.insert(new SearchNode(x2, nx2));
            }
            if (debug) StdOut.println("==== STOP  INSERT TWIN NEIGHBORS IN PQ =");
        }
        return status;
    }

    // min number of moves to solve initial board; -1 if no solution
    public int moves() {
        return totnom;
    }

    public Iterable<Board> solution() {
        return solqueue;
    }

    public static void main(String[] args) {
        // create initial board from file
        In in = new In(args[0]);
        debug = args.length > 1 && args[1].equals("D");
        int N = in.readInt();
        int[][] blocks = new int[N][N];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                blocks[i][j] = in.readInt();
        Board initial = new Board(blocks);

        // solve the puzzle
        Solver solver = new Solver(initial);

        // print solution to standard output
        if (!solver.isSolvable())
            StdOut.println("No solution possible");
        else {
            StdOut.println("Minimum number of moves = " + solver.moves());
            for (Board board : solver.solution())
                StdOut.println(board);
        }
    }
}

