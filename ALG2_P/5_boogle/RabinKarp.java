import java.util.Random;

public class RabinKarp {
    private long patHash;       // pattern hash value
    private int M;              // pattern length
    private long Q;             // modulus
    private int R;              // radix
    private long RM;            // R^(M-1) % Q
    String pat;                 // for Las Vegas only

    public RabinKarp(String pat) {
        this.pat = pat;
        M = pat.length();
        R = 256;
        Q = longRandomPrime();

        RM = 1;
        for (int i = 1; i <= M-1; i++) 
            RM = (R * RM) % Q;
        patHash = hash(pat, M);
    }

    private long hash(String key, int M)
    {
        long h = 0;
        for (int j = 0; j < M; j++)
            h = (R * h + key.charAt(j)) % Q;
        return h;
    }

    // Monte Carlo
    public int search(String txt)
    {
        int N = txt.length();
        long txtHash = hash(txt, M);
        if (patHash == txtHash) return 0;
        for (int i = M; i < N; i++) {
            txtHash = (txtHash + Q - RM*txt.charAt(i-M) % Q) % Q;
            txtHash = (txtHash*R + txt.charAt(i)) % Q;
            if (patHash == txtHash) return i - M + 1;
        }
        return N;
    }

    private static long longRandomPrime() {
//        BigInteger prime = BigInteger.probablePrime(31, new Random());
//        return prime.longValue();
        return (long) 149;
    }

    public static void main(String[] args) {
        String pat = args[0];
        String txt = args[1];
        char[] pattern = pat.toCharArray();
        char[] text    = txt.toCharArray();

        RabinKarp searcher = new RabinKarp(pat);
        int offset = searcher.search(txt);

        // print results
        StdOut.println("text:    " + txt);

        // from brute force search method 1
        StdOut.print("pattern: ");
        for (int i = 0; i < offset; i++)
            StdOut.print(" ");
        StdOut.println(pat);
    }
}


