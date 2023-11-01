public class Outcast
{
    private final WordNet wn;

    // constructor takes a WordNet object
    public Outcast(WordNet wordnet)
    {
        wn = wordnet;
    }

    // given an array of WordNet nouns, return an outcast
    public String outcast(String[] nouns)
    {
        int sum, maxd;
        String maxn;
        maxd = -1;
        maxn = " ";
        for (String n : nouns) {
            sum = 0;
            for (String x : nouns) {
                sum = sum + wn.distance(n, x);
            }
            if (sum > maxd) {
                maxd = sum;
                maxn = n;
            }
        }
        return maxn;
    }

    // for unit testing of this class (such as the one below)
    public static void main(String[] args)
    {
        WordNet wordnet = new WordNet(args[0], args[1]);
        Outcast outcast = new Outcast(wordnet);
        for (int t = 2; t < args.length; t++) {
            In in = new In(args[t]);
            String[] nouns = in.readAllStrings();
            StdOut.println(args[t] + ": " + outcast.outcast(nouns));
        }
    }
}