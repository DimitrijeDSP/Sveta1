public class Radix3Way
{
    public static void sort(String[] a) {
        sort(a, 0, a.length-1, 0);
    }

    private static void sort(String[] a, int lo, int hi, int d) {
        if (hi <= lo) return;
        int lt = lo, gt = hi;
        int v = charAt(a[lo], d);
        int i = lo + 1;
        while (i <= gt)
        {
            int t = charAt(a[i], d);
            if (t < v) exch(a, lt++, i++);
            else if (t > v) exch(a, i, gt--);
            else i++;
        }

        StdOut.println("####################");
        prt(a);
        sort(a, lo, lt-1, d);
        if (v >= 0) sort(a, lt, gt, d+1);
        sort(a, gt+1, hi, d);
    }

    private static int charAt(String s, int d) {
        if (d == s.length()) return -1;
        return s.charAt(d);
    }

    private static void exch(String[] a, int i, int j) {
        String temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

    public static void prt(String[] x) {
        for (String y : x)
            StdOut.print(y+" ");
        StdOut.printf("\n");            
    }

    public static void main(String[] args) {
        String[] x = {"abcx","xxxx","zxyx","xccx",
                      "ssdx","eeex","rrrx","tttx",
                      "abcx","xxxy","zxyx","xccy",
                      "ssdy","eeex","rrry","tttx"};
        if (args.length == 0) {
            Radix3Way.sort(x);
            prt(x);
        }
        else {
            Radix3Way.sort(args);
            prt(args);
        }
    }
}