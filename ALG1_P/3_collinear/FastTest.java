public class FastTest 
{
    public static void main(String[] args)
    {
        int N = 10, x, y, P = 5;
        StdOut.println(P);
        for (int i=0; i<P; i++) {
            x = StdRandom.uniform(N);
            y = StdRandom.uniform(N);
            StdOut.println(x+" "+y);
        }
    }
}
