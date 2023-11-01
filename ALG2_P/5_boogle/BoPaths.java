import java.util.Hashtable;

public class BoPaths {
// -------- trie part -------------
    private static final int R = 26;        // A-Z ASCII
    private Node root;                      // root of trie
    private int nt;
    private Bag<String> words;
    private Hashtable<String, String> ht;
    private class Node {
        private Node[] next = new Node[R];
    }
// -------- trie part -------------
    private BoTrieST<Integer> dict;
    private boolean[] seen;

    public BoPaths(BoGraph G, BoTrieST<Integer> dict) {
        seen = new boolean[G.V()];
        root = new Node();
        words = new Bag<String>();
        ht = new Hashtable<String, String>();
        nt = 0;
        this.dict = dict;
        for (int i = 0; i < G.V(); i++)
            seen[i] = false;
        for (int i = 0; i < G.V(); i++) { 
            int ind = G.getBBL(i) - 65;
            StringBuilder sb = new StringBuilder();
            sb.append(G.getBBL(i));
            Node temp = root.next[ind];
            root.next[ind] = dfs(G, i, temp, root, sb);             
        }
    }

    private String convert(StringBuilder str) {
        StringBuilder str1 = new StringBuilder();
        for (int i = 0; i < str.length(); i++) {
            char x = str.charAt(i);
            str1.append(x);
            if (x == 'Q') str1.append('U');
        }
        return str1.toString();
    }

    private Node dfs(BoGraph G, int v, Node curr, Node pare, StringBuilder str) {
        Node curr1 = curr;
        boolean found = false;
        // .Q   => .QU     1  3  ok
        // Q.   => QU.     1  3  ok 
        // QQ   => QUQU    2  4  ok
        // Q    => QU      1  2  X
        int strl = str.length();
        int strl1 = strl;
        if (strl >= 1 && str.charAt(0) == 'Q') strl1++;
        if (strl >= 2 && str.charAt(1) == 'Q') strl1++;
        if (strl1 > 2) { 
            String str1 = convert(str);
            for (String x : dict.keysWithPrefix(str1)) {
                found = true;
                // StdOut.printf("current string %s is"+
                // " preffix of %s from dictionary\n", str1, x);
                if (!ht.containsKey(str1) && x.compareTo(str1) == 0) {
                    words.add(x);
                    ht.put(str1, "");
                }
            }
            if (!found) {
                str.deleteCharAt(str.length() - 1); 
                return curr1;
            }
        }

        int ind;
        if (curr1 == null) {
            curr1 = new Node();
            pare.next[G.getBBL(v) - 65] = curr1;     
            nt++; 
        }
        seen[v] = true;
        for (int w : G.adj(v)) {
            if (seen[w]) continue;
            int ind1 = G.getBBL(w) - 65;
            char c = (char) ind1;
            str.append(G.getBBL(w));
            Node temp = curr1.next[ind1];
            curr1.next[ind1] = dfs(G, w, temp, curr1, str);
        }
        seen[v] = false;
        str.deleteCharAt(str.length() - 1);
        return curr1; 
    }

    private void ckrf(Node x) {
        if (x == null) 
            StdOut.printf("ref=nul \n");
        else 
            StdOut.printf("ref=val \n");
    }

    private void ckrt() {
        for (int i = 0; i < R; i++) {
            if (root.next[i] == null) 
                StdOut.printf("nul ");
            else 
                StdOut.printf("val ");
        }
        StdOut.println();
    }

//    public Iterable<String> wordsFound() {
    public Bag<String> wordsFound() {
        return words;
    }

    public static void main(String[] args) {
        char[][] b =  {
            { 'A', 'B', 'T', 'Y' },
            { 'T', 'A', 'S', 'F' },
            { 'M', 'X', 'T', 'O' },
            { 'Z', 'A', 'B', 'R' }
        };
        BoggleBoard bb;
        if (args.length == 2)
            bb = new BoggleBoard(args[1]);
        else
            bb = new BoggleBoard(b);
        StdOut.println(bb);

        BoGraph G = new BoGraph(bb);
        StdOut.println(bb);
        StdOut.println(G.toChars());

        TST<Integer> dict = new TST<Integer>();

        String word;
        In in = new In(args[0]);
        while (!in.isEmpty()) {
            word = in.readString();
            dict.put(word, word.length());
        }

        String[] tst = {"ABC", "WOR", "BEE", "BEEX"};
        for (int s = 0; s < tst.length; s++)
            StdOut.printf("longestPrefixOf(%s)=%s<-\n", tst[s], dict.longestPrefixOf(tst[s]));

//        BoPaths bp = new BoPaths(G, dict);
//        for (String x : bp.wordsFound()) 
//            StdOut.println(x);
    }
}
