public class KnuthMorrisPratt {
    private int M;
    private int[][] dfa;
    private final int R;   // radix
    private String pat;

    public KnuthMorrisPratt(String pat) {
        this.R = 256;
        this.pat = pat;
        this.M = pat.length();
        dfa = new int [R][M];
        dfa[pat.charAt(0)][0] = 1;
        for (int X = 0, j = 1; j < M; j++) {
            for (int c = 0; c < R; c++) {
                dfa[c][j] = dfa[c][X];
            }
            dfa[pat.charAt(j)][j] = j+1;
            X = dfa[pat.charAt(j)][X];    
        }
    }

    private void printdfa(String x) {
        for (int i = 0; i < x.length(); i++) {
            for (int j = 0; j < M; j++) {
                StdOut.printf("%d ", dfa[x.charAt(i)][j]);
            }
            StdOut.printf("\n");
        }
    }

    public int search(String txt) {
        int i, j, N = txt.length();
        for (i = 0, j = 0; i < N && j < M; i++) 
            j = dfa[txt.charAt(i)][j];
        if (j == M) 
            return i - M;
        else
            return N;
    }

    public int search(In in) {
        int i, j;
        for (i = 0, j = 0; !in.isEmpty() && j < M; i++) 
            j = dfa[in.readChar()][j];
        if (j == M) 
            return i - M;
        else
            return -1;
    }

    public static void main(String[] args) {
        KnuthMorrisPratt kmp = new KnuthMorrisPratt(args[0]);
        kmp.printdfa("ABC");
    }
}