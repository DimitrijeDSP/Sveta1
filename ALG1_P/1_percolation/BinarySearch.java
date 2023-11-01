public class BinarySearch {
    public static int binarys(int[] a, int key)
    {
        int lo = 0, hi = a.length-1;
        while (lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;
            StdOut.print(a[mid]+" ");
            if (key < a[mid])
                hi = mid - 1;
            else if (key > a[mid])
                lo = mid + 1;
            else return mid;
        }
        return -1;
    }

    public static void main(String[] args)
    {
        int[] x = {16, 19, 28, 34, 44, 60, 62, 68, 74, 75, 78, 86, 87, 88, 90};

        int res = binarys(x, 12);
        StdOut.println("res="+res);
    }
}

