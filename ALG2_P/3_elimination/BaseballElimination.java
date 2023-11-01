// INPUT FILE FORMAT
// 7
// U.S.A.    14  5  9    0 1 2 3 1 2 0
// England   12  3  7    1 0 2 1 2 1 0
// France    16  2  7    2 2 0 1 1 1 0
// Germany   13  3  5    3 1 1 0 0 0 0
// Ireland   11  3  5    1 2 1 0 0 1 0
// Belgium   12  4  7    2 1 1 0 1 0 2
// China     13  2  2    0 0 0 0 0 2 0

public class BaseballElimination {
    private int n;
    private String[] teams;
    private int[] w;
    private int[] l;
    private int[] r;
    private int[][] g;
    private int ct;   // current team examined
    private int estat;   // elimination status from testFF() 
    private FordFulkerson ff;

    // FlowNetwork fn;

    // create a baseball division from given 
    // filename in format specified below
    public BaseballElimination(String filename) {
        In in = new In(filename);
        n = in.readInt();
        teams = new String[n];
        w = new int[n];
        l = new int[n];
        r = new int[n];
        g = new int[n][];
        ct = -1;
        ff = null;
        estat = -1;
 
        for (int i = 0; i < n; i++) {
            g[i] = new int[n];
            teams[i] = in.readString();
            w[i] = in.readInt();
            l[i] = in.readInt();
            r[i] = in.readInt();
            for (int j = 0; j < n; j++)
                g[i][j] = in.readInt();
        }
    }

    private void printTeams() {
        StdOut.println("                w[i] l[i] r[i]          g[i][j]");
        StdOut.println("i  team         wins loss left  ");
        StdOut.println("                w[i] l[i] r[i]          g[i][j]");
        for (int i = 0; i < n; i++) {
            StdOut.printf("%d %s %d\t%d\t%d\t", i, teams[i], w[i], l[i], r[i]);
            for (int j = 0; j < n; j++) 
                StdOut.printf("\t%d", g[i][j]);
            StdOut.printf("\n");
        }
    }

    // number of teams
    public int numberOfTeams() {
        return n;
    }

    // all teams
    public Iterable<String> teams() {
        Bag<String> t = new Bag<String>();
        for (int i = 0; i < n; i++)
            t.add(teams[i]);
        return t;
    }

    private int findTeam(String t) {
        int x = -1;
        if (t == null) return x;
        for (int i = 0; i < n; i++) {
            if (teams[i].compareTo(t) == 0) {
                x = i;
                break;
            }        
        }
        return x;
    }

    // number of wins for given team
    public int wins(String team) {
        int t = findTeam(team);
        if (t == -1) throw new java.lang.IllegalArgumentException();
        return w[t];
    }

    // number of losses for given team
    public int losses(String team) {
        int t = findTeam(team);
        if (t == -1) throw new java.lang.IllegalArgumentException();
        return l[t];
    }

    // number of remaining games for given team
    public int remaining(String team) {
        int t = findTeam(team);
        if (t == -1) throw new java.lang.IllegalArgumentException();
        return r[t];
    }

    // number of remaining games between team1 and team2
    public int against(String team1, String team2) {
        int t1 = findTeam(team1);
        if (t1 == -1) throw new java.lang.IllegalArgumentException();
        int t2 = findTeam(team2);
        if (t2 == -1) throw new java.lang.IllegalArgumentException();
        return g[t1][t2];
    }

    private void testFF(int x)
    {
        int delta;
        if (x == ct) return;

        double inf = Double.POSITIVE_INFINITY;
        int i, j, s = n, t = n+1, cnt = n+2;

        if (n <= 1) {
            ct = x;
            estat = 1;
            ff = null;
            return;   // no elimination, only one team
        }
        FlowNetwork fn = new FlowNetwork(n*n);

        for (i = 0; i < n; i++) {
            if (i == x) continue;
            delta = w[x] + r[x] - w[i];
            if (delta < 0) {
                ct = x;
                estat = 2;
                ff = null;
                return;   // simple elimination
            }
            fn.addEdge(new FlowEdge(i, t, delta, 0));
        }

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (i == x || j == x) continue;
                if (j <= i) continue;
                fn.addEdge(new FlowEdge(s, cnt, g[i][j], 0));
                fn.addEdge(new FlowEdge(cnt, i, inf, 0));
                fn.addEdge(new FlowEdge(cnt, j, inf, 0));
                cnt++;
            }
        }

        // StdOut.println(fn);

        // compute maximum flow and minimum cut
        ff = new FordFulkerson(fn, s, t);
        ct = x;
        estat = 0;
        return; // complex elimination, we will use flow graph
    }

    // is given team eliminated?
    public boolean isEliminated(String team) {
        if (n == 1) return false;
        int t = findTeam(team);
        if (t == -1) throw new java.lang.IllegalArgumentException();

        if (ct != t) testFF(t);
        if (estat == 2) return true;
        if (estat == 1) return false;
        if (estat == 0) { 
            for (int i = 0; i < n; i++) {
                if (i == t) continue;
                if (ff.inCut(i)) return true;
            }
        }
        return false;        
    } 

    // subset R of teams that eliminates given team; null if not eliminated
    public Iterable<String> certificateOfElimination(String team) {
        int t = findTeam(team);
        if (t == -1) throw new java.lang.IllegalArgumentException();
        Bag<String> x = new Bag<String>();
        if (ct != t) testFF(t);
        if (estat == 1) return x;
        if (estat == 0) {  
            for (int i = 0; i < n; i++) {
                if (i == t) continue;
                if (ff.inCut(i)) x.add(teams[i]);
            }
        }
        if (estat == 2) {  
            for (int i = 0; i < n; i++) {
                if (i == t) continue;
                if (w[t] + r[t] - w[i] < 0) x.add(teams[i]);
            }
        }
        if (x.isEmpty()) return null;
        return x;
    }

    public static void main(String[] args) {
        BaseballElimination division = new BaseballElimination(args[0]);
        division.printTeams();

//        for (String team : division.teams()) {
//            if (division.isEliminated(team)) {
//                StdOut.print(team + " is eliminated by the subset R = { ");
//                for (String t : division.certificateOfElimination(team))
//                    StdOut.print(t + " ");
//                StdOut.println("}");
//            }
//            else {
//                StdOut.println(team + " is not eliminated");
//            }
//        }
    }
}