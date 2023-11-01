public class LSD
{
    public static void sort(String[] a, int W) {
        int R = 256;
        int N = a.length;
        String[] aux = new String[N];

        for (int d = W-1; d >= 0; d--) {
            int[] count = new int[R+1];
            for (int i = 0; i < N; i++)
                count[a[i].charAt(d) + 1]++;
            for (int r = 0; r < R; r++)
                count[r + 1] += count[r];
            for (int i = 0; i < N; i++)
                aux[count[a[i].charAt(d)]++] = a[i];
            for (int i = 0; i < N; i++)
                a[i] = aux[i];
            StdOut.printf("############ d=%d\n",d);
            prt(a);
        }
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
            LSD.sort(x, 4);
            prt(x);
        }
        else {
            LSD.sort(args, args[0].length());
            prt(args);
        }
    }
}