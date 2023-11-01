import java.util.List;
import java.util.Arrays;

public class IS
{
    public static void main(String[] args)
    {
        Integer[] a = {3, 10, 4, 2, 8};
        Integer[] b = {10, 4, 12, 3, 23, 1, 8};
        List<Integer> aList =  Arrays.asList(a);
        List<Integer> bList =  Arrays.asList(b);
        aList.retainAll(bList);
        System.out.println(" a intersection b "+aList);
        for (int x : aList.listIterator())
            StdOut.println("presek "+x);
    }
}