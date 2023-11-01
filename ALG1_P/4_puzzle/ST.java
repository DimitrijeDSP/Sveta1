import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.SortedMap;
import java.util.TreeMap;

public class ST<Key, Value>
{
    private TreeMap<Key, Value> st;

    public ST() {
        st = new TreeMap<Key, Value>();
    }

    void put(Key key, Value val) {
        if (key == null) throw
        new NullPointerException("called get() with null key");
        if (val == null)
            st.remove(key);
        else
            st.put(key, val);
    }

    Value get(Key key) {
        if (key == null) throw
        new NullPointerException("called get() with null key");
        return st.get(key);
    }

    void delete(Key key) {
        if (key == null) throw
        new NullPointerException("called get() with null key");
        put(key, null);
    }

    boolean contains(Key key) {
        if (key == null) throw
        new NullPointerException("called get() with null key");
        return get(key) != null;
//        return st.containsKey(key);
    }

    boolean isEmpty() {
        return size() == 0;
    }

    int size() {
        return st.size();
    }

    Iterable<Key> keys()
    {
        return st.keySet();
    }

    public static void main(String[] args)
    {
        ST<String, Integer> st = new ST<String, Integer>();
        for (int i = 0; !StdIn.isEmpty(); i++)
        {
            String key = StdIn.readString();
            st.put(key, i);
        }
        for (String s : st.keys())
            StdOut.println(s + " " + st.get(s));
    }

}