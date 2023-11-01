import java.util.Hashtable;

public class BoggleSolver
{
    private int[][] xrefx;
    private TST<Integer> dict;
    private Hashtable<String, Bag<String>> htx;
    // Initializes the data structure using the given 
    // array of strings as the dictionary.
    // (You can assume each word in the dictionary 
    // contains only the uppercase letters A through Z.)
    public BoggleSolver(String[] dictionary) {

        int[][] xrefx1 = {   
        { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15},
        {12,  8,  4,  0, 13,  9,  5,  1, 14, 10,  6,  2, 15, 11,  7,  3},
        {15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0},
        { 3,  7, 11, 15,  2,  6, 10, 14,  1,  5,  9, 13,  0,  4,  8, 12},
        { 3,  2,  1,  0,  7,  6,  5,  4, 11, 10,  9,  8, 15, 14, 13, 12},
        {15, 11,  7,  3, 14, 10,  6,  2, 13,  9,  5,  1, 12,  8,  4,  0},
        {12, 13, 14, 15,  8,  9, 10, 11,  4,  5,  6,  7,  0,  1,  2,  3},
        { 0,  4,  8, 12,  1,  5,  9, 13,  2,  6, 10, 14,  3,  7, 11, 15}
        };
        xrefx = xrefx1;
        dict = new TST<Integer>();
        htx = new Hashtable<String, Bag<String>>();
        for (int i = 0; i < dictionary.length; i++) {
            dict.put(dictionary[i], dictionary[i].length());
        }
    }

    // Returns the set of all valid words in 
    // the given Boggle board, as an Iterable.
    public Iterable<String> getAllValidWords(BoggleBoard board) {
        Bag<String> sb;
        String[] x = xboard(board);
        if (x != null) {
            for (int i = 0; i < 8; i++) {
                sb = htx.get(x[i]);
                if (sb != null) return sb;
            }
        }
        BoGraph G = new BoGraph(board);
        BoPaths bp = new BoPaths(G, dict);
        StringBuilder xx = new StringBuilder();
        for (int j = 0; j < G.V(); j++) 
            xx.append(G.getBBL(j));
        sb = bp.wordsFound(); 
        if (sb != null) htx.put(xx.toString(), sb);
        return sb;
    }

    // Returns the score of the given word if it is 
    // in the dictionary, zero otherwise.
    // (You can assume the word contains only the 
    // uppercase letters A through Z.)
    public int scoreOf(String word) {
        if (!dict.contains(word)) return 0;
        int len = word.length();
        if (len < 3) return 0;
        if (len == 3) return 1;
        if (len == 4) return 1;
        if (len == 5) return 2;
        if (len == 6) return 3;
        if (len == 7) return 5;
        return 11;   // ge 8
    }

    private String[] xboard(BoggleBoard b) {
        int br = b.rows();
        int bc = b.cols();
        String[] x = new String[8];
        if (bc != 4 || br != 4) return null;
        for (int i = 0; i < 8; i++) {
            StringBuilder sb = new StringBuilder();
            for (int j = 0; j < 16; j++) {
                sb.append(b.getLetter(xrefx[i][j] / bc, xrefx[i][j] % bc));
            }
            x[i] = sb.toString();
        }
        return x;
    }

    public static void main(String[] args) {
        char[][] b =  {
            { 'I', 'R', 'L', 'S' },
            { 'E', 'F', 'D', 'N' },
            { 'T', 'L', 'O', 'E' },
            { 'E', 'W', 'N', 'V' }
        };
        BoggleBoard bb;
        if (args.length == 2)
            bb = new BoggleBoard(args[1]);
        else
//            bb = new BoggleBoard(b);
            bb = new BoggleBoard(10,10);
        StdOut.println(bb);
        BoggleSolver bs = new BoggleSolver(new In(args[0]).readAllStrings());
 //       String[] xx = bs.xboard(bb);
        for (String x : bs.getAllValidWords(bb))
            StdOut.println(x + " : " + bs.scoreOf(x));
    }
}