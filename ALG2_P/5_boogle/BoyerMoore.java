public class BoyerMoore {
    private final int R;     // the radix
    private int[] right;     // the bad-character skip array

    private String pat;      // or as a string

    public BoyerMoore(String pat) {
        this.R = 256;
        this.pat = pat;

        right = new int[R];
        for (int c = 0; c < R; c++)
            right[c] = -1;
        for (int j = 0; j < pat.length(); j++)
            right[pat.charAt(j)] = j;
    }

    public int search(String txt) {
        int N= txt.length();
        int M = pat.length();
        int skip;
        for (int i = 0; i <= N - M; i += skip) {
            skip = 0;
            for (int j = M - 1; j >= 0; j--) {
                if (j == M-1) StdOut.printf("%c ",txt.charAt(i+j));
                if (pat.charAt(j) != txt.charAt(i+j)) {
                    skip = Math.max(1, j - right[txt.charAt(i+j)]);
                    break;
                }
            }
            if (skip == 0) { StdOut.printf("\n"); return i; }
        }
        StdOut.printf("\n");
        return N;
    }

    // test client
    public static void main(String[] args) {
        String pat = args[0];
        String txt = args[1];

        BoyerMoore boyermoore1 = new BoyerMoore(pat);
        int offset1 = boyermoore1.search(txt);

        // print results
        StdOut.println("text:    " + txt);

        StdOut.print("pattern: ");
        for (int i = 0; i < offset1; i++)
            StdOut.print(" ");
        StdOut.println(pat);
    }
}