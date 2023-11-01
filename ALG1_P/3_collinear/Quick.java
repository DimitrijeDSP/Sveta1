
public class Quick
{

    private static void exch(Comparable[] a, int i, int j)
    {
        Comparable swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }

    private static boolean less(Comparable v, Comparable w)
    {
		return v.compareTo(w) < 0;
	}

	private static boolean isSorted(Comparable[] a, int min, int max)
	{
		if (max >= a.length) return false;
	    for (int i = min; i <= max; i++)
	        if (less(a[i], a[i-1])) return false;
	    return true;
    }

//  changed to public, just to test
    public static int partition(Comparable[] a, int lo, int hi)
    {
        int i = lo, j = hi+1;
        while (true)
        {
			while (less(a[++i], a[lo]))
			    if (i == hi) break;          // left

			while (less(a[lo], a[--j]))
			    if (j == lo) break;          // right

            if (i >= j) break;               // cross ?
            exch(a, i, j);                   // swap
		}

		exch(a, lo, j);                      // swap partitioning item
		return j;                            // item known to be in place
	}

    public static void sort(Comparable[] a)
    {
		StdRandom.shuffle(a);
		sort(a, 0, a.length - 1);
	}

	private static void sort(Comparable[] a, int lo, int hi)
	{
		if (hi <= lo) return;
		int j = partition(a, lo, hi);
		sort(a, lo, j-1);
		sort(a, j+1, hi);
	}

	public static Comparable select(Comparable[] a, int k)
	{
		StdRandom.shuffle(a);
		int lo = 0, hi = a.length - 1;
		while (hi > lo)
		{
			int j = partition(a, lo, hi);
			if      (j < k) lo = j + 1;
			else if (j > k) hi = j - 1;
			else            return a[k];
		}
		return a[k];
	}

    public static void sort3W(Comparable[] a, int lo, int hi)
    {
		 if (hi <= lo) return;
		 int lt = lo, gt = hi;
		 Comparable v = a[lo];
		 int i = lo;
		 while (i <= gt)
		 {
			 int cmp = a[i].compareTo(v);
			 if (cmp < 0) exch(a, lt++, i++);
			 else if (cmp > 0) exch (a, i, gt--);
			 else i++;
		 }

//		 sort (a, lo, lt -1);
//		 sort (a, gt+1, hi);
	 }


}