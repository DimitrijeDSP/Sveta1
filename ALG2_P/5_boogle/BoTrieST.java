import java.util.Hashtable;

public class BoTrieST {
    private static final int R = 26;  // ASCII CAPITAL LETTERS
    private Bag<String> words;
    private Hashtable<String, String> ht;
    private boolean[] seen;
    private Node root;      // root of trie
    private int N;          // number of keys in trie

    private static class Node {
        private int val;
        private Node[] next = new Node[R];
    }

    public void put(String key, int val) {
        root = put(root, key, val, 0);
    }

    private Node put(Node x, String key, int val, int d) {
        if (x == null) x = new Node();
        if (d == key.length()) {
            if (x.val == 0) N++;
            x.val = val;
            return x;
        }
        int c = key.charAt(d) - 'A';
        x.next[c] = put(x.next[c], key, val, d+1);
        return x;
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

    public Iterable<String> findWords(BoGraph G) {
        int ind1, ind2;
        char c;
        Node tn;
 
        seen = new boolean[G.V()];
        words = new Bag<String>();
        ht = new Hashtable<String, String>();
        for (int i = 0; i < G.V(); i++)
            seen[i] = false;
        for (int i = 0; i < G.V(); i++) {
            StringBuilder str = new StringBuilder();
            c = G.getBBL(i);
            ind1 = c - 65;
            tn = root.next[ind1];
            if (c == 'Q' && tn != null) tn = tn.next['U' - 65];
            str.append(c);
            dfs(G, i, tn, str);
        }
        return words;
    }

    private void dfs(BoGraph G, int v, Node curr, StringBuilder str) {
        int ind1, ind2;
        char c;
        Node tn;
 
//      StdOut.printf("str=%s<-\n", str.toString());
        int currlen = str.length();
        if (curr == null) { 
            str.deleteCharAt(currlen - 1);
            return;
        }

        String str1 = convert(str);
        if (curr.val == str1.length() 
            && !ht.containsKey(str1) 
            && str1.length() >= 3)  {
                words.add(str1);
                ht.put(str1, "");
        }

        seen[v] = true;
        for (int w : G.adj(v)) {
            if (seen[w]) continue;
            c = G.getBBL(w);
            ind1 = c - 65;
            tn = curr.next[ind1];
            if (c == 'Q' && tn != null) tn = tn.next['U' - 65];
            str.append(c);
            dfs(G, w, tn, str);
        }
        seen[v] = false;
        str.deleteCharAt(currlen - 1);
    }
}