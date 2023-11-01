import java.util.Hashtable;

public class BoggleSolver
{
    private BoTrieST dict;
    private Hashtable<String, String> ht;
    // Initializes the data structure using the given 
    // array of strings as the dictionary.
    // (You can assume each word in the dictionary 
    // contains only the uppercase letters A through Z.)
    public BoggleSolver(String[] dictionary) {
        dict = new BoTrieST();
        ht = new Hashtable<String, String>();
        for (int i = 0; i < dictionary.length; i++) {
            dict.put(dictionary[i], dictionary[i].length());
            ht.put(dictionary[i], "");
        }
    }

    // Returns the set of all valid words in 
    // the given Boggle board, as an Iterable.
    public Iterable<String> getAllValidWords(BoggleBoard board) {
        BoGraph G = new BoGraph(board);
        return dict.findWords(G);
    }

    // Returns the score of the given word if it is 
    // in the dictionary, zero otherwise.
    // (You can assume the word contains only the 
    // uppercase letters A through Z.)
    public int scoreOf(String word) {
        if (!ht.containsKey(word)) return 0;
        int len = word.length();
        if (len < 3) return 0;
        if (len == 3) return 1;
        if (len == 4) return 1;
        if (len == 5) return 2;
        if (len == 6) return 3;
        if (len == 7) return 5;
        return 11;   // ge 8
    }

    public static void main(String[] args) {
        char[][] b =  {
            { 'S', 'T', 'Y', 'P' },
            { 'E', 'T', 'R', 'N' },
            { 'L', 'S', 'E', 'A' },
            { 'B', 'H', 'M', 'I' }
        };

        BoggleBoard bb;
        if (args.length == 2)
            bb = new BoggleBoard(args[1]);
        else
            bb = new BoggleBoard(b);
//            bb = new BoggleBoard(10,10);
        StdOut.println(bb);
        BoggleSolver bs = new BoggleSolver(new In(args[0]).readAllStrings());
        for (String x : bs.getAllValidWords(bb))
            StdOut.println(x + " : " + bs.scoreOf(x));
    }
}