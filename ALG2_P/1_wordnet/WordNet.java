import java.util.Scanner;
import java.util.Hashtable;

public class WordNet
{
    private static final int INFINITY = Integer.MAX_VALUE;
    private RedBlackBST<String, Queue<Integer>> st =
            new RedBlackBST<String, Queue<Integer>>();
//  private RedBlackBST<Integer, String> stx = new RedBlackBST<Integer, String>();
    private Hashtable<Integer, String> stx = new Hashtable<Integer, String>();
    private Hashtable<String, String> ht = new Hashtable<String, String>();
    private final Digraph dg;
    private final SAP sap;

    // constructor takes the name of the two input files
    public WordNet(String synsets, String hypernyms)
    {
        In in1, in2;
        Scanner s, z;
        String line, x, y, word;
        int v, w;
        int count = 0;

        in1 = new In(synsets);
        while (!in1.isEmpty()) {
            line = in1.readLine();
            s = new Scanner(line).useDelimiter(",");
            v = Integer.decode(s.next()).intValue();
            x = s.next();
            stx.put(v, x);
            z = new Scanner(x).useDelimiter(" ");
            while (z.hasNext()) {
                word = z.next();
                if (!st.contains(word))
                     st.put(word, new Queue<Integer>());
                Queue<Integer> q = st.get(word);
                q.enqueue(v);
            }
            y = s.next();
            count++;
        }

        boolean[] bx = new boolean[count];
        dg = new Digraph(count);
        in2 = new In(hypernyms);
        boolean first = true;
        v = -1;
        w = -1;
        while (!in2.isEmpty()) {
            line = in2.readLine();
            s = new Scanner(line).useDelimiter(",");
            while (s.hasNextInt()) {
                if (first) {
                    v = Integer.decode(s.next()).intValue();
                    bx[v] = true;
                    first = false;
                    continue;
                }
                w = Integer.decode(s.next()).intValue();
                dg.addEdge(v, w);
            }
            first = true;
        }
        int cnt = 0;
        for (int i = 0; i < count; i++)
            if (!bx[i]) cnt++;
        if (cnt > 1 || new DirectedCycle(dg).hasCycle())
            throw new java.lang.IllegalArgumentException();

        sap = new SAP(dg);
    }

    // the set of nouns (no duplicates), returned as an Iterable
    public Iterable<String> nouns()
    {
        return st.keys();
    }

    // is the word a WordNet noun?
    public boolean isNoun(String word)
    {
        return st.contains(word);
    }

    private String findRoute(String nounA, String nounB, boolean mode)
    {
        String key = nounA+" "+nounB;
        String res, res1, res2;

        res = ht.get(key);
        if (res != null) {
            Scanner sc = new Scanner(res).useDelimiter(":");
            res1 = sc.next();
            res2 = sc.next();
            if (mode)
                return res1;
            else
                return res2;
        }
        if (!isNoun(nounA) || !isNoun(nounB))
            throw new java.lang.IllegalArgumentException();
        int len, minlen = INFINITY, minanc = -1;
        Queue<Integer> q1 = st.get(nounA);
        Queue<Integer> q2 = st.get(nounB);
        for (int x : q1) {
            for (int y : q2) {
                len = sap.length(x, y);
                if (len < minlen) {
                    minlen = len;
                    minanc = sap.ancestor(x, y);
                }
            }
        }
        if (minlen == INFINITY) {
            ht.put(key, "ERROR:ERROR");
            return "ERROR";
        }

        res1 = stx.get(minanc);
        res2 = Integer.valueOf(minlen).toString();
        ht.put(key, res1+":"+res2);
        if (mode)
            return res1;
        else
            return res2;
    }

    // distance between nounA and nounB (defined below)
    public int distance(String nounA, String nounB)
    {
        if (!isNoun(nounA) || !isNoun(nounB))
            throw new java.lang.IllegalArgumentException();
        String x = findRoute(nounA, nounB, false);
        if (x.compareTo("ERROR") == 0) return -1;
        return new Integer(x).intValue();
    }

    // a synset (second field of synsets.txt) that is
    // the common ancestor of nounA and nounB
    // in a shortest ancestral path (defined below)
    public String sap(String nounA, String nounB)
    {
        if (!isNoun(nounA) || !isNoun(nounB))
            throw new java.lang.IllegalArgumentException();
        String x = findRoute(nounA, nounB, true);
        if (x.compareTo("ERROR") == 0) return null;
        return x;
    }

    // for unit testing of this class
    public static void main(String[] args)
    {
        //WordNet wn = new WordNet("synsets.txt", "hypernyms.txt");
    }
}