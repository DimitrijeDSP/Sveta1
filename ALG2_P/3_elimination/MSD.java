public class MSD
{
    public static void sort(String[] a, int W) {
        String[] aux = new String[a.length];
        sort(a, aux, 0, a.length-1, 0);
    }

    private static int charAt(String s, int d) {
        if (d == s.length()) return -1;
        return s.charAt(d);
    }

    private static void sort(String[] a, String[] aux, int lo, int hi, int d) {
        int R = 256;
        int N = a.length;

        if (hi <= lo) return;
        int[] count = new int[R+2];
        for (int i = lo; i <= hi; i++)
           count[charAt(a[i], d) + 2]++;
        for (int r = 0; r < R+1; r++)
              count[r + 1] += count[r];
        for (int i = lo; i <= hi; i++)
            aux[count[charAt(a[i], d) + 1]++] = a[i];
        for (int i = lo; i <= hi; i++)
            a[i] = aux[i - lo];
        StdOut.printf("############ d=\n");
        prt(a);

        for (int r = 0; r < R; r++)
            sort(a, aux, lo + count[r], lo + count[r+1] -1, d+1);
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
            MSD.sort(x, 4);
            prt(x);
        }
        else {
            MSD.sort(args, args[0].length());
            prt(args);
        }
    }
}