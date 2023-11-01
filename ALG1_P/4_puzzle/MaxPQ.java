public class MaxPQ<Key extends Comparable<Key>>
{
    private Key[] pq;
    private int N;
    private int comp;

    public MaxPQ(int capacity)
    {
        comp = 0;
        pq = (Key[]) new Comparable[capacity+1];
    }

    public boolean isEmpty()
    {
        return N == 0;
    }

    public int getComp()
    {
        return comp;
    }

    public void insert(Key x)
    {
        pq[++N] = x;
        swim(N);
    }

    public Key delMax()
    {
        Key max = pq[1];
        exch(1, N--);
        sink(1);
        pq[N+1] = null;
        return max;
    }

    private void swim(int k)
    {
        while (k > 1 && less(k/2, k))
        {
            exch(k, k/2);
            k = k/2;
        }
    }

    private void sink(int k)
    {
        while (2*k <= N)
        {
            int j = 2*k;
            if (j < N && less(j, j+1)) j++;
            if (!less(k, j)) break;
            exch(k, j);
            k = j;
        }
    }

    private boolean less(int i, int j)
    {
        comp++;
        return pq[i].compareTo(pq[j]) < 0;
    }

    private void exch(int i, int j)
    {
        Key t = pq[i];
        pq[i] = pq[j];
        pq[j] = t;
    }

    private String toStr()
    {
        StringBuilder s = new StringBuilder();
        for (int i=1; i<=N; i++)
            s.append(" " + pq[i]);
        return s.toString();
    }

    public static void main(String[] args)
    {
        MaxPQ<Integer> x = new MaxPQ<Integer>(20);
        int[] a = {92, 75, 65, 57, 47, 44, 17, 35, 51, 45, 61, 58, 10};

        for (int i=0; i<13; i++) {
            x.insert(a[i]);
        }
        StdOut.println(x.toStr());

        MaxPQ<Integer> x1 = new MaxPQ<Integer>(20);
        int[] a1 = {94, 89, 75, 87, 63, 43, 38, 52, 73, 24};

        for (int i=0; i<10; i++) {
            x1.insert(a1[i]);
        }
        x1.delMax();
        x1.delMax();
        x1.delMax();
        StdOut.println(x1.toStr());

        MaxPQ<Integer> x2 = new MaxPQ<Integer>(20);
        int[] a2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

        for (int i=0; i<15; i++) {
            x2.insert(a2[i]);
        }
        StdOut.println(x2.toStr());
        StdOut.println("comp="+x2.getComp());

        MaxPQ<Integer> x3 = new MaxPQ<Integer>(20);
        int[] a3 = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

        for (int i=0; i<15; i++) {
            x3.insert(a3[i]);
        }
        StdOut.println(x3.toStr());
        StdOut.println("comp="+x3.getComp());

        MaxPQ<Integer> x4 = new MaxPQ<Integer>(20);
        int[] a4 = {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15};

        for (int i=0; i<15; i++) {
            x4.insert(a4[i]);
        }
        StdOut.println(x4.toStr());
        StdOut.println("comp="+x4.getComp());

        MaxPQ<Integer> x5 = new MaxPQ<Integer>(20);
        int[] a5 = {11, 15, 17, 8, 2, 4, 35, 75, 11, 10, 13, 99, 3, 12, 19};

        for (int i=0; i<15; i++) {
            x5.insert(a5[i]);
        }
        StdOut.println(x5.toStr());
        StdOut.println("comp="+x5.getComp());

    }

}