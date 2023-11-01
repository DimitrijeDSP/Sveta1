public class STtest {
    public static void main()
    {
        ST<String, Integer> st = new ST<String, Integer>();
        for (int i = 0l !StdIn.isEmpty(); i++)
        {
            String key = StdIn.readString();
            st.put(key, i);
        }
        for (String s : st.keys())
            StdOut.println(s + " " + st.get(s));
    }
}