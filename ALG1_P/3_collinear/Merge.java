public class Merge
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

    private static void merge(Comparable[] a, Comparable[] aux, int lo, int mid, int hi)
    {
    	assert isSorted(a, lo, mid);    // precondition: a[lo..mid] sorted
        assert isSorted(a, mid+1, hi);  // precondition: a[mid+1..hi] sorted

        for (int k = lo; k <= hi; k++)
            aux[k] = a[k];

        int i = lo, j = mid+1;
        for (int k = lo; k <= hi; k++)
        {
    		if      (i > mid)              a[k] = aux[j++];
    		else if (j > hi)               a[k] = aux[i++];
    		else if (less(aux[j], aux[i])) a[k] = aux[j++];
    		else                           a[k] = aux[i++];
    	}

    	assert isSorted(a, lo, hi);   // postcondition: a[lo..hi] sorted

	    StdOut.println("AFTER MERGE CALL");
        for (i=0; i<a.length; i++)
	         StdOut.printf("%d ", a[i]);
	    StdOut.println(" ");
    }

    private static void sort(Comparable[] a, Comparable[] aux, int lo, int hi)
    {
		if (hi <= lo) return;
		int mid = lo + (hi - lo)/2;
		sort (a, aux, lo, mid);
		sort (a, aux, mid+1, hi);
		merge(a, aux, lo, mid, hi);
	}

    public static void sort(Comparable[] a)
    {
		Comparable[] aux = new Comparable[a.length];
		sort(a, aux, 0, a.length - 1);
	}


}